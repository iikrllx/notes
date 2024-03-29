static void *threadFunc(void *arg)
{
	char *s = (char *) arg;
	printf("%s", s);
	printf("ID of thread: %d\n", pthread_self());
	return (void *) strlen(s);
}

/*
Порядок вывода первых двух строчек зависит от того,
как планировщик распорядится двумя потоками
*/

int main(int argc, char **argv)
{
	pthread_t t1;
	void *res;
	int s;

	// Создание нового потока внутри текущего процесса
	// &t1 - id потока
	// NULL (атрибуты по умолчанию) - указатель на структуру pthread_attr_t (атрибуты потока)
	// threadFunc - указатель на функцию, которая будет выполнена в новом потоке
	// "Hello world\n" - аргумент, который будет передан в функцию
	s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
	// Возвращает 0 в случае успешного создания потока
	if (s != 0) abort();

	printf("Main thread id = %d\n", t1);

	// Позволяет проверить на тождественность два идентификатора потоков.
	if (pthread_equal(t1, pthread_self()))
		printf("tid matches self\n");

	// Сообщение из главного процесса
	printf("Message from main()\n");

	// pthread_join() для потоков, похожа на действие вызова waitpid() в контексте процессов
	// Ожидает завершения указанного потока в &res записывает результат выполнения потока
	// Можно передать NULL вместо &res, тогда результат не будет сохранен
	//
	// Потоки не имеют иерархии. Любой поток в процессе может воспользоваться функцией
	// pthread_join() для присоединения к другому (любому) потоку в том же процессе
	//
	// Если родительский процесс создал потомка с помощью fork(), он и только он может
	// ожидать этого потомка, используя вызов wait(). Между потоком, который вызывает
	// функцию pthread_create(), и потоком, который при этом создается, нет таких отношений
	s = pthread_join(t1, &res);
	if (s != 0) abort();

	printf("Thread returned %ld\n", (long) res);
	exit(EXIT_SUCCESS);

	return 0;
}
