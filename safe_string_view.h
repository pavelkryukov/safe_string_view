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

/**
 * Returns true if 'strlen(view.data()) == view.length()'
 * Behavior is undefined if 'view' is not a valid std::string_view:
 *  - points to not-allocated data
 *  - points to a memory chunk _less_ than view.length()
 */
inline bool is_safe_string_view(std::string_view view)
{
    if (std::find(view.begin(), view.end(), '\0') != view.end())
        return false;

    const volatile auto* ptr = view.data() + view.length();

    // TODO: check if view.data() + view.length() is a dereferencable pointer
    return *ptr == '\0';
}

#endif // SAFE_STRING_VIEW
