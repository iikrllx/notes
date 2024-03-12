char* reverseWords(const char* text)
{
	char *s = malloc(sizeof(char) * strlen(text) + 1);
	const char *p = text;
	char *t = s;
	int len = 0;

	while (1)
	{
		if (*p == ' ' || *p == '\0')
		{
			for (int i = 0; i < len; i++)
				*t++ = *(p - 1 - i);

			if (*p == ' ')
				*t++ = ' ';

			if (*p == '\0')
			{
				*t++ = '\0';
				break;
			}

			len = 0;
		}
		else
			len++;

		p++;
	}

	return s;
}

int main(void)
{
	char *s = reverseWords("hello,  world!");
	printf("%s\n", s);
	free(s);

	return 0;
}
