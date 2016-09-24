#include <stdio.h>
struct x {
	char f1[24];
	long f2;
	short f3;
};

void output_func(struct x *arg1) {
	printf("%s\n", arg1->f1);
	printf("%lu\n", arg1->f2);
	printf("%d\n", arg1->f3);
}
