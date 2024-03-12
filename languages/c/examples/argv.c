int main(int argc, char *argv[])
{
  int sv = argc;

  // Ехо вывод всех аргументов по порядоку abc coa 123
  while (--argc > 0) {
    printf("%s%s", *++argv, " ");
  }

  if (sv > 1) {
    printf("\n");
  }

  return 0;
}
