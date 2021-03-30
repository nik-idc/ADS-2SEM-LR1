#include "pch.h"
#include "CppUnitTest.h"
#include <ctime>
#include "..\rbTreeMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTLR1
{
	TEST_CLASS(UTLR1)
	{
	public:
		
		TEST_METHOD(TestGetKeysAndGetValues)
		{
			srand(time(NULL));

			rbTreeMap<int, char> t;

			size_t arrSize = rand() % 100 + 1; // Generating a random size for key and value arrays
			int *arr = new int[arrSize];
			char *chArr = new char[arrSize];

			// Filling the key and value arrays, with keys beeing generated so that there are no two same keys
			for (size_t i = 0; i < arrSize; i++)
			{
				arr[i] = rand() % 500 + 1;
				chArr[i] = rand() % 255;

				for (size_t j = 0; j < i; j++)
				{
					while (arr[i] == arr[j])
					{
						arr[i] = rand() % 500 + 1;
						j = 0;
					}
				}

				t.insert(arr[i], chArr[i]);
			}

			// Asserting whether getKeys and getValues return an array of needed size
			for (size_t i = 0; i < arrSize; i++)
			{
				Assert::IsTrue(sizeof(t.getKeys()) == sizeof(arr));
				Assert::IsTrue(sizeof(t.getValues()) == sizeof(chArr));
			}

			delete[] arr;
		}

		TEST_METHOD(TestInsert)
		{
			rbTreeMap<int, char> t;
			int *arr;

			t.insert(23, 'a');
			t.insert(12, 'b');
			t.insert(21, 'c');
			t.insert(2, 'd');
			t.insert(4, 'e');
			t.insert(43, 'f');
			t.insert(11, 'g');
			t.insert(32, 'h');
			t.insert(10, 'i');

			int supposedToBe[9] = {21, 4, 32, 2, 11, 23, 43, 10, 12}; // What the breadth-first traversal of the above tree should look like

			// Getting the keys array of our tree
			arr = t.getKeys();

			// Asserting the correctness of restoring the red-black tree property function
			for (size_t i = 0; i < 9; i++)
			{
				Assert::IsTrue(arr[i] == supposedToBe[i]);
			}
			delete arr;
		}

		TEST_METHOD(TestFind)
		{
			srand(time(NULL));

			rbTreeMap<int, char> t;
			
			int *arr = new int[100];

			// Unqiue RNG for keys
			for (size_t i = 0; i < 100; i++)
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

			// Asserting if all the elements had been added to the tree
			for (size_t i = 0; i < 100; i++)
			{
				Assert::IsTrue(t.find(arr[i]));
			}

			delete[] arr;
		}

		TEST_METHOD(TestRemove)
		{
			srand(time(NULL));

			rbTreeMap<int, char> t;

			int *arr = new int[100];

			// Unqiue RNG for keys
			for (size_t i = 0; i < 100; i++)
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

			// Asserting whether the element is truly removed from the list by using the find function
			for (size_t i = 0; i < 100; i++)
			{
				t.remove(arr[i]);
				Assert::IsTrue(!t.find(arr[i]));
			}

			delete[] arr;
		}

		TEST_METHOD(TestClear)
		{
			srand(time(NULL));

			rbTreeMap<int, char> t;

			int *arr = new int[100];

			// Unqiue RNG for keys
			for (size_t i = 0; i < 100; i++)
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

			t.clear();
			Assert::IsTrue(t.empty());

			delete[] arr;
		}
	};
}
