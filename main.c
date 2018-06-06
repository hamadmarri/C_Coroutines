#include <stdio.h>
#include <setjmp.h>
#include "coroutines.c"
#include "functions.c"

int main() {

	initializeCoroutines();
	addCoroutine(&do_stuff1);
	addCoroutine(&do_stuff2);
	startCoroutines();

	return 0;
}