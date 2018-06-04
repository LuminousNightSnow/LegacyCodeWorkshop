#ifndef GILDEDROSE_H
#define GILDEDROSE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GildedRose;

enum class Items {
  Aged_Brie,
  Backstage_passes_to_a_TAFKAL80ETC_concert,
  Sulfuras_Hand_of_Ragnaros,
  Other
};

class Item {
public:
  Item(const string &name, int days_remaining, int quality);
  friend class GildedRose;
  friend std::ostream &operator<<(std::ostream &s, Item &item);

private:
  string name_;
  Items item_type;
  int days_remaining;
  int quality;
};

class GildedRose {
public:
  void printItems(std::ostream &out_stream = std::cout);
  void addItem(const Item &item);
  void updateQuality();

private:
  vector<Item> items_;
};

#endif // GILDEDROSE_H
