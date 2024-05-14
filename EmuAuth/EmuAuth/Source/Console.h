#pragma once

namespace Console
{
    enum class Color
    {
        Default,
        DarkBlue,
        DarkGreen,
        DarkCyan,
        DarkRed,
        DarkPurple,
        DarkYellow,
        DarkWhite,
        DarkGrey,
        DarkBlueLite,
        Green,
        Cyan,
        Red,
        Purple,
        Yellow,
        White
    };

    void Base(Color color, const char* prefix, const char* text, va_list args);
    void Info(const char* text, ...);
    void Warning(const char* text, ...);
    void Error(const char* text, ...);
    void Success(const char* text, ...);
    void Debug(const char* text, ...);
    std::string ReadInput(const char* text);
    void Title(const char* name, const char* subtext);
}
