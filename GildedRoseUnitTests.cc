#include <gtest/gtest.h>

#include "GildedRose.h"

class ItemTest : public testing::Test {
public:
  ItemTest(const string &name_) : name_(name_) {}

protected:
  vector<Item> items_;
  int days_remaining_{5};
  int initial_quality_{20};
  string name_;
  void MakeAndUpdateItem() {
    items_.push_back(Item(name_, days_remaining_, initial_quality_));
    GildedRose app(items_);
    app.updateQuality();
    EXPECT_EQ(items_[0].days_remaining, days_remaining_ - 1);
  }
};

class NormalItemTest : public ItemTest {
public:
  NormalItemTest(const string &name_ = "+5 Dexterity Vest") : ItemTest(name_) {}
};

class BrieItemTest : public ItemTest {
public:
  BrieItemTest(const string &name_ = "Aged Brie") : ItemTest(name_) {}

protected:
  const int max_quality_{50};
};

TEST_F(NormalItemTest, before_sell_date) {
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ - 1);
}

TEST_F(NormalItemTest, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ - 2);
}

TEST_F(NormalItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ - 2);
}

TEST_F(NormalItemTest, zero_quality_after_sell_date) {
  days_remaining_ = -1;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_);
}

TEST_F(NormalItemTest, zero_quality_before_sell_date) {
  days_remaining_ = 1;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_);
}

TEST_F(NormalItemTest, zero_quality_at_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_);
}

TEST_F(NormalItemTest, sell_date_quality_one) {
  days_remaining_ = 0;
  initial_quality_ = 1;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ - 1);
}

TEST_F(BrieItemTest, before_sell_date) {
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ + 1);
}

TEST_F(BrieItemTest, before_sell_date_with_max_quality) {
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_);
}

TEST_F(BrieItemTest, on_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 10;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ + 2);
}

TEST_F(BrieItemTest, on_sell_date_near_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = 49;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, max_quality_);
}

TEST_F(BrieItemTest, on_sell_date_with_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, max_quality_);
}

TEST_F(BrieItemTest, after_sell_date) {
  days_remaining_ = -10;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, initial_quality_ + 2);
}

TEST_F(BrieItemTest, after_sell_date_with_max_quality) {

  days_remaining_ = -10;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(items_[0].quality, max_quality_);
}
