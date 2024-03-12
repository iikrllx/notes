/*
Подсчитывает сумму массива, находит минимальное, максимальное число
Создает новые массивы динамическим способом, в которые записываются
четные / нечетные числа
*/

void *_int_malloc(size_t size)
{
  void *mem = malloc(size * sizeof(int));
  assert(mem != NULL);
  return mem;
}

void print_array(int arr[], size_t size)
{
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(void)
{
  int arr[] = {10, 50, 5, 4, 100, 1};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  int max = arr[0], min;
  int sum = 0, i;
  int *odd, *even;
  int odd_size = 0;
  int even_size = 0;

  printf("Main array: ");
  print_array(arr, size);

  for (i = 0; i < size; i++)
    (arr[i] % 2 == 0) ? even_size++ : odd_size++;

  odd = _int_malloc(odd_size);
  even = _int_malloc(even_size);

  int j, z;
  for (i = 0, j = z = 0; i < size; i++) {
    sum += arr[i];

    if (arr[i] % 2 == 0) {
      *(even + j) = arr[i];
      j++;
    } else {
      *(odd + z) = arr[i];
      z++;
    }

    if (max < arr[i])
      max = arr[i];
    else
      min = arr[i];
  }

  printf("max: %d / min: %d / sum: %d\n",
    max, min, sum);

  printf("\n");
  printf("Even array: ");
  print_array(even, even_size);

  printf("Odd array: ");
  print_array(odd, odd_size);

  free(odd);
  free(even);

  return 0;
}
