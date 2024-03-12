void print_chars(int n, char c)
{
  int i;
  for (i = 0; i < n; i++) {
    char *s;
    int j;

    s = calloc(i + 2, sizeof(char));
    if (!s)
      abort();

    for (j = 0; j < i + 1; j++)
      s[j] = c;

    printf("%s\n", s);

    free(s);
  }
}

int main(void)
{
  print_chars(10, 'x');
  return 0;
}
