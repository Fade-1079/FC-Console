# FC-Console-Helper

# FC Console

A lightweight C++ console utility library for creating colourful, interactive and animated terminal applications.

FC Console provides an easy way to work with console colours, RGB text, backgrounds, cursor controls, text formatting, progress bars, tables, separators, and animations without repeatedly writing terminal escape sequences.

## Features

- **Text colours** — Standard and bright colours, plus custom RGB values.
- **Background colours** — Change terminal text backgrounds.
- **Text formatting** — Bold, dim, italic, underline, blink, reverse, hidden and strikethrough.
- **Console controls** — Clear the screen, clear lines, reset formatting and change the terminal title.
- **Cursor controls** — Move, position, save, restore, hide and show the cursor.
- **Progress bars** — Display progress with custom widths and colours.
- **Animations** — Spinners, dots, pulsing text, typing effects and rainbow text.
- **Tables** — Print formatted tables from vectors.
- **Text utilities** — Center text, draw boxes, print separators and repeat characters.
- **Input** — Simple console input functions.
- **RGB support** — Create custom colours using RGB values.

## Project Structure

```text
FC-Console/
│
├── console.h
├── console.cpp
├── example.cpp
└── README.md
```

## Requirements

- C++17 or newer
- A terminal with ANSI escape sequence support
- Windows, Linux or macOS

## Installation

Download or clone the repository:

```bash
git clone https://github.com/YOUR_USERNAME/FC-Console.git
```

Add `console.h` and `console.cpp` to your C++ project.

Include the header:

```cpp
#include "console.h"
```

Compile the project:

```bash
g++ -std=c++17 main.cpp console.cpp -o app
```

To compile the included example:

```bash
g++ -std=c++17 example.cpp console.cpp -o example
```

On Windows with Visual Studio, add both `console.cpp` and `example.cpp` to your project and make sure the project uses C++17 or newer.

## Quick Start

```cpp
#include "console.h"

int main()
{
    FC::Console::EnableANSI();
    FC::Console::Clear();

    FC::Console::PrintLn(
        "Welcome to FC Console!",
        FC::Color::BrightCyan
    );

    FC::Console::Separator(
        '=',
        40,
        FC::Color::BrightBlue
    );

    FC::Anim::Spin(
        "Loading",
        2000,
        80,
        FC::Color::BrightGreen,
        FC::Spinner::Line
    );

    FC::Console::PrintLn(
        "Ready!",
        FC::Color::BrightGreen
    );

    FC::Console::Pause();

    return 0;
}
```

## Colours

FC Console includes several predefined colours.

```cpp
FC::Console::PrintLn("Red", FC::Color::Red);
FC::Console::PrintLn("Green", FC::Color::Green);
FC::Console::PrintLn("Blue", FC::Color::Blue);
FC::Console::PrintLn("Yellow", FC::Color::Yellow);

FC::Console::PrintLn("Bright Red", FC::Color::BrightRed);
FC::Console::PrintLn("Bright Green", FC::Color::BrightGreen);
FC::Console::PrintLn("Bright Blue", FC::Color::BrightBlue);
FC::Console::PrintLn("Bright Cyan", FC::Color::BrightCyan);
```

Available colours:

- Default
- Black
- Red
- Green
- Yellow
- Blue
- Magenta
- Cyan
- White
- Gray
- BrightBlack
- BrightRed
- BrightGreen
- BrightYellow
- BrightBlue
- BrightMagenta
- BrightCyan
- BrightWhite
- Orange
- Pink
- Purple

### Custom RGB

```cpp
FC::Console::PrintRGB("Custom colour", 255, 100, 50);
```

You can also create a colour:

```cpp
FC::Color custom(120, 50, 255);

FC::Console::PrintLn("Custom RGB colour", custom);
```

## Background Colours

```cpp
FC::Console::SetBackground(FC::Color::Blue);
FC::Console::PrintLn("Blue background");

FC::Console::Bg(FC::Color::Red);
FC::Console::PrintLn("Red background");

FC::Console::Reset();
```

## Text Styles

```cpp
FC::Console::Bold();
FC::Console::PrintLn("Bold text");

FC::Console::Italic();
FC::Console::PrintLn("Italic text");

FC::Console::Underline();
FC::Console::PrintLn("Underlined text");

FC::Console::Strike();
FC::Console::PrintLn("Strikethrough text");

FC::Console::ResetStyle();
```

You can also use the style enum:

```cpp
FC::Console::SetStyle(FC::Style::Bold);
FC::Console::PrintLn("Bold");

FC::Console::SetStyle(FC::Style::Reverse);
FC::Console::PrintLn("Reverse");

FC::Console::Reset();
```

## Separators and Boxes

```cpp
FC::Console::Separator('-', 50, FC::Color::BrightCyan);

FC::Console::Separator('=', 40, FC::Color::BrightBlue);

FC::Console::Box(
    "Welcome to FC Console",
    FC::Color::BrightGreen
);

FC::Console::Center(
    "Centered text",
    FC::Color::BrightYellow
);
```

## Progress Bars

```cpp
for (int i = 0; i <= 100; i += 5)
{
    FC::Console::ProgressBar(
        i,
        100,
        30,
        FC::Color::BrightGreen
    );

    FC::Console::Delay(50);
}

FC::Console::NewLine();
```

You can also use:

```cpp
FC::Console::DrawProgress(
    50,
    100,
    30,
    FC::Color::BrightCyan
);
```

## Animations

### Spinner

```cpp
FC::Anim::Spin(
    "Loading",
    2000,
    80,
    FC::Color::BrightCyan,
    FC::Spinner::Line
);
```

Available spinner types:

- Line
- Dots
- Bounce
- Circle
- Arrows
- Clock
- Square
- Pulse

### Dots

```cpp
FC::Anim::Dots(
    "Connecting",
    2000,
    200,
    FC::Color::BrightGreen
);
```

### Typing Animation

```cpp
FC::Anim::Type(
    "Welcome to FC Console!",
    35,
    FC::Color::BrightYellow
);
```

### Rainbow Text

```cpp
FC::Anim::Rainbow(
    "Rainbow effect!",
    35
);
```

### Pulse

```cpp
FC::Anim::Pulse(
    "Starting application...",
    2000,
    150,
    FC::Color::BrightMagenta
);
```

### Animated Progress

```cpp
FC::Anim::Progress(
    "Installing",
    3000,
    FC::Color::BrightGreen
);
```

## Tables

Tables use a vector of string vectors.

```cpp
#include <vector>
#include <string>

std::vector<std::vector<std::string>> data = {
    {"Name", "Age", "Status"},
    {"Alex", "18", "Online"},
    {"Jordan", "20", "Offline"},
    {"Taylor", "19", "Online"}
};

FC::Console::Table(
    data,
    FC::Color::BrightCyan
);
```

## Cursor Controls

```cpp
FC::Console::SetCursor(10, 5);

FC::Console::MoveCursorUp(2);
FC::Console::MoveCursorDown(2);
FC::Console::MoveCursorLeft(5);
FC::Console::MoveCursorRight(5);

FC::Console::SaveCursor();
FC::Console::LoadCursor();

FC::Console::HideCursor();
FC::Console::ShowCursor();
```

Print at a specific position:

```cpp
FC::Console::PrintAt(
    5,
    5,
    "Hello!",
    FC::Color::BrightGreen
);
```

## Console Management

```cpp
FC::Console::Clear();
FC::Console::ClearLine();

FC::Console::SetTitle("My Application");

FC::Console::SetSize(120, 40);

FC::Console::Reset();
FC::Console::ResetConsole();
```

Get the terminal dimensions:

```cpp
int width = FC::Console::Width();
int height = FC::Console::Height();
```

## Input and Utilities

```cpp
std::string name = FC::Console::Input("Enter your name: ");

FC::Console::PrintLn(
    "Hello, " + name,
    FC::Color::BrightGreen
);

FC::Console::Pause("Press enter to continue...");

FC::Console::Delay(1000);

FC::Console::Beep(800, 150);
```

Other utilities:

```cpp
FC::Console::Repeat('*', 30);
FC::Console::NewLine(2);

FC::Console::Write("Raw output");

FC::Console::Print(
    "Hello",
    FC::Color::BrightCyan
);

FC::Console::PrintLn(
    "Hello with newline",
    FC::Color::BrightGreen
);
```

## API Reference

### Console

| Function | Description |
|---|---|
| `EnableANSI()` | Enables ANSI support on Windows |
| `Print()` | Prints coloured text |
| `PrintLn()` | Prints text with a newline |
| `Write()` | Writes raw output |
| `SetColor()` | Changes text colour |
| `SetBackground()` | Changes background colour |
| `Bg()` | Background colour shortcut |
| `SetStyle()` | Applies a text style |
| `Bold()` | Enables bold text |
| `Dim()` | Enables dim text |
| `Italic()` | Enables italic text |
| `Underline()` | Underlines text |
| `Strike()` | Strikes through text |
| `ResetStyle()` | Resets text styling |
| `Reset()` | Resets terminal formatting |
| `SetOpacity()` | Approximates opacity using dim text |
| `Clear()` | Clears the terminal |
| `ClearLine()` | Clears the current line |
| `ResetConsole()` | Resets formatting and clears the terminal |
| `SetTitle()` | Changes the terminal title |
| `SetSize()` | Requests a terminal size |
| `SetCursor()` | Positions the cursor |
| `MoveCursor()` | Moves the cursor to coordinates |
| `MoveCursorUp()` | Moves the cursor up |
| `MoveCursorDown()` | Moves the cursor down |
| `MoveCursorLeft()` | Moves the cursor left |
| `MoveCursorRight()` | Moves the cursor right |
| `ShowCursor()` | Shows the cursor |
| `HideCursor()` | Hides the cursor |
| `SaveCursor()` | Saves cursor position |
| `LoadCursor()` | Restores cursor position |
| `Beep()` | Plays a console beep |
| `Pause()` | Waits for input |
| `Delay()` | Waits for a duration |
| `Width()` | Gets terminal width |
| `Height()` | Gets terminal height |
| `Input()` | Reads a line of input |
| `Separator()` | Prints a separator |
| `Box()` | Draws a text box |
| `Center()` | Centers text |
| `ProgressBar()` | Prints a progress bar |
| `DrawProgress()` | Progress bar alternative |
| `Table()` | Prints a formatted table |
| `Colorize()` | Returns coloured text |
| `PrintRGB()` | Prints custom RGB text |
| `PrintAt()` | Prints at coordinates |
| `NewLine()` | Prints multiple newlines |
| `Repeat()` | Repeats a character |

### Anim

| Function | Description |
|---|---|
| `Spin()` | Runs a spinner |
| `Dots()` | Runs a dots animation |
| `Type()` | Types text character by character |
| `Rainbow()` | Prints rainbow-coloured text |
| `Pulse()` | Pulses text |
| `Progress()` | Runs an animated progress bar |

and more! 
## Notes

- The library uses ANSI escape sequences for terminal formatting.
- Some terminal features depend on the terminal emulator.
- `SetOpacity()` uses dim text as an approximation; it does not provide true transparency.
- `SetSize()` depends on terminal support.
- Unicode spinner characters may look different depending on the terminal font.
- The library uses C++17 or newer.


Bug reports, improvements and feature suggestions are welcome.

If you find a problem, lmk @fade1079 on disc

---

**FC Console**  
A simple console library for C++ applications.
