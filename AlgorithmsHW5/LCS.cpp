#include <iostream>
#include<string>

using namespace std;

//string LCS_Length(string A, string B)
//{
//	int m = A.length();
//	int n = B.length();
//	int b[30][30], c[30][30];														//Table C will build the solution, table B will hold pointers
//
//	for ( int i = 1; i <= m; i++ )													//Initialization of table C
//		c[i][0] = 0;
//	for ( int j = 0; j <= n; j++ )
//		c[0][j] = 0;
//
//	for ( int i = 1; i <= m; i++ )
//	{
//		for ( int j = 1; i <= n; j++ )
//		{
//			if ( )
//		}
//	}
//}

int main()
{
	string A, B;
	cout << endl << "Enter string A:";
	getline(cin, A);
	cout << endl << "Enter string B:";
	getline(cin, B);
	A[1] = 'C';
	cout << endl << A;

	getchar();

	return 0;
}