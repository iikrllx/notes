int main(void)
{
	/* Main -> niaM */

	char s[] = "Main";
	int len = strlen(s);

	for (int i = 0, j = len - 1; i < len / 2; i++)
	{
		char x = s[i];
		s[i] = s[j];
		s[j] = x;
		j--;
	}

	return 0;
}
