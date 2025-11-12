#include <stdio.h>
#include <termios.h>
#include "terminal.h"

#define DRAW_FRAME 10

int main() {
	struct termios oldattr = init_term();
	int frame = 0;
	int directional_code = 1;

	for (;;) {
		int new_dir = handle_keypress();
		if (new_dir != 0) {
			directional_code = new_dir;
		}
		if (new_dir == -1) {
			break;
		}

		if (frame == DRAW_FRAME) {
			printf("The directional code is: %d", directional_code);
			draw_next_frame();
			frame = 0;
		}
		frame++;
	}

	clean_exit(oldattr);

	return 0;
}
