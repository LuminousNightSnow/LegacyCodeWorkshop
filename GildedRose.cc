#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> &items) : items(items) {}

void GildedRose::updateQuality() {
  for (auto &item : items) {
    if (!IsSpecialItem(item)) {
      UpdateNormalItem(item);
      continue;
    }
    if (item.name == Items::Aged_Brie) {
      UpdateBrieItem(item);
      continue;
    }

    if (item.name == Items::Sulfuras_Hand_of_Ragnaros) {
      continue;
    }

    if (item.name == Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
      UpdateBackstagePassItem(item);
      continue;
    }
  }
}

bool GildedRose::IsSpecialItem(Item item) const {
  return item.name == Items::Aged_Brie ||
         item.name == Items::Sulfuras_Hand_of_Ragnaros ||
         item.name == Items::Backstage_passes_to_a_TAFKAL80ETC_concert;
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
