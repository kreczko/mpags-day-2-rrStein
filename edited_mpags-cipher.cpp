// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <map>

// For std::isalpha and std::isupper
#include <cctype>

// std::string base_pair(char base)
// {
//   switch (base)
//   {
//   case 'T':
//     return 'A';
//     ... etc default: // handle error
//   }
// }

std::string transformChar(const char in_char){

  std::string inputText{""};

  // Uppercase alphabetic characters
  if (std::isalpha(in_char))
  {
    inputText = std::toupper(in_char);
    // continue;
  }

  std::vector<std::string> digits{"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};

  std::map <char, std::string> my_map = {
      {'0', "ZERO"}
  };

  my_map['1'] = "ONE";
  my_map['2'] = "TWO";
  my_map['3'] = "THREE";
  my_map['4'] = "FOUR";
  my_map['5'] = "FIVE";
  my_map['6'] = "SIX";
  my_map['7'] = "SEVEN";
  my_map['8'] = "EIGHT";
  my_map['9'] = "NINE";

  std::map <char, std::string>::iterator it;
  it = my_map.find(in_char);
  inputText += my_map[in_char];

//   // Transliterate digits to English words
//   switch (in_char)
//   {
//   case '0':
//     inputText += "ZERO";
//     break;
//   case '1':
//     inputText += "ONE";
//     break;
//   case '2':
//     inputText += "TWO";
//     break;
//   case '3':
//     inputText += "THREE";
//     break;
//   case '4':
//     inputText += "FOUR";
//     break;
//   case '5':
//     inputText += "FIVE";
//     break;
//   case '6':
//     inputText += "SIX";
//     break;
//   case '7':
//     inputText += "SEVEN";
//     break;
//   case '8':
//     inputText += "EIGHT";
//     break;
//   case '9':
//     inputText += "NINE";
//     break;
//   }

  return inputText;
}

bool processCommandLine(
  const std::vector<std::string>& args,
  bool& helpRequested,
  bool& versionRequested,
  std::string& inputFileName,
  std::string& outputFileName){

  typedef std::vector<std::string>::size_type size_type;
  const size_type nArgs{args.size()};

  for (size_type i{1}; i < nArgs; ++i)
  {

  if (args[i] == "-h" || args[i] == "--help")
  {
    helpRequested = true;
  }
  else if (args[i] == "--version")
  {
    versionRequested = true;
  }
  else if (args[i] == "-i")
  {
    // Handle input file option
    // Next element is filename unless -i is the last argument
    if (i == nArgs - 1)
    {
      std::cerr << "[error] -i requires a filename argument" << std::endl;
      // exit main with non-zero return to indicate failure
      //return 1;
    }
    else
    {
      // Got filename, so assign value and advance past it
      inputFileName = args[i + 1];
      ++i;
    }
  }
  else if (args[i] == "-o")
  {
    // Handle output file option
    // Next element is filename unless -o is the last argument
    if (i == nArgs - 1)
    {
      std::cerr << "[error] -o requires a filename argument" << std::endl;
      outputFileName = "";
      // exit main with non-zero return to indicate failure
      //return 1;
    }
    else
    {
      // Got filename, so assign value and advance past it
      outputFileName = args[i + 1];
      ++i;
    }
  }
  else
  {
    // Have an unknown flag to output error message and return non-zero
    // exit status to indicate failure
    std::cerr << "[error] unknown argument '" << args[i] << "'\n";
    return 1;
  }
}
// std::make_tuple<bool, bool> rtup = {helpRequested, versionRequested};

return 0;
  }

    // Main function of the mpags-cipher program
int main(int argc, char *argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Add a typedef that assigns another name for the given type for clarity
//   typedef std::vector<std::string>::size_type size_type;
//   const size_type nCmdLineArgs {cmdLineArgs.size()};

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

  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  if (!inputFile.empty()) {
    std::cout << "[warning] input from file ('"
              << inputFile
              << "') not implemented yet, using stdin\n";
  }

  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  while(std::cin >> inputChar)
  {
    inputText += transformChar(inputChar);
    std::cout << "Enter more letters or press Ctrl + D to exit" <<std::endl;
    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
  }

  // Output the transliterated text
  // Warn that output file option not yet implemented
  if (!outputFile.empty()) {
    std::cout << "[warning] output to file ('"
              << outputFile
              << "') not implemented yet, using stdout\n";
  }

  std::cout << inputText << std::endl;

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}
