/*

Реализация стека с помощью связного списка.
* Реализация связанного списка стека может
увеличиваться и уменьшаться в соответствии
с потребностями во время выполнения
* Требуется дополнительная память из-за использования
указателей

*/

struct StackNode {
  int data;
  struct StackNode *prev;
};

int is_empty(struct StackNode *root)
{
  return root == NULL;
  /* Или можно написать: return !root; */
}

void print_stack(struct StackNode *root)
{
  // цикл будет работать до того, пока root НЕ NULL
  while (root) {
    printf("%d\n", root -> data);
    root = root -> prev;
  }
}

int peek(struct StackNode *root)
{
  if (is_empty(root))
    return INT_MIN;
  return root -> data;
}

int pop(struct StackNode **root)
{
  if (is_empty(*root))
    return INT_MIN;

  // сохраняем в переменную значение
  // потому что указатель изменится на предыдущее значение
  int popped = (*root) -> data;
  *root = (*root) -> prev;

  return popped;
}

void push(struct StackNode **root, int data)
{
  struct StackNode *sn;

  sn = malloc(sizeof(struct StackNode));
  assert(sn != NULL);

  sn -> data = data;
  sn -> prev = *root;

  // теперь *root будет равен новому значение
  // а prev будет прошлый элемент
  *root = sn;

  printf("%d pushed to stack\n", data);
}

int main(void)
{
  struct StackNode *root = NULL;

  push(&root, 10);
  push(&root, 20);
  push(&root, 30);

  print_stack(root);

  printf("\nTop element is %d\n", peek(root));
  printf("%d popped from stack\n", pop(&root));
  printf("Top element is %d\n", peek(root));

  print_stack(root);

  free(root);

  return 0;
}
