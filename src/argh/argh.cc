// src/argh/argh.cc
// v0.3.2
//
// Author: Cayden Lund
//   Date: 09/28/2021
//
// This file contains the argh implementation.
// Use this utility to parse command line arguments.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (opensource.org/licenses/MIT)

#include "argh.h"
#include "positional_arg.h"

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
    // Access flags using the operator[] with a string.
    //
    //    if (args["-h"] || args["--help"])
    //    {
    //        std::cout << "Help message." << std::endl;
    //        return 0;
    //    }
    //
    // Access parameters using the operator() with a string.
    //
    //    std::string output_file = args("--output");
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
            parse_argument(argv[i]);
        }
    }
    // The argh constructor, as above, but with an array of strings.
    //
    //   * int argc           - The count of command line arguments.
    //   * std::string argv[] - The command line arguments.
    argh::argh(int argc, std::string argv[])
    {
        initialize();

        for (int i = 0; i < argc; i++)
        {
            parse_argument(argv[i]);
        }
    }

    // A zero-argument method for initializing the instance variables.
    void argh::initialize()
    {
        this->args = std::vector<std::string>();
        this->flags = std::unordered_set<std::string>();
        this->parameters = std::unordered_map<std::string, std::string>();
        this->positional_arguments = std::vector<positional_arg>();

        this->double_dash_set = false;
        this->last_flag = "";
    }

    // A private method for parsing a single argument.
    //
    //   * std::string arg - The argument to parse.
    void argh::parse_argument(std::string arg)
    {
        // Make sure the argument is not empty.
        if (arg.length() == 0)
            return;

        // If we've seen a double dash, we're parsing positional arguments.
        if (double_dash_set)
        {
            this->args.push_back(arg);
            positional_arg arg_obj(arg);
            this->positional_arguments.push_back(arg_obj);
            return;
        }

        // Is the argument a single dash?
        if (arg == "-")
        {
            // A single dash is a positional argument.
            parse_positional_argument(arg);
            this->last_flag = "";
            return;
        }

        // Is the argument a double dash?
        if (arg == "--")
        {
            // A double dash means that all following arguments are positional arguments.
            this->args.push_back(arg);
            this->double_dash_set = true;
            this->last_flag = "";
            return;
        }

        // Is the argument a flag?
        if (is_flag(arg))
        {
            parse_flag(arg);
            return;
        }

        // If we've made it this far, the argument is either the value of a parameter
        // or a positional argument.
        parse_positional_argument(arg);
    }

    // A helper method for parsing a single flag.
    //
    //  * std::string arg - The argument to parse.
    void argh::parse_flag(std::string arg)
    {
        // Does the argument contain '='?
        if (arg.find('=') != std::string::npos)
        {
            // If so, it's a parameter.
            std::string key = arg.substr(0, arg.find('='));
            std::string value = arg.substr(arg.find('=') + 1);

            this->parameters[key] = value;
            this->flags.insert(key);
            this->args.push_back(arg);
            this->last_flag = "";
            return;
        }
        // Does the flag start with a double dash?
        if (arg.length() >= 2 && arg.substr(0, 2) == "--")
        {
            this->flags.insert(arg);
            this->args.push_back(arg);
            this->last_flag = arg;
            return;
        }
        else
        {
            // Treat each character following the single dash as a flag.
            for (long unsigned int i = 1; i < arg.length(); i++)
            {
                std::string flag = "-" + arg.substr(i, 1);
                this->flags.insert(flag);
                this->last_flag = flag;
            }
            this->args.push_back(arg);
            return;
        }
    }

    // A helper method for parsing a single positional argument.
    //
    //  * std::string arg - The argument to parse.
    void argh::parse_positional_argument(std::string arg)
    {
        if (this->last_flag.length() > 0)
        {
            this->parameters[this->last_flag] = arg;
            positional_arg arg_obj(this->last_flag, arg);
            this->positional_arguments.push_back(arg_obj);
        }
        else
        {
            positional_arg arg_obj(arg);
            this->positional_arguments.push_back(arg_obj);
        }

        this->last_flag = "";
        this->args.push_back(arg);
    }

    // A method to determine whether an argument is a flag.
    //
    //   * std::string arg - The argument to check.
    //
    //   * return (bool) - True if the argument is a flag, false otherwise.
    bool argh::is_flag(std::string arg)
    {
        if (arg.length() < 2)
            return false;
        if (arg == "--")
            return false;
        return arg[0] == '-';
    }

    // A method to mark an argument as a parameter, not a positional argument.
    // Note: This method runs in O(N) time, where N is the number of arguments,
    // provided that there is only one of the given parameter.
    //
    //   * std::string arg - The argument to mark as a parameter.
    void argh::mark_parameter(std::string arg)
    {
        for (long unsigned int i = 0; i < this->positional_arguments.size(); i++)
        {
            if (this->positional_arguments[i].get_owner() == arg)
            {
                this->positional_arguments.erase(this->positional_arguments.begin() + i);
                mark_parameter(arg);
                return;
            }
        }
    }

    // Overload the [] operator to access a flag by name.
    //
    //   * std::string name - The name of the flag.
    //
    //   * return (bool) - The value of the flag.
    bool argh::operator[](std::string name)
    {
        return this->flags.count(name);
    }

    // Overload the () operator to access a parameter by name.
    //
    //   * std::string name - The name of the parameter.
    //
    //   * return (std::string) - The value of the parameter.
    std::string argh::operator()(std::string name)
    {
        mark_parameter(name);
        if (this->parameters.count(name))
            return this->parameters[name];
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
        if ((long unsigned int)index < this->positional_arguments.size())
            return this->positional_arguments[index].get_value();
        return "";
    }

    // Returns the number of positional arguments.
    //
    //   * return (int) - The number of positional arguments.
    int argh::size()
    {
        return this->positional_arguments.size();
    }
}
