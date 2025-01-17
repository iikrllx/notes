/*
malloc округляет до ближайшего блока
есть функция mmap, это и есть системный вызов, который использует malloc

mmap значительно уменьшает обращений к ядру (это системный вызов)
malloc это функция и в strace можно увидеть что используется mmap */

int main(void)
{
  char *buf;
  buf = malloc(1024); // Бронируем 1024 байт в куче (неиниц.памяти)
  // Когда функция malloc выделяет память,
  // то она резервирует место на куче и возвращает адрес этого участка
  // У нас будет гарантия, что компьютер не отдаст нашу память кому-то ещё
  // В этом примере мы работаем с указателем точно также, как и с массивом
  for (int i = 0; i < 1024; i++) {
    buf[i] = '\0'; // Это аналог -> memset(buf, 0, sizeof(buf));
  }

  free(buf); // Теперь освобождает эти 1024 байт
  // То есть буфер, который был полон 0, опять забьется разным мусором
  // Но после этого наш указатель будет все равно доступен, и по его адресу
  // будет доступен разный мусор

  // Теперь buf не указывает никуда, раньше у него был адрес 0x5555555592a0
  // по которому можно было получить мусор (после free), а теперь он указывает
  // в 0x0 что хорошо и не приведет к ошибкам
  buf = NULL;

  int *a; // Здесь sizeof вернет 8
  a = malloc(4);
  int arr[4]; // Здесь вернет 16, потому что длина 4,
  // в каждом находится 1 int, который весит 4, тем самым 4 * 4 = 16

  // Можно передать arr функции как объект int *parr
  // Но мы не сможем передать *a как a[4]
  // В Си нет массивов :) есть только указатели

  // malloc осуществлеятся в куче
  // а определение массива осуществляется в стеке

  // Также в malloc памяти время жизни определяется free
  // Так как malloc осуществляется в куче, то и время жизни соответствующее
  // Массивы они живут до того времени, пока программа не выйдет за пределы
  // функции где был инициализирован массив, а в куче работает иначе

  // То есть массив создается во время компиляции, в то время как с помощью malloc
  // память выделяется во время выполнения

  // Если мы знаем что arr[20] не будет переполнен, то тогда можно
  // использовать это объявление спокойно
  // Если же знаем что может переполниться (например пользователь введет символов больше
  // чем надо), то тогда лучше использовать malloc/free

  // Когда идет аллокация памяти и затем возврат этого буфера другим указателям
  // Затем в одной из такой функции идет free(pointer_to_buf);
  // Происходит munmap_chunk(): invalid pointer это означает что указатель был изменен
  // и free должен происходить с тем же указателем что вернул malloc

  char *abc;
  abc = malloc(1024);
  if (abc == NULL) {
    abort();
  }

  size_t in;
  for (in = 0; in < 1024; in++) {
    abc[in] = 'c';
  }
  abc[in] = '\0';

  // str и buf идентичны
  char *str = buf;
  // здесь у нас str становится мусором и buf тоже
  // то есть освобождается и str и buf
  free(str);

  return 0;
}
