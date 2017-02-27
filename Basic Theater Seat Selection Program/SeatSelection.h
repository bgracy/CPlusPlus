#ifndef SEAT_SELECTION_H
#define SEAT_SELECTION_H


class SeatSelection
{
	public:
		//***** Constructors / Destructor *****//
		SeatSelection	();
		SeatSelection	(int, int);
		~SeatSelection	();

		//***** Methods *****//
		bool	GetSeats			(int);
		bool	FindSeatsTogether	(int);

	private:
		int					SeatsLeft;
		int					StartRow;
		int					EndRow;
		static	const int	Seats		= 10;
		static	const int	Rows		= 20;
	
		bool				AllSeats	[Rows] [Seats];
		int					RowFound	[10];
		int					SeatFound	[10];
};

#endif