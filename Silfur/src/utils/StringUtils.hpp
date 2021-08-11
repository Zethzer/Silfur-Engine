#pragma once

#include <string>

namespace Silfur::StringUtils
{
#ifdef SF_WINDOWS
#include <Windows.h>
    
    // Source : https://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
    static std::wstring s2ws(const std::string& s)
    {
        int len;
        int slength = (int) s.length() + 1;
        len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
        std::wstring buf;
        buf.resize(len);
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength,
            const_cast<wchar_t*>(buf.c_str()), len);
        return buf;
    }
#endif // SF_WINDOWS
}
