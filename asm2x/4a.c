#include <stdio.h>
union x {
	char u1;
	int u2;
	int u3;
};

void output_func(union x *arg1) {
	printf("%c\n", arg1->u1);
	printf("%d\n", arg1->u2);
	printf("%d\n", arg1->u3);
}
