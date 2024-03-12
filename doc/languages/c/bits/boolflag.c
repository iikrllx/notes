/* Флаг можно еще использовать для условия выполнения */

bool checkifanyeven(int arr[], int len)
{
  int flag = false;

  for (int i = 0; i < len; i++) {
    if (arr[i] % 2 == 0) {
      flag = true;
      break;
    }
  }

  return flag;
}

int main(void)
{
  int arr[] = {1, 2, 3, 4, 5, 6};
  int len = sizeof(arr) / sizeof(arr[0]);

  if (checkifanyeven(arr, len))
    puts("yeah");
  else
    puts("no");
}
