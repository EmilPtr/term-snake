#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "snake.h"
#include "terminal.h"

#define DRAW_FRAME 5
#define SLEEP_TIME 20000


int main() {
	printf(getenv("LINES") ? "\n" : "");
	struct termios oldattr = init_term();
	int frame = 0;
	int directional_code = 1;
	struct segment* tailptr = malloc(sizeof(struct segment));
	struct segment tail = *tailptr;
	tail = init_snake(tail);

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
			printf("The directional code is: %d", directional_code);
			switch (directional_code) {
				case 1: tail.y-=1; break;
				case 2: tail.x+=1; break;
				case 3: tail.y+=1; break;
				case 4: tail.x-=1; break;
				default:;
			}
			print_coord(tail.y, tail.x, 'O');
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
