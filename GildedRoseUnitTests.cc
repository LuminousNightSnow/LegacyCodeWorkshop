#include <gtest/gtest.h>

#include "GildedRose.h"

TEST(GildedRoseTest, normal_item_before_sell_date) {
  vector<Item> items;
  const int days_remaining{10};
  const int intitial_quality{20};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality - 1);
}

TEST(GildedRoseTest, normal_item_on_sell_date) {
  vector<Item> items;
  const int days_remaining{0};
  const int intitial_quality{10};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality - 2);
}

TEST(GildedRoseTest, normal_item_after_sell_date) {
  vector<Item> items;
  const int days_remaining{-1};
  const int intitial_quality{8};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality - 2);
}

TEST(GildedRoseTest, normal_at_zero_quality_after_sell_date) {
  vector<Item> items;
  const int days_remaining{-1};
  const int intitial_quality{0};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality);
}

TEST(GildedRoseTest, normal_at_zero_quality_before_sell_date) {
  vector<Item> items;
  const int days_remaining{1};
  const int intitial_quality{0};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality);
}

TEST(GildedRoseTest, normal_at_zero_quality_at_sell_date) {
  vector<Item> items;
  const int days_remaining{0};
  const int intitial_quality{0};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality);
}

TEST(GildedRoseTest, normal_at_at_sell_date_quality_one) {
  vector<Item> items;
  const int days_remaining{0};
  const int intitial_quality{1};
  items.push_back(Item("+5 Dexterity Vest", days_remaining, intitial_quality));
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].days_remaining, days_remaining - 1);
  EXPECT_EQ(items[0].quality, intitial_quality - 1);
}
