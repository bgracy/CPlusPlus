#include <iostream>

using namespace std;

#include "SeatSelection.h"

void main ()
{
	int				TypeofSeat;
	int				NumSeats;
	SeatSelection	Premium (1, 5);
	SeatSelection	Regular (6, 15);

	do {
		cout << "Premium (1) or Regular (2) or Exit (0): ";
		cin >> TypeofSeat;
		if ((TypeofSeat != 1) && (TypeofSeat != 2))
			exit (0);
		else
			{
			cout << "Number of tickets: ";
			cin >> NumSeats;

			if (TypeofSeat == 1)
				Premium.GetSeats (NumSeats);
			else
				Regular.GetSeats (NumSeats);
			}
		cout << endl;
		} while (TypeofSeat == 1 || TypeofSeat == 2);
}