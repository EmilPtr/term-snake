#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "snake.h"
#include "terminal.h"

#define DRAW_FRAME 5
#define SLEEP_TIME 20000
#define SIZE = 20


int main() {
	struct termios oldattr = init_term();
	int frame = 0;
	int directional_code = 1;
	struct segment* tailptr = malloc(sizeof(struct segment));
	init_snake(tailptr);
	struct segment* headptr = tailptr;
	struct apple apple = rand_apple();

	srand(time(NULL));

	for (;;) {
		int new_dir = handle_keypress();
		if (new_dir != 0) {
			directional_code = new_dir;
		}
		if (new_dir == -1) {
			break;
		}

		if (frame == DRAW_FRAME) {
			system("clear");
			headptr = create_head(headptr, directional_code);
			if (headptr->x != apple.x || headptr->y != apple.y) {
				tailptr = delete_tail(tailptr);
				print_coord(apple.y, apple.x, '#');
			} else {
				apple = rand_apple();
			}
			draw_snake(tailptr);
			print_coord(0, 0, 0);
			frame = 0;
			fflush(stdout);
		}
		frame++;

		usleep(SLEEP_TIME);
	}

	clean_exit(oldattr);

	return 0;
}
