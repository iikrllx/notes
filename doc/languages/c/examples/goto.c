/*
 * switch работает на основе goto, там есть такие же метки 0: 1: и переход к ним.
 * еще longjmp и setjmp тоже работают на основе goto
*/

void gtexample()
{
  char *s = NULL;
  if (!s)
    goto fail;

  puts("1");
  puts("2");
  puts("free");

  return;

  fail:
    puts("out");
    abort();
}

int main(void)
{
  gtexample();
  return 0;
}
