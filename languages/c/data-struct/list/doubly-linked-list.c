/*
Каждый узел двунаправленного линейного списка содержит
два поля указателей - на следующий и на предыдущий узлы.
Указатель на предыдущий узел корня списка содержит
нулевое значение. Указатель на следующий узел
последнего узла также содержит нулевое значение.
*/

struct Node {
  int data;
  struct Node *next; // указатель на следующий узел
  struct Node *prev; // указатель на предыдущий узел
};

void *malloc_wrapper()
{
  void *p = malloc(sizeof(struct Node));
  assert(p != NULL);
  return p;
}

void del_node(struct Node **head, int key)
{
  struct Node *key_node = *head;
  struct Node *temp, *prev_key;

  while (key_node -> data != key) {
    prev_key = key_node;
    key_node = key_node -> next;
  }

  prev_key -> next = key_node -> next;
  temp = key_node -> next;
  temp -> prev = prev_key;
}

void del_last(struct Node **head)
{
  struct Node *last = *head;
  while (last -> next -> next != NULL)
    last = last -> next;
  last = last -> next = NULL;
}

void del_head(struct Node **head)
{
  (*head) = (*head) -> next;
  (*head) -> prev = NULL;
}

void append(struct Node **head, int new_data)
{
  struct Node *new_node;
  struct Node *last = (*head);

  new_node = malloc_wrapper();
  new_node -> data = new_data;
  new_node -> prev = NULL;
  new_node -> next = NULL;

  while (last -> next != NULL)
    last = last -> next;

  new_node -> prev = last;
  last -> next = new_node;
}

void push(struct Node **head, int new_data)
{
  struct Node *new_node;
  new_node = malloc_wrapper();

  new_node -> data = new_data;
  new_node -> next = (*head);
  new_node -> prev = NULL;

  if ((*head) != NULL)
    (*head) -> prev = new_node;
  (*head) = new_node;
}

void print_list(struct Node *node)
{
  struct Node *last;

  while (node != NULL) {
    printf("%d ", node -> data);
    last = node; // здесь будет последнее значение, сохраняем его
    node = node -> next; // node будет равен NULL так как node -> next
  }
  printf("\n");

  while (last != NULL) {
    printf("%d ", last -> data);
    last = last -> prev; // начиная с последнего значения идем обратно к первому
  }
  printf("\n");
}

int main(void)
{
  struct Node *head;
  struct Node *second;
  struct Node *third;

  head = malloc_wrapper();
  second = malloc_wrapper();
  third = malloc_wrapper();

  head -> data = 1;
  head -> next = second;
  head -> prev = NULL;

  second -> data = 2;
  second -> next = third;
  second -> prev = head;

  third -> data = 3;
  third -> next = NULL;
  third -> prev = second;

  print_list(head);
  push(&head, 0);
  print_list(head);

  append(&head, 4);
  print_list(head);

  del_node(&head, 2);
  print_list(head);

  del_head(&head);
  print_list(head);

  del_last(&head);
  print_list(head);

  free(head);
  free(second);
  free(third);

  return 0;
}
