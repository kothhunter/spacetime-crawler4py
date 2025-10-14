#include "list.hpp"
#include <iostream>

#include <cstring>
#include <cassert>

namespace list {

// Create a linked list from a C-string
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

// Delete all nodes in the list
void free(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Print linked list to ostream
void print(std::ostream& out, Node* head) {
    for (Node* current = head; current; current = current->next) {
        out << current->data;
    }
}

// Return a deep copy of the linked list
Node* copy(Node* head) {
    if (!head) return nullptr;

    Node* new_head = new Node{head->data, nullptr};
    Node* current_old = head->next;
    Node* current_new = new_head;

    while (current_old) {
        current_new->next = new Node{current_old->data, nullptr};
        current_new = current_new->next;
        current_old = current_old->next;
    }
    return new_head;
}

// Compare two lists lexicographically (strcmp)
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

// Compare up to `n` nodes in two lists (strncmp)
int compare(Node* lhs, Node* rhs, int n) {
    for (int i = 0; i < n; ++i) {
        if (!lhs || !rhs) return (lhs ? 1 : (rhs ? -1 : 0));
        if (lhs->data != rhs->data) return (lhs->data < rhs->data) ? -1 : 1;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return 0;
}

// Count number of nodes in  linked list
int length(Node* head) {
    int count = 0;
    while (head) {
        ++count;
        head = head->next;
    }
    return count;
}

// Reverse a linked list and return the new head
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

// Append two linked lists
Node* append(Node* lhs, Node* rhs) {
    if (!lhs) return copy(rhs);
    if (!rhs) return copy(lhs);

    Node* new_head = copy(lhs);
    Node* tail = last(new_head);
    tail->next = copy(rhs);
    return new_head;
}

// Get index of a node in the list
int index(Node* head, Node* node) {
    int idx = 0;
    while (head) {
        if (head == node) return idx;
        head = head->next;
        ++idx;
    }
    return -1;
}

// Find the first occurrence of a character in the list
Node* find_char(Node* head, char c) {
    while (head) {
        if (head->data == c) return head;
        head = head->next;
    }
    return nullptr;
}

// Find the first occurrence of a sublist in a list
Node* find_list(Node* haystack, Node* needle) {
    if (!needle) return haystack;

    for (Node* start = haystack; start; start = start->next) {
        if (compare(start, needle, length(needle)) == 0) {
            return start;
        }
    }
    return nullptr;
}

// Get the nth node of a list
Node* nth(Node* head, int n) {
    for (int i = 0; head && i < n; ++i) {
        head = head->next;
    }
    return head;
}

// Get the last node of a list
Node* last(Node* head) {
    if (!head) return nullptr;
    while (head->next) {
        head = head->next;
    }
    return head;
}

} 
