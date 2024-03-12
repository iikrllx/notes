int main(void)
{
	int flags, fd;

	fd = open("/tmp/fff", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) abort();

	flags = fcntl(fd, F_GETFL);
	if (flags == -1) abort();

	if (flags & O_RDWR)
		puts("O_RDWR");

	/*
	С помощью fcntl получает флаги файла
	Функция `fcntl(fd, F_GETFL)` возвращает флаги, которые применяются к
	файловому дескриптору во время операций ввода-вывода, такие как `O_RDWR`,
	`O_APPEND`, `O_NONBLOCK` и другие, но для `O_CREAT` проверка не сработает.
	*/

	/* Можно установить новый флаг */
	flags |= O_APPEND;
	if (fcntl(fd, F_SETFL, flags) == -1)
		abort();

	if (flags & O_APPEND)
		puts("O_APPEND");

	unlink("/tmp/fff");
	close(fd);

	return 0;
}
