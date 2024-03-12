/* Реализация Очереди с помощью связного списка */

struct QNode {
  int key;
  struct QNode *next;
};

// Стуктура очереди, которая содержит в себе
// указатели на структуру QNode
// будет доступ к front -> key; front -> next
struct Queue {
  struct QNode *front, *rear;
};

void print_que(struct Queue *q)
{
  struct QNode *qn = q -> front;
  while (qn != NULL) {
    printf("%d ", qn -> key);
    qn = qn -> next;
  }

  printf("\n");
}

struct QNode *new_node(int k)
{
  struct QNode *temp = malloc(sizeof(struct QNode));
  assert(temp != NULL);

  temp -> key = k;
  temp -> next = NULL;

  return temp;
}

void enQueue(struct Queue *q, int k)
{
  struct QNode *temp = new_node(k);

  // указатели front и rear будут смотреть на значение
  // указателя temp, key - 10 / next - 0x0
  // и ВЫЙТИ ИЗ ФУНКЦИИ
  // это условие срабатывает только для первого значения
  if (q -> rear == NULL) {
    q -> front = q -> rear = temp;
    return;
  }

  /*
    А что если сделать free(temp);
    Тогда q будет указывать на пустые значения
    указателя temp */


  // указатель rear на указатель next теперь будет
  // указывать на новое значение, не 10, а на 20
  q -> rear -> next = temp;

  // здесь q -> rear смотрит на значение front (10)
  // чтобы оно стало смотреть на новое значение
  // происходит актуализация значения
  q -> rear = temp;
}

void deQueue(struct Queue *q)
{
  if (q -> front == NULL)
    return;

  q -> front = q -> front -> next;

  /*
    Если в очереди произошло удаление всех элементов
    то есть q -> front равен NULL, то и по логике
    последний элемент, тоже должен быть NULL
    очередь пуста ! */
  if (q -> front == NULL)
    q -> rear = NULL;
}

int main(void)
{
  // create queue
  struct Queue *q = malloc(sizeof(struct Queue));
  assert(q != NULL);
  q -> front = q -> rear = NULL;

  enQueue(q, 10);
  enQueue(q, 20);
  deQueue(q);
  deQueue(q);
  enQueue(q, 30);
  enQueue(q, 40);
  enQueue(q, 50);

  printf("Queue Front: %d\n", q -> front -> key);
  printf("Queue Rear: %d\n", q -> rear -> key);

  printf("All numbers: ");
  print_que(q);

  free(q);

  return 0;
}
