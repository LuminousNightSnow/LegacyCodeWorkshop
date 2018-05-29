#include "GildedRose.h"
#include "GildedRoseConditionals.h"
#include "GildedRoseOO.h"

#include <chrono>
#include <iostream>

void Setup_OO(ItemContainer &itemsOO);

void Setup(vector<Item> &items);

using namespace std;
using namespace std::chrono;

// ostream &operator<<(ostream &s, Item &item) {
//  s << item.name << ", " << item.days_remaining << ", " << item.quality;
//  return s;
//}

int main() {
  const int number_of_runs = 10000000;

  vector<Item> items;
  Setup(items);

  GildedRose app(items);

  vector<ItemCond> itemsCond;
  itemsCond.push_back(ItemCond(Items::Plus_5_Dexterity_Vest, 10, 20));
  itemsCond.push_back(ItemCond(Items::Aged_Brie, 2, 0));
  itemsCond.push_back(ItemCond(Items::Elixir_of_the_Mongoose, 5, 7));
  itemsCond.push_back(ItemCond(Items::Sulfuras_Hand_of_Ragnaros, 0, 80));
  itemsCond.push_back(ItemCond(Items::Sulfuras_Hand_of_Ragnaros, -1, 80));
  itemsCond.push_back(
      ItemCond(Items::Backstage_passes_to_a_TAFKAL80ETC_concert, 15, 20));
  itemsCond.push_back(
      ItemCond(Items::Backstage_passes_to_a_TAFKAL80ETC_concert, 10, 49));
  itemsCond.push_back(
      ItemCond(Items::Backstage_passes_to_a_TAFKAL80ETC_concert, 5, 49));
  GildedRoseCond appCond(itemsCond);

  high_resolution_clock::time_point tick = high_resolution_clock::now();
  for (int run = 0; run < number_of_runs; ++run) {
    for (int day = 0; day <= 30; day++) {
      app.updateQuality();
    }
  }
  high_resolution_clock::time_point tock = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(tock - tick).count();
  cout << duration << endl;

  tick = high_resolution_clock::now();
  for (int run = 0; run < number_of_runs; ++run) {
    for (int day = 0; day <= 30; day++) {
      appCond.updateQuality();
    }
  }

  tock = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(tock - tick).count();
  cout << duration << endl;

  ItemContainer itemsOO;
  Setup_OO(itemsOO);

  GildedRoseOO appOO(itemsOO);

  tick = high_resolution_clock::now();
  for (int run = 0; run < number_of_runs; ++run) {
    for (int day = 0; day <= 30; day++) {
      appOO.updateQuality();
    }
  }

  tock = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(tock - tick).count();
  cout << duration << endl;
}

void Setup(vector<Item> &items) {
  items.push_back(Item(Items::Plus_5_Dexterity_Vest, 10, 20));
  items.push_back(Item(Items::Aged_Brie, 2, 0));
  items.push_back(Item(Items::Elixir_of_the_Mongoose, 5, 7));
  items.push_back(Item(Items::Sulfuras_Hand_of_Ragnaros, 0, 80));
  items.push_back(Item(Items::Sulfuras_Hand_of_Ragnaros, -1, 80));
  items.push_back(
      Item(Items::Backstage_passes_to_a_TAFKAL80ETC_concert, 15, 20));
  items.push_back(
      Item(Items::Backstage_passes_to_a_TAFKAL80ETC_concert, 10, 49));
  items.push_back(
      Item(Items::Backstage_passes_to_a_TAFKAL80ETC_concert, 5, 49));
}

void Setup_OO(ItemContainer &itemsOO) {

  itemsOO.push_back(ItemPointer(new NormalItem("+5 Dexterity Vest", 10, 20)));
  itemsOO.push_back(ItemPointer(new BrieItem("Aged Brie", 2, 0)));
  itemsOO.push_back(
      ItemPointer(new NormalItem("Elixir of the Mongoose", 5, 7)));
  itemsOO.push_back(
      ItemPointer(new SulfurasItem("Sulfuras, Hand of Ragnaros", 0, 80)));
  itemsOO.push_back(
      ItemPointer(new SulfurasItem("Sulfuras, Hand of Ragnaros", -1, 80)));
  itemsOO.push_back(ItemPointer(new BackstagePassItem(
      "Backstage passes to a TAFKAL80ETC concert", 15, 20)));
  itemsOO.push_back(ItemPointer(new BackstagePassItem(
      "Backstage passes to a TAFKAL80ETC concert", 10, 49)));
  itemsOO.push_back(ItemPointer(new BackstagePassItem(
      "Backstage passes to a TAFKAL80ETC concert", 5, 49)));
}
