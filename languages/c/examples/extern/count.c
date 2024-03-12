#include <stdio.h>

/* Если мы захотим использовать var переменную здесь
то придется добавить #inlude "abc.h" в этот файл */
void sum(char arr[], int x)
{
  int sum = 0;
  for (int i = 0; i < x; i++) {
    sum += arr[i];
  }

  printf("%d\n", sum);
}
