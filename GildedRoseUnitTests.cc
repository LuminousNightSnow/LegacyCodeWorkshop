#include <gtest/gtest.h>

#include "GildedRose.h"

TEST(GildedRoseTest, mormal_item_before_sell_date) {
  vector<Item> items;
  int days_remaining{10};
  int intitial_quality{20};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality - 1);
}
