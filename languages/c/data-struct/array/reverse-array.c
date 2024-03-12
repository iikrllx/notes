/*
1 2 3 4 5 6
6 5 4 3 2 1
*/

void print_array(int arr[], int size)
{
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void reverse_array(int arr[], int start, int end)
{
  int temp;
  while (start < end) {
    temp = arr[start]; // сохраняем 1 или 2 или 3
    arr[start] = arr[end]; // ставим на первые числа последние числа
    /*
      так как у переменной счетчика start
      число изменяется каждую итерацию, нам нужно использовать переменную
      temp которая хранит числа 1 2 3 */
    arr[end] = temp;

    /*
      от start++ до end-- у нас идет 3 итерации
      поэтому будут взаимодействованы числа 1 2 3
      нужна вместо чисел 1 2 3 поставить 6 5 4
      а вместо числе 6 5 4 поставить 3 2 1 */
    start++;
    end--;
  }
}

int main(void)
{
  int arr[] = {1, 2, 3, 4, 5, 6};
  int size = sizeof(arr) / sizeof(arr[0]);
  print_array(arr, size);

  // здесь мы вычитаем из 6 один
  // потому что нужно начать с 0, заканчивая 5 индексом
  // поэтому в том цикле идет с 0 до 5, чтобы перебрать весь массив
  reverse_array(arr, 0, size - 1);
  print_array(arr, size);

  return 0;
}
