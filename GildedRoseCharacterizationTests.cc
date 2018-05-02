#include <fstream>
#include <gtest/gtest.h>
#include <streambuf>
#include <string>

#include "GildedRose.h"
#include "GildedRoseOO.h"

std::string ReadCharacterizationInput(const std::string &file_name) {
  std::ifstream file(file_name, std::ifstream::in);
  std::stringstream s;
  s << file.rdbuf();
  return s.str();
}

ostream &operator<<(ostream &s, Item &item) {
  s << item.name << ", " << item.days_remaining << ", " << item.quality;
  return s;
}

ostream &operator<<(ostream &s, IItem &item) {
  s << item.GetName() << ", " << item.GetDaysRemaining() << ", "
    << item.GetQuality();
  return s;
}
vector<Item> SetupSomeItems() {
  vector<Item> items;
  items.push_back(Item("+5 Dexterity Vest", 10, 20));
  items.push_back(Item("Aged Brie", 2, 0));
  items.push_back(Item("Elixir of the Mongoose", 5, 7));
  items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
  items.push_back(Item("Sulfuras, Hand of Ragnaros", -1, 80));
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 10, 49));
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 5, 49));
  return items;
}

stringstream RunGildedRoseApp(vector<Item> &items) {
  GildedRose app(items);

  stringstream output;
  output << "OMGHAI!" << std::endl;

  for (int day = 0; day <= 30; day++) {
    output << "-------- day " << day << " --------" << std::endl;
    output << "name, days remaining, quality" << std::endl;
    for (auto i = items.begin(); i != items.end(); i++) {
      output << *i << std::endl;
    }
    output << std::endl;

    app.updateQuality();
  }
  return output;
}

stringstream RunGildedRoseOOApp() {
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

  stringstream output;
  output << "OMGHAI!" << std::endl;

  for (int day = 0; day <= 30; day++) {
    output << "-------- day " << day << " --------" << std::endl;
    output << "name, days remaining, quality" << std::endl;
    for (auto item : items) {
      output << *item << std::endl;
    }
    output << std::endl;

    app.updateQuality();
  }
  return output;
}

TEST(GildedRoseCharacterizationTest, Full_Behaviour) {
  std::string ground_truth =
      ReadCharacterizationInput("../input_for_characterization_test.txt");

  vector<Item> items = SetupSomeItems();

  stringstream output = RunGildedRoseApp(items);

  EXPECT_EQ(ground_truth, output.str());
}

TEST(GildedRoseOOCharacterizationTest, Full_Behaviour) {
  std::string ground_truth =
      ReadCharacterizationInput("../input_for_characterization_test.txt");

  stringstream output = RunGildedRoseOOApp();

  EXPECT_EQ(ground_truth, output.str());
}
