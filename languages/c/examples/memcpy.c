/* Осуществляет копирование содержимого одной области памяти в другую */

int main(void)
{
  setlocale(LC_ALL, "");
  wchar_t *s = L"Хе";
  wint_t len = wcslen(s); // 2
  // sizeof(wchar_t *) * len -> 16

  wchar_t *pt = malloc(sizeof(wchar_t *) * len);
  if (pt == NULL)
    abort();

  memcpy(pt, s, sizeof(wchar_t *) * len);
  printf("%ls\n", pt);

  /* Здесь нет разницы (для char *), можно использовать memcpy, а можно strcpy / strncpy
   * strcpy работает копирование пока не встретит NULL, а memcpy все равно на NULL,
   * он копирует конкретно size_t n. memcpy нужно использовать, если данные не только символы.
   * for encrypted data or binary data, memcpy is ideal way to go.
   * То есть когда мы не знаем, что за данные (не только строки) лучше использовать memcpy. */

  return 0;
}
