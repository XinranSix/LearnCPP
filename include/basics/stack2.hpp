#include <deque>
#include <string>
#include <stdexcept>
#include "stack1.hpp"

template<>
class Stack<std::string> {
private:
    std::deque<std::string> elems; // 包含元素的容器
public:
    void push(std::string const &); // 压入元素
    void pop();                     // 弹出元素
    std::string top() const;        // 返回栈顶元素
    bool empty() const {            // 返回栈是否为空
        return elems.empty();
    }
};

void Stack<std::string>::push(std::string const &elem) {
    elems.push_back(elem); // 把传入的实参elem附加到末端
}

void Stack<std::string>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<std::string>::pop(): empty stack");
    }
    elems.pop_back(); // 删除末端元素
}

std::string Stack<std::string>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<std::string>::top(): empty stack");
    }
    return elems.back(); // 返回末端元素的拷贝
}
