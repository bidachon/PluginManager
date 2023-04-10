#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include <cstring>
#include <filesystem>
#include <iostream>

#ifdef __unix__
#  include <dlfcn.h>
#  include <unistd.h>
#endif

// [DO NOT MERGE] RKERR TODO : Write a logging abstraction
#define LOG_TODO_INFO(msg)  std::cerr << "[INFO]  " << msg << std::endl;
#define LOG_TODO_ERROR(msg) std::cerr << "[ERROR] " << msg << std::endl;


// [DO NOT MERGE] RKERR TODO : Improve this file:
//       - test on and handle more platforms
//       - split into h/cpp to remove inlines
//       - consider using boost, for example executable path from
//         boost::dll::program_location -- or remove the assumption about
//         executable path

namespace plugin::detail
{

inline void *libraryOpen(const char *filename)
{
#ifdef _WIN32
    return ((void*)LoadLibrary(filename));
#elif __unix__
    return dlopen(filename, RTLD_NOW | RTLD_GLOBAL);
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.")
#endif
}

inline void *librarySymbol(void *handle, const char *symbol)
{
#ifdef _WIN32
    return ((void*)GetProcAddress((HINSTANCE)handle, symbol));
#elif __unix__
    return dlsym(handle, symbol);
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.")
#endif
}

inline int libraryClose(void *handle)
{
#ifdef _WIN32
    return FreeLibrary((HINSTANCE)handle);
#elif __unix__
    return dlclose(handle);
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.")
#endif
}

inline std::string GetApplicationPath()
{
#ifdef _WIN32
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.")
#elif __unix__
    const size_t bufSize = 512;
    char nameBuf[bufSize] = {0};
    const auto retVal = readlink("/proc/self/exe", nameBuf, bufSize);
    if (retVal < 0) {
        LOG_TODO_ERROR("Failed to read application path with error " << errno << ":" << std::strerror(errno));
        return {};
    }

    return std::filesystem::path{ nameBuf }.remove_filename();
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.")
#endif
}

} // end namespaces

#endif