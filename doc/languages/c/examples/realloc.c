/* Пример динамического выделения памяти */

int main(int argc, char **argv)
{
  int buf_size = 6;
  char *buf = malloc(buf_size * sizeof(char));
  assert(buf != NULL);

  char arr[] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd'};
  int len = sizeof(arr) / sizeof(arr[0]);

  int i, j = 1;

  for (i = 0; i < len; i++) {
    buf[i] = arr[i];
    j++;

    if (j >= buf_size) {
      buf = realloc(buf, j + sizeof(char));
      assert(buf != NULL);
    }
  }

  // buf - это строка, необходимо закрыть нулем
  buf[i] = '\0';

  printf("%s\n", buf); // helloworld
  printf("%d\n", j);   // 11
  printf("%d\n", i);   // 10

  free(buf);
  buf = NULL;

  return 0;
}
