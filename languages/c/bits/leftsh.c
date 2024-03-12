int main(void)
{
	unsigned int flag = 0;

	for (unsigned int i = 0; i < 41; i++)
	{
		flag |= (1 << i);
		printf("%d:%d\n", i, flag);
	}

	/*
		Можно заметить, что на 31 начинается -1
		мы задаем больше 32 бит, поэтому так
		а unsigned int это 32 бит (4 байта)
		Переваливает за число:
		10000000000000000000000000000000

		Чтобы не получать -1, можно воспользоваться %u
		printf("%d:%u\n", i, flag); */

	unsigned long xflag = 0;
	for (unsigned int i = 0; i < 41; i++)
	{
		xflag |= (1UL << i);
		printf("%d:%lu\n", i, xflag);
	}

	/*
		Здесь xflag будет иметь больше значений, чем flag
		Дойдет до 40:2199023255551
		В printf длинные числа выводятся %lu / %ld / %llu / %lld
		unsigned long не везде имеет 8 байт, в таких случаях можно
		использовать uint64_t */

	return 0;
}
