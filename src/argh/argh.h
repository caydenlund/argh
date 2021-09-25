// src/argh/argh.h
// v0.1.0
//
// Author: Cayden Lund
//   Date: 09/24/2021
//
// This file contains the argh headers.
// Use this utility to parse command line arguments.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (opensource.org/licenses/MIT)

#ifndef ARGH_H
#define ARGH_H

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
    //           The value is always the next argument in the argv vector.
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
    class argh
    {
    public:
        // The argh constructor.
        //
        //   * char *argv[] - The command line arguments.
        argh(char *argv[]);

        // The argh constructor, overloaded to accept an array of strings.
        //
        //   * std::string argv[] - The command line arguments.
        argh(std::string argv[]);

        // A method to mark an argument as a parameter, not a flag.
        //
        //   * std::string arg - The argument to mark as a parameter.
        void mark_parameter(std::string arg);

        // Overload the [] operator to access the flags by name.
        //
        //   * std::string name - The name of the flag.
        //   * std::initializer_list<std::string> names - The list of names of the flag.
        //
        //   * return (bool) - The value of the flag.
        bool operator[](std::string name);
        bool operator[](std::string names[]);

        // Overload the () operator to access the parameters by name.
        //
        //   * std::string name - The name of the parameter.
        //   * std::initializer_list<std::string> names - The list of names of the parameter.
        //
        //   * return (std::string) - The value of the parameter.
        std::string operator()(std::string name);
        std::string operator()(std::string names[]);

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
        std::string operator[](int index);

    private:
        // The set of flags.
        std::unordered_set<std::string> flags;

        // The set of parameters.
        std::unordered_set<std::string> parameters;

        // The positional arguments.
        std::vector<std::string> positional_arguments;
    };
}

#endif