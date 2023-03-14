#ifndef __TABLE_
#define __TABLE_

#include "Card.hpp"
#include "InventoryHolder.hpp"
#include <vector>

class Table : public InventoryHolder<Card>
{
	public:
		std::vector<Card> takeAll();
		void put(Card card) override;
	
	private:
		Card take(Card card) override;
};

#endif // !__TABLE_
