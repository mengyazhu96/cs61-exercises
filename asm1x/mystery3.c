int op1(int arg1, int arg2) {
	return ~(arg1 & arg2);
}

int op2(int arg1, int arg2) {
	return ~arg1 | arg2;
}

int mystery3(void) {
	const char* msg = "It worked!";
	return 4;
}