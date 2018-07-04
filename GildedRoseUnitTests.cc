#include <gtest/gtest.h>

#include "GildedRose.h"

class ItemTest : public testing::Test {
public:
  ItemTest(const string &name_) : name_(name_) {}

protected:
  vector<Item> items_;
  int days_remaining_{5};
  int initial_quality_{20};
  const int max_quality_{50};
  string name_;
  GildedRose unit;

  void MakeAndUpdateItem() {
    unit.addItem(Item(name_, days_remaining_, initial_quality_));
    unit.updateQuality();
    EXPECT_EQ(unit.begin()->GetDaysRemaining(), days_remaining_ - 1);
  }
};

class NormalItemTest : public ItemTest {
public:
  NormalItemTest(const string &name_ = "+5 Dexterity Vest") : ItemTest(name_) {}
};

class BrieItemTest : public ItemTest {
public:
  BrieItemTest(const string &name_ = "Aged Brie") : ItemTest(name_) {}
};

class SulfurasItemTest : public ItemTest {
public:
  SulfurasItemTest(const string &name_ = "Sulfuras, Hand of Ragnaros")
      : ItemTest(name_) {}

protected:
  virtual void MakeAndUpdateItems() {
    unit.addItem(Item(name_, days_remaining_, initial_quality_));
    unit.updateQuality();
    EXPECT_EQ(unit.begin()->GetDaysRemaining(), days_remaining_);
  }
};

class BackstagePassItemTest : public ItemTest {
public:
  BackstagePassItemTest(
      const string &name_ = "Backstage passes to a TAFKAL80ETC concert")
      : ItemTest(name_) {}
};

TEST_F(NormalItemTest, before_sell_date) {
  days_remaining_ = 10;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ - 1);
}

TEST_F(NormalItemTest, before_sell_date_two_items) {
  days_remaining_ = 10;
  const int days_remaining_item1 = 7;
  const int initial_quality_item1 = 25;
  unit.addItem(
      Item("Escape Rope", days_remaining_item1, initial_quality_item1));
  unit.addItem(Item(name_, days_remaining_, initial_quality_));
  unit.updateQuality();

  auto current_item = unit.begin();
  EXPECT_EQ(current_item->GetDaysRemaining(), days_remaining_item1 - 1);
  EXPECT_EQ(current_item->GetQuality(), initial_quality_item1 - 1);
  current_item++;
  EXPECT_EQ(current_item->GetDaysRemaining(), days_remaining_ - 1);
  EXPECT_EQ(current_item->GetQuality(), initial_quality_ - 1);
}

TEST_F(NormalItemTest, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ - 2);
}

TEST_F(NormalItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ - 2);
}

TEST_F(NormalItemTest, zero_quality_after_sell_date) {
  days_remaining_ = -1;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest, zero_quality_before_sell_date) {
  days_remaining_ = 1;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest, zero_quality_at_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest, sell_date_quality_one) {
  days_remaining_ = 0;
  initial_quality_ = 1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ - 1);
}

TEST_F(BrieItemTest, before_sell_date) {
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 1);
}

TEST_F(BrieItemTest, before_sell_date_two_items) {
  initial_quality_ = 0;
  days_remaining_ = 10;
  const int days_remaining_item1 = 7;
  const int initial_quality_item1 = 2;
  unit.addItem(Item(name_, days_remaining_item1, initial_quality_item1));
  unit.addItem(Item(name_, days_remaining_, initial_quality_));
  unit.updateQuality();

  auto current_item = unit.begin();
  EXPECT_EQ(current_item->GetDaysRemaining(), days_remaining_item1 - 1);
  EXPECT_EQ(current_item->GetQuality(), initial_quality_item1 + 1);
  current_item++;
  EXPECT_EQ(current_item->GetDaysRemaining(), days_remaining_ - 1);
  EXPECT_EQ(current_item->GetQuality(), initial_quality_ + 1);
}

// TODO: add more tests with more than one item, e.g. for different items

TEST_F(BrieItemTest, before_sell_date_with_max_quality) {
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(BrieItemTest, on_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 10;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 2);
}

TEST_F(BrieItemTest, on_sell_date_near_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = 49;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(BrieItemTest, on_sell_date_with_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(BrieItemTest, after_sell_date) {
  days_remaining_ = -10;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 2);
}

TEST_F(BrieItemTest, after_sell_date_with_max_quality) {

  days_remaining_ = -10;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(SulfurasItemTest, before_sell_date) {
  MakeAndUpdateItems();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(SulfurasItemTest, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(SulfurasItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItems();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_);
}

TEST_F(BackstagePassItemTest, long_before_sell_date) {
  days_remaining_ = 20;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 1);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_upper_bound) {
  days_remaining_ = 10;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 2);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_upper_bound_at_max_quality) {
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_lower_bound) {
  days_remaining_ = 6;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 2);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_lower_bound_at_max_quality) {
  days_remaining_ = 6;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, very_close_to_sell_date_upper_bound) {
  days_remaining_ = 5;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 3);
}

TEST_F(BackstagePassItemTest,
       very_close_to_sell_date_upper_bound_at_max_quality) {
  days_remaining_ = 5;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, very_close_to_sell_date_lower_bound) {
  days_remaining_ = 1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), initial_quality_ + 3);
}

TEST_F(BackstagePassItemTest,
       very_close_to_sell_date_lower_bound_at_max_quality) {

  days_remaining_ = 1;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, on_sell_date) {

  days_remaining_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), 0);
}

TEST_F(BackstagePassItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), 0);
}

TEST_F(BackstagePassItemTest,
       very_close_to_sell_date_lower_bound_at_quality_48) {
  days_remaining_ = 5;
  initial_quality_ = 48;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), 50);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_lower_bound_at_quality_49) {
  days_remaining_ = 5;
  initial_quality_ = 49;
  MakeAndUpdateItem();
  EXPECT_EQ(unit.begin()->GetQuality(), 50);
}
