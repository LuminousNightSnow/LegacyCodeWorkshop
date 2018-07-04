#include "IItem.h"
#include "NormalItem.h"
#include <gtest/gtest.h>

using namespace std;

TEST(NormalItemTest1, UpdateNormalItem_WhenTypical) {

  const string name_{"+5 Dexterity Vest"};
  const int days_remaining_{5};
  const int initial_quality_{20};
  ItemPointer unit =
      MakeItem<NormalItem>(name_, days_remaining_, initial_quality_);

  unit->update();
  EXPECT_EQ(unit->GetDaysRemaining(), days_remaining_ - 1);
  EXPECT_EQ(unit->GetQuality(), initial_quality_ - 1);
}
