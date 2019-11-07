// Standard Library includes
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"
#include "TransformChar.hpp"

// Main function of the mpags-cipher program
int main(int argc, char *argv[]) {
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs{argv, argv + argc};

  // Options that might be set by the command-line arguments
  bool helpRequested{false};
  bool versionRequested{false};
  std::string inputFile{""};
  std::string outputFile{""};
  std::string method{""};
  int caesarKey{5};

  // Process command line arguments with the corresponding function
  processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile,
                     outputFile, method, caesarKey);

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
              << "Encrypts/Decrypts input alphanumeric text using classical "
                 "ciphers\n\n"
              << "Available options:\n\n"
              << "  -h|--help        Print this help message and exit\n\n"
              << "  --version        Print version information\n\n"
              << "  -i FILE          Read text to be processed from FILE\n"
              << "                   Stdin will be used if not supplied\n\n"
              << "  -o FILE          Write processed text to FILE\n"
              << "                   Stdout will be used if not supplied\n\n"
              << "  -m Method        Specify method: encrypt or decrypt\n\n"
              << "  -key             Key (integer) used for the Caesar cipher, "
                 "default is 5\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar{'x'};
  std::string inputText{""};

  bool ok_to_read = false;

  // Read in user input from stdin/file
  if (!inputFile.empty()) {

    std::ifstream in_file{inputFile};

    ok_to_read = in_file.good();
  }

  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  if (ok_to_read) {
    std::string name = inputFile;

    std::ifstream in_file{name};

    //   in_file >> inputChar;
    while (in_file >> inputChar) {
      //   std::cout << inputChar << std::endl;
      inputText += transformChar(inputChar);
    }
  } else {

    // If no file is input, revert to taking user input from keyboard
    std::cout << "Enter some characters to transform and press ENTER: \n"
              << std::endl;

    while (std::cin >> inputChar) {
      inputText += transformChar(inputChar);
      std::cout << "Enter another letter or press Ctrl + D to exit"
                << std::endl;
    }
  }

  // Initialise variables for the cipher output
  std::string encryption{""};
  std::string decryption{""};

  // If no method is specified, notify user and proceed to output transliterated
  // text
  if (!method.empty()) {
    if (method == "encrypt") {
      encryption = runCaesarCipher(inputText, caesarKey, method);
      std::cout << "The input text is: \n"
                << inputText << "\nThe encrypted string is: \n"
                << encryption << "\n"
                << std::endl;

    } else if (method == "decrypt") {

      decryption = runCaesarCipher(inputText, caesarKey, method);
      std::cout << "The input text is: \n"
                << inputText << "\nThe decrypted string is: \n"
                << decryption << "\n"
                << std::endl;
    }
  } else {
    std::cout << "No encryption/decryption method passed\n" << std::endl;
  }

  // Output the encrypted, decrypted, or transliterated text depending on input
  // arguments
  if (!outputFile.empty()) {
    std::cout << "Writing transformed text into file: \n"
              << outputFile << std::endl;
    std::string name{outputFile};
    std::ofstream out_file{name};
    bool ok_to_write = out_file.good();

    if (ok_to_write) {
      if (method == "encrypt") {
        out_file << encryption;
      } else if (method == "decrypt") {
        out_file << decryption;
      } else {
        out_file << inputText;
      }
      std::cout << "Write successful" << std::endl;
    } else {
      std::cout << "WARNING: text output unsuccesful, out file not ok to write."
                << std::endl;
    }
  }

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}
