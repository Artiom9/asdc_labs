#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    Node<T>* top;
public:
    Stack() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    T* getLastElement() {
        if (isEmpty())
            return nullptr;
        else
            return &top->data;
    }

    void pop() {
        if (!isEmpty()) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    while (!stack.isEmpty()) {
        std::cout << *stack.getLastElement() << " ";
        stack.pop();
    }

    return 0;
}
