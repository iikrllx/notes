int main(void)
{
	/* ENOMEM 12 Cannot allocate memory */
	/* Может случится Heap Overflow, запросили памяти больше чем есть на самом деле */
	unsigned long n = 1024 * 1024 * 1024 * 32ul;
	printf("%lu\n", n);
	void *p = malloc(n);
	printf("%d\n", errno);
	if (!p) abort();

	return 0;
}
