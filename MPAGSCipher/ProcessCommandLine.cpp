#include <iostream>
#include <vector>
#include <cctype>

bool processCommandLine(
    const std::vector<std::string> &args,
    bool &helpRequested,
    bool &versionRequested,
    std::string &inputFileName,
    std::string &outputFileName)
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