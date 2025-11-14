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

void init_snake(struct segment* tail, int width, int height);

struct segment* create_head(struct segment* head, int directional_code);

void draw_snake(struct segment* tail);

struct segment* delete_tail(struct segment* tail);

struct apple rand_apple(int width, int height);

bool check_collision(struct segment* tail, struct segment* head);

#endif // TERM_SNAKE_SNAKE_H
