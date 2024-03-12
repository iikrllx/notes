int main(int argc, char **argv, char **envp)
{
	/* Number to string */
	int n = 123;
	char buf[32];
	sprintf(buf, "Number is %d", n);
	printf("%s\n", buf); // Number is 123

	char *s = "geeksforgeeks";
	snprintf(buf, 6, "%s\n", s);
	printf("%s\n", buf); // geeks

	/*
	#define _GNU_SOURCE
	#include <stdio.h>
	*/

	char *buffer;
	int r;

	r = asprintf(&buffer, "The total is %d\n", 5 + 8);

	printf("%s", buffer);
	free(buffer);

	/* Числа от 0 до 9 будут выглядеть как 00 / 01 / 02 и т.д ...
	   А числа выше 9 будут выглядеть как обычно */
	char hex[7];
	sprintf(hex, "%02X%02X%02X", 1, 2, 3);

	return 0;
}
