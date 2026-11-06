
#pragma once

#include <string>
#include <vector>
#include <cstddef>
// simple library, for consoles designed for easier use
namespace FC
{
    struct Color
    {
        int r, g, b;

        constexpr Color(int red = -1, int green = -1, int blue = -1)
            : r(red), g(green), b(blue) {}

        static const Color Default;
        static const Color Black, Red, Green, Yellow, Blue;
        static const Color Magenta, Cyan, White, Gray;

        static const Color BrightBlack, BrightRed, BrightGreen;
        static const Color BrightYellow, BrightBlue, BrightMagenta;
        static const Color BrightCyan, BrightWhite;
        static const Color Orange, Pink, Purple;
    };

    enum class Style
    {
        Bold, Dim, Italic, Underline,
        Blink, Reverse, Hidden, Strike
    };

    enum class Spinner
    {
        Line, Dots, Bounce, Circle,
        Arrows, Clock, Square, Pulse
    };
    // main stuff
    namespace Console
    {
        void EnableANSI();
        void Print(const std::string& text, Color color = Color::Default);
        void PrintLn(const std::string& text = "", Color color = Color::Default);
        void Write(const std::string& text);
        void SetColor(Color color);
        void SetBackground(Color color);
        void Bg(Color color);
        void SetStyle(Style style);
        void Bold();
        void Dim();
        void Italic();
        void Underline();
        void Strike();
        void ResetStyle();
        void Reset();
        void SetOpacity(double opacity);
        void Clear();
        void ClearLine();
        void ResetConsole();
        void SetTitle(const std::string& title);
        void SetSize(int width, int height);
        void SetCursor(int x, int y);
        void MoveCursor(int x, int y);
        void MoveCursorUp(int amount = 1);
        void MoveCursorDown(int amount = 1);
        void MoveCursorLeft(int amount = 1);
        void MoveCursorRight(int amount = 1);
        void ShowCursor();
        void HideCursor();
        void SaveCursor();
        void LoadCursor();
        void Beep(int frequency = 800, int duration = 150);
        void Pause(const std::string& message = "Press enter to continue...");
        void Delay(int milliseconds);
        int Width();
        int Height();

        std::string Input(const std::string& prompt = "");

        void Separator(char character = '-', int length = 40,
            Color color = Color::Default);

        void Box(const std::string& text, Color color = Color::Default);
        void Center(const std::string& text, Color color = Color::Default);

        void ProgressBar(int value, int maximum = 100, int width = 30,
            Color color = Color::BrightGreen);

        void DrawProgress(int value, int maximum = 100, int width = 30,
            Color color = Color::BrightGreen);

        void Table(const std::vector<std::vector<std::string>>& rows,
            Color color = Color::Default);

        std::string Colorize(const std::string& text, Color color);

        void PrintRGB(const std::string& text, int red, int green, int blue);

        void PrintAt(int x, int y, const std::string& text,
            Color color = Color::Default);

        void NewLine(int count = 1);
        void Repeat(char character, int count);
    }
    // animations, looks cool i guess
    namespace Anim
    {
        void Spin(const std::string& message, int duration, int interval = 80,
            Color color = Color::BrightCyan, Spinner spinner = Spinner::Line);

        void Dots(const std::string& message, int duration, int interval = 250,
            Color color = Color::BrightCyan);

        void Type(const std::string& text, int interval = 35,
            Color color = Color::Default);

        void Rainbow(const std::string& text, int interval = 35);

        void Pulse(const std::string& text, int duration, int interval = 150,
            Color color = Color::BrightCyan);

        void Progress(const std::string& message, int duration,
            Color color = Color::BrightGreen);
    }
}
