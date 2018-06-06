

void do_stuff1() {
	static int i = 0;

	COROUTINE_START
	for (; i < 100; ++i) {
		printf("%d ", i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}


void do_stuff2() {
	static int i = 0;

	COROUTINE_START
	for (; i < 100; ++i) {
		printf("-%d ", i);

		COROUTINE_PREEMPT
	}
	COROUTINE_END
}