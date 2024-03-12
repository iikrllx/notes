/*

Бинарное дерево - связный список

      tree
      ----
       1    <-- root
     /   \
    2     3
   /
  4             leaves

*/

struct node
{
  int data;
  struct node *left;
  struct node *right;
};

/* Очистка дерева */
void free_tree(struct node *tree)
{
  if (tree != NULL) {
    free_tree(tree -> left);
    free_tree(tree -> right);
    free(tree);
  }
}

void tree_print(struct node *tree)
{
  /*
    tree указывает на 1, address, address
    идет вызов tree_print из самой же функции tree_print
    доходит это до числа 4 и затем tree будет равняться NULL
    после того как условие не проходит, происходит выход из
    функции (осуществляется printf, начиная с 4 заканчивая 1) */
  if (tree != NULL) { // пока не встретится пустой узел
    tree_print(tree -> left);
    tree_print(tree -> right);
    printf("%d", tree -> data);
  }
}

struct node* new_node(int data)
{
  struct node *np = malloc(sizeof(struct node));

  np -> data = data;
  np -> left = NULL;
  np -> right = NULL;

  return np;
}

int main(void)
{
  struct node *root = new_node(1);

  /*
       1
     /   \
    NULL NULL
  */

  root -> left = new_node(2); // 2, 0x0, 0x0
  root -> right = new_node(3); // 3, 0x0, 0x0

  /*

         1
       /   \
      2     3
     / \    / \
 NULL NULL NULL NULL

  */

  root -> left -> left = new_node(4);

  /*

              1
           /    \
          2      3
        /  \    /  \
       4  NULL NULL NULL
      / \
   NULL NULL

  */

  tree_print(root);
  printf("\n");
  free_tree(root);

  return 0;
}
