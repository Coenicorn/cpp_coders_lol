#include <iostream>

int main(void)
{
    while (1)
    {
        float n1, n2, r;
        char op;
        
        std::cout << "Enter the expression: ";
        std::cin >> op;

        if (op == 'q')
            return 0;

        std::cin >> n1 >> n2;

        switch (op)
        {
            case '+':
                r = n1 + n2;
                break;
            case '*':
                r = n1 * n2;
                break;
            case '-':
                r = n1 - n2;
                break;
            case '/':
                r = n1 / n2;
                break;
        }

        // this is painful
        std::cout << "\n" << n1 << " " << op << " " << n2 << " = " << r << "\n";
    }

    std::cout << "\n";

    return 0;
}