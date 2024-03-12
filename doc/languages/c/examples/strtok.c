int main(void) {
  char str[] = "Hello, world!";
  char *token;

  /* strtok НЕ принимает указатель на строку: (char *str = "Hello, world!") */
  /* только строку в массиве или нужно обращаться к malloc */
  /* во втором параметре указаны разделители (separaters) пробел, запятые и т.д */
  token = strtok(str, ",!");

  /*
    char *s = "Hello";
    Означает указатель на неизменяемое значение, то есть 'H'
    нельзя изменить, (СТРОКА ЭТО КОНСТАНТА) это типо
    const char arr[] = "Hello";

    Чтобы передавать указатель можно сделать так:
    char *a = strdup("Hello, world!");
    После strdup необходимо сделать free, во избежении mem leak

    Или так:
    char *s = malloc("Hello");
    memcpy(s, "Hello", strlen("Hello"));
    И смело передавать указатель s в strtok
    ...
    free(s); */

  /* пока есть лексемы, продолжаем цикл */
  /* каждый раз когда найдена лексема, на месте, где был найден ограничитель,
  помещается нулевой символ, таким образом strtok продвигается вдоль строки */
  while (token != NULL) {
    printf("%s |", token); // здесь выводится Hello | world |
    // если не передать данную строку, то получится бесконечный цикл
    // это делается для того чтобы всю строку можно было разбить на лексемы
    token = strtok(NULL, ",!");
  }

  return 0;
}
