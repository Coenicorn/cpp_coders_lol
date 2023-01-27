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