#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "coroutines.c"
#include "functions.c"

/*
Author: Hamad Al Marri
Credits: https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html 
by Simon Tatham
*/


void callbackFib(long *f) {
	printf("callbackFib:\t\t%ld\n", *f);
}

int main() {

	initializeCoroutines();

	addCoroutine(&print_numbers, NULL);
	
	addCoroutine(&print_letters, NULL);

	void* args[] = {COROUTINE_ARG "$$$$$", COROUTINE_ARG 6};
	addCoroutine(&print_args1, args);

	void* args2[] = {COROUTINE_ARG "####", COROUTINE_ARG 11};
	addCoroutine(&print_args2, args2);

	void *args3[5][3];

	for (long i = 0; i < 5; ++i) {
		char *is = (char*) malloc(3);
		snprintf (is, sizeof(is), "%ld", i);

		args3[i][0] = COROUTINE_ARG is; 	// name
		args3[i][1] = COROUTINE_ARG 0; 		// i
		args3[i][2] = COROUTINE_ARG 10; 	// times

		addCoroutine(&multipule_copies, args3[i]);
	}


	void* args4[] = {
		COROUTINE_ARG 0,				// i
		COROUTINE_ARG 0,				// a
		COROUTINE_ARG 1,				// b
		COROUTINE_ARG 20, 				// size
		COROUTINE_ARG &callbackFib,		// callback function
	};


	addCoroutine(&fib, args4);

	startCoroutines();

	return 0;
}