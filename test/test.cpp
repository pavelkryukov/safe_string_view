/*
 * Copyright (c) 2022 Pavel I. Kryukov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "catch.hpp"
#include "../safe_string_view.h"

#include <iostream>

#include <malloc.h>

#define ASSERT(arg) CHECK(is_safe_string_view(arg))
#define ASSERT_FALSE(arg) CHECK_FALSE(is_safe_string_view(arg))

TEST_CASE("Literal")
{
    const char* literal = "Literal";

    ASSERT(std::string_view(literal));
    ASSERT_FALSE(std::string_view(literal, 5));
    ASSERT_FALSE(std::string_view(literal, 15));
}

TEST_CASE("std::string")
{
    const std::string string("String");
    const std::string_view view(string);

    ASSERT(std::string{});
    ASSERT(view);
    ASSERT_FALSE(view.substr(0, 5));
}

TEST_CASE("suffix")
{
    std::string_view view("suffixed");
    view.remove_suffix(4);

    ASSERT_FALSE(view);
}

TEST_CASE("prefix")
{
    std::string_view view("prefixed");
    view.remove_prefix(4);

    ASSERT(view);
}

TEST_CASE("stack")
{
    struct Example {
        const char array[8] = {'a', 'r', 'r', 'a', 'a', 'r', 'r', 'a'};
        int garbage    = -1;
        int terminator = 0;
    } example;
    static_assert(sizeof(Example) == 8 * sizeof(char) + 2 * sizeof(int));

    ASSERT_FALSE(std::string_view(example.array, sizeof example.array));

    // This is true because strlen captures 'garbage' variable
    ASSERT(std::string_view(example.array));
}

TEST_CASE("heap")
{
    static constexpr size_t SIZE = 4 * 1024;

    auto aligned = std::make_unique<std::array<char, SIZE>>();
    std::fill(aligned->begin(), aligned->end(), 'f');

    volatile char* ptr = aligned->end();
    *ptr = 'f';

    ASSERT_FALSE(std::string_view(aligned->data(), aligned->size()));
}

TEST_CASE("heap_terminated")
{
    static constexpr size_t SIZE = 4 * 1024;

    auto aligned = std::make_unique<std::array<char, SIZE>>();
    std::fill(aligned->begin(), aligned->end(), 'f');

    volatile char* ptr = aligned->end();
    *ptr = '\0';

    ASSERT(std::string_view(aligned->data(), aligned->size()));
}
