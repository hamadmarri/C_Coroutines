

void print_numbers() {
	static int i = 0;

	COROUTINE_START
	for (; i < 50; ++i) {
		printf("print_numbers:\t\t%d\n", i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void print_letters() {
	static int i = 65;

	COROUTINE_START
	for (; i < 65 + 58; ++i) {
		if (i == 66 + 25)
			i += 6;

		printf("print_letters:\t\t%c\n", (char) i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void print_args1() {
	static int i = 0;
	char *name;
	long times;

	/*
		this approach looks nicer, but loading args in local veriables
		everytime might not be a good idea, print_my_name2 uses direct casting
	*/
	COROUTINE_LOAD_ARGS // reload args
	name = (char*) here->args[0];
	times = (long) here->args[1];

	COROUTINE_START_WITH_ARGS
	for (; i < times; ++i) {
		printf("print_args1:\t\t%s\n", name);
		COROUTINE_PREEMPT		
	}
	COROUTINE_END
}


void print_args2() {
	// direct args casting
	static int i = 0;

	COROUTINE_START
	for (; i < (long) here->args[1]; ++i) {
		printf("print_args2:\t\t%s\n", (char*) here->args[0]);
		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void multipule_copies() {
	char *name;
	long *i;
	long times;

	COROUTINE_LOAD_ARGS
	name = (char*) here->args[0];
	i = (long*) &(here->args[1]);
	times = (long) here->args[2];

	COROUTINE_START_WITH_ARGS

	for (;*i < times; ++(*i)) {
		printf("multipule_copies %s:\t%ld\n", name, *i);
		COROUTINE_PREEMPT
	}

	COROUTINE_END
}



void fib() {
	long *i;
	long *a;
	long *b;
	long c;
	long size;
	void (*ptrCallBack)(long*);

	COROUTINE_LOAD_ARGS
	i = (long*) &(here->args[0]);
	a = (long*) &(here->args[1]);
	b = (long*) &(here->args[2]);
	size = (long) here->args[3];
	ptrCallBack = (void (*)(long*)) (here->args[4]);

	COROUTINE_START_WITH_ARGS
	if (*i < size)
		ptrCallBack(i);

	if (++(*i) < size)
		ptrCallBack(i);

	for (*i = 2; *i < size; ++(*i)) {
		c = *b + *a;
		*a = *b;
		*b = c;
		ptrCallBack(&c);

		COROUTINE_PREEMPT
	}

	COROUTINE_END
}