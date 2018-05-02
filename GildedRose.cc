#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> &items) : items(items) {}

void GildedRose::updateQuality() {
  for (auto &item : items) {
    if (!IsSpecialItem(item)) {
      UpdateNormalItem(item);
      continue;
    }
    if (item.name == "Aged Brie") {
      UpdateBrieItem(item);
      continue;
    }

    if (item.name == "Sulfuras, Hand of Ragnaros") {
      continue;
    }

    if (item.name == "Backstage passes to a TAFKAL80ETC concert") {
      UpdateBackstagePassItem(item);
      continue;
    }
  }
}

bool GildedRose::IsSpecialItem(Item item) const {
  return item.name == "Aged Brie" ||
         item.name == "Sulfuras, Hand of Ragnaros" ||
         item.name == "Backstage passes to a TAFKAL80ETC concert";
}

void GildedRose::UpdateNormalItem(Item &item) const {
  item.days_remaining -= 1;
  DecreaseQuality(item);

  if (item.days_remaining < 0) {
    DecreaseQuality(item);
  }
}

void GildedRose::DecreaseQuality(Item &item) const {
  item.quality = max(item.quality - 1, min_quality_);
}

void GildedRose::UpdateBrieItem(Item &item) const {
  item.days_remaining -= 1;
  IncreaseQuality(item);

  if (item.days_remaining < 0) {
    IncreaseQuality(item);
  }
}

void GildedRose::IncreaseQuality(Item &item) const {
  item.quality = min(item.quality + 1, max_quality_);
}

void GildedRose::UpdateBackstagePassItem(Item &item) const {
  item.days_remaining -= 1;
  if (item.days_remaining < 0) {
    item.quality = 0;
    return;
  }
  IncreaseQuality(item);
  if (item.days_remaining < 10) {
    IncreaseQuality(item);
  }
  if (item.days_remaining < 5) {
    IncreaseQuality(item);
  }
}
