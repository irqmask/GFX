/// Define a set of exceptions which shall be used exclusivly.

#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <stdexcept>


#ifdef _MSC_VER
    #define NOEXCEPT
#else
    #define NOEXCEPT noexcept
#endif

#define LOC __FILE__, __LINE__, __FUNCTION__

class GameException : std::exception
{
public:
    GameException(const char* file, uint32_t line, const char* function);

    virtual const char* what() const NOEXCEPT;

protected:
    const char* file;
    const int line;
    const char* function;

    char message[2048];
    char full_message[4096];


    template <class... Args>
    void compileErrorMessage(const char* format, ...);
};


template <class... Args>
void GameException::compileErrorMessage(const char* format, ...)
{
    va_list args;
    va_start(args, format);
#ifdef _WIN32
    vsnprintf_s(message, sizeof(message) - 1, _TRUNCATE, format, args);
#else
    vsnprintf(message, sizeof(message) - 1, format, args);
#endif
    va_end(args);
    message[sizeof(message) - 1] = '\0';
#ifdef _WIN32
    _snprintf_s(full_message, sizeof(full_message) - 1, _TRUNCATE, "%s:%d %s:\n%s", file, line, function, message);
#else
    snprintf(full_message, sizeof(full_message) - 1, "%s:%d %s:\n%s", file, line, function, message);
#endif

    full_message[sizeof(full_message) - 1] = '\0';
}


class InvalidParameter : GameException
{
public:
	template <class... Args>
	InvalidParameter(const char* file, uint32_t line, const char* function, const char* fmt, Args... args)
		: GameException(file, line, function)
	{
		compileErrorMessage(fmt, args...);
	};
};


class OperationFailed : GameException
{
public: 
    template <class... Args>
    OperationFailed(const char* file, uint32_t line, const char* function, const char* fmt, Args... args)
        : GameException(file, line, function)
    {
        compileErrorMessage(fmt, args...);
    };
};


class ResourceMissing : GameException
{
public:
    template <class... Args>
    ResourceMissing(const char* file, uint32_t line, const char* function, const char* fmt, Args... args)
        : GameException(file, line, function)
    {
        compileErrorMessage(fmt, args...);
    };
};
