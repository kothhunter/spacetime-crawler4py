#include "string.hpp"
#include "list.hpp"
#include <utility>  
#include <iostream>

String::String(const char *s) {
    head = list::from_string(s);
}

String::String(const String &s) {
    head = list::copy(s.head);
}

String::String(String &&s) {
    head = s.head;
    s.head = nullptr;
}

String::String(list::Node* new_head) {
    head = new_head;
}

String::~String() {
    list::free(head);
}

void String::swap(String &s) {
    std::swap(head, s.head);
}

String &String::operator=(const String &s) {
    if (this != &s) {
        list::free(head);
        head = list::copy(s.head);
    }
    return *this;
}

String &String::operator=(String &&s) {
    if (this != &s) {
        list::free(head);
        head = s.head;
        s.head = nullptr;
    }
    return *this;
}

char String::operator[](int index) const {
    if (index < 0 || index >= size()) {
        std::cerr << "ERROR";
        std::cerr.flush();
        return '\0';
    }

    list::Node* node = list::nth(head, index);
    return node ? node->data : '\0';  
}

int String::size() const {
    return list::length(head);
}

String String::reverse() const {
    return String(list::reverse(head));
}

int String::indexOf(char c) const {
    list::Node* node = list::find_char(head, c);
    return node ? list::index(head, node) : -1;
}

int String::indexOf(const String &s) const {
    if (!s.head) return 0;

    list::Node* node = list::find_list(head, s.head);
    return node ? list::index(head, node) : -1;
}

bool String::operator==(const String &s) const {
    return list::compare(head, s.head) == 0;
}

std::strong_ordering String::operator<=>(const String &s) const {
    return list::compare(head, s.head) <=> 0;
}

String String::operator+(const String &s) const {
    //creates new linked list
    list::Node* new_head = list::append(head, s.head); 
    return String(new_head);
}

String &String::operator+=(const String &s) {
    if (!head) {
        head = list::copy(s.head);
    } 
    else {
        list::last(head)->next = list::copy(s.head);
    }
    return *this;
}

void String::print(std::ostream &out) const {
    list::print(out, head);
}

void String::read(std::istream &in) {
    list::free(head);
    head = list::from_string("");
    list::Node* temp = list::from_string("");

    char c;
    while (in.get(c) && !std::isspace(c)) {
        list::Node* newNode1 = new list::Node{c, nullptr};
        if (!head) {
            head = temp = newNode1;
        } else {
            temp->next = newNode1;
            temp = newNode1;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}