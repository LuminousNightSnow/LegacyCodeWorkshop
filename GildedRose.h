#ifndef GILDEDROSE_H
#define GILDEDROSE_H
#include "IItem.h"
#include <iostream>
#include <string>
#include <vector>

class GildedRose {
private:
  using items_t = std::vector<ItemPointer>;

public:
  void printItems(std::ostream &out_stream = std::cout);
  void addItem(ItemPointer item);
  void updateQuality();

  using iterator = items_t::iterator;
  using const_iterator = items_t::const_iterator;
  const_iterator begin() { return items_.cbegin(); };
  const_iterator end() { return items_.cend(); }

private:
  items_t items_;
};

#endif // GILDEDROSE_H
