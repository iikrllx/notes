// Обработчик сигнала
void signal_handler(int sig) {
	printf("Получен сигнал %d\n", sig);
}

// Функция потока
void *thread_func(void *arg) {
	// Устанавливаем обработчик сигнала SIGUSR1
	signal(SIGUSR1, signal_handler);

	// Цикл, чтобы поток был занят и мог получить сигнал
	while (1) {
		printf("Поток работает...\n");
		sleep(1); // Пауза, чтобы не загружать CPU
	}
	return NULL;
}

int main() {
	pthread_t thread_id;
	// Создаем поток
	if (pthread_create(&thread_id, NULL, thread_func, NULL) != 0) {
		perror("Не удалось создать поток");
		return 1;
	}

	// Даем время потоку начать выполнение
	sleep(2);

	// Отправляем сигнал SIGUSR1 потоку
	if (pthread_kill(thread_id, SIGUSR1) != 0) {
		perror("Не удалось отправить сигнал");
		return 2;
	}

	// Ждем завершения потока (в данном примере поток не завершится сам,
	// так как у нас бесконечный цикл в функции потока)
	pthread_join(thread_id, NULL);

	return 0;
}
