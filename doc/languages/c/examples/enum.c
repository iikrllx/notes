/*
enum - тип перечислений, набор
целочисленных значений (int) */
int main(void)
{
  enum names {
    Kirill,
    Amy,
    Frank = 10,
    Ara,
  };

  printf("%d\n", Kirill); // 0
  printf("%d\n", Amy); // 1
  printf("%d\n", Frank); // 10
  printf("%d\n", Ara); // 11

  // Принятно писать названия перечислений
  // с заглавных букв
  enum fd {
    STDIN,
    STDOUT,
    STDERR,
  };

  // Объявляется переменная
  // К ней присваивается значение
  enum fd a;
  a = STDIN;

  // Не обязательно писать enum fd a;
  // Можно и int n = STDIN; и затем обращаться

  printf("\n%d\n", a);
  printf("%d\n", STDOUT);
  printf("%d\n", STDERR);

  return 0;
}
