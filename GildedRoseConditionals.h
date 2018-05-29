#ifndef CPP_GILDEDROSECONDITIONALS_H
#define CPP_GILDEDROSECONDITIONALS_H
#include <string>
#include <vector>

#include "ItemTypes.h"
using namespace std;

class ItemCond {
public:
  Items name;
  int days_remaining;
  int quality;
  ItemCond(Items name, int days_remaining, int quality)
      : name(name), days_remaining(days_remaining), quality(quality) {}
};

class GildedRoseCond {
public:
  vector<ItemCond> &items;
  GildedRoseCond(vector<ItemCond> &items);

  void updateQuality();
};

#endif // CPP_GILDEDROSECONDITIONALS_H
