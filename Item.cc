#include "Item.h"

void NormalItem::Update() {
  DecreaseDaysRemaining();
  DecreaseQuality();

  if (GetDaysRemaining() < 0) {
    DecreaseQuality();
  }
}
