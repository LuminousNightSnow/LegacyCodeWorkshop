//
// Created by q213677 on 04.07.2018.
//
#include "BrieItem.h"

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
