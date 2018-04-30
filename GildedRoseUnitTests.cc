#include <gtest/gtest.h>

#include "GildedRose.h"
#include "GildedRoseOO.h"

class ItemTest : public testing::Test {
public:
  ItemTest(const string &name_) : name_(name_) {}

protected:
  ItemContainer items_;
  int days_remaining_{5};
  int initial_quality_{20};
  string name_;

  const int max_quality_{50};

  virtual void MakeAndUpdateItems() = 0;
};

class NormalItemTest : public ItemTest {
public:
  NormalItemTest(const string &name_ = "+5 Dexterity Vest") : ItemTest(name_) {}
  virtual void MakeAndUpdateItems() override {
    items_.push_back(std::shared_ptr<IItem>(
        new NormalItem(name_, days_remaining_, initial_quality_)));
    GildedRoseOO app(items_);
    app.updateQuality();
    EXPECT_EQ(items_[0]->GetDaysRemaining(), days_remaining_ - 1);
  }
};

class BrieItemTest : public ItemTest {
public:
  BrieItemTest(const string &name_ = "Aged Brie") : ItemTest(name_) {}
  virtual void MakeAndUpdateItems() override {
    items_.push_back(std::shared_ptr<IItem>(
        new BrieItem(name_, days_remaining_, initial_quality_)));
    GildedRoseOO app(items_);
    app.updateQuality();
    EXPECT_EQ(items_[0]->GetDaysRemaining(), days_remaining_ - 1);
  }
};

class SulfurasItemTest : public ItemTest {
public:
  SulfurasItemTest(const string &name_ = "Sulfuras, Hand of Ragnaros")
      : ItemTest(name_) {}

protected:
  virtual void MakeAndUpdateItems() override {
    items_.push_back(std::shared_ptr<IItem>(
        new SulfurasItem(name_, days_remaining_, initial_quality_)));
    GildedRoseOO app(items_);
    app.updateQuality();
    EXPECT_EQ(items_[0]->GetDaysRemaining(), days_remaining_);
  }
};

class BackstagePassItemTest : public ItemTest {
public:
  BackstagePassItemTest(
      const string &name_ = "Backstage passes to a TAFKAL80ETC concert")
      : ItemTest(name_) {}

protected:
  virtual void MakeAndUpdateItems() override {
    items_.push_back(std::shared_ptr<IItem>(
        new BackstagePassItem(name_, days_remaining_, initial_quality_)));
    GildedRoseOO app(items_);
    app.updateQuality();
    EXPECT_EQ(items_[0]->GetDaysRemaining(), days_remaining_ - 1);
  }
};

TEST_F(NormalItemTest, before_sell_date) {
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ - 1);
}

TEST_F(NormalItemTest, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ - 2);
}

TEST_F(NormalItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ - 2);
}

TEST_F(NormalItemTest, zero_quality_after_sell_date) {
  days_remaining_ = -1;
  initial_quality_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest, zero_quality_before_sell_date) {
  days_remaining_ = 1;
  initial_quality_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest, zero_quality_at_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest, sell_date_quality_one) {
  days_remaining_ = 0;
  initial_quality_ = 1;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ - 1);
}

TEST_F(BrieItemTest, before_sell_date) {
  initial_quality_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 1);
}

TEST_F(BrieItemTest, before_sell_date_with_max_quality) {
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(BrieItemTest, on_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 10;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 2);
}

TEST_F(BrieItemTest, on_sell_date_near_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = 49;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(BrieItemTest, on_sell_date_with_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(BrieItemTest, after_sell_date) {
  days_remaining_ = -10;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 2);
}

TEST_F(BrieItemTest, after_sell_date_with_max_quality) {

  days_remaining_ = -10;
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(SulfurasItemTest, before_sell_date) {
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(SulfurasItemTest, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(SulfurasItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_);
}

TEST_F(BackstagePassItemTest, long_before_sell_date) {
  days_remaining_ = 20;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 1);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_upper_bound) {
  days_remaining_ = 10;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 2);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_upper_bound_at_max_quality) {
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_lower_bound) {
  days_remaining_ = 6;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 2);
}

TEST_F(BackstagePassItemTest, close_to_sell_date_lower_bound_at_max_quality) {
  days_remaining_ = 6;
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, very_close_to_sell_date_upper_bound) {
  days_remaining_ = 5;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 3);
}

TEST_F(BackstagePassItemTest,
       very_close_to_sell_date_upper_bound_at_max_quality) {
  days_remaining_ = 5;
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, very_close_to_sell_date_lower_bound) {
  days_remaining_ = 1;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), initial_quality_ + 3);
}

TEST_F(BackstagePassItemTest,
       very_close_to_sell_date_lower_bound_at_max_quality) {

  days_remaining_ = 1;
  initial_quality_ = max_quality_;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), max_quality_);
}

TEST_F(BackstagePassItemTest, on_sell_date) {

  days_remaining_ = 0;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), 0);
}

TEST_F(BackstagePassItemTest, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItems();
  EXPECT_EQ(items_[0]->GetQuality(), 0);
}
