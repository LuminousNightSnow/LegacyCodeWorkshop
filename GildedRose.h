#include <string>
#include <vector>

using namespace std;

class Item {
public:
  string t;
  int d;
  int v;
  Item(string name, int days_remaining, int quality)
      : t(name), d(days_remaining), v(quality) {}
};

class GildedRose {
public:
  vector<Item> &items;
  GildedRose(vector<Item> &items);

  void updateQuality();
};
