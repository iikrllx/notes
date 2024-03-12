/* Если abc.h будет найден (в системе) ABC объявится
а если нет, то не объявится и условное выражение
не пройдет */
#if defined __has_include
	#if __has_include("abc.h")
		#define ABC
	#endif
#endif

/* Если <sys/io.h> будет найден в системе, тогда include сработает */
#if defined __has_include
	#if __has_include(<sys/io.h>)
		#include <sys/io.h>
		#define _IO_H
	#endif
#endif

int main(void)
{
  #ifdef ABC
    puts("Good");
  #else
    puts("Not good");
  #endif

  #ifdef _IO_H
    puts("_IO_H");
  #endif

  return 0;
}
