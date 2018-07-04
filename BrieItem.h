//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_BRIEITEM_H
#define CPP_BRIEITEM_H

#include "IItem.h"
class BrieItem : public IItem {
public:
  BrieItem(const std::string &name, const int days_remaining, const int quality)
      : IItem(name, days_remaining, quality) {}

  void update() override;

private:
  void UpdateQuality();
};
#endif // CPP_BRIEITEM_H

void BrieItem::update() {
  UpdateQuality();
  DecreaseDaysRemaining();
}

void BrieItem::UpdateQuality() {
  IncreaseQuality();

  if (GetDaysRemaining() <= 0) {
    IncreaseQuality();
  }
}
