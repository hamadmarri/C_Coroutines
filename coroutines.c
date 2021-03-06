#include <setjmp.h>

// maximum number of coroutines
#define MAX_COROUTINES 100

// number of iterations or "time" that is given to each coroutine before release to other coroutines
#define MAX_NUM_OF_ITERATIONS 4

#define true 1
#define false 0


// each coroutine function (with no args) must use start macro to setjmp
#define COROUTINE_START int r = setjmp(here->thread);\
switch (r) {\
	case 0:


// each coroutine function (with args) must use COROUTINE_LOAD_ARGS macro to setjmp and then load args
#define COROUTINE_LOAD_ARGS int r = setjmp(here->thread);


// each coroutine function (with args) must use COROUTINE_START_WITH_ARGS macro to start switch
#define COROUTINE_START_WITH_ARGS switch (r) {\
	case 0:


// each coroutine function must use preempt macro to go back to manager coroutine, which is the startCoroutines() function
#define COROUTINE_PREEMPT if (--here->num_of_iterations == 0) {\
	here->num_of_iterations = MAX_NUM_OF_ITERATIONS;\
	longjmp(manager->thread, 1);\
}\
case 1:;

// if the coroutine is done must use this macro at the end of the function to mark itself as done
#define COROUTINE_END }\
here->done = true;\
longjmp(manager->thread, 1);\
while(1); // for no return function


#define COROUTINE_FUNCTION __attribute__((noreturn))

#define COROUTINE_ARG (void*)


// index for adding coroutines
static int index = 0;

// number of added coroutines
static int num_of_coroutines = 0;


/*
	 Coroutine structure that is used to hold running coroutines
	 	jmp_buf thread: is jmp buffer that saves the jmp context of each coroutine
	 	void (*ptrFun)(): is a pointer to function, it is used at first time to call the function, after that longjmp is used
	 	int started: used to check if not started yet, call the function, if already started call longjmp
	 	int done: if the coroutine is done or not
	 	int num_of_iterations: 	number of iterations or "time" that is given to the coroutine before release to other
	 							coroutines (can be removed and be global if needed)
	 							the current approach is useful for varying each coroutine iterations separately
	 	void **args: generic array of (void*) type. Usage in main.c						
*/
struct Coroutine {
	jmp_buf thread;
	void (*ptrFun)();
	int started;
	int done;
	int num_of_iterations;
	void **args;
};

// array of coroutines ( +1 for the master coroutine)
static struct Coroutine coroutines[MAX_COROUTINES + 1];

// pointer to the first coroutine in the array, which is the manager coroutine (i.e. startCoroutines() function)
struct Coroutine *manager = NULL;

// will be set before calling/longjmping to each coroutine, so the coroutine can setjmp itself
struct Coroutine *here = NULL;



void initializeCoroutines() {
	// startCoroutines() is first coroutine
	num_of_coroutines = 1;
	manager = &(coroutines[0]);
}


void addCoroutine(void (*ptrFun)(), void* args[]) {
	if (index < MAX_COROUTINES) {
		coroutines[++index].ptrFun = ptrFun;
		coroutines[index].started = false;
		coroutines[index].done = false;
		coroutines[index].num_of_iterations = MAX_NUM_OF_ITERATIONS;
		coroutines[index].args = args;
		num_of_coroutines++;
	}
}


/*
	the algorithm is a do-while loop until no more coroutines are not done yet
	it is a round-robin scheduler.
	Duff's device is used to inline the do-while and the for loop within the switch cases, so if
	longjmp from children coroutines (i.e. do_stuff1 and do_stuff2) to this function, the switch will continue from case 1
*/
void startCoroutines() {

	volatile int i = 1;
	int r = setjmp(coroutines[0].thread);

	switch (r) {
		case 0:
		do {
			coroutines[0].done = true;
			for (i = 1; i < num_of_coroutines; ++i) {
				
				if (coroutines[i].done) 
					continue;

				coroutines[0].done = false;
				here = &(coroutines[i]);

				// if coroutine is not started yet, need to call the coroutine function first
				if (!coroutines[i].started) {
					coroutines[i].started = true; // mark it as started
					coroutines[i].ptrFun(); // calling the coroutine function
				} else {
					// if it is already started, means it has already setjmp, so will longjmp to it
					longjmp(coroutines[i].thread, 1);
					case 1:;
				}
			}

		} while (!coroutines[0].done);
	} // switch
}

