#ifndef __TABLE_
#define __TABLE_

#include "Card.hpp"
#include "InventoryHolder.hpp"
#include <vector>

template <class T, class U>
class Table : public InventoryHolder<Card<T,U>>
{
	public:
		std::vector<Card<T,U>> takeAll();
		void put(Card<T,U> card) override;
	
	private:
		Card<T,U> take(Card<T,U> card) override;
};

typedef Table<CardSymbol, CangkulNumber> CangkulTable;
typedef Table<CardColor, CardNumber> MainTable;

#endif // !__TABLE_
