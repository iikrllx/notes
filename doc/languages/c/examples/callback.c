/*
Функция обратного вызова, функция, которая передается
в другую функцию для последующего вызова из нее

В данном примере equal является функцией обратного вызова
*/

typedef bool(*callback_func)(int, int);

bool equal(int a, int b)
{
  return (a == b) ? true : false;
}

/* принимает адрес функции, которую нужно вызвать */
void compare(int one, int two, callback_func func)
{
  if (func(one, two))
    printf("Числа %d и %d равны\n", one, two);
  else
    printf("Числа %d и %d неравны\n", one, two);
}

int main(void)
{
  int x, y;
  x = 33;
  y = 33;

  compare(x, y, equal);

  return 0;
}
