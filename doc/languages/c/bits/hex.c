int main(void)
{
	unsigned char a = 0x64;
	int b = 0xFAFA;

	printf("value of a: %X [%x]\n", a, a);
	printf("value of b: %X [%x]\n", b, b);

	// %x / %X выводит hex числа, X - uppercase, x - lowercase

	/* Пример hex to unsigned long */
	char *s = "0x83";
	char *endptr;
	unsigned long hex;

	// hex to unsigned long 0x83 -> 131
	// 0x83 hex / 131 dec
	hex = strtoul(s, &endptr, 16);

	if (*endptr != '\0')
		abort();

	/* 131 */
	printf("%d\n", hex);

	//char str[] = "12345";
	//unsigned long result = strtoul(str, NULL, 10);
	//12345

	return 0;
}
