/**
 * @file arg.h
 * @author Cayden Lund (cayden.lund@utah.edu)
 * @brief The header-only library to parse command line arguments.
 * @version 3.0
 *
 * @copyright Copyright (c) 2022 Cayden Lund
 *
 */

#ifndef ARG_H
#define ARG_H

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Use this class to parse command line arguments.
 * @details
 *     This class is used to parse command line arguments.
 *
 *     We use the following style of arguments
 *     (adapted from GNU's style guide):
 *
 *       * Arguments are options if they begin with a hyphen delimiter (`-`).
 *
 *       * Multiple options may follow a hyphen delimiter in a single token if
 *         the options do not take arguments.
 *         Thus, `-abc` is equivalent to `-a -b -c`.
 *
 *       * Option names are single alphanumeric characters.
 *
 *       * Certain options require an argument.
 *         For example, the -o option of the ld command requires an argument:
 *         an output file name.
 *
 *       * An option and its argument may or may not appear as separate tokens.
 *         (In other words, the whitespace separating them is optional.)
 *         Thus, `-o foo` and `-ofoo` are equivalent.
 *
 *       * Options typically precede other non-option arguments.
 *
 *       * The argument `--` terminates all options; any following arguments are
 *         treated as non-option arguments, even if they begin with a hyphen.
 *
 *       * A token consisting of a single hyphen character is interpreted as an
 *         ordinary non-option argument.
 *         By convention, it is used to specify input from or output to
 *         the standard input and output streams.
 *
 *       * Options may be supplied in any order, or appear multiple times.
 *
 *       * Long options consist of `--` followed by a name made of alphanumeric
 *         characters and dashes.
 *         Option names are typically one to three words long, with hyphens to
 *         separate words. Users can abbreviate the option names as long as the
 *         abbreviations are unique.
 *
 *       * To specify an argument for a long option,
 *         write either `--name=value` or `--name value`.
 *
 *     This style of arguments deviates from GNU's style in the following ways:
 *
 *       * In GNU style, to specify an argument for a long option,
 *         write `--name=value`.
 *
 *         In argh, either `--name=value` or `--name value` is accepted.
 *
 *       * In GNU style, an option and its argument may or may not appear
 *         as separate tokens.
 *         (In other words, the whitespace separating them is optional.)
 *         Thus, `-o foo` and `-ofoo` are equivalent.
 *
 *         In argh, an option and its argument must appear as separate tokens.
 *         (In other words, the whitespace separating them is required.)
 *         Thus, `-ofoo` would be interpreted as `-o -f -o -o`,
 *         even if `-o` requires an argument.
 *
 *       * Some GNU programs require options to precede other arguments.
 *
 *         In argh, options may appear anywhere.
 *         In other words, `-o output.txt input.txt` and
 *         `input.txt -o output.txt` are equivalent.
 *
 *     Usage is quite simple.
 *
 *     1. Pass the argv array to the constructor:
 *
 *            argh args(argc, argv);
 *
 *     2. Access whether an option is present using the operator[]
 *        with a string.
 *        It returns an integer count of the number of occurrences of
 *        the option.
 *
 *            if (args["-h"] || args["--help"])
 *            {
 *                display_help_message();
 *                return 0;
 *            }
 *
 *            int verbosity_level = args["-v"];
 *
 *     3. Access an option's value using the operator() with a string.
 *
 *            std::string output_file = args("-o");
 *
 *     4. Access non-option arguments by index using the operator[]
 *        with an integer.
 *
 *            std::string program_name = args[0];
 *            std::string input_file_name = args[1];
 *
 *        Note: argh can't on its own determine whether an argument belongs to
 *            an option or not.
 *            (E.g., should `file.txt` belong to `-q` or not in
 *            `program -q file.txt`?)
 *            Thus, it initially assumes that all arguments do not belong to
 *            an option.
 *
 *            There are two ways to tell argh that an option takes an argument:
 *              1. Using the operator() (see item 3 above).
 *              2. Using the function accepts_argument() (see item 5 below).
 *
 *     5. Tell argh that an option takes an argument using accepts_argument()
 *        with a string.
 *
 *            args.accepts_argument("-o");
 *
 */
class argh {
   public:
    /**
     * @brief Construct a new argh object.
     *
     * @param argc The count of arguments.
     * @param argv The argument array.
     */
    argh(int argc, char *argv[]);

    /**
     * @brief Tells argh that the given option requires an argument.
     *
     * @param arg The option that requires an argument.
     */
    void accepts_argument(const std::string &arg);

    /**
     * @brief Reports the number of times the given option occurs.
     *
     * @param name The option to count.
     * @return int The number of times the option occurs.
     */
    int operator[](const std::string &name);

    /**
     * @brief Reports the (argument) value of the given option
     *     and tells argh that the option accepts an argument.
     *
     * @param name The option to get the value of.
     * @return std::string The value of the option.
     */
    std::string operator()(const std::string &name);

    /**
     * @brief Accesses the argument at the given index.
     *
     * @param index The index of the argument.
     * @return std::string The value of the argument.
     */
    std::string operator[](int index);

    /**
     * @brief Returns the number of arguments.
     *
     * @return int The number of arguments.
     */
    int size();

   private:
    // The original argv array.
    const int argc;
    const char **argv;

    /**
     * @brief A struct to hold the information about an option.
     *
     */
    struct option {
        // The name of the option. (E.g., "-o")
        std::string name;

        // The value of the option. (E.g., "output.txt")
        std::string value;

        // The number of times the option occurs.
        int count;
    };

    /**
     * @brief A struct to hold the information about an argument.
     *
     */
    struct argument {
        // The value of the argument.
        std::string value;

        // The last option that occurred before this argument.
        std::string last_option;
    };

    // The non-option arguments.
    std::vector<argument> arguments;

    // The dictionary of options.
    // The key is the option name.
    // The value is a tuple of the form (count, argument).
    std::unordered_map<std::string, std::tuple<int, std::string>> options;
};

#endif