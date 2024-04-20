#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class Queue {
private:
    Node<T>* frontPtr;
    Node<T>* rearPtr;
public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr) {}

    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
    }

    T* front() {
        if (isEmpty())
            return nullptr;
        else
            return &frontPtr->data;
    }

    void dequeue() {
        if (!isEmpty()) {
            Node<T>* temp = frontPtr;
            if (frontPtr == rearPtr) {
                frontPtr = rearPtr = nullptr;
            } else {
                frontPtr = frontPtr->next;
            }
            delete temp;
        }
    }
};

int main() {
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    while (!queue.isEmpty()) {
        std::cout << *queue.front() << " ";
        queue.dequeue();
    }

    return 0;
}
