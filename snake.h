#ifndef TERM_SNAKE_SNAKE_H
#define TERM_SNAKE_SNAKE_H

struct segment {
	int x;
	int y;
	struct segment *next;
};

struct segment init_snake(struct segment tail);

#endif // TERM_SNAKE_SNAKE_H
