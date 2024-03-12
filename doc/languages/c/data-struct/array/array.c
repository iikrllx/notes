void print_array(double points[], int npoints)
{
  for (int i = 0; i < npoints; i++)
    printf("%d: %0.1f\n", i, points[i]);
}

int main(void)
{
  /* Пример статического массива */
  double points[4] = {1.0, 3.14, -1.2, 12.64};
  int npoints = sizeof(points) / sizeof(points[0]);
  print_array(points, npoints);

  /*
    Пример динамического массива
    Размер массива программа получает во время выполнения */
  int len;
  int *arr;

  scanf("%d", &len);

  arr = malloc(len * sizeof(int));
  assert(arr != NULL);

  for (int i = 0; i < len; i++) {
    arr[i] = i + 1;
    printf("%d: %d\n", i, arr[i]);
  }

  free(arr);

  return 0;
}
