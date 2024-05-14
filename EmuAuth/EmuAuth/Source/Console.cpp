#include "Global.h"

void Console::Base(Color color, const char* prefix, const char* text, va_list args)
{
    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::White));
    printf("[");

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(color));
    printf("%s", prefix);

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::White));
    printf("] ");

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::DarkWhite));
    vprintf(text, args);
    printf("\n");
}

void Console::Info(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    Base(Color::Cyan, "i", text, args);
    va_end(args);
}

void Console::Warning(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    Base(Color::Yellow, "w", text, args);
    va_end(args);
}

void Console::Error(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    Base(Color::Red, "e", text, args);
    va_end(args);
}

void Console::Success(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    Base(Color::Green, "s", text, args);
    va_end(args);
}

void Console::Debug(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    Base(Color::DarkGrey, "d", text, args);
    va_end(args);
}

std::string Console::ReadInput(const char* text)
{
    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::White));
    printf(text);

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::DarkWhite));
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void Console::Title(const char* name, const char* subtext)
{
    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Console::Color::Purple));
    printf("%s\n", name);

    SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Console::Color::DarkWhite));
    printf("%s\n\n", subtext);
}