#include "BrieItem.h"
#include "IItem.h"
#include "NormalItem.h"
#include "SulfurasItem.h"
#include <gtest/gtest.h>

using namespace std;

class ItemTest1 : public testing::Test {
public:
  ItemTest1(const string &name) : name_(name), max_quality_(50) {}
  virtual ~ItemTest1() = default;

protected:
  int days_remaining_{5};
  int initial_quality_{20};
  const int max_quality_;
  string name_;
  ItemPointer unit;

  virtual void MakeAndUpdateItem() = 0;
};

class NormalItemTest1 : public ItemTest1 {
public:
  NormalItemTest1(const string &name = std::string{"+5 Dexterity Vest"})
      : ItemTest1(name) {}
  virtual void MakeAndUpdateItem() override {

    unit = MakeItem<NormalItem>(name_, days_remaining_, initial_quality_);
    unit->update();
    EXPECT_EQ(unit->GetDaysRemaining(), days_remaining_ - 1);
  }
};

class BrieItemTest1 : public ItemTest1 {
public:
  BrieItemTest1(const string &name = std::string{"Aged Brie"})
      : ItemTest1(name) {}
  virtual void MakeAndUpdateItem() override {

    unit = MakeItem<BrieItem>(name_, days_remaining_, initial_quality_);
    unit->update();
    EXPECT_EQ(unit->GetDaysRemaining(), days_remaining_ - 1);
  }
};

class SulfurasItemTest1 : public ItemTest1 {
public:
  SulfurasItemTest1(const string &name = std::string{"Aged Brie"})
      : ItemTest1(name) {}
  virtual void MakeAndUpdateItem() override {

    unit = MakeItem<SulfurasItem>(name_, days_remaining_, initial_quality_);
    unit->update();
    EXPECT_EQ(unit->GetDaysRemaining(), days_remaining_);
  }
};

TEST_F(NormalItemTest1, UpdateNormalItem_WhenTypical) {

  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ - 1);
}

TEST_F(NormalItemTest1, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ - 2);
}

TEST_F(NormalItemTest1, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ - 2);
}

TEST_F(NormalItemTest1, zero_quality_after_sell_date) {
  days_remaining_ = -1;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest1, zero_quality_before_sell_date) {
  days_remaining_ = 1;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest1, zero_quality_at_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}

TEST_F(NormalItemTest1, sell_date_quality_one) {
  days_remaining_ = 0;
  initial_quality_ = 1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ - 1);
}

TEST_F(BrieItemTest1, before_sell_date) {
  initial_quality_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ + 1);
}

TEST_F(BrieItemTest1, before_sell_date_with_max_quality) {
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}

TEST_F(BrieItemTest1, on_sell_date) {
  days_remaining_ = 0;
  initial_quality_ = 10;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ + 2);
}

TEST_F(BrieItemTest1, on_sell_date_near_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = 49;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), max_quality_);
}

TEST_F(BrieItemTest1, on_sell_date_with_max_quality) {
  days_remaining_ = 0;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), max_quality_);
}

TEST_F(BrieItemTest1, after_sell_date) {
  days_remaining_ = -10;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_ + 2);
}

TEST_F(BrieItemTest1, after_sell_date_with_max_quality) {

  days_remaining_ = -10;
  initial_quality_ = max_quality_;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), max_quality_);
}

TEST_F(SulfurasItemTest1, before_sell_date) {
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}

TEST_F(SulfurasItemTest1, on_sell_date) {
  days_remaining_ = 0;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}

TEST_F(SulfurasItemTest1, after_sell_date) {
  days_remaining_ = -1;
  MakeAndUpdateItem();
  EXPECT_EQ(unit->GetQuality(), initial_quality_);
}
