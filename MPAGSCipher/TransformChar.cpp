#include <cctype>
#include <iostream>
#include <map>

std::string transformChar(const char in_char) {

  std::string inputText{""};

  // Convert to uppercase alphabetic characters
  if (std::isalpha(in_char)) {
    inputText = std::toupper(in_char);
  }

  // std::vector<std::string>
  // digits{"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};

  // Map input numbers to their corresponding words
  const std::map<char, std::string> my_map = {
    {'0', "ZERO"},
    {'1', "ONE"},
    {'2', "TWO"},
    {'3', "THREE"},
    {'4', "FOUR"},
    {'5', "FIVE"},
    {'6', "SIX"},
    {'7', "SEVEN"},
    {'8', "EIGHT"},
    {'9', "NINE"},
  };

  inputText += my_map.at(in_char);

  // If the character isn't alphabetic or numeric or space, DONT add it.
  // Our ciphers can only operate on alphabetic characters.

  return inputText;
}