#include "terminal.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define ESCAPE_KEY 27
#define SEQ_START 91
#define UP_CHAR 'A'
#define DOWN_CHAR 'B'
#define RIGHT_CHAR 'C'
#define LEFT_CHAR 'D'
#define QUIT_CHAR 'q'

#define SLEEP_TIME 20000

// Initialize raw mode and non-block char-read from keyboard
// RETURNS: the termios attributes of the old terminal
struct termios init_term() {
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	system("tput smcup");
	return oldattr;
}

// Handle the keypresses from the terminal and return the respective directional code to the key pressed
// Up key: 1
// Right key: 2
// Down key: 3
// Left key: 4
// No key: 0
// Quit key: -1
int handle_keypress() {
	char keypress;
	ssize_t bytes = read(STDIN_FILENO, &keypress, 1);
	if (bytes == 0 || bytes == -1) {return 0;}

	if (keypress == ESCAPE_KEY) {
		char seq[2];
		read(STDIN_FILENO, seq, 2);
		if (seq[0] == SEQ_START) {
			switch (seq[1]) {
			case UP_CHAR: return 1;
			case DOWN_CHAR: return 3;
			case RIGHT_CHAR: return 2;
			case LEFT_CHAR: return 4;
			default: return 0;
			}
		}
	}

	if (keypress == QUIT_CHAR) {
		return -1;
	}

	return 0;
}

// Ensures a clean exit of the game and restoring old terminal settings
void clean_exit(struct termios oldattr) {
	system("clear");
	system("tput rmcup");
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}

// Draws the next frame of the game
void draw_next_frame() {
	fflush(stdout);
	usleep(SLEEP_TIME);
	system("clear");
}