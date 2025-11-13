#include "snake.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct segment init_snake(struct segment tail) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	tail.x = w.ws_col/2;
	tail.y = w.ws_row/2;
	tail.next = nullptr;
	return tail;
}
