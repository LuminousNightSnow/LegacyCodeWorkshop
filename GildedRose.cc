#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> &items) : items(items) {}

void GildedRose::updateQuality() {
  for (int i = 0; i < items.size(); i++) {
    if (!IsSpecialItem(items[i])) {
      UpdateNormalItem(items[i]);
      continue;
    }
    if (items[i].name == "Aged Brie") {
      UpdateBrieItem(items[i]);
      continue;
    }

    if (items[i].name == "Sulfuras, Hand of Ragnaros") {
      continue;
    }

    if (items[i].name == "Backstage passes to a TAFKAL80ETC concert") {
      UpdateBackstagePassItem(items[i]);
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
