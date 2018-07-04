#include <gtest/gtest.h>

#include "BrieItem.h"
#include "GildedRose.h"
#include "NormalItem.h"

TEST(GildedRose, GildedRoseTest_OneNormalItem) {
  const std::string name = "Normal item";
  int days_remaining = 10;
  const int initial_quality = 20;
  GildedRose unit;
  unit.addItem(MakeItem<NormalItem>(name, days_remaining, initial_quality));
  unit.updateQuality();

  const auto item = unit.begin();
  EXPECT_EQ((*item)->GetDaysRemaining(), days_remaining - 1);
  EXPECT_EQ((*item)->GetQuality(), initial_quality - 1);
}

TEST(GildedRose, GildedRoseTest_TwoNormalItem) {
  int days_remaining = 10;
  const int initial_quality = 20;
  GildedRose unit;
  unit.addItem(
      MakeItem<NormalItem>("Normal Item", days_remaining, initial_quality));
  unit.addItem(
      MakeItem<BrieItem>("Aged Brie", days_remaining, initial_quality));

  unit.updateQuality();

  auto item = unit.begin();
  EXPECT_EQ((*item)->GetDaysRemaining(), days_remaining - 1);
  EXPECT_EQ((*item)->GetQuality(), initial_quality - 1);
  EXPECT_EQ((*item)->GetName(), "Normal Item");
  ++item;
  EXPECT_EQ((*item)->GetDaysRemaining(), days_remaining - 1);
  EXPECT_EQ((*item)->GetQuality(), initial_quality + 1);
  EXPECT_EQ((*item)->GetName(), "Aged Brie");
}
