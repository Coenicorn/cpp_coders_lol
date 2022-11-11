#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// store positions of vowels in the alphabet
std::vector<int> vowelpositions = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0};

/* takes string with lowercase letters marks the occurrences of each letter. Assumes input integrity */
void checkOccurrences(std::string input)
{
    // array of 26 integers, representing the 26 letters of the alphabet, to mark occurrences
    std::vector<int> occurrences = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // loop through and mark occurrences
    for (int i = 0, l = input.size(); i < l; i++)
    {
        // since input is lower case, we can calculate the index in the vector by subtracting 97 (lowercase a)
        occurrences[input[i] - 97]++;
    }

    // get most occurring vowel and consonant
    char con = 'b', vow = 'a';
    int conI = 0, vowI = 0;

    // set to 25, 'cuz occurrences.size() = 26 - 1 = 25
    for (int i = 25; i >= 0; i--)
    {
        // check if c is a vowel
        int isVowel = vowelpositions[i];

        if (isVowel && occurrences[i] >= vowI)
        {
            vowI = occurrences[i];
            vow = i + 97;
        } else if (occurrences[i] >= conI)
        {
            conI = occurrences[i];
            con = i + 97;
        }
    }

    // some c++ formatting magic -_-
    std::cout << "Most frequent vowel: " << vow << " (" << vowI << " times)\n";
    std::cout << "Most frequent consonant: " << con << " (" << conI << " times)\n";
    
    // some beautiful ternary action
    char f = conI > vowI ? con : vow;
    // if they both occur the same amount, print the one that comes first in the aphabet (the one with the lowest character code)
    if (conI == vowI) f = con > vow ? vow : con;

    std::cout << "Most frequent letter, overall: " << f << " (" << occurrences[(int)f-97] << " times)\n";
}

std::string extractStreamContents(std::istream &stream)
{
    std::string output;
    char c;

    while (stream.get(c))
    {
        output += c;
    }

    return output;
}

int main(int argc, char *argv[])
{
    std::string input;
    std::istream *stream;

    // program is run without file input
    if (argc == 1)
    {
        stream = &std::cin;
    }

    // program is run with file input
    if (argc > 2)
    {
        std::cout << "cannot handle parameter list\n";

        return 1;
    }

    // no need for checking errors here since the input string is already processed
    checkOccurrences(input);

    return 0;
}