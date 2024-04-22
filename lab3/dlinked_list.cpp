#include <iostream>
#include <cassert>

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
struct LinkedList {
    Node<T>* head;
    Node<T>* tail;
    std::size_t size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    Node<T>* insertAfter(Node<T>* node, T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!node) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = newNode;
        } else {
            newNode->next = node->next;
            newNode->prev = node;
            if (node->next) node->next->prev = newNode;
            node->next = newNode;
            if (node == tail) tail = newNode;
        }
        ++size;
        return newNode;
    }

    Node<T>* insertBefore(Node<T>* node, T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!node) {
            newNode->prev = tail;
            if (tail) tail->next = newNode;
            tail = newNode;
            if (!head) head = newNode;
        } else {
            newNode->prev = node->prev;
            newNode->next = node;
            if (node->prev) node->prev->next = newNode;
            node->prev = newNode;
            if (node == head) head = newNode;
        }
        ++size;
        return newNode;
    }

    Node<T>* find(int value) {
        Node<T>* current = head;
        while (current && current->data != value) {
            current = current->next;
        }
        return current;
    }

    void remove(Node<T>* node) {
        if (!node) return;
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;
        if (node == tail) tail = node->prev;
        delete node;
        --size;
    }

    void assertNoCycles() {
        int count = 0;
        Node<T>* current = head;
        while (current) {
            count++;
            if (count > size) {
                std::cerr << "Cycle detected!" << std::endl;
                assert(false);
            }
            current = current->next;
        }
    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList<int> list;
    list.insertAfter(nullptr, 5);
    list.insertBefore(nullptr, 10);
    list.insertAfter(list.find(5), 15);

    // Testing find
    Node<int>* found = list.find(10);
    assert(found && found->data == 10);

    // Testing remove
    list.remove(found);
    assert(list.size == 2);

    // Testing assertNoCycles
    list.assertNoCycles();

    return 0;
}
