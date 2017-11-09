#include<iostream>
#include<functional>
#include<algorithm>
#include<math.h>


using namespace std;

void knapsack()
{
	int weights[20], values[20], table[100][100], knapsack_weight, n, x,y,k=0,current, solution_set[50];			//table[i] represents weight of knapsack, table[][j] represents no. of items
	cout << endl << "Enter the weight of the knapsack: ";
	cin >> knapsack_weight;
	while ( knapsack_weight <= 0 )
	{
		cout << endl << "Wrong input, please enter a value greater than zero:";
		cin >> knapsack_weight;
	}
	cout << endl << "How many items?: ";
	cin >> n;
	for ( int i = 1; i <= n; i++ )
	{
		cout << endl << "Enter the weight of item " << i << ":";
		cin >> weights[i];
		cout << endl << "Enter the value of item " << i << ":";
		cin >> values[i];
	}

	cout << endl << "The table is:" << endl;

	for ( int i = 1; i <= n; i++ )							//Rows from 1 to no. of items
	{
		for ( int j = 0; j <= knapsack_weight; j++ )							//Columns from 0 to weight to knapsack
		{
			if ( j == 0 )														//Initializing the first column to zero
			{
				table[i][j] = 0;
			}
			else
			{
				if ( weights[i] <= j && i==1 )									//For the first row
				{
					table[i][j] = values[i];
				}
				else															//For subsequent rows
				{
					table[i][j] = table[i - 1][j];								//Keeps the previous solution, takes the value from the cell one position above
					if ( weights[i] <= j )
					{
						table[i][j] = max(values[i] + table[i - 1][j - weights[i]], table[i][j]);			//Formula for calculating new value at a cell
					}
				}
			}
			cout << table[i][j] << " ";												//Prints out the table
		}
		cout << endl;
	}
	cout << endl << "Maximum value that the knapsack can contain: " << table[n][knapsack_weight];

	//Algorithm to backtrack and print the item numbers picked
	current = table[n][knapsack_weight];							//Starting from last cell in the table
	x = n; y = knapsack_weight;

	while(current!=0 )
	{
		if ( table[x - 1][y] == current )									//If value above a cell is the same as the current cell, then that item was not picked
		{
			current = table[x - 1][y];										//Move to the cell above
			x--;
		}
		else																//If value above a cell is not the same as the current cell
		{																	
			solution_set[k] = x;											//Add the current item as part of the list of items picked
			k++;
			current = table[x - 1][y - weights[x]];							//Proceed to the next cell
			y = y - weights[x];
			x--;
		}
	}
	
	//Printing out the list of items picked
	cout << endl << "Item numbers picked are: " << endl;
	std::sort(solution_set, solution_set + k);
	for ( int i = 0; i < k; i++ )
	{
		cout << solution_set[i] << " ";
	}
	
}

void MakeChangeOptimalB(int change, int k, int c)
{
	int coins[20], coin_count[20];				//'Coins' holds the set of coins with different denominations, 'coin_count' holds number of coins of a particular denomination


	for ( int i = 0; i <= k; i++ )										//Creating the set of coins, for example : {1, 3, 9, 27, 81} when c = 3 and k = 4
	{	
		coins[i] = pow(c, i);
		coin_count[i] = 0;
	}
	std::sort(coins, coins + (k + 1), std::greater<int>());				//Arranging the set of coins in decreasing order so that algorithm can be applied starting from first position in array

	//Algorithm to make change
	while ( change != 0 )
	{
		for ( int i = 0; i <= k; i++ )
		{
			if ( change >= coins[i] )
			{
				coin_count[i] = coin_count[i] + floor(change / coins[i]);
				change = change - (coin_count[i] * coins[i]);
			}
			else
			{
				continue;
			}
		}
	}

	//Printing out the result
	for ( int i = 0; i <= k; i++ )
	{
		cout << endl << "No. of coins of denomination " << coins[i] << " :" << coin_count[i];
	}
}

//Greedy method to make change using the algorithm provided in question 2 A of the written section
void MakeChangeOptimalA(int change)
{
	int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
	do
	{
		if ( change < 5 )
		{															//Make change using pennies
			pennies = pennies + change;
			change = change - pennies;
		}
		else if ( change >= 5 && change < 10 )
		{															//Make change using nickels
			nickels = nickels + 1;
			change = change - 5;
		}
		else if ( change >= 10 && change < 25 )
		{															//Make change using dimes
			dimes = dimes + floor(change / 10);
			change = change - (dimes * 10);
		}
		else if ( change >= 25 )
		{															//Make change using quarters
			quarters = quarters + floor(change / 25);
			change = change - (quarters * 25);
		}
	}
	while ( change != 0 );
	cout << endl << "No. of quarters: " << quarters;
	cout << endl << "No. of dimes: " << dimes;
	cout << endl << "No. of nickels: " << nickels;
	cout << endl << "No. of pennies: " << pennies << endl;

}

//Makes change using greedy method and may not always be optimal
int MakeChangeNK(int change, int coins[], int n)
{
	int currentcoin;                           //Considers a coin in the set of coins
	if ( change == 0 )                         //If no change is available to be made
	{
		return 0;
	}

	for ( int i = 0; i < n; i++ )              //Loop goes through each coin in the set of coins
	{
		currentcoin = coins[i];                //Always selects largest coin first as list of coins is in descending order
		if ( change >= currentcoin )           
		{
			cout << currentcoin << " ";        //Change is made using the current coin
			return 1 + MakeChangeNK(change - currentcoin, coins, n);        //Call the same algorithm recursively on the remaining change
		}
	}

	return 0;		      //If change cannot be made
}

int main()
{
	int ch, answer, coins[20], change, n, k, c;
	
	do					//Prints out a menu
	{
		cout << endl << endl << "1. Problem 1 (Providing 0-1 Knapsack solution using dynamic programming, table and backtracking)" << endl << "2. Problem 2 part A-A (Making change using quarters, dimes, nickels and pennies)" << endl << "3. Problem 2 part A-B (Making change when the set of coins are: c^k)" << endl << "4. Problem 2 part B (Making change using algorithm that runs in O(nk) time)" << endl << "5. Exit" << endl << "Enter choice:";
		cin >> ch;
		switch ( ch )
		{
			case 1:
				knapsack();
				break;
			case 2:
				cout << endl << "Enter the amount of change: ";
				cin >> change;
				while ( change <= 0 )
				{
					cout << endl << "Wrong input, please enter a value greater than zero:";
					cin >> change;
				}
				cout << endl << "Answer using algorithm provided in question 2 A of the written section:";
				MakeChangeOptimalA(change);								//Make change using greedy method which produces optimal solution
				break;
			case 3: 
				cout << endl << "Enter the amount of change: ";
				cin >> change;
				while ( change <= 0 )
				{
					cout << endl << "Wrong input, please enter a value for change greater than zero:";
					cin >> change;
				}
				cout << endl << "Enter the value of 'k' (k >= 1):";
				cin >> k;
				while ( k < 1 )
				{
					cout << endl << "Wrong input, please enter a value for 'k' greater than zero:";
					cin >> k;
				}
				cout << endl << "Enter the value of 'c' (c > 1):";
				cin >> c;
				while ( c <= 1 )
				{
					cout << endl << "Wrong input, please enter a value for 'c' greater than one:";
					cin >> c;
				}
				MakeChangeOptimalB(change, k, c);					//Make change using greedy method for a certain value of c and k
				break;

			case 4:
				cout << endl << "Enter the amount of change: ";
				cin >> change;
				while ( change <= 0 )							
				{
					cout << endl << "Wrong input, please enter a value greater than zero:";
					cin >> change;
				}
				cout << endl << "How many distinct denominations (k)?: ";
				cin >> n;
				cout << endl << "Enter the set of " << n << " distinct coins: ";
				for ( int i = 0; i < n; i++ )
				{
					cin >> coins[i];
				}
				std::sort(coins, coins + n, std::greater<int>());		//Sorting the set of coins in descending order so that greedy algorithm can be applied
				cout << endl << "The coins are: ";
				answer = MakeChangeNK(change, coins, n);					//Applying the greedy algorithm to make change
				break;
			case 5:
				break;
			default: cout << endl << "Invalid choice!";
				break;
		}
	}
	while ( ch != 5 );
	return 0;
}