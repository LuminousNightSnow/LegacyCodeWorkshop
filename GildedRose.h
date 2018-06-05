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

  const string &getName_() const { return name_; }
  Items getItem_type() const { return item_type; }
  int GetDaysRemaining() const { return days_remaining; }
  int GetQuality() const { return quality; }

private:
  string name_;
  Items item_type;
  int days_remaining;
  int quality;
};

class GildedRose {
private:
  using Items_t = std::vector<Item>;

public:
  using iterator = Items_t::iterator;
  using const_iterator = Items_t::const_iterator;
  void printItems(std::ostream &out_stream = std::cout);
  void addItem(const Item &item);
  void updateQuality();

  const_iterator begin() { return items_.cbegin(); };
  const_iterator end() { return items_.cend(); }

private:
  bool IsSpecialItem(Item item);
  void UpdateNormalItem(Item &item);
  Items_t items_;
};

#endif // GILDEDROSE_H
