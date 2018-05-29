#ifndef CPP_GILDEDROSEOO_H
#define CPP_GILDEDROSEOO_H

#include "Item.h"

class GildedRoseOO {
public:
  ItemContainer items;

  GildedRoseOO(ItemContainer &items) : items(items) {}
  void updateQuality() {
    for (const auto &item : items) {
      item->Update();
    }
  }
};

#endif // CPP_GILDEDROSEOO_H
