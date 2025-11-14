#ifndef TERM_SNAKE_TERMINAL_H
#define TERM_SNAKE_TERMINAL_H

// Initialize raw mode and non-block char-read from keyboard
// RETURNS: the termios attributes of the old terminal
struct termios init_term();

// Handle the keypresses from the terminal and return the respective directional code to the key pressed
// Up key: 1
// Right key: 2
// Down key: 3
// Left key: 4
// No key: 0
// Quit key: -1
int handle_keypress();

// Ensures a clean exit of the game and restoring old terminal settings
void clean_exit(struct termios term);

// Prints a character at the specified coordinate
void print_coord(int row, int col, char c);

void print_border(int width, int height);

void game_over_anim(int score);

#endif // TERM_SNAKE_TERMINAL_H
