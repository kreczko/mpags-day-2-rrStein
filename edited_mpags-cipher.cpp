// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

// For std::isalpha and std::isupper
#include <cctype>
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"

// Main function of the mpags-cipher program
int main(int argc, char *argv[])
{
    // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

    // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  // for (size_type i {1}; i < nCmdLineArgs; ++i) {

  processCommandLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile);

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
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
  char inputChar {'x'};
  std::string inputText {""};

  bool ok_to_read = false;
  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  if (!inputFile.empty()) {
    // std::cout << "[warning] input from file ('"
    //           << inputFile
    //           << "') not implemented yet, using stdin\n";

    // std::string name = inputFile;

    std::ifstream in_file {inputFile};

    ok_to_read = in_file.good();
  }

  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  if (ok_to_read)
  {
      std::string name = inputFile;

      std::ifstream in_file{name};

    //   in_file >> inputChar;
      while (in_file >> inputChar){
          std::cout << inputChar << std::endl;
          inputText += transformChar(inputChar);
      }
  }
    else {

  std::cout << "Enter some characters to transform and press ENTER:" << std::endl;

  while(std::cin >> inputChar)
  {
    inputText += transformChar(inputChar);
    std::cout << "Enter more letters or press Ctrl + D to exit" <<std::endl;
    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
  }
  }
  // Output the transliterated text
  // Warn that output file option not yet implemented
  if (!outputFile.empty()) {
    std::cout << "Writing transformed text into file: "
              << outputFile
              ;
    std::string name{outputFile};
    std::ofstream out_file{name};
    bool ok_to_write = out_file.good();

    if(ok_to_write){
        out_file << inputText;
        std::cout << "Write successful" << std::endl;
    } else {
    std::cout << "WARNING: text output unsuccesful, out file not ok to write."
    }
  }

  std::cout << inputText << std::endl;

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}
