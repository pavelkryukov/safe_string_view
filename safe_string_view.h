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
 
#ifndef SAFE_STRING_VIEW
#define SAFE_STRING_VIEW

#include <cstring>
#include <string_view>

// Looks like a libstd++ bug...
namespace std {
    using ::strnlen_s;   
} // namespace std

#if defined(__STDC_WANT_LIB_EXT1__) and __STDC_WANT_LIB_EXT1__ == 1
/**
 * Returns true if view.data() is a valid null-terminated C string
 * Behavior is undefined if view.data() is not a pointer to allocated data
 *
 * TODO: check if view.data() + view.length() is a valid pointer
 */
inline bool is_safe_string_view(std::string_view view)
{
    return std::strnlen_s(view.data(), view.length() + 1) == view.length();
}

#endif // defined(__STDC_WANT_LIB_EXT1__) and __STDC_WANT_LIB_EXT1__ == 1

#endif // SAFE_STRING_VIEW
