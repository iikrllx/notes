/*

Реализация стека с помощью одномерного массива.
* Легко реализовать, память сохраняется,
поскольку указатели не задействованы
* Это не динамично. Он не растет и не сжимается
в зависимости от потребностей во время выполнения

*/

struct Stack {
  int top;
  unsigned capacity;
  int *array;
};

int is_empty(struct Stack *stack)
{
  return stack -> top == -1;
}

int is_full(struct Stack *stack)
{
  // возвращает 1 если происходит равенство.
  // capacity равен 100 - 1, значит при stack -> top == 99
  // функция вернет 1, при неравенстве вернет 0
  return stack -> top == stack -> capacity - 1;

  /*
    Аналог:

    if (stack -> top == stack -> capacity - 1)
      return 1;
    else
      return 0;
  */
}

int peek(struct Stack *stack)
{
  /*
    Здесь используется INT_MIN потому что функция
    возвращает int значение, если написать просто return;
    компилятор будет ругаться, поэтому используется INT_MIN */
  if (is_empty(stack))
    return INT_MIN;
  // возвращает вершину стека
  return stack -> array[stack -> top];
}

// убирает элемент с верхушки стека, уменьшает индекс на 1
int pop(struct Stack *stack)
{
  if (is_empty(stack))
    return INT_MIN;
  // например stack -> top равен 2
  // после этой операции будет 1
  return stack -> array[stack -> top--];
}

// функция добавления элемента в стек, увеличиет индекс на 1
void push(struct Stack *stack, int item)
{
  /*
    проверяет на заполненность стека
    если вернет 1, то сработает return
    если вернет 0, то ничего не произойдет */
  if (is_full(stack))
    return;

  /*
    идет обращение к элементу массива
    stack -> array[index]
    строка: ++stack -> top (префиксная форма, потому что сразу нужен 0)
    инкрементирует значение stack -> top
    было -1, стало 0
    stack -> array[0] = item; */
  stack -> array[++stack -> top] = item;
  printf("%d pushed to stack\n", item);
}

// функция создания стека в определенном объеме (capacity)
// начинается с 0 элемента (затем увеличивается, поэтому с -1)
struct Stack *create_stack(unsigned capacity)
{
  struct Stack *stack = malloc(sizeof(struct Stack));
  assert(stack != NULL);

  stack -> top = -1;
  stack -> capacity = capacity;
  // указатель на зарезервированную память 400 байт
  stack -> array = malloc(stack -> capacity * sizeof(int));
  assert(stack -> array != NULL);

  return stack;
}

int main(void)
{
  struct Stack *stack = create_stack(100);

  push(stack, 10);
  push(stack, 20);
  push(stack, 30);

  printf("\n%d peek from stack\n", peek(stack)); // 30
  printf("%d popped from stack\n", pop(stack));  // 30
  printf("%d peek from stack\n", peek(stack));   // 20

  return 0;
}
