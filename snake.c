#include "snake.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "terminal.h"

void init_snake(struct segment* tail) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	tail->x = w.ws_col/2;
	tail->y = w.ws_row/2;
	tail->next = nullptr;
}

struct segment* create_head(struct segment* head, int directional_code) {
	head->next = malloc(sizeof(struct segment));
	int oldx = head->x;
	int oldy = head->y;
	head=head->next;
	head->next = nullptr;

	switch(directional_code) {
		case 1:
			head->x = oldx;
			head->y = oldy-1;
			break;
		case 2:
			head->x = oldx+1;
			head->y = oldy;
			break;
		case 3:
			head->x = oldx;
			head->y = oldy+1;
			break;
		case 4:
			head->x = oldx-1;
			head->y = oldy;
			break;
		default:;
	}

	return head;
}

void draw_snake(struct segment* tail) {
	struct segment* seg = tail;
	print_coord(seg->y, seg->x, '#');
	if (seg->next == nullptr) return;
	do {
		seg = seg->next;
		print_coord(seg->y, seg->x, '#');
	} while (seg->next != nullptr);
}

struct segment* delete_tail(struct segment* tail) {
	struct segment* seg = tail;
	seg = seg->next;
	free(tail);
	return seg;
}

struct apple rand_apple() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	struct apple new_apple = {
		.x = (rand() % (w.ws_col + 1)),
		.y = (rand() % (w.ws_row + 1))
	};
	return new_apple;
}