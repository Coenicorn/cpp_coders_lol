#include <iostream>
#include <vector>
#include <algorithm>

// function declarations
std::vector<int> getUserInput(int nInput);
int getSmallestMissingNumber(std::vector<int> numbers);

int main(void)
{
    int nInput;
    std::cout << "How many numbers? ";
    std::cin >> nInput;

    std::cout << "Please enter the numbers ";
    std::vector<int> numbers = getUserInput(nInput);

    int smallestMissingNumber = getSmallestMissingNumber(numbers);

    std::cout << "The smallest missing number is " << smallestMissingNumber << "\n";

    return 0;
}

std::vector<int> getUserInput(int nInput)
{
    int n, i;
    std::vector<int> numbers;

    // doesn't check input integrity, super fragile :(
    for (i = 0; i < nInput; i++)
    {
        std::cin >> n;
        numbers.push_back(n);
    }

    return numbers;
}

int getSmallestMissingNumber(std::vector<int> numbers)
{
    // sort vector from lowest to highest
    std::sort(numbers.begin(), numbers.end());

    int l = numbers.size();

    // loop through elements of the array to check if the gap between the current and the next is greater than 1
    // if it is, return current + 1
    for (int i = 0; i < l - 1; i++)
    {
        // get gap between current and next
        int gap = numbers[i+1] - numbers[i];
        if (gap > 1)
        {
            return numbers[i]+1;
        }
    }

    return numbers[l-1] + 1;
}