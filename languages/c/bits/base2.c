int main(void)
{
  /*
    Операции побитового сдвига
    >> сдвигает биты числа вправо, дописывая слева нули
    << сдвигает биты числа влево, дописывая справа нули
    Вышедшие за пределы биты отбрасываются
    00000101 << 2 == 00010100
    00000101 >> 2 == 00000001
  */

  int a = 12; // 00001100
  // После сдвига получается число 00110000, то есть 48
  printf("%d << %d\n", a, a << 2); // 12 << 48


  /*
    Битовая маскировка позволяет использовать:
    * Редактирование отдельных битов
    * Проверка наличия определенных битовых значений или их отсутствия

    Смысл: применяем маску к значению, где в нашем случае значение - это наше
    состояние, например 00000101, а маска - это снова двоичное число, которое
    указывает на интересующие биты

    Например, в шестнадцатиричной системе 0x40 вернет число 64
    что соответствует 6 битам - 1000000 (справо налево)
    Если 0x45, то все равно так же 6 бит

    Шестнадцатеричные числа обычно помечаются префиксом 0x.
    Например, число 0x12 - это шестнадцатеричный эквивалент десятичного числа 18,
    тогда как 18 - это просто число 18.

    Как мы получили из числа 0x40 -> 64? все просто!
    Шестнадцатеричные числа переводятся в десятичную тем же способом, что и
    двоичные в десятичную, только умножаем на 16, а не на 2

    0x40 = порядок степеней считается справа налева, 4 * 16(1), получается 64
    тем самым 0x40 = 64
    4 * 16(1) - 16 в первой степени даст 16, затем 4 * 16 получаем 64

    0x04 = равен числу 4, потому что 4 * 16(0)
    16 в 0 степени даст = 1
    4 * 1 = 4

    0x20 = 2 * 16(1) = 32

    Таблица соответствия:
    0  0x01
    1  0x02
    2  0x04
    3  0x08
    4  0x10
    5  0x20
    6  0x40
    7  0x80
  */


  /* Установка бита в 2 позиции */
  int value = 3; // 00000011 (1 бит)

  // 4 -> 00000100 (2 бит)
  int mask = 0x04;

  printf("%d\n", mask); // выведет число 4
  // Затем делаем 011 = 011 | 100 -> 111
  value = value | mask; // На что получаем число 7

  printf("%d\n", 0x40); // 64
  printf("%d\n", 0x20); // 32


  /* Сброс бита 1 (очистка бита) */
  // 00000010 - это число 2, выражение ~2 будет равно -3, потому что 1 бит (последняя цифра)
  // преобразуется в 1 и получается 11 что равно тройке, так же меняется 1 бит, поэтому -3
  //printf("%d\n", (~0x02)); // -3

  // Сам сброс выглядит так:
  int gg = 3; // 011
  // 3    -> 011
  // 0x02 -> 2 (010) -> инверсия 101
  // 011 & 101 = 001
  gg = 3 & (~0x02);
  printf("%d\n", gg); // 1

  printf("%d\n", 10 & (~0x08));
  // 10   -> 1010
  // 0x08 -> 8 (1000) -> инверсия 0111
  // 1010 & 0111 = 0010 (2)

  printf("%d\n", 20 & (~0x02));
  // 00010100 & 010
  // 00000101
  // 00000010 -> инверсия 00000101
  // 10100 & 00101 = 10100


  /*
    Операторы операции + присваивания
    &= |= ^= ~=
  */
  unsigned char nnn = 3;
  printf("%d\n", nnn |= (1 << 3)); // Здесь будет число 11
  printf("%d\n", nnn); // Здесь будет число 11
  // Если бы мы убрали оператор присваивания, то
  // в выводе значение nnn получили бы прежнее число 3


  /* Умножение и деление на 2 */
  int n = 2; // 010
  n <<= 1; // 100
  // n теперь равно числу 4, умножили на 2

  int n = 4; // 100
  n >>= 1; // 010
  // n теперь равно числу 2, разделили на 2


  // Старший бит, это который стоит на 7 позиции
  // Младший бит, это который стоит на позиции 0

  // проверить число x на число 2 в двоичном представлении
  if (x == 0b0000010)
    puts("false true false");

  return 0;
}
