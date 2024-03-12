int size = 0;

void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

void heapify(int *array, int size, int i)
{
	if (size == 1) {
		printf("Single element in the heap\n");
	} else {
		int largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < size && array[l] > array[largest])
			largest = l;
		if (r < size  && array[r] > array[largest])
			largest = r;

		if (largest != i)
		{
		      swap(&array[i], &array[largest]);
		      heapify(array, size, largest);
		}
	}
}

void insert(int *array, int newNum)
{
	if (size == 0)
	{
		array[0] = newNum;
		size += 1;
	} else {
		array[size] = newNum;
		size += 1;

		for (int i = size / 2 - 1; i >= 0; i--)
			heapify(array, size, i);
	}
}

void printArray(int *array)
{
	for (int i = 0; i < size; i++)
		printf("%d: %d\n", i, array[i]);
}

void deleteRoot(int *array, int x)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (x == array[i])
			break;
	}

	swap(&array[i], &array[size - 1]);
	size -= 1;
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(array, size, i);
	}
}

int main(void)
{
	int array[3];

	insert(array, 3);
	insert(array, 4);
	insert(array, 9);
	insert(array, 5);
	insert(array, 2);

	printArray(array);

	deleteRoot(array, 4);

	printf("\n");
	printArray(array);

	return 0;
}
