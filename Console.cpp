#include "console.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif


namespace FC
{

    const Color Color::Default(-1, -1, -1);
    const Color Color::Black(0, 0, 0);
    const Color Color::Red(170, 0, 0);
    const Color Color::Green(0, 170, 0);
    const Color Color::Yellow(170, 170, 0);
    const Color Color::Blue(0, 0, 170);
    const Color Color::Magenta(170, 0, 170);
    const Color Color::Cyan(0, 170, 170);
    const Color Color::White(210, 210, 210);
    const Color Color::Gray(128, 128, 128);

    const Color Color::BrightBlack(85, 85, 85);
    const Color Color::BrightRed(255, 85, 85);
    const Color Color::BrightGreen(85, 255, 85);
    const Color Color::BrightYellow(255, 255, 85);
    const Color Color::BrightBlue(85, 85, 255);
    const Color Color::BrightMagenta(255, 85, 255);
    const Color Color::BrightCyan(85, 255, 255);
    const Color Color::BrightWhite(255, 255, 255);
    const Color Color::Orange(255, 165, 0);
    const Color Color::Pink(255, 105, 180);
    const Color Color::Purple(160, 32, 240);

    namespace
    {
        const char* ResetCode = "\033[0m";

        void Sleep(int milliseconds)
        {
            if (milliseconds > 0)
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(milliseconds)
                );
        }

        std::string ForegroundCode(Color color)
        {
            if (color.r < 0 || color.g < 0 || color.b < 0)
                return "\033[39m";

            std::ostringstream stream;

            stream << "\033[38;2;"
                << color.r << ";"
                << color.g << ";"
                << color.b << "m";

            return stream.str();
        }

        std::string BackgroundCode(Color color)
        {
            if (color.r < 0 || color.g < 0 || color.b < 0)
                return "\033[49m";

            std::ostringstream stream;

            stream << "\033[48;2;"
                << color.r << ";"
                << color.g << ";"
                << color.b << "m";

            return stream.str();
        }

        std::string StyleCode(Style style)
        {
            switch (style)
            {
            case Style::Bold:      return "\033[1m";
            case Style::Dim:       return "\033[2m";
            case Style::Italic:    return "\033[3m";
            case Style::Underline: return "\033[4m";
            case Style::Blink:     return "\033[5m";
            case Style::Reverse:   return "\033[7m";
            case Style::Hidden:    return "\033[8m";
            case Style::Strike:    return "\033[9m";
            }

            return ResetCode;
        }

        int Clamp(int value, int minimum, int maximum)
        {
            return std::max(minimum, std::min(value, maximum));
        }

        std::string SpinnerFrame(Spinner spinner, int index)
        {
            static const std::vector<std::string> line = {
                "|", "/", "-", "\\"
            };

            static const std::vector<std::string> dots = {
                ".  ", ".. ", "...", "   "
            };

            static const std::vector<std::string> bounce = {
                "(   )", "(*  )", "(* *)", "( ** )"
            };

            static const std::vector<std::string> circle = {
                "(o  )", "( o )", "(  o)", "( o )"
            };

            static const std::vector<std::string> arrows = {
                "<", "^", ">", "v"
            };

            static const std::vector<std::string> clock = {
                "[|]", "[/]", "[-]", "[\\]"
            };
            static const std::vector<std::string> square = { // this looks kinda bad, actually it looks shit but it was either this or sm more shit
                "|__|",
                "|  |",
                "|--|",
                "|  |"
            };
            static const std::vector<std::string> pulse = {
                "_", ".", "o", "O", "o", "."
            };

            const std::vector<std::string>* frames = &line;

            switch (spinner)
            {
            case Spinner::Line:   frames = &line; break;
            case Spinner::Dots:   frames = &dots; break;
            case Spinner::Bounce: frames = &bounce; break;
            case Spinner::Circle: frames = &circle; break;
            case Spinner::Arrows: frames = &arrows; break;
            case Spinner::Clock:  frames = &clock; break;
            case Spinner::Square: frames = &square; break;
            case Spinner::Pulse:  frames = &pulse; break;
            }

            return (*frames)[static_cast<std::size_t>(index) % frames->size()];
        }
    }

    namespace Console
    {
        void EnableANSI()
        {
#ifdef _WIN32
            HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

            if (output == INVALID_HANDLE_VALUE)
                return;

            DWORD mode = 0;

            if (!GetConsoleMode(output, &mode))
                return;

            SetConsoleMode(
                output,
                mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
            );
#endif
        }

        void Print(const std::string& text, Color color)
        {
            EnableANSI();

            std::cout << ForegroundCode(color)
                << text
                << ResetCode;

            std::cout.flush();
        }

        void PrintLn(const std::string& text, Color color)
        {
            Print(text, color);
            std::cout << '\n';
        }

        void Write(const std::string& text)
        {
            std::cout << text;
            std::cout.flush();
        }

        void SetColor(Color color)
        {
            EnableANSI();
            std::cout << ForegroundCode(color);
        }

        void SetBackground(Color color)
        {
            EnableANSI();
            std::cout << BackgroundCode(color);
        }

        void Bg(Color color)
        {
            SetBackground(color);
        }

        void SetStyle(Style style)
        {
            EnableANSI();
            std::cout << StyleCode(style);
        }

        void Bold()
        {
            SetStyle(Style::Bold);
        }

        void Dim()
        {
            SetStyle(Style::Dim);
        }

        void Italic()
        {
            SetStyle(Style::Italic);
        }

        void Underline()
        {
            SetStyle(Style::Underline);
        }

        void Strike()
        {
            SetStyle(Style::Strike);
        }

        void ResetStyle()
        {
            Reset();
        }

        void Reset()
        {
            std::cout << ResetCode;
            std::cout.flush();
        }

        void SetOpacity(double opacity)
        {
            if (opacity < 1.0)
                Dim();
            else
                Reset();
        }

        void Clear()
        {
            EnableANSI();
            std::cout << "\033[2J\033[H";
            std::cout.flush();
        }

        void ClearLine()
        {
            std::cout << "\033[2K\r";
            std::cout.flush();
        }

        void ResetConsole()
        {
            Reset();
            ShowCursor();
            Clear();
        }

        void SetTitle(const std::string& title)
        {
            EnableANSI();
            std::cout << "\033]0;" << title << "\007";
        }

        void SetSize(int width, int height)
        {
            width = std::max(1, width);
            height = std::max(1, height);

            std::cout << "\033[8;"
                << height << ";"
                << width << "t";

            std::cout.flush();
        }

        void SetCursor(int x, int y)
        {
            x = std::max(1, x);
            y = std::max(1, y);

            std::cout << "\033[" << y << ";" << x << "H";
            std::cout.flush();
        }

        void MoveCursor(int x, int y)
        {
            SetCursor(x, y);
        }

        void MoveCursorUp(int amount)
        {
            if (amount < 1) amount = 1;
            std::cout << "\033[" << amount << "A";
        }

        void MoveCursorDown(int amount)
        {
            if (amount < 1) amount = 1;
            std::cout << "\033[" << amount << "B";
        }

        void MoveCursorLeft(int amount)
        {
            if (amount < 1) amount = 1;
            std::cout << "\033[" << amount << "D";
        }

        void MoveCursorRight(int amount)
        {
            if (amount < 1) amount = 1;
            std::cout << "\033[" << amount << "C";
        }
        

        void ShowCursor()
        {
            std::cout << "\033[?25h";
        }

        void HideCursor()
        {
            std::cout << "\033[?25l";
        }

        void SaveCursor()
        {
            std::cout << "\033[s";
        }

        void LoadCursor()
        {
            std::cout << "\033[u";
        }

        void Beep(int frequency, int duration)
        {
#ifdef _WIN32
            ::Beep(
                static_cast<DWORD>(frequency),
                static_cast<DWORD>(duration)
            );
#else
            std::cout << '\a';
            Sleep(duration);
#endif
        }

        void Pause(const std::string& message)
        {
            if (!message.empty())
                PrintLn(message, Color::Gray);

            std::string input;
            std::getline(std::cin, input);
        }

        void Delay(int milliseconds)
        {
            Sleep(milliseconds);
        }

        int Width()
        {
#ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO info;

            if (GetConsoleScreenBufferInfo(
                GetStdHandle(STD_OUTPUT_HANDLE), &info))
            {
                return info.srWindow.Right - info.srWindow.Left + 1;
            }
#endif
            return 80;
        }

        int Height()
        {
#ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO info;

            if (GetConsoleScreenBufferInfo(
                GetStdHandle(STD_OUTPUT_HANDLE), &info))
            {
                return info.srWindow.Bottom - info.srWindow.Top + 1;
            }
#endif
            return 25;
        }

        std::string Input(const std::string& prompt)
        {
            if (!prompt.empty())
                Print(prompt, Color::BrightCyan);

            std::string value;
            std::getline(std::cin, value);

            return value;
        }

        void Separator(char character, int length, Color color)
        {
            length = std::max(0, length);

            PrintLn(std::string(length, character), color);
        }

        void Box(const std::string& text, Color color)
        {
            int width = static_cast<int>(text.size()) + 4;

            PrintLn("+" + std::string(width - 2, '-') + "+", color);
            PrintLn("| " + text + " |", color);
            PrintLn("+" + std::string(width - 2, '-') + "+", color);
        }

        void Center(const std::string& text, Color color)
        {
            int width = Width();
            int padding = std::max(0, (width - static_cast<int>(text.size())) / 2);

            PrintLn(std::string(padding, ' ') + text, color);
        }

        void ProgressBar(int value, int maximum, int width, Color color)
        {
            if (maximum <= 0)
                maximum = 1;

            width = std::max(1, width);
            value = Clamp(value, 0, maximum);

            double ratio = static_cast<double>(value) / maximum;
            int filled = static_cast<int>(ratio * width);

            std::string bar = "[";

            bar += std::string(filled, '#');
            bar += std::string(width - filled, '-');
            bar += "] ";

            int percent = static_cast<int>(ratio * 100);

            std::cout << "\r";
            Print(bar, color);
            std::cout << percent << "%";
            std::cout.flush();
        }

        void DrawProgress(int value, int maximum, int width, Color color)
        {
            ProgressBar(value, maximum, width, color);
        }

        void Table(
            const std::vector<std::vector<std::string>>& rows,
            Color color
        )
        {
            if (rows.empty())
                return;

            std::size_t columns = 0;

            for (const auto& row : rows)
                columns = std::max(columns, row.size());

            std::vector<std::size_t> widths(columns, 0);

            for (const auto& row : rows)
            {
                for (std::size_t i = 0; i < row.size(); ++i)
                {
                    widths[i] = std::max(widths[i], row[i].size());
                }
            }

            auto drawLine = [&]()
                {
                    std::string line = "+";

                    for (std::size_t width : widths)
                        line += std::string(width + 2, '-') + "+";

                    PrintLn(line, color);
                };

            drawLine();

            for (std::size_t rowIndex = 0; rowIndex < rows.size(); ++rowIndex)
            {
                std::cout << "|";

                for (std::size_t column = 0; column < columns; ++column)
                {
                    std::string value;

                    if (column < rows[rowIndex].size())
                        value = rows[rowIndex][column];

                    std::cout << " "
                        << std::left
                        << std::setw(static_cast<int>(widths[column]))
                        << value
                        << " |";
                }

                std::cout << '\n';

                if (rowIndex == 0)
                    drawLine();
            }

            drawLine();
        }

        std::string Colorize(const std::string& text, Color color)
        {
            return ForegroundCode(color) + text + ResetCode;
        }

        void PrintRGB(const std::string& text, int red, int green, int blue)
        {
            Print(text, Color(
                Clamp(red, 0, 255),
                Clamp(green, 0, 255),
                Clamp(blue, 0, 255)
            ));
        }

        void PrintAt(int x, int y, const std::string& text, Color color)
        {
            SetCursor(x, y);
            Print(text, color);
        }

        void NewLine(int count)
        {
            for (int i = 0; i < count; ++i)
                std::cout << '\n';
        }

        void Repeat(char character, int count)
        {
            if (count > 0)
                std::cout << std::string(count, character);

            std::cout.flush();
        }
    }

    namespace Anim
    {
        void Spin(
            const std::string& message,
            int duration,
            int interval,
            Color color,
            Spinner spinner
        )
        {
            if (interval < 1)
                interval = 1;

            int elapsed = 0;
            int frame = 0;

            Console::HideCursor();

            while (elapsed < duration)
            {
                std::string symbol = SpinnerFrame(spinner, frame++);

                std::cout << "\r";
                Console::Print(symbol + " " + message, color);
                Console::Write("\033[K");

                Sleep(interval);
                elapsed += interval;
            }

            std::cout << "\r";
            Console::Write("\033[K");
            Console::ShowCursor();
        }

        void Dots(
            const std::string& message,
            int duration,
            int interval,
            Color color
        )
        {
            Spin(message, duration, interval, color, Spinner::Dots);
        }

        void Type(const std::string& text, int interval, Color color)
        {
            for (char character : text)
            {
                Console::Print(std::string(1, character), color);
                Sleep(interval);
            }

            Console::NewLine();
        }

        void Rainbow(const std::string& text, int interval)
        {
            const Color colors[] = {
                Color::BrightRed,
                Color::Orange,
                Color::BrightYellow,
                Color::BrightGreen,
                Color::BrightCyan,
                Color::BrightBlue,
                Color::BrightMagenta
            };

            for (std::size_t i = 0; i < text.size(); ++i)
            {
                Console::Print(
                    std::string(1, text[i]),
                    colors[i % 7]
                );

                Sleep(interval);
            }

            Console::NewLine();
        }

        void Pulse(
            const std::string& text,
            int duration,
            int interval,
            Color color
        )
        {
            if (interval < 1)
                interval = 1;

            int elapsed = 0;
            bool bright = true;

            while (elapsed < duration)
            {
                Console::Write("\r");

                if (bright)
                    Console::Print(text, color);
                else
                    Console::Print(text, Color::Gray);

                Sleep(interval);

                elapsed += interval;
                bright = !bright;
            }

            Console::Write("\r");
            Console::Write("\033[K");
        }

        void Progress(
            const std::string& message,
            int duration,
            Color color
        )
        {
            if (duration < 0)
                duration = 0;

            int interval = duration / 100;

            for (int i = 0; i <= 100; ++i)
            {
                Console::Write("\r");
                Console::Print(message + " ", color);
                Console::ProgressBar(i, 100, 25, color);

                Sleep(interval);
            }

            Console::NewLine();
        }
    }
}