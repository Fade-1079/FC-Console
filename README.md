## FC Console Library

This example demonstrates some of the main features available in FC Console, all working together in one simple C++ application. It includes console setup, custom colours, text formatting, loading animations, progress bars, tables, typing effects, and user input.

It's a good starting point if you want to understand how the library works and how its different functions can be combined to create more interactive and visually appealing console applications.

### What this example demonstrates

- **Console setup:** Enables ANSI support, clears the terminal, and sets a custom window title.
- **Boxes and separators:** Organises the console output into neat sections.
- **Text colours and styles:** Prints text using predefined colours, bold formatting, and custom RGB values.
- **Animations:** Uses a spinner and pulsing text to make loading screens more interesting.
- **Progress bars:** Displays a progress bar that updates as the application runs.
- **Tables:** Organises information into rows and columns.
- **Typing effects:** Displays text one character at a time.
- **User input:** Reads a name from the user and responds with a personalised message.
- **Console cleanup:** Pauses before exiting and resets the terminal formatting.

### Example code

```cpp
#include "console.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    FC::Console::EnableANSI();
    FC::Console::Clear();
    FC::Console::SetTitle("FC Console Demo");

    FC::Console::Box(
        "Welcome to FC Console!",
        FC::Color::BrightCyan
    );

    FC::Console::Center(
        "A colourful C++ console library",
        FC::Color::BrightYellow
    );

    FC::Console::Separator(
        '=',
        45,
        FC::Color::BrightBlue
    );

    FC::Console::PrintLn("Bright green text!", FC::Color::BrightGreen);
    FC::Console::Bold();
    FC::Console::PrintLn("Bold text!");
    FC::Console::ResetStyle();

    FC::Console::PrintRGB("Custom rgb colour", 255, 120, 50);

    // Loading animations
    FC::Anim::Spin(
        "Loading",
        2000,
        80,
        FC::Color::BrightCyan,
        FC::Spinner::Dots
    );

    FC::Anim::Pulse(
        "Almost ready...",
        1500,
        150,
        FC::Color::BrightMagenta
    );

    FC::Console::PrintLn("Ready!", FC::Color::BrightGreen);

    // Progress bar
    FC::Console::PrintLn("\Loading:");

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

    FC::Console::NewLine(2);

    // Table
    std::vector<std::vector<std::string>> data = {
        {"Feature", "Status"},
        {"Colours", "Available"},
        {"Animations", "Available"},
        {"Progress Bars", "Available"},
        {"Tables", "Available"}
    };

    FC::Console::Table(data, FC::Color::BrightCyan);

    FC::Console::NewLine();
    FC::Anim::Type(
        "Hello!",
        35,
        FC::Color::BrightYellow
    );

    FC::Console::NewLine(2);

    std::string name = FC::Console::Input("Enter user: ");

    FC::Console::PrintLn(
        "Hello, " + name + "!",
        FC::Color::BrightGreen
    );

    FC::Console::Separator(
        '-',
        45,
        FC::Color::BrightBlue
    );

    FC::Console::Pause("Press enter to exit...");

    FC::Console::ResetConsole();

    return 0;
}
```

### How it works

The application starts by preparing the console and displaying a welcome section. It then demonstrates different text colours, formatting styles, and RGB colours.

Next, it runs loading animations before displaying a progress bar. Once the progress reaches 100%, a table is printed to show example library features and their statuses.

Finally, the typing animation displays a greeting, the program asks the user for their name, and it prints a personalised response before exiting.

This is just one example of what you can build with FC Console. You can combine these functions in your own projects to create colourful menus, loading screens, status displays, interactive tools, and much more.

If you need any help let me know at @fade1079
