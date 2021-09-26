// src/argh/argh.cc
// v0.2.0
//
// Author: Cayden Lund
//   Date: 09/26/2021
//
// This file contains the argh implementation.
// Use this utility to parse command line arguments.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (opensource.org/licenses/MIT)

#include "argh.h"

#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

// The argh namespace contains all of the argh functionality
// and utility functions.
namespace argh
{
    // The argh::argh class is the main class for the argh utility.
    // Use this class to parse command line arguments from the argv vector.
    //
    // We follow the GNU style of arguments, and define two types of arguments:
    //
    //   1. Options.
    //      These may be defined as a single dash followed by a single letter,
    //      or by a double dash followed by a single word.
    //      A list of single-letter options may be given at once, following a single dash without spaces.
    //      These are usually not required arguments.
    //      There are two kinds of options:
    //        a. Flags. These are boolean arguments that are either present or not present.
    //        b. Parameters. These are arguments that take a value.
    //           If a parameter contains the character '=', its value is the rest of the string.
    //           Otherwise, the value is the next argument in the argv vector.
    //   2. Positional arguments.
    //      These are arguments that are interpreted by the program.
    //      Positional arguments are often required.
    //
    // Usage is quite simple.
    //
    // Pass the argv vector to the constructor.
    //
    //    argh::argh args(argv);
    //
    // Access flags using the operator[] with a string or a list of strings.
    //
    //    if (args["h"] || args["help"])
    //    {
    //        std::cout << "Help message." << std::endl;
    //        return 0;
    //    }
    //
    //    if (args[{"v", "verbose"}])
    //    {
    //        std::cout << "Verbose mode." << std::endl;
    //        return 0;
    //    }
    //
    // Access parameters using the operator() with a string or a list of strings.
    //
    //    std::string output_file = args({"o", "output"});
    //
    // Access positional arguments using the operator[] with an integer.
    //
    //    std::string filename = args[0];
    //
    // The argh constructor.
    //
    //   * int argc     - The count of command line arguments.
    //   * char *argv[] - The command line arguments.
    argh::argh(int argc, char *argv[])
    {
        initialize();

        for (int i = 1; i < argc; i++)
        {
            args.push_back(argv[i]);
        }
    }
    // The argh constructor, as above, but with an array of strings.
    //
    //   * int argc           - The count of command line arguments.
    //   * std::string argv[] - The command line arguments.
    argh::argh(int argc, std::string argv[])
    {
        initialize();

        std::cout << "Args (" << argc << "):" << std::endl;
        for (int i = 0; i < argc; i++)
        {
            this->args.push_back(argv[i]);
            std::cout << i << ". " << argv[i] << std::endl;
        }
        // std::cout << std::endl;
    }

    // A zero-argument method for initializing the instance variables.
    void argh::initialize()
    {
        this->args = std::vector<std::string>();
        this->flags = std::unordered_set<std::string>();
        this->parameters = std::unordered_map<std::string, std::string>();
    }

    // A method to mark an argument as a parameter, not a flag.
    //
    //   * std::string arg - The argument to mark as a parameter.
    void argh::mark_parameter(std::string arg)
    {
    }

    // Overload the [] operator to access the flags by name.
    //
    //   * std::string name - The name of the flag.
    //   * std::initializer_list<std::string> names - The list of names of the flag.
    //
    //   * return (bool) - The value of the flag.
    bool argh::operator[](std::string name)
    {
        return false;
    }
    bool argh::operator[](std::string names[])
    {
        return false;
    }

    // Overload the () operator to access the parameters by name.
    //
    //   * std::string name - The name of the parameter.
    //   * std::initializer_list<std::string> names - The list of names of the parameter.
    //
    //   * return (std::string) - The value of the parameter.
    std::string argh::operator()(std::string name)
    {
        return "";
    }
    std::string argh::operator()(std::string names[])
    {
        return "";
    }

    // Overload the [] operator to access the positional arguments by index.
    //
    // ==============================================================================================================
    // |                                                                                                            |
    // |  It's important to note that the parser does not understand the difference                                 |
    // |  between a positional argument and the value of a parameter!                                               |
    // |                                                                                                            |
    // |  For instance:                                                                                             |
    // |    "program -o output.txt file.txt"                                                                        |
    // |       Should "output.txt" be interpreted as a positional argument, or as the value of the "-o" parameter?  |
    // |    "program -v file.txt"                                                                                   |
    // |       Should "file.txt" be interpreted as a positional argument, or as the value of the "-v" parameter?    |
    // |                                                                                                            |
    // |  For this reason, all arguments that are not flags or parameters                                           |
    // |  are considered positional arguments by default.                                                           |
    // |  If you want to change this behavior, you can use one of the following approaches:                         |
    // |    1. Use the argh::set_parameter(parameter) function to mark the argument                                 |
    // |       following a given parameter as the parameter's value.                                                |
    // |    2. Use the argh::operator(parameter) operater to query the value of a parameter                         |
    // |       before using the argh::operator[] to access the positional arguments.                                |
    // |                                                                                                            |
    // ==============================================================================================================
    //
    //   * int index - The index of the positional argument.
    //
    //   * return (std::string) - The value of the positional argument.
    std::string argh::operator[](int index)
    {
        return "";
    }
}
