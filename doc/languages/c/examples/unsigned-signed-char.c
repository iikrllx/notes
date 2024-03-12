/*
Диапазон чисел char

char это обычный signed char, который занимает от -128 до 127
различных комбинаций числа

unsigned char, занимает от 0 до 255 возможных комбинаций числа
*/

int main(void)
{
  signed char c = -128;
  while (c != 127) {
    c++;
    printf("%d\n", c);
  }

  puts("------------------");

  unsigned char n = 0;
  while (n != 255) {
    n++;
    printf("%d\n", n);
  }

  return 0;
}
