int bbb(char *a, char *b)
{
  // strcmp example with pointers
  for (; *a == *b; a++, b++) {
    if (*a == '\0') {
      return 0;
    }
  }
  return *a - *b;
}

int aaa(char *a, char *b)
{ // strcmp
  int i;
  // Условие цикла, если символы совпадают при
  // сравнении, то продолжаем дальше, инкремент
  for (i = 0; a[i] == b[i]; i++) {
    if (a[i] == '\0') {
      return 0;
    }
  }

  return a[i] - b[i];
}

int main(void)
{
  printf("%d\n", aaa("Hello", "Hello"));
  printf("%d\n", bbb("Hello", "Hello"));

  return 0;
}
