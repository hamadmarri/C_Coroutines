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

int main() {

	initializeCoroutines();

	addCoroutine(&do_stuff1, NULL);
	
	void* args[] = {"$$$$$", (void*) 6};
	addCoroutine(&print_my_name, args);

	addCoroutine(&do_stuff2, NULL);

	void* args2[] = {"####", (void*) 11};
	addCoroutine(&print_my_name2, args2);

	void *args3[10][3];

	for (long i = 0; i < 10; ++i) {
		char *is = (char*) malloc(3);
		snprintf (is, sizeof(is), "%ld", i);

		args3[i][0] = is; // print id
		args3[i][1] = (void*) 0; // counter
		args3[i][2] = (void*) 11; // times

		addCoroutine(&multipule_calls, args3[i]);
	}

	startCoroutines();

	return 0;
}