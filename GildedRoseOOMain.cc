#include "GildedRoseOO.h"

#include <iostream>

using namespace std;

ostream &operator<<(ostream &s, IItem &item) {
  s << item.GetName() << ", " << item.GetDaysRemaining() << ", "
    << item.GetQuality();
  return s;
}

int main() {
  ItemContainer items;
  items.push_back(ItemPointer(new NormalItem("+5 Dexterity Vest", 10, 20)));
  items.push_back(ItemPointer(new BrieItem("Aged Brie", 2, 0)));
  items.push_back(ItemPointer(new NormalItem("Elixir of the Mongoose", 5, 7)));
  items.push_back(
      ItemPointer(new SulfurasItem("Sulfuras, Hand of Ragnaros", 0, 80)));
  items.push_back(
      ItemPointer(new SulfurasItem("Sulfuras, Hand of Ragnaros", -1, 80)));
  items.push_back(ItemPointer(new BackstagePassItem(
      "Backstage passes to a TAFKAL80ETC concert", 15, 20)));
  items.push_back(ItemPointer(new BackstagePassItem(
      "Backstage passes to a TAFKAL80ETC concert", 10, 49)));
  items.push_back(ItemPointer(new BackstagePassItem(
      "Backstage passes to a TAFKAL80ETC concert", 5, 49)));

  GildedRoseOO app(items);

  cout << "OMGHAI!" << endl;

  for (int day = 0; day <= 30; day++) {
    cout << "-------- day " << day << " --------" << endl;
    cout << "name, days remaining, quality" << endl;
    for (auto item : items) {
      cout << *item << endl;
    }
    cout << endl;

    app.updateQuality();
  }
}
