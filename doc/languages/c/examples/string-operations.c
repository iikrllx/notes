int main(void)
{
	char *s = "hello world and fucking mind";
	char *p = strstr(s, "fuck");
	if (!p) abort();
	printf("%s\n", p); /* fucking mind */

	/* first occurrence */
	printf("%s\n", strchr(s, 'l')); /* llo world and fucking mind */

	/* last occurrence */
	printf("%s\n", strrchr(s, 'l')); /* ld and fucking mind */

	/* auto terminate with null byte */

	/* rewrite */
	char ss[128] = "meow";
	strcpy(ss, "hello");
	printf("%s\n", ss); /* hello */

	/* append */
	char bb[128] = "wow:";
	strcat(bb, "hello");
	printf("%s\n", bb); /* wow:hello */

	/* don't forget 'free'
	 * 'strdup' work with auto malloc */
	char *nn = strdup("anna");
	printf("%s\n", nn); /* anna */
	free(nn);

	return 0;
}
