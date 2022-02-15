#pragma once

#include <string>

namespace Silfur
{
    // Convert a unicode codepoint to UTF-8
    // Source : https://gist.github.com/MightyPork/52eda3e5677b4b03524e40c9f0ab1da5
    std::string ToUtf8(unsigned int p_codePoint);
}
