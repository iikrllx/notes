/*
getopt() - короткие
getopt_long() - короткие + длинные
getopt_long_only() - длинные

Если функция требует аргумента, например --output=file
То тогда в формат будет выглядеть так "ho:v", что означает
что --output нужно передать что-то

Так же getopt записывает что-либо в глобальные переменные
по типу optarg и т.д

Нужно запомнить что getopt вызывыается в цикле
Хотя можно вместо while ставить if, но все мануалы и документации
твердят об цикле, не понятно почему ... ПРОСТО ТАК НАДО
*/

/* Пример классического getopt */
int main(int argc, char **argv)
{
  int n;
  while ((n = getopt(argc, argv, "hu")) != -1) {
    switch (n) {
      case 'h': puts("help"); break;
      case 'u': puts("usage"); break;
      default: exit(1);
    }
  }

  return 0;
}
