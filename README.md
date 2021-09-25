# argh

The last argument parser that you'll ever need!

argh is a C++ library that provides a simple, powerful, and easy-to-use
API for parsing command line arguments.

## Features:

* **Lightning-quick.** No complicated input validation. No internal type conversions. No regular expressions. Enjoy the performance benefits of plain old C++!
* **Easy to use.** No manual parsing. No special cases or special handling of flags. argh works for you to take the busywork out of writing your command-line utility.
* **Versatile.** It *just works* in every situation.
* **Support for grouped flags.** `program do_a_thing -a -b -c` is the same as `prg do_a_thing -abc` (which is the same as `prg -abc do_a_thing`).
* **Support for options.** Know that the user specified an output file with `prg -o output.txt do_a_thing`.
* **Support for ordered arguments.**
* **Unit tests** with the popular gtest library.
* **Indepdendent.** The only dependency outside of the standard library is the gtest library, which is only used for unit tests and is automatically downloaded and compiled as necessary with Bazel.
* All that, and even **a bag of chips!**

*Note: actual chips not included.

# Example Usage:

    #include "argh/argh.h"

    #include <string>

    int main(int argc, char* argv[])
    {
        argh::argh args(argv);
        // And just like that, the arguments are parsed and available in args!

        if (args["-v"])
        {
            std::cout << "Version ..." << std::endl;
            return 0;
        }

        if (args[{"-h", "--help"}])
        {
            std::cout << Usage: ... << std::endl;
            return 0;
        }

        if (args[{"-o", "--output"}])
        {
            std::cout << "Output file: " << args({"-o", "--output"}) << std::endl;
        }

        std::cout << "Program name: " << args[0] << std::endl;
        std::cout << "First argument: " << args[1] << std::endl;
        // ...
    }

# Documentation:

## Core Concepts:

* **Argument:** A single entry in `argv`.

We follow the GNU conventions of arguments. There are two kinds of arguments: *options* and *positional arguments.*

* **Option:** An argument that starts with a `-` or `--`.

There are two kinds of options: *flags* and *parameters.*

* **Flag:** Boolean options that are either *present* or *not present.*

* **Parameter:** An option that takes a value.

* **Positional Argument:** An argument that does not start with a `-` or `--`, and that is not the value of a parameter.

## Nota Bene:

The parser cannot understand on its own whether an argument that does not start with a `-` or `--` is *the value of a parameter* or *a positional argument.*

That is, if the arguments were `prg -v output.txt`, should we interpret `output.txt` as the value of the `-v` option or as its own positional argument?


For this reason, all arguments that are not flags or parameters
are considered positional arguments by default.
If you want to change this behavior, use one of the following approaches:
1. Use the `argh::set_parameter(parameter)` function to mark the argument
following a given parameter as the parameter's value.
2. Use the `argh::operator(parameter)` operater to query the value of a parameter
before using the argh::operator[] to access the positional arguments.

That being said,

## Class members:

## `argh::argh(char* argv[])`

The argh constructor.

`char *argv[]` - The command line arguments.

## `void argh::mark_parameter(std::string arg)`

A method to mark an argument as a parameter, not a flag.

`std::string arg` - The argument to mark as a parameter.

## `bool argh::operator[](std::string name)`

Overload the [] operator to access a single flag's value by name.

`std::string name` - The name of the flag.

`return (bool)` - True when the flag is present, false otherwise.

## `bool argh::operator[](std::string names[])`

Overload the [] operator to access the flags by name.

`std::string names[]` - The list of names of the flag.

`return (bool)` - True when any of the flags is present.

## `std::string argh::operator()(std::string name)`

Overload the () operator to access the parameters by name.

`std::string name` - The name of the parameter.

`return (std::string)` - The value of the parameter, if present; otherwise, an empty string.

## `std::string argh::operator()(std::string names[])`

`std::string names[]` - The list of names of the parameter.

`return (std::string)` - The value of the first parameter present; if none are present, an empty string.

Overload the [] operator to access the positional arguments by index.

## `std::string argh::operator[](int index)`

`int index` - The index of the positional argument.

`return (std::string)` - The value of the positional argument.
