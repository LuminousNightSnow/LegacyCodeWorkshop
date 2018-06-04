#include <gtest/gtest.h>

#include "GildedRose.h"

TEST(GildedRoseTest, normal_item_before_sell_date) {

  GildedRose app;

  const int days_remaining{10};
  const int initial_quality{20};
  app.addItem(Item("+5 Dexterity Vest", days_remaining, initial_quality));

  app.updateQuality();

  EXPECT_EQ(app.begin()->GetDaysRemaining(), days_remaining - 1);
  EXPECT_EQ(app.begin()->getQuality(), initial_quality - 1);
}
