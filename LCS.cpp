#include <iostream>
#include<string>

using namespace std;

int b[30][30];																			//Table C will build the solution, table B will hold pointers
int c[30][30];

int LCS_Length(string X, string Y)
{
	int m = X.length();
	int n = Y.length();
	int length = 0;														

	for ( int i = 0; i <= m; i++ )													//Initialization of table C
		c[i][0] = 0;
	for ( int j = 0; j <= n; j++ )
		c[0][j] = 0;

	//for ( int i = 0; i < m; i++ )
	//{
	//	for ( int j = 0; j < n; j++ )
	//	{
	//		if ( X[i] == Y[j] )
	//		{
	//			c[i][j] = c[i - 1][j - 1] + 1;
	//			b[i+1][j+1] = 1;
	//		}
	//		else if ( c[i - 1][j] >= c[i][j - 1] )
	//		{
	//			c[i][j] = c[i - 1][j];												//Build a particular solution using the value from the cell above
	//			b[i+1][j+1] = 2;
	//		}
	//		else
	//		{
	//			c[i][j] = c[i][j - 1];
	//			b[i+1][j+1] = 0;
	//		}
	//	}
	//}
	for ( int i = 0; i < m; i++ )
	{
		for ( int j = 0; j < n; j++ )
		{
			if ( X[i] == Y[j] )
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if ( c[i - 1][j] >= c[i][j - 1] )
			{
				c[i][j] = c[i - 1][j];												//Build a particular solution using the value from the cell above
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 0;
			}
		}
	}
	cout << endl << "Table C:";
	for ( int i = 0; i < m; i++ )
	{
		cout << endl;
		for ( int j = 0; j < n; j++ )
		{
			cout << " " << c[i][j];
		}
	}

	cout << endl << "Table B:";
	for ( int i = 0; i < m; i++ )
	{
		cout << endl;
		for ( int j = 0; j < n; j++ )
		{
			cout << " " << b[i][j];
		}
	}


	length = c[m-1][n-1];
	return length;
}

void print_LCS(string X, int i, int j)
{
	
	/*if ( i == 1 || j == 1 )
	{
		return;
	}
	if ( b[i][j] == 1 )
	{
		
		print_LCS(X, i - 1, j - 1);
		cout << " " << X[i - 1];
	}
	else if ( b[i][j] == 2 )
		print_LCS(X, i - 1, j);
	else
		print_LCS(X, i, j - 1);*/

	char lcs[30];
	int k = 0;
	int x = i-1, y = j-1;
	while ( x > 0 || y > 0 )
	{
		if ( b[x][y] == 2 )
		{
			x--;
		}
		else if ( b[x][y] == 1 )
		{
			//cout << " " << X[x];
			lcs[k] = X[x];
			k++;
			x--; y--;
		}
		else
		{
			y--;
		}
	}
	lcs[k] = '\0';
	std::reverse(lcs, lcs + k);
	cout << endl << "LCS is: ";
	for ( int i = 0; i < k; i++ )
	{
		cout << lcs[i];
	}

}

int main()
{
	string A, B;
	cout << endl << "Enter string A:";
	getline(cin, A);
	cout << endl << "Enter string B:";
	getline(cin, B);
	
	cout << endl << "Length of LCS: " << LCS_Length(A, B);
	print_LCS(A, A.length(), B.length());

	return 0;
}