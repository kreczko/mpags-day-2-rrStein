#ifndef MPAGSCIPHER_RUNCAESARCIPHER_HPP
#define MPAGSCIPHER_RUNCAESARCIPHER_HPP

#include <iostream>

//! Encrypt or decrypt text with the Caesar cipher
std::string runCaesarCipher(const std::string &text, const int &key,
                            const std::string &method);

#endif // MPAGSCIPHER_RUNCAESARCIPHER_HPP