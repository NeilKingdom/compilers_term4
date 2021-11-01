/*
* File Name: cdatatypes.c
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa
* Course: CST8152 Compilers
* Lab: Lab 0
* Date: May 1, 2021
* Professor: Paulo Sousa
* Purpose: Create a list of data type sizes, test limits of short data type
* Function list: task1() - Prints a list of data types and their sizes
*				 task2() - Calculates and prints the last positive value for short and unsigned short
*				 task3() - Prints the last positive value of short when incrementing by 10000
*/

/* Single line comment */

#include <stdio.h>
#include <limits.h>
#include <stddef.h>

void task1(void);
void task2(void);
void task3(void);

/*
* Function Name: main
* Author: Paulo Sousa
* Course: CST8152 Compilers
* Lab: Lab 0
* Date: May 1, 2021
* Professor: Paulo Sousa
* Purpose: Create a sequence of tasks to evaluate datatypes.
*/
int main(void) {
	int code = 0;
	task1();
	task2();
	task3();
	return code;
}

/*
* Function Name: task1
* Author: Paulo Sousa
* Course: CST8152 Compilers
* Lab: Lab 0
* Date: May 1, 2021
* Professor: Paulo Sousa
* Purpose: Prints a list of data types and their sizes
*/
void task1(void) {
	printf("* TASK 1 *\n");
	printf("*************************************\n");
	printf("The size of type char is: %lu\n", sizeof(char));
	printf("The size of type short int is: %lu\n", sizeof(short));
	printf("The size of type int is: %lu\n", sizeof(int));
	printf("The size of type long int is: %lu\n", sizeof(long));
	printf("The size of type float is: %lu\n", sizeof(float));
	printf("The size of type double is: %lu\n", sizeof(double));
	printf("The size of type long double is: %lu\n", sizeof(long double));
	printf("The size of type unsigned char is: %lu\n", sizeof(unsigned char));
	printf("The size of type unsigned short int is: %lu\n", sizeof(unsigned short));
	printf("The size of type unsigned int is: %lu\n", sizeof(unsigned int));
	printf("The size of type unsigned long int is: %lu\n", sizeof(unsigned long));
	printf("The size of derived type size_t is: %lu\n", sizeof(size_t));
	printf("The size of derived type wchar_t is: %lu\n", sizeof(wchar_t));
	return;
}


/*
* Function Name: task2
* Author: Paulo Sousa
* Course: CST8152 Compilers
* Lab: Lab 0
* Date: May 1, 2021
* Professor: Paulo Sousa
* Purpose: Calculates and prints the last positive value for short and unsigned short
*/
void task2(void) {
	/* Signed values */
	int max_value = 1;
	int i;
	printf("* TASK 2 *\n");
	printf("*************************************\n");
	for (i = 0; i < sizeof(short) * 8 - 1; i++) {
		max_value *= 2;
	}
	max_value -= 1;
	printf("The last positive value is: %d\n", max_value);
	printf("SHRT_MAX = %d\n", SHRT_MAX);
	/* Unsigned values */
	max_value = 1;
	for (i = 0; i < sizeof(short) * 8; i++) {
		max_value *= 2;
	}
	max_value -= 1;
	printf("The last positive unsigned value is: %u\n", max_value);
	printf("USHRT_MAX = %d\n", USHRT_MAX);
	return;
}

/*
* Function Name: task3
* Author: Paulo Sousa
* Course: CST8152 Compilers
* Lab: Lab 0
* Date: May 1, 2021
* Professor: Paulo Sousa
* Purpose: Prints the last positive value of short when incrementing by 10000
*/
void task3(void) {
	short iov = 0;
	printf("* TASK 3 *\n");
	printf("*************************************\n");
	while (iov >= 0) {
		iov += 10000;
		printf("iov: %d\n", iov);
	}
	iov -= 10000;
	printf("The last positive value is: %d\n", iov);
	/* printf("The last positive value is: %d\n", (short)(iov-10000)); */
	return;
}
