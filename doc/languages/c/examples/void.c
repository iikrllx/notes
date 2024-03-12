void my_func(int n, char c)
{
  void *p = &c;
  void *q = &n;
  printf("%c\n", *(char *)p);
  printf("%d\n", *(int *)q);
}

int main(void)
{
  int n = 2;
  char c = 'A';
  my_func(n, c);

  return 0;
}
