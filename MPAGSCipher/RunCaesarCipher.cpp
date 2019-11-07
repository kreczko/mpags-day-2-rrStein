#include <cctype>
#include <iostream>

// Encrypt or decrypt (method) the input (text) using the Caesar cipher with key
// (key)

std::string runCaesarCipher(const std::string &text, const int &key,
                            const std::string &method) {
  std::string result{""};
  int len{text.size()};
  int s{key};

  // "Reverse" the key if decryption is requested
  if (method == "decrypt") {
    s = 26 - key; // Based on 26 letter alphabet
  }
  // Loop through the whole text and apply transformation to each character
  for (int i = 0; i < len; i++) {
    // Encrypt Uppercase letters based on their ASCII codes (the +/- 65)
    if (isupper(text[i])) {
      result += char(int(text[i] + s - 65) % 26 + 65);

      // Extra code for encrypting lowercase letters based on their ASCII codes
      // } else {
      //     result += char(int(text[i] + s - 97) % 26 + 97);
    }
  }

  // Return the result of ciphering
  return result;
}