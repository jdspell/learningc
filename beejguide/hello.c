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
}
