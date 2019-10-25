#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>

// Process command line arguments - ignore zeroth element, as we know this to
// be the program name and don't need to worry about it
// Make basic checks on the input arguments and throw notifications accordingly.

bool processCommandLine(
    const std::vector<std::string> &args,
    bool &helpRequested,
    bool &versionRequested,
    std::string &inputFileName,
    std::string &outputFileName,
    std::string &method,
    int &CaesarKey
    )
{

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
                std::cerr << "[error] -i requires a filename argument\n" << std::endl;
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
                std::cerr << "[error] -o requires a filename argument\n" << std::endl;
                outputFileName = "";
                // exit main with non-zero return to indicate failure
                return 1;
            }
            else
            {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-m") {
            if (i == nArgs -1){
                std::cerr << "[error] -m requires mode (encrypt or decrypt) argument \n" << std::endl;
                return 1;
            }
            else if (args[i + 1] != "encrypt" && args[i + 1] != "decrypt"){
                std::cout << "[WARNING] method specified incorrectly, defaulting to only character transformation\n" << std::endl;
            }

                else
                {
                    method = args[i + 1];
                    ++i;
                }
        }
        else if (args[i] == "-key")
        {
            std::stringstream value(args[i+1]);
            int x = 0;
            value >> x;
            if (i == nArgs - 1)
            {
                std::cerr << "[error] -key requires an integer (between 1 and 26) argument\n" << std::endl;
                return 1;
            }
            else if (x> 26 || x < 1) {
                std::cout << "[Warning] -key argument out of bounds, defaulting to key = 5\n" << std::endl;
                CaesarKey = 5;
                ++i;
            } else {
                CaesarKey = x;
                ++i;
            }
         } else
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