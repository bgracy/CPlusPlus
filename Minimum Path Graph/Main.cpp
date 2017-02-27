#include <iostream>

using namespace std;

#include <ctype.h>
#include <limits.h>
#include <memory.h>

typedef	unsigned int	UINT;

const	int		MaxNodes	(12);

		int		Cost			[MaxNodes] [MaxNodes];
		char	CurrentPath		[MaxNodes];
		UINT	MinCost			(UINT_MAX);
		char	MinPath			[MaxNodes];
		int		NumNodes;
		bool	Visited			[MaxNodes];

void ReadInCosts (char, int);
void FindMinCost (int, UINT, int);

void main ()
	{
	int		i;
	char	x;
	char	y;
	bool	Again;

		do {
			do {
			cout << "A maximum of 12 nodes is allowed.\n"
				 << "How many nodes will there be? " << endl;
			cin >> NumNodes;
			
			if ((NumNodes < 13) && (NumNodes > 1))
					{
					for (i = 0; i < NumNodes; i++)
						{
						x = (i + 'A');
						ReadInCosts (x, i);
						}
					}
				else;
				} while ((NumNodes > 12) || (NumNodes < 2)); 

			memset (Visited, false, MaxNodes);
			for (i = 0; i < NumNodes; i++)
				{
				CurrentPath [0]	= i + 'A';
				FindMinCost (i, 0, 1);
				}
			
			if (MinCost < UINT_MAX)
					{
					cout << "The minimum cost of those nodes is " << MinCost << " by going to each node in this order: " << endl;
					for (i = 0; i < NumNodes; i++)
						cout << MinPath [i] << endl;
					}
				else
					cout << "Could not reach all nodes in the graph" << endl;
			
			cout << endl;
			cout << "Do you have more graphs you would like to test?  Y/N" << endl;
			cin >> y;
			cout << endl;

			if (toupper (y) == 'Y')
					{
					Again = true;
					MinCost = UINT_MAX;
					}
				else
					{
					Again = false;
					exit (0);
					}
		} while (Again == true);
	}

void ReadInCosts (char c, int CurrNode)
	{
	char			temp;
	char			yn;
	int				i;
	unsigned int	COST;


	for (i = 0; i < NumNodes; i++)
		{
		temp = i + 'A';
		if (i != CurrNode)
				{
				cout << "Is there a cost between " << c << " and " << temp << "?  Y/N: ";
				cin >> yn;
				cout << endl;
				if (toupper (yn) == 'Y')
						{
						cout << "What is the cost between them: ";
						cin >> Cost [CurrNode] [i];
						cout << endl;
						}
				else
					Cost [CurrNode] [i] = 0;
				}
			else
				Cost [CurrNode] [i] = 0;
		}
	}


void FindMinCost  (int CurrentNode, UINT CurrentCost, int NumNodesVisited)
	{
	int		i;
	int		TempCost;

	Visited [CurrentNode] = true;
	for (i = 0; i < NumNodes; i++)
		if (!Visited [i] && (Cost [CurrentNode] [i] > 0))
				{
				TempCost = CurrentCost + Cost [CurrentNode] [i];
				if (TempCost < MinCost)
						{
						CurrentPath [NumNodesVisited] = i + 'A';
						FindMinCost (i, TempCost, NumNodesVisited + 1);
						}
					else;
				}
			else;
	for (i = 0; Visited [i] && (i < NumNodes); i++);
	if (i == NumNodes)
			{
			MinCost = CurrentCost;
			memcpy (MinPath, CurrentPath, NumNodes);
			}
		else;
	Visited [CurrentNode] = false;
	}
