#include <stdio.h>
struct x {
	int f1;
	short f2;
	char f3;
};

void output_func(struct x *arg1) {
	printf("%d\n", arg1->f1);
	printf("%c\n", arg1->f2);
	printf("%c\n", arg1->f3);
}
