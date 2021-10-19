// src/argh/positional_arg.h
// v0.1.0
//
// Author: Cayden Lund
//   Date: 09/28/2021
//
// This file contains the implementation of the positional_arg class.
// For use in the argh library.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <opensource.org/licenses/MIT>

#include "positional_arg.h"

#include <string>

namespace argh
{
    // The positional_arg class represents a single positional argument and a value of a parameter.
    // Note that since we can't tell the difference between the two, this class represents both.
    // The "owner" property tracks the potential parameter that the argument might belong to.
    // If the user marks a parameter as such, argh iterates through the vector of positional
    // arguments and removes those belonging to that parameter.

    // The one-argument constructor for the positional_arg class that simply sets the value.
    //
    //   * std::string value - The value of the argument.
    positional_arg::positional_arg(std::string value)
    {
        this->value = value;
    }
    // The two-argument constructor that sets the value and the owner.
    //
    //   * std::string owner - The owner of the argument.
    //   * std::string value - The value of the argument.
    positional_arg::positional_arg(std::string owner, std::string value)
    {
        this->owner = owner;
        this->value = value;
    }

    // Returns the owner of the argument.
    //
    //   * return (std::string) - The owner of the argument.
    std::string positional_arg::get_owner()
    {
        return this->owner;
    }

    // Returns the value of the argument.
    //
    //   * return (std::string) - The value of the argument.
    std::string positional_arg::get_value()
    {
        return this->value;
    }
}