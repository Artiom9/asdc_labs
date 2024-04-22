#include <iostream>
#include <cassert>

template<typename T>
struct Node {
    T data;
    Node* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
struct LinkedList {
    Node<T>* head;
    Node<T>* tail;
    std::size_t size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    Node<T>* insertAfter(Node<T>* node, T value) {
        Node<T>* newNode = new Node<T>(value);
        //If there is no node (nullptr), then write it at the beginning of the list
        if (!node) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = newNode;
        } else {
            newNode->next = node->next;
            node->next = newNode;
            if (node == tail) tail = newNode;
        }
        size++;
        return newNode;
    }

    struct FindNodeResult {
        Node<T>* previous;
        Node<T>* current;
    };

    FindNodeResult find(int value) {
        FindNodeResult result;
        result.previous = nullptr;
        result.current = head;
        while (result.current && result.current->data != value) {
            result.previous = result.current;
            result.current = result.current->next;
        }
        return result;
    }

    void removeAfter(Node<T>* node) {
        if (!node) {
            if (head) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                if (!head) tail = nullptr;
                size--;
            }
        } else if (node->next) {
            Node<T>* temp = node->next;
            node->next = node->next->next;
            delete temp;
            if (!node->next) tail = node;
            size--;
        }
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
    list.insertAfter(nullptr, 10);
    list.insertAfter(nullptr, 15);

    // Testing find
    LinkedList<int>::FindNodeResult result = list.find(10);
    assert(result.current->data == 10);

    // Testing removeAfter
    list.removeAfter(nullptr);
    assert(list.head->data == 10);
    assert(list.size == 2);

    // Testing assertNoCycles
    list.assertNoCycles();

    return 0;
}
