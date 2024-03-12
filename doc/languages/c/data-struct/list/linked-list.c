/*
Односвязаный линейниый список
Каждый узел однонаправленного (односвязного) линейного списка содержит
одно поле указателя на следующий узел. Поле указателя последнего узла
содержит нулевое значение.
*/

// узел связанного списка
struct Node {
  int data; // какие - то данные
  struct Node *next; // указатель на следующей узел
};

void del_node(struct Node **head, int key)
{
  struct Node *temp = *head;
  struct Node *prev;
  // указатель *prev пока что пуст

  /*
    проверка temp != NULL
    сработает если будет: head = NULL;
    либо malloc вернет NULL на указатель */

  // если список не пуст и первый узел равен цифре key
  if (temp != NULL && temp -> data == key) {
    // *head будет указывать на следующий элемент в списке
    // тем самым первый элемент исчезнет
    *head = temp -> next;
    return;

    // temp = temp -> next;
    // почему это не срабатывает ???
    // потому что мы присваиваем temp значение temp -> next
    // а нужно присвоить *head = temp -> next
    // мы же будем в print_list перебирать head
  }

  // если список не пуст и список не равен key
  // когда temp -> data будет равен key тогда цикл прекратится
  // в этом цикле просто нужно дойти до нужного элемента
  // и остановиться на нем
  while (temp != NULL && temp -> data != key) {
    prev = temp;         // указатель prev будет указывать на temp
    temp = temp -> next; // переход к следующему элементу
  }

  // игнорируем значение key
  prev -> next = temp -> next;
}

// добавление в конец списка
void append(struct Node **head, int new_data)
{
  struct Node *new_node = malloc(sizeof(struct Node));

  // *head это адрес, который ссылается на содержимое структуры
  struct Node *last = *head; // ссылка на полный список
  // этот указатель нужен для того чтобы пройти список в цикле
  // и достигнуть NULL, *head для этого не годится, ибо если использовать
  // *head, то не получиться сделать free затем

  // добавление новых данных в узел
  new_node -> data = new_data;
  new_node -> next = NULL;

  // если список, который передали пустой
  if (*head == NULL) {
    *head = new_node;
    return;
  }

  // пройтись полностью по списку узлов
  // 6 1 2 3 затем last значение остается на 3
  while (last -> next != NULL)
    last = last -> next;

  // затем добавить в конец новый узел
  last -> next = new_node;
}

// добавление в начало списка
void push(struct Node **head, int new_data)
{
  // создание нового узла
  // при создании нового узла, у него data и next пусты
  struct Node *new_node = malloc(sizeof(struct Node));

  // добавление новых данных
  new_node -> data = new_data;

  // новый узел будет смотреть на следующий узел
  // тот, который был первым в списке
  // тем самым получается, то new_node становится первым
  new_node -> next = *head;

  // теперь head будет указывать на new_node
  *head = new_node;
}

// вывод списка
void print_list(struct Node *ptr)
{
  while (ptr != NULL) {
    printf("%d\n", ptr -> data);

    /*
      если не добавить эту строку будет бесконечный цикл,
      суть в том, что указатель ptr будет указывать
      на следующий указатель (адрес)
      pointer = next-pointer; */
    ptr = ptr -> next;
  }

  printf("\n");
}

int main(void)
{
  struct Node *head = NULL;
  struct Node *second = NULL;
  struct Node *third = NULL;

  /*
    создаем три узла и запрашиваем память под них
    например, head это указатель на структуру
    он будет указывать на {data = 0, next = 0x0}
    и через этот указатель мы можем взаимодействовать
    со структурой */
  head = malloc(sizeof(struct Node));
  second = malloc(sizeof(struct Node));
  third = malloc(sizeof(struct Node));

  // первый узел
  head -> data = 1;      // назначем данные
  head -> next = second; // связываем первый узел со вторым

  // второй узел
  second -> data = 2;
  second -> next = third;

  // третий узел (закрываем NULL)
  third -> data = 3;
  third -> next = NULL;

  /*
    head
      |
      |
  +---+---+     +---+---+       +----+------+
  | 1  | o----->|  2  | o-----> |  3 | NULL |
  +---+---+     +---+---+       +----+------+
  */

  // вывод всего списка, передаем первый узел
  print_list(head); // 1 2 3

  // вставляем 6 в самое начало
  push(&head, 6);
  print_list(head);

  /*
    Сначала я передавал head, а не &head
    таким образом не получалось добавить нужный элемент
    потому что head это просто адрес указателя
    Чтобы обратиться к ячейкам указателя, нужно передавать как &head
  */

  // вставляем 8 в конец
  append(&head, 8);
  print_list(head);

  // удаление элемента 1 из списка
  del_node(&head, 1);
  print_list(head);

  free(head);
  free(second);
  free(third);

  return 0;
}
