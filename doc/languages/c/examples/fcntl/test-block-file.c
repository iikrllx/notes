int main()
{
	/* Открывает существующий файл */
	const char *file_path = "/tmp/f";
	int fd = open(file_path, O_RDWR);
	if (fd == -1) {
		perror("Ошибка открытия файла");
		return 1;
	}

	struct flock lock;
	memset(&lock, 0, sizeof(lock));

	if (fcntl(fd, F_GETLK, &lock) == -1) {
		perror("Ошибка выполнения fcntl");
		close(fd);
		return 1;
	}

	if (lock.l_type == F_UNLCK)
		printf("Файл '%s' не заблокирован\n", file_path);

	if (lock.l_type == F_WRLCK)
	{
		// Успешно для /tmp/f
		printf("Файл '%s' заблокирован на запись, PID: %d\n", file_path, lock.l_pid);
		exit(1);
	}

	/* Если не сделать exit(1) Запись write сработает
	   Если заблокирован, нужно делать exit(1) и не писать туда */
	write(fd, "hello", 5);

	close(fd);

	return 0;
}
