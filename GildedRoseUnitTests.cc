#include <gtest/gtest.h>

#include "GildedRose.h"

class ItemTest : public testing::Test {
public:
  ItemTest(const string &name_) : name_(name_) {}

protected:
  vector<Item> items_;
  int days_remaining_{0};
  int initial_quality_{20};
  string name_;
  virtual void MakeAndUpdateItem() = 0;
};

class NormalItemTest : public ItemTest {
public:
  NormalItemTest(const string &name_ = "+5 Dexterity Vest") : ItemTest(name_) {}

protected:
  void MakeAndUpdateItem() override {
    items_.push_back(Item(name_, days_remaining_, initial_quality_));
    GildedRose app(items_);
    app.updateQuality();
    EXPECT_EQ(items_[0].days_remaining, days_remaining_ - 1);
  }
};

TEST_F(NormalItemTest, before_sell_date) {
  days_remaining_ = 10;
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
