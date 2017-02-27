#include <iostream>

using namespace std;

#include "SeatSelection.h"

//***** Constructors / Destructor *****//

SeatSelection::SeatSelection ()
{
	SeatsLeft	= 0;
	StartRow	= 0;
	EndRow		= 0;
}

SeatSelection::SeatSelection (int StartingRow, int NumRows)
{
	SeatsLeft	= 0;
	StartRow	= StartingRow -1;
	EndRow		= StartRow + NumRows;
	for (int i = StartRow; i < EndRow; i++)
		{
		for (int j = 0; j < 10; j++)
			{
			AllSeats [i] [j] = false;
			SeatsLeft++;
			}
		}
}

SeatSelection::~SeatSelection ()
{
}

//***** Methods/Functions *****//

bool SeatSelection::GetSeats (int NumSeats)
{	
	if (NumSeats == 1)
		{
		for (int i = StartRow; i < EndRow; i++)
			{
			for (int j = 0; j < 10; j++)
				{
				if (AllSeats [i] [j] == false)
					{
					cout << "Your seat is: " << i+1 << char(j + 65) << endl;
					AllSeats [i] [j] = true;
					SeatsLeft--;
					return true;
					}
				else;
				}
			}
		cout << "Sorry, only " << SeatsLeft << " seats of that type are available." << endl;
		}
	else
		{
		if (NumSeats <= SeatsLeft)
			{
			if ((FindSeatsTogether (NumSeats)) == false)
				{
				int	SeatsFound = 0;
				for (int i = StartRow; i < EndRow; i++)
					{
					for (int j = 0; j < 10; j++)
						{
						if (AllSeats [i] [j] == false)
							{
							RowFound	[SeatsFound] = i;
							SeatFound	[SeatsFound] = j;
							SeatsFound++;
							SeatsLeft--;
							AllSeats	[i] [j] = true;
							if (SeatsFound == NumSeats)
								{
								cout << "Your seats are: ";
								for (int m = 0; m < NumSeats; m++)
									{
									cout << ((RowFound [m]) + 1) << char((SeatFound [m]) + 65) << " ";
									}
								cout << endl;
								return true;
								}
							else;
							}
						else;
						}
					}
				}
			else
				{
				cout << "Your seats are: ";
				for (int k = 0; k < NumSeats; k++)
					{
					cout << ((RowFound [k]) + 1) << char (SeatFound [k] + 65) << " ";
					}
				cout << endl;
				}
			}
		else
			cout << "Sorry, only " << SeatsLeft << " seats of that type are available." << endl;
		}
}

bool SeatSelection::FindSeatsTogether (int NumSeats)
{
	int	ConsecutiveSeats	= 0;
	for (int i = StartRow; i < EndRow; i++)
		{
		for (int j = 0; j < 10; j++)
			{
			if (AllSeats [i] [j] == false)
				{
				if (ConsecutiveSeats == 0)
					{
					RowFound	[ConsecutiveSeats] = i;
					SeatFound	[ConsecutiveSeats] = j;
					ConsecutiveSeats++;
					}
				else														
					{
					if (i != RowFound [ConsecutiveSeats-1])
						{
						ConsecutiveSeats = 0;
						RowFound	[ConsecutiveSeats] = i;
						SeatFound	[ConsecutiveSeats] = j;
						ConsecutiveSeats++;
						}
					else
						{
						RowFound	[ConsecutiveSeats] = i;
						SeatFound	[ConsecutiveSeats] = j;
						ConsecutiveSeats++;
						if (ConsecutiveSeats == NumSeats)
							{
							for (int l = 0; l < NumSeats; l++)
								{
								AllSeats [RowFound [l]] [SeatFound [l]] = true;
								}
							SeatsLeft = SeatsLeft - NumSeats;
							return true;
							}
						else;
						}
					}
				}
			else
				{
				ConsecutiveSeats = 0;
				}
			}
		}
	return false;
}