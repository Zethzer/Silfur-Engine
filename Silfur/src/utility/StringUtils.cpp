#include "StringUtils.hpp"

#include "log/Log.hpp"

namespace Silfur
{
    std::string ToUtf8(unsigned int p_codePoint)
    {
        char utf8str[5] = {0x00};

        // U+0000   U+007F    0xxxxxxx
        if (p_codePoint <= 0x007F) {
            utf8str[0] = (char) p_codePoint;
        }
            // U+0080   U+07FF    110xxxxx  10xxxxxx
        else if (p_codePoint <= 0x07FF) {
            // 2-byte unicode
            utf8str[0] = (char) (((p_codePoint >> 6) & 0x1F) | 0xC0);
            utf8str[1] = (char) (((p_codePoint >> 0) & 0x3F) | 0x80);
        }
            // Invalid block of utf8
        else if (0xd800 <= p_codePoint && p_codePoint <= 0xdfff) {
            return "Error ! Invalid block of UTF-8.";
        }
            // U+0800   U+FFFF    1110xxxx  10xxxxxx    10xxxxxx
        else if (p_codePoint <= 0xFFFF) {
            // 3-byte unicode
            utf8str[0] = (char) (((p_codePoint >> 12) & 0x0F) | 0xE0);
            utf8str[1] = (char) (((p_codePoint >>  6) & 0x3F) | 0x80);
            utf8str[2] = (char) (((p_codePoint >>  0) & 0x3F) | 0x80);
        }
            // U+10000  U+10FFFF  11110xxx  10xxxxxx    10xxxxxx    10xxxxxx
        else if (p_codePoint <= 0x10FFFF) {
            utf8str[0] = (char) (((p_codePoint >> 18) & 0x07) | 0xF0);
            utf8str[1] = (char) (((p_codePoint >> 12) & 0x3F) | 0x80);
            utf8str[2] = (char) (((p_codePoint >>  6) & 0x3F) | 0x80);
            utf8str[3] = (char) (((p_codePoint >>  0) & 0x3F) | 0x80);
        }
        else {
            return "Error ! Code point is out of UTF-8 range.";
        }

        return std::string(utf8str);
    }
}
