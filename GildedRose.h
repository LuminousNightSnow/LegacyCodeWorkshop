#ifndef GILDEDROSE_H
#define GILDEDROSE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GildedRose;

class Item {
public:
  Item(string name, int days_remaining, int quality)
      : t(name), d(days_remaining), v(quality) {}
  friend class GildedRose;
  friend std::ostream &operator<<(std::ostream &s, Item &item);

private:
  string t;
  int d;
  int v;
};

class GildedRose {
public:
  void printItems();
  void addItem(const Item &item);
  void updateQuality();

private:
  vector<Item> items_;
};

const std::string item1 = "Aged Brie";
const std::string item2 = "Backstage passes to a TAFKAL80ETC concert";
const std::string item3 = "Sulfuras, Hand of Ragnaros";
#endif // GILDEDROSE_H
