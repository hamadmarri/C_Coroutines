

void do_stuff1() {
	static int i = 0;

	COROUTINE_START
	for (; i < 50; ++i) {
		printf("%d ", i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void do_stuff2() {
	static int i = 65;

	COROUTINE_START
	for (; i < 65 + 58; ++i) {
		if (i == 66 + 25)
			i += 6;

		printf("%c ", (char) i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void print_my_name() {
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
		printf("%s ", name);
		COROUTINE_PREEMPT		
	}
	COROUTINE_END
}


void print_my_name2() {
	// direct args casting
	static int i = 0;

	COROUTINE_START
	for (; i < (long) here->args[1]; ++i) {
		printf("%s ", (char*) here->args[0]);
		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void multipule_calls() {
	char *name;
	long *i;
	long times;

	COROUTINE_LOAD_ARGS
	name = (char*) here->args[0];
	i = (long*) &(here->args[1]);
	times = (long) here->args[2];

	COROUTINE_START_WITH_ARGS

	for (;*i < times; ++(*i)) {
		printf("(%s) ", name);
		COROUTINE_PREEMPT
	}

	COROUTINE_END
}