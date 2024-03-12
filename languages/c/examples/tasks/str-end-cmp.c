/*
Complete the solution so that it returns true
if the first argument(string) passed in ends with the 2nd argument
(also a string).

solution('abc', 'bc') // returns true
solution('abc', 'd') // returns false
*/

bool solution(const char *string, const char *ending)
{
  for (int i = strlen(ending), j = strlen(string); i >= 0; i--, j--)
    if (string[j] != ending[i])
      return false;
  return true;
}

int main(void)
{
  printf("%d\n", solution("abc", "bc"));
  printf("%d\n", solution("abc", "d"));
  printf("%d\n", solution("abc", ""));
  printf("%d\n", solution("ails", "fails"));

  return 0;
}
