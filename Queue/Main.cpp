#include <iostream>

#include <ctype.h>

using namespace std;

#include "UBQueue.h"
#include "WCS_String.h"

void main ()
	{
	UBQueue <WCS_String> UBQ;
	char		c;
	WCS_String	W1;

	do {
		cout << "Push 'q' to queue a string, 'd' to dequeue a string, 's' to see the current size of the queue, and 'x' to exit the program." << endl;
		cin >> c;
		cin.ignore ();

		switch (toupper (c))
			{
			case 'Q':
				cout << "Type a string you want added to the queue:" << endl;
				cin >> W1;

				UBQ.Queue (W1);
				cout << "\n" << endl;
				break;
			case 'D':
				cout << UBQ.DeQueue () << endl;
				cout << "\n" << endl;
				break;
			case 'S':
				cout << "The current size is " << UBQ.Size () << ".\n" << endl;
				break;
			case 'X':
				cout << "Exiting the program." << endl;
				exit (0);
				break;
			default:
				cout << "Key not allowed. Press Q, D, S, or X.\n" << endl;
			}
		} while (c != toupper ('x'));
	}