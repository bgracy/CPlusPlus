#ifndef UBQUEUE_H
#define UBQUEUE_H

#include "UBArray.h"

template <class DATA>
class UBQueue: private UBArray <DATA, unsigned int>
	{
	public:
				//*****CONSTRUCTOR/DESTRUCTOR*****//
						UBQueue		();
						~UBQueue	();
				//************FUNCTIONS***********//
		bool			Queue		(const DATA &);
		DATA &			DeQueue		();
		unsigned int	Size		() const;
	private:
		unsigned int	Front;
		unsigned int	End;
	};

template <class DATA>
UBQueue <DATA>::UBQueue ()
	{
	Front	= 0;
	End		= 0;
	}

template <class DATA>
UBQueue <DATA>::~UBQueue ()
	{

	}

template <class DATA>
bool UBQueue <DATA>::Queue (const DATA & D)
	{
	(*this) [End++] = D;
	return true;
	}

template <class DATA>
DATA & UBQueue <DATA>::DeQueue ()
	{
	if (End > Front)
			{
			return (*this) [Front++];
			}
		else;
	}

template <class DATA>
unsigned int UBQueue <DATA>::Size () const
	{
	return End - Front;
	}

#endif