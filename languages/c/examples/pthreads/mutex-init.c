// Глобальный мьютекс
pthread_mutex_t lock;

void* do_work(void* arg) {
	// Блокировка мьютекса
	pthread_mutex_lock(&lock);

	// Критическая секция - это участок кода в многопоточной программе,
	// где происходит доступ к общим ресурсам (например, переменным, файлам, базам данных и т.д.),
	// который должен быть выполнен только одним потоком в один и тот же момент времени.

	// Критическая секция начало
	printf("Поток %ld занял мьютекс\n", (long)pthread_self());
	// Симулируем работу в критической секции
	sleep(1);
	printf("Поток %ld освободил мьютекс\n", (long)pthread_self());
	// Критическая секция конец

	// Разблокировка мьютекса
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main() {
	pthread_t thread1, thread2;

	/*
	Функция `pthread_mutex_init` используется для инициализации мьютекса перед его
	использованием в программе. Мьютекс - это механизм синхронизации, который используется
	для контроля доступа к общим ресурсам в многопоточных приложениях, чтобы предотвратить
	возникновение гонок за ресурсы (race conditions) и обеспечить корректную работу при
	параллельной обработке данных.

	Инициализация мьютекса необходима для установки начальных параметров мьютекса,
	таких как его тип и атрибуты. Это гарантирует, что мьютекс находится в правильном
	и стабильном состоянии перед использованием.
	*/

	// Инициализация мьютекса
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("Ошибка инициализации мьютекса\n");
		return 1;
	}

	// Создание потоков
	pthread_create(&thread1, NULL, &do_work, NULL);
	pthread_create(&thread2, NULL, &do_work, NULL);

	// Ожидание завершения потоков
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Уничтожение мьютекса
	pthread_mutex_destroy(&lock);

	return 0;
}
