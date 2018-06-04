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
  Item(const string &name, int days_remaining, int quality)
      : name_{name}, days_remaining{days_remaining}, quality{quality} {
    if (name == "Aged Brie") {
      item_type = Items::Aged_Brie;
    } else if (name == "Backstage passes to a TAFKAL80ETC concert") {
      item_type = Items::Backstage_passes_to_a_TAFKAL80ETC_concert;
    } else if (name == "Sulfuras, Hand of Ragnaros") {
      item_type = Items::Sulfuras_Hand_of_Ragnaros;
    } else {
      item_type = Items::Other;
    }
  }
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
