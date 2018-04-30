#include <string>
#include <vector>

using namespace std;

class Item {
public:
  string name;
  int days_remaining;
  int quality;
  Item(string name, int days_remaining, int quality)
      : name(name), days_remaining(days_remaining), quality(quality) {}
};

class GildedRose {
public:
  vector<Item> &items;
  GildedRose(vector<Item> &items);

  void updateQuality();

private:
  bool IsSpecialItem(Item item) const;
  void UpdateNormalItem(Item &item) const;
  void UpdateBrieItem(Item &item) const;
  void UpdateBackstagePassItem(Item &item) const;

  const int min_quality_ = 0;
  const int max_quality_ = 50;

  inline void DecreaseQuality(Item &item) const;

  inline void IncreaseQuality(Item &item) const;
};
