void sigalrm_handler()
{
  printf("good");
}

int main(void)
{
  //signal(SIGALRM, sigalrm_handler);

  struct timeval tval;
  struct tm *ptm;
  char time_format[16];

  time_t ti; // Определяем переменную ti типа time_t
  time(&ti); // Записываем текущее время в секундах

  // Можно еще так получить текущее время
  // А если нужны секунды то &tval.tv_sec
  //gettimeofday(&tval, NULL);

  ptm = localtime(&ti); // Возвращает локальное время
  //ptm = localtime(&tval.tv_sec);

  strftime(time_format, 16, "%H:%M:%S", ptm); // Формат времени

  printf("%s\n", time_format);

  //alarm(2); // Будильник на 2 секунды
  sleep(10);

  time_t nt;
  time(&nt);

  printf("%f", difftime(nt, ti)); // Разница во времени 10 секунд

  return 0;
}
