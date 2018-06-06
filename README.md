
# Description
The algorithm is a do-while loop until no more coroutines are not done yet
it is a round-robin scheduler.
Duff's device is used to inline the do-while and the for loop within the switch cases, so if
longjmp from children coroutines (i.e. do_stuff1 and do_stuff2) to this function, the switch will continue from case 1


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

	*COROUTINE_START*
	for (; i < 100; ++i) {
		printf("%d ", i);

		*COROUTINE_PREEMPT*
	}
	*COROUTINE_END*
}
```