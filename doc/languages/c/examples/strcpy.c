/*
Функция strlen(s) вычисляет длину строки s
без учета завершающего ее символа '\0'
*/

/* Узнать длину строки через указатель - strlen() */
int len(char *s)
{
  int n;
  for (n = 0; *s != '\0'; s++) {
    n++;
  }

  // for (n = 0; *s != '\0'; s++, n++); Можно в одну строку

  return n;
}

/* Копирование str значения в src - strcpy() */
void copy(char *src, char *str)
{
  /* В отладчике можно заметить что цикл проходит
  мгновенно одной итерацией, но это не так, это потому
  что нет тела цикла */

  /* Здесь нет 0 потому что 0 - это false
  и он есть в конце каждой строки по дефолту
  и цикл сам завершится когда достигнет этого false
  поэтому его можно не указывать (это касается указателей) */
  while ((*src++ = *str++));
}

int main(void)
{
  char *str = "Hello";
  char arr[] = "Nananananana";

  printf("%d\n", len(str));
  printf("%d\n", len(arr));
  printf("\n");

  /* Важно понимать, что мы можем представить массив в описании функции
  как char *s, но в самом определении этой сущности у нас будет не char *list
  а char list[100], потому что нам нужно строку положить в буфер */
  char list[100];
  copy(list, "Hello world");
  printf("%p - %s\n", list, list);

  return 0;
}

/*
  Вот пример объявления массива под один символ + strcpy:
  char t[2];
  strcpy(t, "H");
  printf("%s\n", t); // H

  Под t[0] будет H
  Под t[1] будет 0
*/
