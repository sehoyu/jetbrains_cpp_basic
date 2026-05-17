#include "dllist.hpp"

#include <sys/fcntl.h>

Node* createNode(void* data) {
    Node* p = (Node*) malloc(sizeof(Node));
    p->data = data;
    p->prev = nullptr;
    p->next = nullptr;
    return p;
}

void freeNode(Node* node) {
    free(node->data);
    free(node);
    return;
}

void link(Node* cursor, Node* node) {
    node->next = cursor->next;
    node->prev = cursor;
    cursor->next->prev = node;
    cursor->next = node;
    return;
}

void unlink(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    return;
}

void initList(List& list) {
    list.sentry.data = nullptr;
    list.sentry.prev = &list.sentry;
    list.sentry.next = &list.sentry;
    return;
}

void insert(List& list, void* data) {
    Node* p = createNode(data);
    link(&list.sentry, p);
    return;
}

void remove(List& list, bool (*pred)(void*)) {
    Node* current = list.sentry.next;
    while (current != &list.sentry) {
        Node* nextNode = current->next;
        if (pred(current->data)) {
            unlink(current);
            freeNode(current);
        }
        current = nextNode;
    }
    return;
}