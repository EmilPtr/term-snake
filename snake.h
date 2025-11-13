#ifndef TERM_SNAKE_SNAKE_H
#define TERM_SNAKE_SNAKE_H

struct segment {
	int x;
	int y;
	struct segment *next;
};

struct apple {
	int x;
	int y;
};

void init_snake(struct segment* tail);

struct segment* create_head(struct segment* head, int directional_code);

void draw_snake(struct segment* tail);

struct segment* delete_tail(struct segment* tail);

struct apple rand_apple();

#endif // TERM_SNAKE_SNAKE_H
