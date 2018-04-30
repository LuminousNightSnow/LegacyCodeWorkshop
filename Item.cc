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
  if (GetDaysRemaining() < 10) {
    IncreaseQuality();
  }
  if (GetDaysRemaining() < 5) {
    IncreaseQuality();
  }
}
