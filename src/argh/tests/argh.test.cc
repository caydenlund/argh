// src/argh/tests/argh.test.cc
// v0.1.0
//
// Author: Cayden Lund
//   Date: 09/24/2021
//
// This file contains the unit tests for the argh library.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (opensource.org/licenses/MIT)

#include <gtest/gtest.h>

#include "argh/argh.h"

// Test the argh::argh class constructor.
// This test ensures that the argh::argh class can be instantiated
// without throwing an exception.
TEST(argh_argh_test, argh_argh_constructor_test)
{
    std::string argv_a[] = {"test"};
    argh::argh args_a(argv_a);

    std::string argv_b[] = {"test", "-h"};
    argh::argh args_b(argv_b);

    std::string argv_c[] = {"test", "--help"};
    argh::argh args_c(argv_c);

    std::string argv_d[] = {"test", "-hv"};
    argh::argh args_d(argv_d);

    std::string argv_e[] = {"test", "--help", "-v"};
    argh::argh args_e(argv_e);

    std::string argv_f[] = {"test", "-hv", "-o", "output.txt"};
    argh::argh args_f(argv_f);

    std::string argv_g[] = {"test", "-vo", "output.txt"};
    argh::argh args_g(argv_g);
}

// Test the argh::argh class operator[] for flags.
// This test ensures that the argh::argh class can correctly
// report whether or not a single flag is present in argv.
TEST(argh_argh_test, argh_argh_operator_flag_test)
{
    std::string argv_a[] = {"test"};
    argh::argh args_a(argv_a);
    ASSERT_FALSE(args_a["-h"]);
    ASSERT_FALSE(args_a["--help"]);
    ASSERT_FALSE(args_a["-v"]);
    ASSERT_FALSE(args_a["--verbose"]);
    ASSERT_FALSE(args_a["-o"]);

    std::string argv_b[] = {"test", "-h"};
    argh::argh args_b(argv_b);
    ASSERT_TRUE(args_b["-h"]);
    ASSERT_FALSE(args_b["--help"]);
    ASSERT_FALSE(args_b["-v"]);
    ASSERT_FALSE(args_b["--verbose"]);
    ASSERT_FALSE(args_b["-o"]);

    std::string argv_c[] = {"test", "--help"};
    argh::argh args_c(argv_c);
    ASSERT_FALSE(args_c["-h"]);
    ASSERT_TRUE(args_c["--help"]);
    ASSERT_FALSE(args_c["-v"]);
    ASSERT_FALSE(args_c["--verbose"]);
    ASSERT_FALSE(args_c["-o"]);

    std::string argv_d[] = {"test", "-hv"};
    argh::argh args_d(argv_d);
    ASSERT_TRUE(args_d["-h"]);
    ASSERT_FALSE(args_d["--help"]);
    ASSERT_TRUE(args_d["-v"]);
    ASSERT_FALSE(args_d["--verbose"]);
    ASSERT_FALSE(args_d["-o"]);

    std::string argv_e[] = {"test", "--help", "-v"};
    argh::argh args_e(argv_e);
    ASSERT_FALSE(args_e["-h"]);
    ASSERT_TRUE(args_e["--help"]);
    ASSERT_TRUE(args_e["-v"]);
    ASSERT_FALSE(args_e["--verbose"]);
    ASSERT_FALSE(args_e["-o"]);

    std::string argv_f[] = {"test", "-hv", "-o", "output.txt"};
    argh::argh args_f(argv_f);
    ASSERT_TRUE(args_f["-h"]);
    ASSERT_FALSE(args_f["--help"]);
    ASSERT_TRUE(args_f["-v"]);
    ASSERT_FALSE(args_f["--verbose"]);
    ASSERT_TRUE(args_f["-o"]);

    std::string argv_g[] = {"test", "-vo", "output.txt"};
    argh::argh args_g(argv_g);
    ASSERT_FALSE(args_g["-h"]);
    ASSERT_FALSE(args_g["--help"]);
    ASSERT_TRUE(args_g["-v"]);
    ASSERT_FALSE(args_g["--verbose"]);
    ASSERT_TRUE(args_g["-o"]);
}

// Test the argh::argh class operator[] for flags.
// This test ensures that the argh::argh class can correctly
// report whether or not any one in a list of flags is present in argv.
TEST(argh_argh_test, argh_argh_operator_flags_test)
{
    std::string args_list[] = {"-h", "--help"};

    std::string argv_a[] = {"test"};
    argh::argh args_a(argv_a);
    ASSERT_FALSE(args_a[args_list]);

    std::string argv_b[] = {"test", "-h"};
    argh::argh args_b(argv_b);
    ASSERT_TRUE(args_b[args_list]);

    std::string argv_c[] = {"test", "--help"};
    argh::argh args_c(argv_c);
    ASSERT_TRUE(args_c[args_list]);

    std::string argv_d[] = {"test", "-hv"};
    argh::argh args_d(argv_d);
    ASSERT_TRUE(args_d[args_list]);

    std::string argv_e[] = {"test", "--help", "-v"};
    argh::argh args_e(argv_e);
    ASSERT_TRUE(args_e[args_list]);

    std::string argv_f[] = {"test", "-hv", "-o", "output.txt"};
    argh::argh args_f(argv_f);
    ASSERT_TRUE(args_f[args_list]);

    std::string argv_g[] = {"test", "-vo", "output.txt"};
    argh::argh args_g(argv_g);
    ASSERT_FALSE(args_g[args_list]);
}

// Test the argh::argh class operator[] for parameters.
// This test ensures that the argh::argh class can correctly
// report the value of a given parameter in argv.
TEST(argh_argh_test, argh_argh_operator_param_test)
{
    std::string argv_a[] = {"test"};
    argh::argh args_a(argv_a);
    ASSERT_STREQ("", args_a("-o").c_str());

    std::string argv_b[] = {"test", "-o", "output.txt"};
    argh::argh args_b(argv_b);
    ASSERT_STREQ("output.txt", args_b("-o").c_str());

    std::string argv_c[] = {"test", "-o", "output.txt", "-v"};
    argh::argh args_c(argv_c);
    ASSERT_STREQ("output.txt", args_c("-o").c_str());

    std::string argv_d[] = {"test", "-vo", "output.txt"};
    argh::argh args_d(argv_d);
    ASSERT_STREQ("output.txt", args_d("-o").c_str());
}

// Test the argh::argh class operator[] for parameters.
// This test ensures that the argh::argh class can correctly
// report the value of one of the given parameters in argv.
TEST(argh_argh_test, argh_argh_operator_param_list_test)
{
    std::string args_list[] = {"-o", "--output"};

    std::string argv_a[] = {"test"};
    argh::argh args_a(argv_a);
    ASSERT_STREQ("", args_a(args_list).c_str());

    std::string argv_b[] = {"test", "-o", "output.txt"};
    argh::argh args_b(argv_b);
    ASSERT_STREQ("output.txt", args_b(args_list).c_str());

    std::string argv_c[] = {"test", "--output", "output.txt", "-v"};
    argh::argh args_c(argv_c);
    ASSERT_STREQ("output.txt", args_c(args_list).c_str());

    std::string argv_d[] = {"test", "-vo", "output.txt"};
    argh::argh args_d(argv_d);
    ASSERT_STREQ("output.txt", args_d(args_list).c_str());
}

// Test the argh::argh class's method mark_parameter.
// Later tests ensure that it functions correctly,
// but this test ensures that it doesn't throw an exception.
TEST(argh_argh_test, argh_argh_mark_param_test)
{
    std::string argv[] = {"test", "-o", "output.txt"};
    argh::argh args(argv);
    args.mark_parameter("-o");
    args.mark_parameter("--nonexistent-parameter");
}

// This test ensures that the argh::argh class can correctly
// query the positional arguments, before marking anything as a parameter.
TEST(argh_argh_test, argh_argh_positional_simple_test)
{
    std::string argv_a[] = {"test"};
    argh::argh args_a(argv_a);
    ASSERT_STREQ("test", args_a[0].c_str());
    ASSERT_STREQ("", args_a[1].c_str());

    std::string argv_b[] = {"test", "output.txt"};
    argh::argh args_b(argv_b);
    ASSERT_STREQ("test", args_b[0].c_str());
    ASSERT_STREQ("output.txt", args_b[1].c_str());
    ASSERT_STREQ("", args_b[2].c_str());

    std::string argv_c[] = {"test", "output.txt", "--verbose"};
    argh::argh args_c(argv_c);
    ASSERT_STREQ("test", args_c[0].c_str());
    ASSERT_STREQ("output.txt", args_c[1].c_str());
    ASSERT_STREQ("", args_c[2].c_str());

    std::string argv_d[] = {"test", "input.txt", "--verbose", "--output", "output.txt"};
    argh::argh args_d(argv_d);
    ASSERT_STREQ("test", args_d[0].c_str());
    ASSERT_STREQ("input.txt", args_d[1].c_str());
    ASSERT_STREQ("output.txt", args_d[2].c_str());
    ASSERT_STREQ("", args_d[3].c_str());

    std::string argv_e[] = {"test", "-vo", "output.txt", "input.txt"};
    argh::argh args_e(argv_e);
    ASSERT_STREQ("test", args_e[0].c_str());
    ASSERT_STREQ("output.txt", args_e[1].c_str());
    ASSERT_STREQ("input.txt", args_e[2].c_str());
}

// This test ensures that the argh::argh class can correctly
// query the positional arguments, after marking necessary parameters.
TEST(argh_argh_test, argh_argh_positional_complex_test)
{
    std::string argv_a[] = {"test", "-o", "output.txt", "input.txt"};
    argh::argh args_a(argv_a);
    // Positional arguments should be "test", "output.txt", "input.txt".
    ASSERT_STREQ("test", args_a[0].c_str());
    ASSERT_STREQ("output.txt", args_a[1].c_str());
    ASSERT_STREQ("input.txt", args_a[2].c_str());
    ASSERT_STREQ("", args_a[3].c_str());
    // Mark "-o" as a parameter.
    args_a.mark_parameter("-o");
    // Now, positional arguments should be "test", "input.txt".
    ASSERT_STREQ("input.txt", args_a[1].c_str());
    ASSERT_STREQ("", args_a[2].c_str());

    std::string argv_b[] = {"test", "-o", "output.txt", "input.txt", "--verbose"};
    argh::argh args_b(argv_b);
    // Positional arguments should be "test", "output.txt", "input.txt".
    ASSERT_STREQ("test", args_b[0].c_str());
    ASSERT_STREQ("output.txt", args_b[1].c_str());
    ASSERT_STREQ("input.txt", args_b[2].c_str());
    ASSERT_STREQ("", args_b[3].c_str());
    // Mark "-o" as a parameter.
    ASSERT_STREQ("output.txt", args_b("-o").c_str());
    // Now, positional arguments should be "test", "input.txt".
    ASSERT_STREQ("input.txt", args_b[1].c_str());
    ASSERT_STREQ("", args_b[2].c_str());

    std::string argv_c[] = {"test", "input.txt", "--output", "output.txt", "--verbose"};
    argh::argh args_c(argv_c);
    // Positional arguments should be "test", "input.txt", "output.txt".
    ASSERT_STREQ("test", args_c[0].c_str());
    ASSERT_STREQ("input.txt", args_c[1].c_str());
    ASSERT_STREQ("output.txt", args_c[2].c_str());
    ASSERT_STREQ("", args_c[3].c_str());
    // Mark "--output" as a parameter.
    ASSERT_STREQ("output.txt", args_c("--output").c_str());
    // Now, positional arguments should be "test", "input.txt".
    ASSERT_STREQ("input.txt", args_c[1].c_str());
    ASSERT_STREQ("", args_c[2].c_str());
}
