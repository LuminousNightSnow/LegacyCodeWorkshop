//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_BACKSTAGEPASSITEM_H
#define CPP_BACKSTAGEPASSITEM_H

#include "IItem.h"

class BackstagePassItem : public IItem {

public:
  BackstagePassItem(const std::string &name, const int days_remaining,
                    const int quality)
      : IItem(name, days_remaining, quality) {}

  void update() override;

private:
  void UpdateQuality();
};

void BackstagePassItem::update() {
  UpdateQuality();
  DecreaseDaysRemaining();
}

void BackstagePassItem::UpdateQuality() {
  IncreaseQuality();
  const int remaining_days_very_close_sell_date = 5;
  const int remaining_days_close_sell_date = 10;

  if (GetDaysRemaining() <= remaining_days_close_sell_date) {
    IncreaseQuality();
  }

  if (GetDaysRemaining() <= remaining_days_very_close_sell_date) {
    IncreaseQuality();
  }

  if (GetDaysRemaining() <= 0) {
    SetQualityToMinValue();
  }
}
#endif // CPP_BACKSTAGEPASSITEM_H
