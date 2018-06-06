
# Description
The algorithm is a do-while loop until no more coroutines are not done yet
it is a round-robin scheduler.
Duff's device is used to inline the do-while and the for loop within the switch cases, so if
longjmp from children coroutines (i.e. do_stuff1 and do_stuff2) to this function, the switch will continue from case 1

I am using a struct that holds coroutines informations
```C
/*
	 Coroutine structure that is used to hold running coroutines
	 	jmp_buf thread: is jmp buffer that saves the jmp context of each coroutine
	 	void (*ptrFun)(): is a pointer to function, it is used at first time to call the function, after that longjmp is used
	 	int started: used to check if not started yet, call the function, if already started call longjmp
	 	int done: if the coroutine is done or not
	 	int num_of_iterations: 	number of iterations or "time" that is given to the coroutine before release to other
	 							coroutines (can be removed and be global if needed)
	 							the current approach is useful for varying each coroutine iterations separately
	 	int yield: if the function need to return values from time to time (or yields) then this field can be used
*/
struct Coroutine {
	jmp_buf thread;
	void (*ptrFun)();
	int started;
	int done;
	int num_of_iterations;
	// int yield;
};
```

# How to compile
`gcc -std=c11 main.c`


# Basic usage
If you want to implement a for loop such as
```C
void coroutine_function() {
	int i = 0;
	for (; i < 100; ++i) {
		printf("%d ", i);
	}
}
```

Then add these changes (COROUTINE_START, COROUTINE_PREEMPT, COROUTINE_END, and make sure to make variables needed to preserve their values to static variables)
```C
void coroutine_function() {
	static int i = 0;

	COROUTINE_START
	for (; i < 100; ++i) {
		printf("%d ", i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}
```


# Some values to adjust 
// maximum number of coroutines
#define MAX_COROUTINES 4

// number of iterations or "time" that is given to each coroutine before release to other coroutines
#define MAX_NUM_OF_ITERATIONS 5


# Credits
https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html 

by Simon Tatham
