/* Пример getopt с короткими опциями + длинные

ЧТОБЫ НЕ ЗАУЧИВАТЬ ЭТО, МОЖНО ОБРАТИТЬСЯ К man 3 getopt
там даже есть примеры, и надо понимать что option
это готовая структура объявленная в getopt.h
мы просто заполняем ее данными

Чтобы программа поддерживала только опции вида --usage
а не -u, нужно в getopt_long передать (argc, argv, "uh", long_options, NULL)

Если опция не ожидает аргумента, писать no_argument
Если ожидает, писать required_argument
и можно передавать так:
--option=2 --option 2

Данные переменные не отображаются нормально в gdb

Число два можно получить в optarg, который можно перевести в atoi(optarg)
optarg содержит указатель на аргумент (required_argument) переданный после --option

optind содержит индекс аргумента следующего за --option
./a.out -p <n> -s <n> -f 255 8
optind это индекс последнего значения (7), по-умолчанию равен 1
и можно с конца делать argv[optind] и argv[optind - 1]

./a.out -p <n>
optind будет равен 3 (передали 2 аргумента, 1 + 2 = 3)

Переменная optopt содержит недопустимый символ, например, если getopt
обнаружил недопустимый символ опции, возвращается ? или :, а optopt содержит
этот символ
*/

int main(int argc, char **argv)
{
  int n;

  // здесь важно заметить ключевое слово option
  // которое относится к getopt готовой структуре
  // можно вместо no_argument передавать 0
  struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"usage", no_argument, NULL, 'u'},
    {NULL, no_argument, NULL, 0}
  };

  /* если getopt успешен - возвращает номер символа */
  /* если неуспешен то n будет равен 63 коду символа ? */
  while ((n = getopt_long(argc, argv, "hu", long_options, NULL)) != -1) {
    /* используя switch можно выбрать какая функция подходит */
    switch (n) {
      case 'h': puts("help"); break;
      case 'u': puts("usage"); break;
      /* если getopt вернул -1 вывести default + сообщение об ошибке */
      default: exit(EXIT_FAILURE);
    }
  }

  return 0;
}
