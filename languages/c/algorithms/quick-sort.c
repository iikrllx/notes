void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1); // начинается с -1

  // j равен 0, цикл работает до high
  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++; // увеличивает индекс с -1 (по началу)
      swap(&arr[j], &arr[i]);
    }

    // 8 7 2 1 0 9 6
    // swap выполнился 3 раза, потому что в массиве есть 3 числа меньше 6
    // 2 7 8 1 0 9 6
    // 2 1 8 7 0 9 6
    // 2 1 0 7 8 9 6
  }

  // хотел передать здесь &pivot
  // но pivot это не указатель, это переменная
  swap(&arr[i + 1], &arr[high]);
  // опорный элемент ставится между двумя подмассивами
  // слева числа меньшие этого элемента, а справо большие
  // 2 1 0 6 8 9 7

  // вернуть индекс опорного числа
  return (i + 1); // 3
}

void quick_sort(int arr[], int low, int high)
{
  if (low < high) {
    int pivot_index = partition(arr, low, high);

    // элементы индексов от 0 до 2 будут отсортированы
    quick_sort(arr, low, pivot_index - 1); // 0 1 2
    // станет 0 1 2 6 8 9 7

    // элементы индексов от 4 до 6 будут отсортированы
    quick_sort(arr, pivot_index + 1, high); // 7 8 9
    // станет 0 1 2 6 7 8 9

    // важно обратить внимание, что сначало сортируется подмассив
    // чисел меньших pivot элемента (то есть числа 6)
    // затем уже сортируется подмассив чисел больших pivot элемента
    // индекс 3, игнорируется
  }
}

void print_array(int arr[], size_t size)
{
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(void)
{
  int arr[] = {8, 7, 2, 1, 0, 9, 6};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  print_array(arr, size);
  quick_sort(arr, 0, size - 1);
  print_array(arr, size);

  return 0;
}
