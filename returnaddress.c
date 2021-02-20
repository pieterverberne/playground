#include <stdio.h>
#include <inttypes.h>
#include <string.h>

/* 
 * Demonstrate return address overwrite. function2() is never called yet it is executed.
 * Tested on Ubuntu 64 bit
 * gcc -fno-stack-protector -o returnaddress returnaddress.c && ./returnaddress
 */

int function2()
{
	printf("%s\n", __func__);
	int t = 3;
	int k = 5;
	printf("This should not be reached: %d\n", t + k);
}

int *fp = function2;

int function1()
{
	printf("%s\n", __func__);
	// Print return address
	void *addr = __builtin_extract_return_addr (__builtin_return_address (0));
	printf("Return address: %p\n", addr);

	long int j;
	printf("val = 0x%" PRIx64 "\n", *(&j + 3));
	memcpy(&j + 3, (void *)&fp, 8);
	printf("new = 0x%" PRIx64 "\n", *(&j + 3));
}


int main()
{
	printf("function2 pointer: %p\n", fp);
	printf("--\n");
	function1();
}

