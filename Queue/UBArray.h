#ifndef UBARRAY_H
#define UBARRAY_H

#include "WCS_Pointer.h"
#include "RefCount.h"

//	Notes:	The type used to replace INDEX in the following template must support comparison operators

template <class DATA, class INDEX>
	class UBArray
		{
		public:
			enum Exception {ArrayEmpty, NoNextElement, NoPrevElement};
		private:
			struct Node: public RefCount
				{
				DATA				Data;
				INDEX				Index;
				WCS_Pointer <Node>	pNext;
				WCS_Pointer <Node>	pPrev;

				Node ();
				Node (const INDEX &);
				};
		public:
							UBArray		();
							~UBArray	();
			DATA &			At			(const INDEX &);
			const DATA &	At			(const INDEX &) const;
			void			DeleteAll	();
			const INDEX &	GetFirst	() const;
			const INDEX &	GetLast		() const;
			const INDEX &	GetNext		() const;
			const INDEX &	GetPrev		() const;
			bool			Remove		(const INDEX &);
			int				Size		() const;
			DATA &			operator []	(const INDEX &);
			const DATA &	operator []	(const INDEX &) const;
		private:
			void	operator =	(const UBArray <DATA, INDEX> &);
					UBArray		(const UBArray <DATA, INDEX> &);

					WCS_Pointer <Node>		pHead;
					WCS_Pointer <Node>		pTail;
			mutable	WCS_Pointer <Node>		pCurrent;
					int						NumElements;
		};

template <class DATA, class INDEX>
	UBArray <DATA, INDEX>::Node::Node ()
		{

		}

template <class DATA, class INDEX>
	UBArray <DATA, INDEX>::Node::Node (const INDEX & I)
		{
		Index = I;
		}

template <class DATA, class INDEX>
	UBArray <DATA, INDEX>::UBArray ()
		{
		NumElements = 0;
		}

template <class DATA, class INDEX>
	UBArray <DATA, INDEX>::~UBArray ()
		{
		DeleteAll ();
		}

template <class DATA, class INDEX>
	inline DATA & UBArray <DATA, INDEX>::At (const INDEX & I)
		{
		return (*this) [I];
		}

template <class DATA, class INDEX>
	inline const DATA & UBArray <DATA, INDEX>::At (const INDEX & I) const
		{
		return (*this) [I];
		}

template <class DATA, class INDEX>
	void UBArray <DATA, INDEX>::DeleteAll ()
		{
		if (pHead)
			if (pHead == pHead)
					{
					pHead.SetToNull ();
					pTail.SetToNull ();
					}
				else
						{
						do {
							pHead = (*pHead).pNext;
							(*pHead).pPrev.SetToNull ();
							NumElements--;
							} while (NumElements > 0);
						}
			else;
		}

template <class DATA, class INDEX>
	const INDEX & UBArray <DATA, INDEX>::GetFirst () const
		{
		if (pHead)
				{
				pCurrent	= pHead;
				return (*pHead).Index;
				}
			else
				throw ArrayEmpty;
		}

template <class DATA, class INDEX>
	const INDEX & UBArray <DATA, INDEX>::GetLast () const
		{
		if (pTail)
			{
			pCurrent	= pTail;
			return (*pTail).Index;
			}
		else
			throw ArrayEmpty;
		}

template <class DATA, class INDEX>
	const INDEX & UBArray <DATA, INDEX>::GetNext () const
		{
		if ((pCurrent) && (pCurrent != pTail))
				{
				pCurrent = (*pCurrent).pNext;
				return (*pCurrent).Index;
				}
			else
				throw NoNextElement;
		}

template <class DATA, class INDEX>
	const INDEX & UBArray <DATA, INDEX>::GetPrev () const
		{
		if ((pCurrent) && (pCurrent != pHead))
			{
			pCurrent = (*pCurrent).pPrev;
			return (*pCurrent).Index;
			}
		else
			throw NoPrevElement;
		}

template <class DATA, class INDEX>
	bool UBArray <DATA, INDEX>::Remove (const INDEX & I)
		{
		WCS_Pointer <Node>	pTemp;

		if (!pHead || (I < (*pHead).Index) || (I > (*pTail).Index))
				return false;
			else
				if ((*pHead).Index == I)
						{
						if (pHead == pTail)
								{
								pHead.SetToNull ();
								pTail.SetToNull ();
								}
							else
								{
								pHead = (*pHead).pNext;
								(*pHead).pPrev.SetToNull ();
								}
						NumElements--;
						return true;
						}
					else
						if ((*pTail).Index == I)
								{
								pTail = (*pTail).pPrev;
								(*pTail).pNext.SetToNull ();
								NumElements--;
								return true;
								}
							else
								{
								pTemp = pHead;
								do	{
									pTemp = (*pTemp).pNext;
									if ((*pTemp).Index == I)
											{
											(*(*pTemp).pPrev).pNext	= (*pTemp).pNext;
											(*(*pTemp).pNext).pPrev	= (*pTemp).pPrev;
											NumElements--;
											return true;
											}
									} while (I > (*pTemp).Index);
								return false;
								}
		}

template <class DATA, class INDEX>
	inline int UBArray <DATA, INDEX>::Size () const
		{
		return NumElements;
		}

template <class DATA, class INDEX>
	DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & I)
		{
		WCS_Pointer <Node>	pTemp;
		if (!pHead)
				{
				pHead = WCS_Pointer <Node> (new Node (I));
				pTail = pHead;
				NumElements++;
				return (*pHead).Data;
				}
			else
				if (I < (*pHead).Index)
						{
						pTemp			= WCS_Pointer <Node> (new Node (I));
						(*pHead).pPrev	= pTemp;
						(*pTemp).pNext	= pHead;
						pHead			= pTemp;
						NumElements++;
						return (*pTemp).Data;
						}
					else
						if (I == (*pHead).Index)
								return (*pHead).Data;
							else
								if (I == (*pTail).Index)
										return (*pTail).Data;
									else
										if (I > (*pTail).Index)
												{
												pTemp			= WCS_Pointer <Node> (new Node (I));
												(*pTail).pNext	= pTemp;
												(*pTemp).pPrev	= pTail;
												pTail			= pTemp;
												NumElements++;
												return (*pTemp).Data;
												}
											else
												{
												pTemp = (*pHead).pNext;
												while (I > (*pTemp).Index)
													pTemp = (*pTemp).pNext;
												if (I == (*pTemp).Index)
														return (*pTemp).Data;
													else
														{
														WCS_Pointer <Node> pTemp2 (new Node (I));
														(*pTemp2).pPrev				= (*pTemp).pPrev;
														(*pTemp).pPrev				= pTemp2;
														(*pTemp2).pNext				= pTemp;
														(*(*pTemp2).pPrev).pNext	= pTemp2;
														NumElements++;
														return (*pTemp2).Data;
														}
												}
		}

template <class DATA, class INDEX>
	const DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & I) const
		{
		WCS_Pointer <Node>	pTemp;
		if (!pHead)
				{
				throw ArrayEmpty;
				}
			else
				if (I < (*pHead).Index)
					throw ArrayEmpty;
					else
						if (I == (*pHead).Index)
								return (*pHead).Data;
							else
								if (I == (*pTail).Index)
										return (*pTail).Data;
									else
										if (I > (*pTail).Index)
												throw ArrayEmpty;
											else
												{
												pTemp = (*pHead).pNext;
												while (I > (*pTemp).Index)
													pTemp = (*pTemp).pNext;
												if (I == (*pTemp).Index)
														return (*pTemp).Data;
													else
														throw ArrayEmpty;
												}
		}

#endif
