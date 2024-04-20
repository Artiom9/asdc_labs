#include <vector>
#include <iostream>

template<typename T>
class Stack {
private:
    std::vector<T> data;
public:
    bool isEmpty() const {
        return data.empty();
    }

    void push(T value) {
        data.push_back(value);
    }

    T* getLastElement() {
        if (isEmpty())
            return nullptr;
        else
            return &data.back();
    }

    void pop() {
        if (!isEmpty())
            data.pop_back();
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
