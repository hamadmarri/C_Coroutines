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

	addCoroutine(&do_stuff1, NULL);
	
	void* args[] = {"$$$$$", (void*) 6};
	addCoroutine(&print_my_name, args);

	addCoroutine(&do_stuff2, NULL);

	void* args2[] = {"####", (void*) 11};
	addCoroutine(&print_my_name2, args2);

	startCoroutines();

	return 0;
}