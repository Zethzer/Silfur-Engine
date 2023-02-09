#pragma once

#include "utils/log/Log.hpp"
#include "Application.hpp"

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
    #include <shellapi.h>
#endif

extern Silfur::Application* Silfur::CreateApplication(int argc, char** argv);

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    Silfur::Log::Init();

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
    int argc = 0;
    size_t w_len_all_args = 0;
    LPWSTR* szArgList;
    char** argv;

    szArgList = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!szArgList)
    {
        SF_FATAL(Win32, 0, "CommandLineToArgvW failed\n");
        return 0;
    }

    for (int i = 0; i < argc; ++i)
    {
        w_len_all_args += wcslen(szArgList[i]);
    }

    for (int i = 0; i < argc; ++i)
    {
        argv = new char*[w_len_all_args + (argc)];
        size_t w_len = wcslen(szArgList[i]);
        argv[i] = new char[w_len + 1];
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, szArgList[i], w_len + 1, argv[i], w_len + 1, NULL, NULL);
    }

    // Free memory allocated for CommandLineToArgvW arguments.
    LocalFree(szArgList);
#endif

    auto app = Silfur::CreateApplication(argc, argv);
    app->Run();
    delete app;
}
