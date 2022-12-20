#include <iostream>
#include <vector>
#include <string>

#include "stack.h"

bool Stack::isEmpty() const
{
    return (this->elements.size() == 0);
}

int Stack::top() const
{
    return this->elements[this->elements.size() - 1];
}

void Stack::push(int elm)
{
    this->elements.push_back(elm);
}

std::string Stack::toString() const
{
    std::string str;
}





int main(void)
{
    std::cout << "Hello World!";

    return 0;
}