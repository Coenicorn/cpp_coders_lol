#include <iostream>
#include <vector>
#include <math.h>

/* Separate string s at whitespace characters */
std::vector<std::string> seperateAtSpace(std::string s)
{
    std::vector<std::string> inputSeparated;

    int i = 0;
    while (i < s.size())
    {
        // increment i until a non-whitespace character is encountered
        while (std::isspace(s[i]))
            i++;
     
        // set the start of the substring
        int start = i;

        // continue incrementing i until there's a whitespace encountered
        while (!std::isspace(s[i]))
            i++;
        
        // get substring and push to output
        inputSeparated.push_back(s.substr(start, i - start));
    }

    return inputSeparated;
}

/* Get user input separated by spaces */
std::vector<std::string> getUserInput(void)
{
    std::string input;
    getline(std::cin, input);

    return seperateAtSpace(input);
}

/* Converts input vector to a vector of doubles and checks for type errors */
std::vector<double> convertInput(std::vector<std::string> &input)
{
    // check if length is 3
    if (input.size() != 3) throw std::runtime_error("An error occurred: Malformed user input");
    
    std::vector<double> returnValues;

    // check for type double
    for (int i = 0; i < 3; i++)
    {
        // https://stackoverflow.com/questions/29169153/how-do-i-verify-a-string-is-valid-double-even-if-it-has-a-point-in-it

        char *end = nullptr;

        // c++ magic >_>
        double n = strtod(input[i].c_str(), &end);

        if (!(end != input[i].c_str() && *end == '\0' && n != HUGE_VAL))
        {
            throw std::runtime_error("An error occurred: Malformed user input");
        }

        returnValues.push_back(n);
    }

    return returnValues;
}

/* Solves the quadratic formula with a, b and c */
void solveQuadratic(double a, double b, double c)
{
    if (a == 0)
    {
        throw std::runtime_error("An error occurred: a must not be zero");
    }

    // calculate the discriminant
    double d = (b*b)-4*a*c;

    // calculate first solution for if d == 0
    float s1 = (-b+sqrt(d))/(2*a);

    if (d < 0)
    {
        std::cout << "There is no solution.\n";

        return;
    }
    if (d == 0)
    {
        // calculate one solution if d == 0
        std::cout << "There is 1 solution.\n";
        std::cout << "The solution is: " << s1 << "\n";

        return;
    }

    // calculate the other solution
    float s2 = (-b-sqrt(d))/(2*a);
    
    std::cout << "There are 2 solutions.\n";
    std::cout << "The solutions are: " << s1 << " and " << s2 << "\n";
}

int main(void)
{
    std::cout << "Please enter the values of a, b, and c: ";

    std::vector<std::string> input = getUserInput();
    std::vector<double> parsedInput;

    try
    {
        parsedInput = convertInput(input);
    } 
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << '\n';

        return 1;
    }

    // to satisfy the auto grading program
    std::cout << "\n";

    try
    {
        solveQuadratic(parsedInput[0], parsedInput[1], parsedInput[2]);
    } 
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << "\n";

        return 1;
    }

    return 0;
}