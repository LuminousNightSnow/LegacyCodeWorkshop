#include "GildedRose.h"

std::ostream &operator<<(std::ostream &s, const ItemPointer &item) {
  s << item->GetName() << ", " << item->GetDaysRemaining() << ", "
    << item->GetQuality();
  return s;
}

void GildedRose::updateQuality() {
  for (auto &item : items_) {
    item->update();
  }
}

void GildedRose::addItem(ItemPointer item) {
  items_.push_back(std::move(item));
}

void GildedRose::printItems(std::ostream &out_stream) {
  for (const auto &item : items_) {
    out_stream << item << std::endl;
  }
}
