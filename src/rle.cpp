#include <iostream>
#include <vector>

void compressAndPrint(std::string userInput)
{
    std::cout << '\n';

    // for every character in the user input, check the amount of occurrences and store thayut
    int i = 0, l = userInput.size();

    std::vector<int> occurrences;
    std::vector<char> characters;

    while (i < l)
    {
        // store current character
        char currentCharacter = userInput[i];
        characters.push_back(currentCharacter);

        // loop through until the character at i isn't the current character, increment i on the way
        int o = 0;

        // check input for invalid characters
        for (; userInput[i] == currentCharacter; i++, o++)
            if (userInput[i] < 97 || userInput[i] > 122)
            {
                throw std::invalid_argument("invalid input");
                return;
            }

        occurrences.push_back(o);
    }

    std::cout << "The compressed data is: ";

    for (int k = 0, l = occurrences.size(); k < l; k++)
    {
        std::cout << occurrences[k] << characters[k];
    }
}

int main(void)
{
    std::string data;

    std::cout << "Enter the data to be compressed: ";
    std::cin >> data;

    try
    {
        compressAndPrint(data);
    } catch (std::invalid_argument &e)
    {
        std::cout << "error: " << e.what();
    }

    std::cout << "\n";

    return 0;
}