#include <iostream>
#include <chrono>
#include <termios.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

int getch()
{
    // Declare an integer variable to store the character
    int ch;
    // Declare two structs to store the terminal attributes
    struct termios t_old, t_new;

    // Get the current terminal attributes and store in t_old
    tcgetattr(STDIN_FILENO, &t_old);
    // Copy the old attributes to the new struct
    t_new = t_old;
    // Modify the new struct to turn off canonical mode and echo
    t_new.c_lflag &= ~(ICANON | ECHO);
    // Apply the new attributes to the terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    // Read a single character from the standard input
    ch = getchar();

    // Re-apply the old terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    // Return the character that was read
    return ch;
}

int main()
{
    bool running = false;
    high_resolution_clock::time_point start;
    duration<double> elapsed;

    while (true)
    {
        int c = getch();
        if (c == 32) // space
        {
            if (!running)
            {
                cout << "Timer started." << endl;
                start = high_resolution_clock::now();
                running = true;
            }
            else
            {
                cout << "Timer stopped." << endl;
                elapsed = high_resolution_clock::now() - start;
                cout << "Elapsed time: " << elapsed.count() << " seconds." << endl;
                running = false;
            }
        }
    }

    return 0;
}