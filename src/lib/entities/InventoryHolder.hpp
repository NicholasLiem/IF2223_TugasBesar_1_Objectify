#ifndef __INVENTORYHOLDER_
#define __INVENTORYHOLDER_

#include <algorithm>
#include <vector>

template <class T>
class InventoryHolder
{
  public:
    virtual void put(T item) = 0;
    virtual T take(T item) = 0;
    virtual T get(int index) const
    {
        return inventory[index];
    };
    virtual const std::vector<T>& getAll() const
    {
        return inventory;
    }
    virtual void clear()
    {
        inventory.clear();
    };

  protected:
    std::vector<T> inventory;
};

#endif // !__INVENTORYHOLDER_
