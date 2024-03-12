static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
// Мьютекс представляет собой переменную типа pthread_mutex_t
//
// Когда один поток вызывает `pthread_mutex_lock` и успешно захватывает мьютекс,
// все другие потоки, которые попытаются захватить тот же самый мьютекс с помощью `pthread_mutex_lock`,
// будут заблокированы и ожидать, пока мьютекс не освободится. Это означает, что пока мьютекс
// заблокирован (или закрыт), захвативший его поток может безопасно изменять общие данные,
// к которым мьютекс предоставляет эксклюзивный доступ, без риска возникновения гонки за
// ресурсы или других проблем синхронизации.
// Как только поток, владеющий мьютексом, закончит работу с общими данными, он должен освободить
// мьютекс с помощью вызова `pthread_mutex_unlock`, чтобы другие потоки могли продолжить
// работу с теми же данными.

static void *threadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j, s;

	// После инициализации мьютекс находится в открытом состоянии.
	// Для его закрытия и открытия используются функции pthread_mutex_lock()
	// и pthread_mutex_unlock().

	// Предотвращает одновременное изменение общих данных
	for (j = 0; j < loops; j++) {
		s = pthread_mutex_lock(&mtx);
		if (s != 0) abort();

		loc = glob;
		loc++;
		glob = loc;

		s = pthread_mutex_unlock(&mtx);
		if (s != 0) abort();
	}

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t t1, t2;
	int loops, s;
	loops = 10000;

	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0) abort();

	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0) abort();

	s = pthread_join(t1, NULL);
	if (s != 0) abort();

	s = pthread_join(t2, NULL);
	if (s != 0) abort();

	printf("glob = %d\n", glob);
	exit(EXIT_SUCCESS);
}
