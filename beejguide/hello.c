/*Hello world program*/

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	bool x = true;
	if (x) {
		printf("x is true! \n");
	}
	int a = 9999;
	printf("%zu\n", sizeof a);
	printf("%zu\n", sizeof(2 + 7));
	printf("%zu\n", sizeof 3.14);
	int i = 2; // signed integers
	float f = 3.14; // signed floating point numbers
	char *s = "Hello World!"; // char* (char pointer) is the string type
	printf("Hello world\n"); // imma comment
	printf("%s i = %d and f = %f!\n", s, i, f);

	int z = 10;
	printf("z is %d\n", z);
	int *p = &z; // do we need a pointer to pass a pointer to a fxn?
	printf("z is %d\n", *p);
	printf("address of z is %p\n", (void *)&i);

	int q[5] = {1,2,3,4};
	for (int i; i<5; i++) {
		printf("Value in array a is: %d at index: %d", q[i], i);
	}
}
