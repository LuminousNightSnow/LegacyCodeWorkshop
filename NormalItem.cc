//
// Created by q213677 on 04.07.2018.
//

#include "NormalItem.h"

void NormalItem::update() {
  UpdateQuality();
  DecreaseDaysRemaining();
}

void NormalItem::UpdateQuality() {
  DecreaseQuality();

  if (GetDaysRemaining() <= 0) {
    DecreaseQuality();
  }
}
