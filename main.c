#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "snake.h"
#include "terminal.h"

#define DRAW_FRAME 5
#define SLEEP_TIME 20000
#define MIN_X 1
#define MIN_Y 1
#define GAME_OVER_ANIM_DELAY 1500000

int main(int argc, char *argv[]) {\
	int width;
	int height;
	if (argc == 1) {
		width = 32;
		height = 32;
	} else if (argc == 3) {
		width = (int) strtol(argv[1], nullptr, 10);
		height = (int) strtol(argv[2], nullptr, 10);
	} else {
		printf("Usage: snake [width] [height]\n");
		exit(1);
	}

	bool game_over_flag = false;

	int score = 0;

	struct termios oldattr = init_term();
	int frame = 0;
	int directional_code = 1;
	int temp_dir_code = 1;
	struct segment* tailptr = malloc(sizeof(struct segment));
	init_snake(tailptr, width, height);
	struct segment* headptr = tailptr;
	struct apple apple = rand_apple(width, height);

	srand(time(NULL));

	for (;;) {
		int new_dir = handle_keypress();
		if (new_dir != 0  && (directional_code-2 != new_dir && directional_code+2 != new_dir)) {
			temp_dir_code = new_dir;
		}
		if (new_dir == -1) {
			break;
		}

		if (frame == DRAW_FRAME) {
			directional_code = temp_dir_code;

			system("clear");
			print_border(width, height);
			headptr = create_head(headptr, directional_code);

			if (headptr->x > width || headptr->y > height || headptr->x < MIN_X || headptr->y < MIN_Y) {
				game_over_flag = true;
			}
			if (check_collision(tailptr, headptr)) {
				game_over_flag = true;
			}

			if (headptr->x != apple.x || headptr->y != apple.y) {
				tailptr = delete_tail(tailptr);
				print_coord(apple.y, apple.x, '*');
			} else {
				apple = rand_apple(width, height);
				score++;
			}

			draw_snake(tailptr);
			print_coord(height+2, 0, 0);
			printf("Score: %d", score);
			frame = 0;
			fflush(stdout);

			if (game_over_flag) {
				game_over_anim(score);
				usleep(GAME_OVER_ANIM_DELAY);
				break;
			}
		}

		frame++;
		usleep(SLEEP_TIME);
	}

	clean_exit(oldattr);

	return 0;
}
