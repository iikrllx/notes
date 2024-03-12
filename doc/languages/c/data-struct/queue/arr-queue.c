/*
Реализация Очереди с помощью одномерного массива.
front позиция первого элемента в очереди
rear позиция последнего элемента в очереди
*/

struct Queue {
  int front, rear;
  unsigned capacity;
  int *array;
};

int is_empty(struct Queue *qu)
{
  return qu -> rear == -1;
}

int is_full(struct Queue *qu)
{
  return qu -> capacity == qu -> capacity - 1;
}

// Возвращает последний элемент
int rear(struct Queue *qu)
{
  if (is_empty(qu))
    return INT_MIN;
  return qu -> array[qu -> rear];
}

// Возвращает первый элемент
int front(struct Queue *qu)
{
  if (is_empty(qu))
    return INT_MIN;
  return qu -> array[qu -> front];
}

// Удаляет первый элемент (в этом и разница между
// стеком и очередью)
int dequeue(struct Queue *qu)
{
  if (is_empty(qu))
    return INT_MIN;

  int item = qu -> array[qu -> front];
  qu -> front = qu -> front + 1;
  return item;
}

// Добавляет элемент в очередь
void enqueue(struct Queue *qu, int item)
{
  if (is_full(qu))
    return;

  qu -> array[++qu -> rear] = item;
  printf("%d enqueued to queue\n", item);
}

struct Queue *create_queue(unsigned capacity)
{
  struct Queue *qu = malloc(sizeof(struct Queue));
  assert(qu != NULL);

  qu -> capacity = capacity;
  qu -> front = 0;
  qu -> rear = -1;
  qu -> array = malloc(qu -> capacity * sizeof(int));

  return qu;
}

int main(void)
{
  struct Queue *qu = create_queue(1000);

  enqueue(qu, 10);
  enqueue(qu, 20);
  enqueue(qu, 30);
  enqueue(qu, 40);

  printf("%d dequeued from queue\n", dequeue(qu));
  printf("\n%d Front item is\n", front(qu));
  printf("Rear item is %d\n", rear(qu));

  return 0;
}
