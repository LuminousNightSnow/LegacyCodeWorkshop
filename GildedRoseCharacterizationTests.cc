#include <fstream>
#include <gtest/gtest.h>
#include <streambuf>
#include <string>

#include "GildedRose.h"

std::string ReadCharacterizationInput(const std::string &file_name) {
  std::ifstream file(file_name, std::ifstream::in);
  std::stringstream s;
  s << file.rdbuf();
  return s.str();
}

TEST(GildedRoseTest, CharacterizationTest) {
  std::string ground_truth =
      ReadCharacterizationInput("../input_for_characterization_test.txt");

  GildedRose app;

  app.addItem(Item("+5 Dexterity Vest", 10, 20));
  app.addItem(Item("Aged Brie", 2, 0));
  app.addItem(Item("Elixir of the Mongoose", 5, 7));
  app.addItem(Item("Sulfuras, Hand of Ragnaros", 0, 80));
  app.addItem(Item("Sulfuras, Hand of Ragnaros", -1, 80));
  app.addItem(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
  app.addItem(Item("Backstage passes to a TAFKAL80ETC concert", 10, 49));
  app.addItem(Item("Backstage passes to a TAFKAL80ETC concert", 5, 49));

  std::stringstream output;
  output << "OMGHAI!" << std::endl;

  for (int day = 0; day <= 30; day++) {
    output << "-------- day " << day << " --------" << std::endl;
    app.printItems(output);
    output << endl;
    app.updateQuality();
  }

  EXPECT_EQ(ground_truth, output.str());
}
