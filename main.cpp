#include "rbTreeMap.h"

int main()
{
	srand(time(NULL));

	rbTreeMap<int, char> t;

	int *arr = new int[25];

	// Unqiue RNG for keys
	for (size_t i = 0; i < 25; i++)
	{
		arr[i] = rand() % 500 + 1;

		for (size_t j = 0; j < i; j++)
		{
			while (arr[i] == arr[j])
			{
				arr[i] = rand() % 500 + 1;
				j = 0;
			}
		}

		t.insert(arr[i], (char)(rand() % 255));
	}

	t.print();

	delete[] arr;
}