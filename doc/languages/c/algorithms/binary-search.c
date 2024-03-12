int binary_search(int list[], size_t size, int x)
{
  int low, high, middle;

  low = 0;
  high = size - 1;

  // Пока границы не сомкнутся, на деле у нас low не станет high
  // потому что будет выход из функции раньше
  while (low <= high) {

    // найти элемент по середине между двумя точками
    // можно по такой формуле, сложить обе единицы
    // и разделить, например {1, 2, 3, 4, 5}
    // low равен 2, а high 4, делим, получается 3
    // то есть значение 4, а индекс 3
    middle = (low + high) / 2;

    // middle это индекс центрального числа
    // поэтому если индекс равен например 3
    // то в случае если число x будет больше центральному
    // 3 + 1, и затем уже будет от 4 до конца
    if (x < list[middle])
      high = middle - 1;
    else if (x > list[middle])
      low = middle + 1;
    else
      return middle;
  }

  return -1;
}

int main(void)
{
  int arr[] = {1, 2, 3, 4, 5};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  int x = 5;
  int index = binary_search(arr, size, x);

  if (index != -1)
    printf("%s: Index number %d equal %d\n", __FILE__, x, index);
  else
    fprintf(stderr, "%s: Something went wrong!\n", __FILE__);

  return 0;
}

/*
Если написать:
if (x < list[middle])
  low = middle + 1;
else if (x > list[middle])
  high = middle - 1;

Это в корне неверно! Если передать число 5 как x
это число будет больше list[middle] и тогда у нас
high будет равен 1, и поиск будет осуществляться с 0 до 1
и мы не сможем найти индекс числа 5 !!!

Сработает return -1

*/
