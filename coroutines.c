
#define MAX_COROUTINES 4
#define MAX_NUM_OF_ITERATIONS 5
#define true 1
#define false 0


#define COROUTINE_START int r = setjmp(here->thread);\
	switch (r) {\
		case 0:
		

#define COROUTINE_PREEMPT if (--here->num_of_iterations == 0) {\
		here->num_of_iterations = MAX_NUM_OF_ITERATIONS;\
		longjmp(manager->thread, 1);\
		case 1:;\
	}

#define COROUTINE_END }\
			here->done = true;


static int index = 0;
static int num_of_coroutines = 0;

struct Coroutine {
	jmp_buf thread;
	void (*ptrFun)();
	int started;
	int done;
	int num_of_iterations;
};

struct Coroutine coroutines[MAX_COROUTINES];
struct Coroutine *manager = NULL;
struct Coroutine *here = NULL;

void initializeCoroutines() {
	for (int i = 0; i < MAX_COROUTINES; ++i) {
		coroutines[i].ptrFun = NULL;
		coroutines[i].started = false;
		coroutines[i].done = true;
		coroutines[i].num_of_iterations = MAX_NUM_OF_ITERATIONS;
	}

	// startCoroutine is first coroutine
	num_of_coroutines = 1;
	manager = &(coroutines[0]);
}

void addCoroutine(void (*ptrFun)()) {
	if (index + 1 < MAX_COROUTINES) {
		coroutines[++index].ptrFun = ptrFun;
		coroutines[index].done = false;
		num_of_coroutines++;
	}
}


void startCoroutine() {

	int r = setjmp(coroutines[0].thread);

	switch (r) {
		case 0:
		do {
			coroutines[0].done = true;
			for (int i = 1; i < num_of_coroutines; ++i) {
				if (!coroutines[i].done) {
					coroutines[0].done = false;
					here = &(coroutines[i]);
					if (!coroutines[i].started) {
						coroutines[i].started = true;
						(*coroutines[i].ptrFun)();
					} else {
						longjmp(coroutines[i].thread, 1);
						case 1:;
					}
				}
			}

		} while (!coroutines[0].done);
	}
}

