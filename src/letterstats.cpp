#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::vector<int> vowelpositions = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0};

/* converts to lower case and removes non-letters */
std::string formatString(std::string &input)
{
    std::string output;

    for (int i = 0, l = input.size(); i < l; i++)
    {
        char c = input[i];

        // check for non-letter
        if (c < 65 || (c > 90 && c < 97) || c > 122) 
            continue;

        // check for upper case, convert if so
        if (c > 64 && c < 91)
            c += 32;

        output += c;
    }

    return output;
}

/* takes string with lowercase letters marks the occurrences of each letter. Assumes input integrity */
void checkOccurrences(std::string input)
{
    std::vector<int> occurrences = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // since input is lower case, we can calculate the index in the vector by subtracting 97 (lowercase a)
    for (int i = 0, l = input.size(); i < l; i++)
        occurrences[input[i] - 97]++;

    char con = 'b', vow = 'a';
    int conI = 0, vowI = 0;

    // loop through backwards to automatically get alphabetical order
    for (int i = 25; i >= 0; i--)
    {
        int isVowel = vowelpositions[i];

        if (isVowel && occurrences[i] >= vowI)
        {
            vowI = occurrences[i];
            vow = i + 97;
        }
        if (!isVowel && occurrences[i] >= conI)
        {
            conI = occurrences[i];
            con = i + 97;
        }
    }

    std::cout << "Most frequent vowel: " << vow << " (" << vowI << " times)\n";
    std::cout << "Most frequent consonant: " << con << " (" << conI << " times)\n";
    
    char f = conI > vowI ? con : vow;
    // if they both occur the same amount, print the one that comes first in the aphabet (the one with the lowest character code)
    if (conI == vowI) f = con > vow ? vow : con;

    std::cout << "Most frequent letter, overall: " << f << " (" << occurrences[(int)f-97] << " times)\n";
}

std::string extractFromFile(std::istream &stream)
{
    std::string out = "", l = "";

    while (std::getline(stream, l))
    {
        out += l;
    }

    return out;
}

int main(int argc, char *argv[])
{
    std::string input;

    // no command line arguments
    if (argc == 1)
    {
        input = extractFromFile(std::cin);
    }
    // command line argument; file name
    else if(argc == 2)
    {
        std::ifstream stream(argv[1]);

        if (!stream.is_open())
        {
            std::cout << "cannot open input file " << argv[1] << "\n";

            return 1;
        }

        input = extractFromFile(stream);

        stream.close();
    }
    else if(argc > 2)
    {
        std::cout << "cannot handle parameter list\n";

        return 1;
    }

    input = formatString(input);

    checkOccurrences(input);

    return 0;
}
// exactly 120 lines kekw
