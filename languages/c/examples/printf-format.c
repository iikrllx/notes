// Пример обработки спецификаторов printf
void minprintf(char *fmt, ...)
{
	// fmt указывает на "%s %s\n"
	//
	// тип va_list служит для описания переменной, которая будет по очереди указывать
	// на каждый из аргументов "hello" / "abc"
	va_list ap;

	// эти указатели/переменные нужны для обработки аргументов
	char *p, *sval;
	double dval;
	int ival;

	// инициализирует переменную ap, чтобы она указывала на первый безымянный аргумент
	va_start(ap, fmt);

	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		switch (*++p) {
			case 'd':
				ival = va_arg(ap, int);
				putchar(ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}

	// очистка, когда все сделано
	va_end(ap);
}

int main(int argc, char **argv[])
{
	minprintf("%s %s\n", "hello", "abc");

	return 0;
}
