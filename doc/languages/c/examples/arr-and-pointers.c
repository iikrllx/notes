int bbb(char *s)
{ // strlen
  char *p = s;
  while (*p != '\0') { // Можно опустить '\0' и написать просто *p
    p++; // Начиная с h идет продвижение указателя дальше
  }

  // Вычитается разница адресов
  // 0x555555556009 - 0x555555556004 = 5
  // Нет смысла вычитать или сравнивать указатели абсолютно разных адресов
  return p - s;
}

// В описании функции можно массив представить
// как int a[] или int *a
void t(int *a)
{
  printf("%d\n", a[5]);
}

void test_func(int *a, int *b)
{
  // В этой функции принимаются эти адреса
  // 0x7fffffffdfb8 и 0x7fffffffdfbc
  // И изменяется их значение с помощью указателей
  *a = 8;
  *b = 9;
}

int main(void)
{
  int x = 2;
  int *n = &x; // Указателю n присваивается адрес ячейки переменной x
  // print n -> адрес
  // print *n -> значение

  *n = 5; // Означает, что переменная x теперь будет равна 5

  int a, b; // Локальные переменные функции main
  // Допустим у этих переменных адреса 0x7fffffffdfb8 и 0x7fffffffdfbc
  test_func(&a, &b);

  // Указатели и массивы тесно связаны друг с другом
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Объявлен массив, блок из 10 объектов
  int *pa; // Объявлен указатель
  pa = &arr[0]; // Указатель ссылается на 0 объект массива arr
  *pa = 5; // Теперь arr[0] равен 5

  // Если pa указывает на 0 элемент, то pa + 1, будет указывать
  // на следующий, пример:
  *(pa + 1); // Указывает на значение arr[1], переход на следующее значение
  pa + 1;    // Возвращает адрес arr[1], тот же адрес выдаст &arr[1], переход на следующий адрес массива

  int *np;
  np = &arr[5];
  // Теперь проверим тоже самое, только с декрементом
  *(np - 1); // Та же логика что и выше, только на позицию меньше
  np - 1;

  // Поскольку имя массива является расположением его начального элемента
  // Можно заменить pa = &arr[0] на pa = arr
  int *q = arr; // Теперь q ссылается на первый индекс массива arr и имеет значение 5

  // Важно понимать что записи pa[1] и *(pa + 1) эквивалентны (pa в этом случае указатель)
  // А здесь записи &arr[1] и arr + 1 тоже эквивалентны (arr в этом случае массив)
  // print *arr выдаст первое значение под 0 индексом и print arr[0] сделает тоже самое
  //
  // pa[1 - 2];
  // *(pa - 1 - 2);
  //

  // Передается массив
  t(arr);

  // Обращение типа arr[-1] arr[-2] обращаются к элементам перед arr[0]
  // Выходят за границу массива

  // Выражение типа pa += 1 делает инкремент на следующий адрес и присваивает этот адрес
  // указателю pa, идет так же присвоение
  // Выражение типа *pa += 1 делает инкремент на 1 значение указателя pa
  // и присваивает это новое значение указателю pa

  // С указателями можно проводить операции == != > < и т.д
  // (pa > np) ? puts("y") : puts("n");
  // printf("%d", *pa + *np);

  printf("%d\n", bbb("hello"));

  // Например функцию printf работает с символьными строками
  // printf("Hello"); Здесь printf получает указатель на начало массива символов

  /*
	В чем разница ?
	char a[] = "hello";
	char *b = "hello";

	// Адрес не меняется
	// a[] - это массив символов, отдельные символы внутри массива могут изменяться, но
	// a[] указывает всегда на одно и то же место памяти (адрес не меняется)
	// Здесь в конце есть '\0'

	char a[] = "Hello";
	printf("%p\n", a); -> 0x7ffd8c7fa292
	a[0] = 'o';
	a[1] = '1';
	a[2] = '2';
	a[3] = 'o';
	a[4] = 'h';
	printf("%p\n", a); -> 0x7ffd8c7fa292
	printf("%s\n", a); -> o12oh

	// Адрес можно изменить, но конкретные символы редактировать нельзя
	// char *b он не может быть изменен в памяти, это как бы read-only
	// Здесь в конце есть '\0'

	char *b = "Hello"; -> const char *b = "Hello";
	b[0] = 'n'; -> SIGSEGV
	printf("%p\n", b); -> 0x55ee977f9008
	b = "new";
	printf("%p\n", b); -> 0x55ee977f900e
	printf("%s\n", b); -> new

	*b есть указатель, инициализированный так, чтобы указывать на строковую константу
	Но значение указателя можно изменить, и тогда указатель будет указывать на что-либо другое
	(адрес поменяется)

	Еще одна разница (в инкременте):
	char a[] = "Hello";
	char *b = "Hello";
	int i = 0;
	printf("%c\n", a[++i]);
	printf("%c\n", *++b);
  */

  return 0;
}
