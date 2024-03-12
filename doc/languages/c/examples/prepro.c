/* Макрос - поведение обычной функции
макросы не подлежат отладки, макрос быстрее функции
для небольших процедур нужно использовать макросы
Так же есть еще директории препроцессора:
#include
#define
#undef
#ifdef и другие
*/

#define MIN(x, y) ((x <= y) ? (x) : (y))

#define T 0

/* Проверка на определение */
#ifdef T
  /* Если T определен, то будет printf */
  #define info(msg) printf("%s\n", msg)
#else
  /* Если нет, то ничего не будет */
  #define info(msg)
#endif

/* Можно еще исползовать #ifndef (if not defined) */



/*
Если в данный исходник подключен <math.h>
тогда в нем будет системное определение M_PI
если же нет, тогда сработает наше определение:
3.14159265358979

man math.h покажет определения различных констант
*/

#ifdef M_PI
  #define PI M_PI
#else
  #define PI 3.24159265358979
#endif



/* Определение NDEBUG отключает различные проверки assert */
#define NDEBUG
#include <assert.h>

int main(void)
{
  printf("%d\n", MIN(2, 5));
  info("hello");

  printf("Line is %d, File is %s, Date is %s\n", __LINE__, __FILE__, __DATE__);
  printf("Time is %s\n", __TIME__);

  #undef T /* удаление T */
  #define T 100 /* определение, но с новой константой */


  printf("%0.1f\n", PI);


  double x = -1.0;
  assert(x >= 0.0);
  printf("sqrt(x) = %f\n", sqrt(x));

  return 0;
}

/*
Есть уже предопределенные макросы, такие как:
__LINE__ возвращает номер строки где определен данный макрос
__FILE__ возвращает имя текущего файла
__DATE__ дата трансляции
__TIME__ время трансляции
__func__ имя функции
*/


/*
Может быть такое что у нас есть объявления функций в файле header.h
и мы можем по ошибке заинклудить данный файл несколько раз
чтобы этого не сделать, можно в самом header.h прописать

#ifndef _HAVE_HEADER_H
#define _HAVE_HEADER_H

... объявления
void abc();

#endif

и тогда если мы вставим по ошибке
#include "header.h"
#include "header.h"

компилятор удалит вторую запись

или например проверка на <math.h>
#ifndef HAVE_MATH_H
#define HAVE_MATH_H 1

это называется protect header files

Например, configure.ac создает файл config.h в котором
есть определения типа HAVE_STDLIB_H 1 (когда есть),
а когда нет HAVE_STDLIB_H 0
*/
