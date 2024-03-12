int main()
{
	int fd;
	struct flock lock;

	/*
	struct flock {
		// Тип блокировки: F_RDLCK (чтение), F_WRLCK (запись), F_UNLCK (разблокировать)
		short l_type;

		// Как интерпретируется поле 'l_start': SEEK_SET, SEEK_CUR, SEEK_END
		short l_whence;

		// Начало блокировки (сдвиг)
		off_t l_start;

		// Количество блокируемых байтов; 0 означает «до конца файла»
		off_t l_len;

		// Процесс, не дающий нам установить блокировку (только для F_GETLK)
		pid_t l_pid;
	};
	*/

	// Открытие файла для чтения и записи + создает если нет
	fd = open("/tmp/f", O_RDWR | O_CREAT);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	// Инициализация структуры блокировки
	lock.l_type = F_WRLCK;    // Блокировка записи
	lock.l_whence = SEEK_SET; // От начала файла
	lock.l_start = 0;         // Начало блокировки
	lock.l_len = 0;           // 0 означает, что блокируется весь файл

	// Попытка установить блокировку записи на файл
	if (fcntl(fd, F_SETLK, &lock) == -1) {
		perror("fcntl");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// Теперь файл заблокирован для записи другими процессами
	printf("File is locked.\n");

	// Можно запустить другую программу и проверить флаги файла /tmp/f
	sleep(200);

	/*
	// Снятие блокировки
	lock.l_type = F_UNLCK;
	if (fcntl(fd, F_SETLK, &lock) == -1) {
		perror("Ошибка при попытке снять блокировку");
		close(fd);
		exit(EXIT_FAILURE);
	}

	printf("Блокировка снята.\n"); */

	close(fd);

	/*
	Это пример необязательной блокировки.
	А есть строгая блокировка, которую можно релизовать если
	включить с помощью mand атрибута при монтировании ФС.
	Тогда чужие процессы не смогут писать в заблокированные файлы */

	return 0;
}
