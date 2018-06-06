#include <stdio.h>
#include <setjmp.h>
#include "coroutines.c"
#include "functions.c"

/*
Author: Hamad Al Marri
Credits: https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html 
by Simon Tatham
*/

int main() {

	initializeCoroutines();
	addCoroutine(&do_stuff1);
	addCoroutine(&do_stuff2);
	startCoroutines();

	return 0;
}