#pragma once

// Linux > Mac > Windows btw.
enum class OperatingSystem
{
  Linux,
  Mac,
  Windows,
  Current =
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  #define OS_WINDOWS
    Windows
#elif __APPLE__
  #define OS_MAC
    Mac
#elif __linux__
  #define OS_LINUX
    Linux
#else
  #error "Unknown compiler"
#endif

};
