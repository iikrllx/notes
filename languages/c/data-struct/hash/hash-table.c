/*
In hash table, the data is stored in an array format where
each data value has its own unique index value.
Access of data becomes very fast, if we know the index of the desired data.
*/

/* Size of the Hash Table */
#define SIZE 20

struct DataItem {
	int data;
	int key;
};

struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;

int hashCode(int key)
{
	return key % SIZE;
}

struct DataItem *delete(int key)
{
	int hashIndex = hashCode(key);
	while (hashArray[hashIndex] != NULL)
	{
		if (hashArray[hashIndex]->key == key)
			hashArray[hashIndex] = NULL;

		++hashIndex;
		hashIndex %= SIZE;
	}

	return NULL;
}

struct DataItem *search(int key)
{
	int hashIndex = hashCode(key);

	while (hashArray[hashIndex] != NULL)
	{
		if (hashArray[hashIndex]->key == key)
			return hashArray[hashIndex];
		++hashIndex;
		hashIndex % SIZE;
	}

	return NULL;
}

void display()
{
	printf("index: key: data\n");
	for (int i = 0; i < SIZE; i++)
	{
		if (hashArray[i] != NULL)
			printf("%d: %d: %d\n", i, hashArray[i]->key, hashArray[i]->data);
		else
			printf("%d: ~\n", i);
	}
}

void insert(int key, int data)
{
	struct DataItem *item = malloc(sizeof(struct DataItem));
	item->data=data;
	item->key=key;

	/* get the hash
 	* 42 % 20 -> 2
 	* 423 % 20 -> 3
 	* get last N */
	int hashIndex = hashCode(key);

	while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1)
	{
		++hashIndex;
		hashIndex %= SIZE;
	}

	hashArray[hashIndex] = item;
}

int main()
{
	dummyItem = malloc(sizeof(struct DataItem));
	dummyItem->data = -1;
	dummyItem->key = -1;

	insert(1, 20);  /* 1 index */
	insert(2, 70);  /* 2 index */
	insert(42, 80); /* 2 index, but 3 */
	insert(4, 25);  /* 4 index */
	insert(12, 44);
	insert(14, 32);
	insert(17, 11);
	insert(13, 78);
	insert(37, 97);

	display();

	item = search(37);
	if (item)
		printf("after search: %d: %d\n", item->key, item->data);

	delete(37);
	item = search(37);
	if (item)
		printf("after search: %d: %d\n", item->key, item->data);

	display();

	return 0;
}
