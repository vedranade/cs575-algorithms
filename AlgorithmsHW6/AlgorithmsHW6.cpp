#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<functional>

using namespace std;

struct table
{
	int value[30][30];									//Stores the lengths
	char back_pointer[30][30];							//Stores the vertices from where that length was obtained
};
table output_table;

struct V
{
	int key;
	int parent;
	int color;
};
V vertex[30];

void printMST(int adjacency_matrix[30][30], int no_of_vertices)
{
	printf("Edge   Weight\n");
	for ( int i = 1; i < no_of_vertices; i++ )
		printf("%d - %d    %d \n", vertex[i].parent, i, adjacency_matrix[i][vertex[i].parent]);
}

void Prim_algorithm()
{
	int adjacency_matrix[30][30];
	int no_of_vertices;
	cout << endl << "Enter the number of vertices in the graph:";
	cin >> no_of_vertices;
	char matrix_label[27];
	cout << endl << "Enter " << no_of_vertices << " vertices, starting from the source vertex ";		//Accepting each vertex label
	for ( int i = 0; i < no_of_vertices; i++ )
	{
		cin >> matrix_label[i];
	}

	for ( int i = 0; i < no_of_vertices; i++ )
	{
		for ( int j = 0; j < no_of_vertices; j++ )
		{
			adjacency_matrix[i][j] = 0;
		}
	}

	for ( int i = 0; i < no_of_vertices; i++ )
	{
		for ( int j = 0; j < no_of_vertices; j++ )
		{
				cout << endl << "Enter the weight of the edge between vertex " << matrix_label[i] << " and vertex " << matrix_label[j] << "(or 999 if no edge exists):";
				cin >> adjacency_matrix[i][j];
		}
	}
	
	
	for ( int i = 0; i < no_of_vertices; i++ )						//Initialization
	{
		vertex[i].key = 999;
		//vertex[i].parent = -1;
		vertex[i].color = 0;				//0 = white, 1 = black
	}
	vertex[0].key = 0;												//Considering the root vertex as the first vertex in the adjacency matrix
	vertex[0].parent = -1;
	vector<int> p_queue;											//Initializing a min priority queue using standard C++ syntax
	for ( int i = 0; i < no_of_vertices; i++ )
		p_queue.push_back(vertex[i].key);
	std::sort(p_queue.begin(), p_queue.end());						//Storing elements of queue in ascending order

	int u, x, index;
	for(int j = 0; j < no_of_vertices - 1; j++ )
	//while(!p_queue.empty())
	{
		u = p_queue.front();
		p_queue.erase(p_queue.begin());										//Performing the extract_min operation on the priority queue
		x = 0;
		while ( x < no_of_vertices )							//Since we are only storing the key value of a vertex in the queue, we need to obtain the corresponding vertex once a key has been removed from the queue
		{
			if ( vertex[x].key == u )
			{
				index = x;
				break;
			}
			else
				x++;
		}
		vertex[index].color = 1;
		for ( int i = 0; i < no_of_vertices; i++ )
		{
			if ( adjacency_matrix[u][i] && vertex[i].color == 0 && adjacency_matrix[u][i] < vertex[i].key )
			{
				vertex[i].key = adjacency_matrix[u][i];
				p_queue.pop_back();
				p_queue.push_back(vertex[i].key);								//Q.decreaseKey() operation
				std::sort(p_queue.begin(), p_queue.end());
				vertex[i].parent = u;
			}
		}
		//vertex[index].color = 1;
	}

	//printMST(adjacency_matrix, no_of_vertices);
	printf("Edge   Weight\n");
	for ( int i = 1; i < no_of_vertices; i++ )
		printf("%c - %c    %d \n", matrix_label[vertex[i].parent], matrix_label[i], adjacency_matrix[i][vertex[i].parent]);
	
}

void Dijkstra_algorithm()
{
	int k=0;
	int adjacency_matrix[30][30];
	cout << endl << "Enter the number of vertices in the graph:";
	int no_of_vertices;
	cin >> no_of_vertices;
	char matrix_label[27];
	cout << endl << "Enter " << no_of_vertices << " vertices, starting from the source vertex ";		//Accepting each vertex label
	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		cin >> matrix_label[i];
	}

	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		for ( int j = 1; j <= no_of_vertices; j++ )
		{
			adjacency_matrix[i][j] = 0;
		}
	}

	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		for ( int j = 1; j <= no_of_vertices; j++ )
		{
			if(adjacency_matrix[j][i] == 0 )					//Accept a value only if a value is not already present. Would not apply for directed graphs
			{
				cout << endl << "Enter the weight of the edge between vertex " << matrix_label[i] << " and vertex " << matrix_label[j] << "(or 999 if no edge exists):";
				cin >> adjacency_matrix[i][j];
				adjacency_matrix[j][i] = adjacency_matrix[i][j];
			}
		}
	}

	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		for ( int j = 1; j <= no_of_vertices; j++ )
		{
			output_table.value[i][j] = 0;						//Initializing the output table
		}
	}

	int i = 0;
	for ( int j = 0; j <= no_of_vertices; j++ )
	{
		//adjacency_matrix[i][j] = 999;
		output_table.value[i][j] = 999;
	}
	int j = 0;
	for ( int i = 0; i <= no_of_vertices; i++ )
	{
		//adjacency_matrix[i][j] = 999;
		output_table.value[i][j] = 999;
	}
	
	
	//Printing out the adjacency matrix
	cout << endl << "Adjacency matrix:" << endl;
	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		cout << "\t" << matrix_label[i];
	}
	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		cout << endl;
		cout << matrix_label[i] << "\t";
		for ( int j = 1; j <= no_of_vertices; j++ )
		{
			cout << adjacency_matrix[i][j] << "\t";
		}
	}
	
	//Building the output table:
	int current_length=0, flag = 0;
	int current_min;
	char solution_char;
	vector<int> solution_list;
	vector<char> solution_label;
	solution_list.push_back(0);
	k = 1;
	int next_ivalue = 1, previous_ivalue = 0;
	int check_min_flag = 0;
	i = 1;
	solution_label.push_back(matrix_label[i]);
	while ( k <= no_of_vertices )
	{
		j = 1;
		current_min = 999;
		while ( j <= no_of_vertices )
		{
			if ( i == 1 && j == 1 )							//Filling the very first cell of the output table as zero
			{
				output_table.value[k][j] = 0;
				output_table.back_pointer[k][j] = matrix_label[i];
			}
			else 							
			{
					if ( std::find(solution_list.begin(), solution_list.end(), output_table.value[k - 1][j]) != solution_list.end() && std::find(solution_label.begin(), solution_label.end(), output_table.back_pointer[k-1][j]) != solution_label.end() )		//If upper cell is part of the solution
					{
						output_table.value[k][j] = output_table.value[k - 1][j];
						output_table.back_pointer[k][j] = output_table.back_pointer[k - 1][j];
						check_min_flag = 0;
					}
					else if ( output_table.value[k-1][j] < adjacency_matrix[i][j] + current_length )				//If current path is not shorter than previously checked path
					{
						output_table.value[k][j] = output_table.value[k-1][j];
						output_table.back_pointer[k][j] = output_table.back_pointer[k-1][j];
						check_min_flag = 1;
					}
					else													//If a shorter path is present
					{
						output_table.value[k][j] = adjacency_matrix[i][j] + current_length;
						output_table.back_pointer[k][j] = matrix_label[i];
						check_min_flag = 1;
					}
					
					if ( output_table.value[k][j] < current_min && check_min_flag == 1)
					{
						current_min = output_table.value[k][j];
						solution_char = output_table.back_pointer[k][j];
						next_ivalue = j;
						flag = 1;
					}					
							
			}
			j++;
		}
		if ( flag == 1 )
		{
			solution_list.push_back(current_min);					//Obtained minimum value in a row and added it to solution list
			current_length = current_min;
			solution_label.push_back(solution_char);
			previous_ivalue = i;
			i = next_ivalue;
			flag = 0;
			check_min_flag = 0;
		}
		k++;
	}
	
	//Displaying output table:
	cout << endl << "Output: " << endl;
	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		cout << "\t" << matrix_label[i];
	}
	
	for ( int i = 1; i <= no_of_vertices; i++ )
	{
		cout << endl;
		cout << matrix_label[i] << "\t";
		for ( int j = 1; j <= no_of_vertices; j++ )
		{
			cout << output_table.value[i][j] << "," << output_table.back_pointer[i][j] << "\t";
		}
	}	
}

int main()
{
	int ch;
	do
	{
		cout << endl << "1. Problem 1 (Dijkstra's Algorithm)";
		cout << endl << "2. Problem 2 (Prim's Algorithm)";
		cout << endl << "3. Exit";
		cout << endl << "Enter choice:";
		cin >> ch;
		switch (ch )
		{
			case 1:
				Dijkstra_algorithm();
				break;
			case 2:
				Prim_algorithm();
				break;
			case 3:
				break;
			default: cout << endl << "Enter a valid choice!";
				break;
		}
	}
	while ( ch!=3 );
	getchar();
	return 0;
}