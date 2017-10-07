#include<iostream>
#include<math.h>
//ADDING SOME COMMENTS
using namespace std;
int n;

//Performs selection sort
void SelectionSort(int input_numbers[])
{
	int position;										//Used for traversing through the array
	int temp;											//Used for performing swap
	cout << "\nPart A:\nHow many numbers are to be sorted?";
	do
	{
		cin >> n;
		if (n == 0)
		{
			cout << "\nPlease enter a value greater than zero:\n";
		}
	}
	while (n <= 0);
	cout << "\nEnter the numbers: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> input_numbers[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		position = i;									//Set position to start of array when loop starts
		for (int j = i + 1; j < n; j++)
		{
			if (input_numbers[j] < input_numbers[position])
			{
				position = j;
			}
		}

		if (position != i)
		{
			temp = input_numbers[i];
			input_numbers[i] = input_numbers[position];
			input_numbers[position] = temp;
		}
	}

	cout << "\nSorted numbers:\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << input_numbers[i] << " ";
	}

}

void SelectionSort_modified(int input_numbers[])
{
	int k;
	cout << "\nPart B:\nEnter value of k: ";
	//If user enters K greater than number of elements in the array
	do
	{
		cin >> k;
		if (k > n)
		{
			cout << "\nYou entered an incorrect value for k. k cannot be greater than n. Please enter a correct value for k:\n";
		}
	}
	while (k > n);
	cout << "\nFirst k sorted numbers:\n" << endl;
	for (int i = 0; i < k; i++)
	{
		cout << input_numbers[i] << " ";
	}
}

void obtainMedian(int input_numbers[])
{
	if ((n % 2) == 0)
	{
		cout << "\nMedian of the list is:\n" << float((input_numbers[(n / 2) - 1]) + (input_numbers[n / 2])) / 2;
	}
	else
	{
		cout << "\nMedian of the list is:\n" << input_numbers[n / 2];
	}
	cout << "\nMedian of the list is:\n";
}

int main()
{
	int input_numbers[50];								//Stores the input
	int choice;
	//Prints out a menu
	do
	{
		cout << "\n1. Problem 1\n2. Problem 2\n3. Problem 3\n4. Exit\n\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1: SelectionSort(input_numbers);
			SelectionSort_modified(input_numbers);
			obtainMedian(input_numbers);
			break;
		default:
			break;
		}
	}
	while (choice != 4);
	return 0;
}
