void print_array(int arr[], size_t size)
{
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void selection_sort(int arr[], size_t size)
{
  int i, j, min_index;

  // идет size - 1, потому что size 5, а нужно 4
  // итераций будет 3, потому что если не сделать size - 1
  // тогда в последней итерации будет сравнение arr[min_index]
  // с arr[j] (за пределами массива) arr[5], а это мусорное значение

  for (i = 0; i < size - 1; i++) {
    min_index = i; // за основное число берется первое значение
    // массива, а в j идет отсчет со следующего элемента

    // 64 25 12 22 11
    // 11 25 12 22 64
    // 11 12 25 22 64
    // 11 12 22 25 64

    // j = i + 1, плюс один, делается для того чтобы число
    // arr[min_index] не сравнивалось с самим собой
    // потому что под j будет тоже значение, а с (+ 1)
    // эта проблема решается (лишний круг)
    for (j = i + 1; j < size; j++)
      if (arr[min_index] > arr[j])
        min_index = j;

    int temp = arr[min_index];
    arr[min_index] = arr[i];
    arr[i] = temp;
  }
}

int main(void)
{
  int arr[] = {64, 25, 12, 22, 11};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  selection_sort(arr, size);
  print_array(arr, size);

  return 0;
}
