/*
Your task is to make a function that can take any non-negative integer
as an argument and return it with its digits in descending order.
Essentially, rearrange the digits to create the highest possible number.
Exampel: 42145 -> 54421
*/

int get_num_len(uint64_t n)
{
  int i;

  // 42145 / 10
  // 4214 / 10
  // 421 / 10
  // ...
  for (i = 0; n != 0; i++)
    n /= 10;

  return i;
}

uint64_t solution(uint64_t n)
{
  int len = get_num_len(n);
  uint64_t arr[len];

  for (int i = 0; i < len; i++)
  {
    // 423 % 10 -> 3
    // 42 % 10 -> 2
    arr[i] = n % 10;
    n /= 10;
  }

  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < len - 1; j++)
    {
      if (arr[j] < arr[j + 1])
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  uint64_t x = 0;

  for (int i = 0; i < len; i++) {
    // 10 * 0 + n
    // 10 * n + n
    x = 10 * x + arr[i];
  }

  return x;
}

int main(void)
{
  printf("%d\n", solution(42145));
  printf("%d\n", solution(145263));

  return 0;
}
