#include <iostream>
#include <cctype>
#include <map>

std::string transformChar(const char in_char)
{

    std::string inputText{""};

    // Uppercase alphabetic characters
    if (std::isalpha(in_char))
    {
        inputText = std::toupper(in_char);
    }

    //   std::vector<std::string> digits{"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};

    std::map<char, std::string> my_map = {
        {'0', "ZERO"}};

    my_map['1'] = "ONE";
    my_map['2'] = "TWO";
    my_map['3'] = "THREE";
    my_map['4'] = "FOUR";
    my_map['5'] = "FIVE";
    my_map['6'] = "SIX";
    my_map['7'] = "SEVEN";
    my_map['8'] = "EIGHT";
    my_map['9'] = "NINE";

    //   std::map <char, std::string>::iterator it;
    //   it = my_map.find(in_char);
    inputText += my_map[in_char];

    return inputText;
}