/* Пример простой рекурсии

Рекурсия ? Пример: Матрешка
Глубина рекурсии
Прямой ход и обратный ход рекурсии, есть какой-то результат,
происходит return к самому верхнему уровню рекурсии.
*/

void m(int n)
{
	if (n == 1)
	{
		printf("Last: %d\n", n);
		return;
	}
	else
	{
		printf("Top: %d\n", n);
		m(n - 1);
		printf("Bottom: %d\n", n);
	}

}

int main(int argc, char *argv[])
{
	m(7);

	return 0;
}
