#include "Item.h"

void NormalItem::Update() {
  DecreaseDaysRemaining();
  DecreaseQuality();

  if (GetDaysRemaining() < 0) {
    DecreaseQuality();
  }
}

void BrieItem::Update() {
  DecreaseDaysRemaining();
  IncreaseQuality();

  if (GetDaysRemaining() < 0) {
    IncreaseQuality();
  }
}

void SulfurasItem::Update() {}

void BackstagePassItem::Update() {
  DecreaseDaysRemaining();
  if (GetDaysRemaining() < 0) {
    SetQualityToMin();
    return;
  }
  IncreaseQuality();
  if (GetDaysRemaining() < days_close_to_sell_date_) {
    IncreaseQuality();
  }
  if (GetDaysRemaining() < days_very_close_to_sell_date_) {
    IncreaseQuality();
  }
}
