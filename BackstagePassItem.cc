//
// Created by q213677 on 04.07.2018.
//
#include "BackstagePassItem.h"

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
