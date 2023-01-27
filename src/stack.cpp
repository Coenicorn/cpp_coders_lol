#include <iostream>
#include <vector>
#include <string>
#include <sstream>



// WHY THE HECK DO THEY EXPECT ME TO NOT USE A HEADER FILE
// ROUND HEADED DUMB DUMBS

class Stack {
    public:
        Stack();

        bool isEmpty() const;
        // returns true if stack has no elements stored

        int top() const;
        // returns element from top of the stack
        // throws std::runtime_error("stack is empty")

        int pop();
        // returns element from top of the stack and removes it
        // throws std::runtime_error("stack is empty")

        void push(int);
        // puts a new element on top of the stack

        std::string toString() const;
        // returns the contents of the stack in the format
        // [top,next,...,bottom]
        // e.g.: push(1), push(2), toString() -> [2,1]

    private:
        std::vector<int> elements;
};





Stack::Stack() {}

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

int Stack::pop()
{
    if (!elements.size())
        throw std::runtime_error("stack is empty");

    int entry = elements[elements.size()-1];

    elements.pop_back();

    return entry;
}

std::string Stack::toString() const
{
    if (elements.size() == 0)
        return "[]";


    std::stringstream stream;

    stream << "[" << elements[0];

    for (int i = 1; i < elements.size(); i++)
        stream << "," << elements[i];

    stream << "]";

    return stream.str();
}


#define STACK_TESTS
#ifdef STACK_TESTS

int main(void)
{
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(5);

    std::cout << "Stack contents: " << stack.toString() << "\n";

    std::cout << "Top: " << stack.top() << "\n";
    std::cout << "Is empty: " << stack.isEmpty() << "\n";

    std::cout << "Popped: \n";
    while (1)
    {
        try
        {
            std::cout << stack.pop() << " ";
        }
        catch(const std::exception& e)
        {
            break;
        }
    }

    return 0;
}

#endif