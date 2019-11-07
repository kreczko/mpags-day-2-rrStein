#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <iostream>
#include <vector>

bool processCommandLine(const std::vector<std::string> &args,
                        bool &helpRequested, bool &versionRequested,
                        std::string &inputFileName, std::string &outputFileName,
                        std::string &method, int &caesarKey);

#endif // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP