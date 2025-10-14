#include "list.hpp"
#include <iostream>

#include <cstring>
#include <cassert>

namespace list {

Node* from_string(const char* s) {
    if (!s || *s == '\0') return nullptr;

    Node* head = new Node{*s, nullptr};
    Node* current = head;

    for (size_t i = 1; s[i] != '\0'; ++i) {
        current->next = new Node{s[i], nullptr};
        current = current->next;
    }
    return head;
}

void free(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void print(std::ostream& out, Node* head) {
    for (Node* current = head; current; current = current->next) {
        out << current->data;
    }
}

Node* copy(Node* head) {
    if (!head) return nullptr;

    Node* new_head = new Node{head->data, nullptr};
    Node* curr_old = head->next;
    Node* curr_new = new_head;

    while (curr_old) {
        curr_new->next = new Node{curr_old->data, nullptr};
        curr_new = curr_new->next;
        curr_old = curr_old->next;
    }
    return new_head;
}

int compare(Node* lhs, Node* rhs) {
    while (lhs && rhs) {
        if (lhs->data != rhs->data) {
            return (lhs->data < rhs->data) ? -1 : 1;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }

    if (lhs) return 1;
    if (rhs) return -1; 

    return 0;
}

int compare(Node* lhs, Node* rhs, int n) {
    for (int i = 0; i < n; ++i) {
        if (!lhs || !rhs) return (lhs ? 1 : (rhs ? -1 : 0));
        if (lhs->data != rhs->data) return (lhs->data < rhs->data) ? -1 : 1;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return 0;
}

int length(Node* head) {
    int cnt = 0;
    while (head) {
        ++cnt;
        head = head->next;
    }
    return cnt;
}

Node* reverse(Node* head) {
    if (!head) return nullptr;

    Node* new_head = nullptr;
    Node* current = head;

    while (current) {
        Node* new_node = new Node{current->data, new_head};
        new_head = new_node;
        current = current->next;
    }
    
    return new_head;
}

Node* append(Node* lhs, Node* rhs) {
    if (!lhs) return copy(rhs);
    if (!rhs) return copy(lhs);

    Node* new_head = copy(lhs);
    Node* tail = last(new_head);
    tail->next = copy(rhs);
    return new_head;
}

int index(Node* head, Node* node) {
    int idx = 0;
    while (head) {
        if (head == node) return idx;
        head = head->next;
        ++idx;
    }
    return -1;
}

Node* find_char(Node* head, char c) {
    while (head) {
        if (head->data == c) 
            return head;
        head = head->next;
    }
    return nullptr;
}

Node* find_list(Node* haystack, Node* needle) {
    if (!needle) return haystack;

    for (Node* st = haystack; st; st = st->next) {
        if (compare(st, needle, length(needle)) == 0) {
            return st;
        }
    }
    return nullptr;
}

Node* nth(Node* head, int n) {
    for (int i = 0; head && i < n; ++i) {
        head = head->next;
    }
    return head;
}

Node* last(Node* head) {
    if (!head) return nullptr;
    while (head->next) {
        head = head->next;
    }
    return head;
}
} 