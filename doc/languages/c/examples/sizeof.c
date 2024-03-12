int main(void)
{
  int arr[20];
  /* Здесь вернет 80, потому что 4 * 20 */

  int arr[20] = {1, 2, 3, 4};
  /* В данном случае sizeof(arr) вернет нам цифру 80 */

  int mo[] = {1, 2, 3, 4, 5};
  /* А здесь sizeof(mo) вернет нам цифру 20, ибо 4 * 5 элементов */

  char *list[] = {"fly-fm", "fly-wm"};
  /* Здесь sizeof(list) вернет цифру 16, потому что указатель весит 8, два указателя 16
  sizeof(char) - вернет 1, а sizeof(list[0]) вернет 8 (ибо это указатель) на строку
  Естественно при sizeof("hello") будет возвращать по байтно - 6 */

  /* Если нам нужно получить длинну строки указателя, то в этом поможет strlen
  а не sizeof, потому что sizeof вернет размер указателя - 8 !!! */
  char *str = "Hello"; // 5

  /* Вернет 4, да-да, это целочисленное */
  sizeof('\0'); // 4
  sizeof('c');  // 4
  // А если сделать sizeof((char)'c'); // 1

  /* массив строк */
  char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Choice 5",
    "Choice 6",
    "Choice 7",
    "Exit",
  };

  sizeof(choices)     // 64
  sizeof(choices[0])  // 8

  return 0;
}
