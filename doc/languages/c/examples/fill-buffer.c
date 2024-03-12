// Получаем указатель str (тот же адрес, что и прежде)
void aaa(char *s)
{
  *(s+0) = 'G';
  *(s+1) = 'f';
  *(s+2) = 'G';
  *(s+3) = '\0';
  printf("Here - %s\n", s); // GfG
}

int main(void)
{
  // Изначально нужно аллоцировать память
  char *str = malloc(strlen("Hello") * sizeof(char));
  aaa(str); // Передаем указатель str
  printf("%s\n", str); // GfG
  free(str);

  return 0;
}
