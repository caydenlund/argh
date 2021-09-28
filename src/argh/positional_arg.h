// src/argh/positional_arg.h
// v0.1.0
//
// Author: Cayden Lund
//   Date: 09/28/2021
//
// This file contains the positional_arg headers.
// For use in the argh library.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (opensource.org/licenses/MIT)

#ifndef POSITIONAL_ARG_H
#define POSITIONAL_ARG_H

#include <string>

namespace argh
{
    // A class to represent a single positional argument and a value of a parameter.
    // Note that since we can't tell the difference between the two, this class represents both.
    // The "owner" property tracks the potential parameter that the argument might belong to.
    // If the user marks a parameter as such, argh iterates through the vector of positional
    // arguments and removes those belonging to that parameter.
    class positional_arg
    {
        public:
        // The one-argument constructor that simply sets the value.
        //
        //   * std::string value - The value of the argument.
        positional_arg(std::string value);
        // The two-argument constructor that sets the value and the owner.
        //
        //   * std::string owner - The owner of the argument.
        //   * std::string value - The value of the argument.
        positional_arg(std::string owner, std::string value);

        // Returns the owner of the argument.
        //
        //   * return (std::string) - The owner of the argument.
        std::string get_owner();

        // Returns the value of the argument.
        //
        //   * return (std::string) - The value of the argument.
        std::string get_value();

        private:
        // Internal instance variable to track the owner of the argument.
        std::string owner;

        // Internal instance variable to track the value of the argument.
        std::string value;
    };
}

#endif