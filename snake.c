#include "snake.h"

struct segment {
	int x;
	int y;
	struct segment *next;
};