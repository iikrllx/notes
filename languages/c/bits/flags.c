/*
Флаг - это логическая сумма всех используемых флагов
Каждый флаг принимает своё уникальное название

Раньше не было bool типов, поэтому чтобы проверять
значения вида true / false, приводили число к 0 или 1
(имитация логического поведения)

Например:
int flags = O_RDWR | O_CREAT | O_TRUNC | O_APPEND;
*/

enum {
  FIRST = 1 << 0,     /* 1 */
  SECOND = 1 << 1,    /* 2 */
  THIRD = 1 << 2,     /* 4 */
  FOURTH = 1 << 3     /* 8 */
};

void check_bits(int x)
{
  for (int i = CHAR_BIT - 1; i >= 0; i--)
    printf("%d ", (x & (1 << i)) != 0);
  printf("\n");
}

int main(void)
{
  /* combine flags - объединить флаги */
  /* в одно значение можно объединить все остальные значения */
  int flags = FIRST | THIRD | FOURTH; /* 1101 = 13 */

  int x = FOURTH;
  int f = 0x00000010;
  printf("%d\n", f);
  check_bits(2);

  if (flags & x) {
    printf("Флаг найден\n");
    check_bits(flags);
    check_bits(x);
  } else {
    printf("Флаг не найден\n");
  }

  return 0;
}
