#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> &items) : items(items) {}

void GildedRose::updateQuality() {
  for (int i = 0; i < items.size(); i++) {
    if (!IsSpecialItem(items[i])) {
      UpdateNormalItem(items[i]);
      return;
    }
    if (items[i].name != "Aged Brie" &&
        items[i].name != "Backstage passes to a TAFKAL80ETC concert") {
      if (items[i].quality > 0) {
        if (items[i].name != "Sulfuras, Hand of Ragnaros") {
          items[i].quality = items[i].quality - 1;
        }
      }
    } else {
      if (items[i].quality < 50) {
        items[i].quality = items[i].quality + 1;

        if (items[i].name == "Backstage passes to a TAFKAL80ETC concert") {
          if (items[i].days_remaining < 11) {
            if (items[i].quality < 50) {
              items[i].quality = items[i].quality + 1;
            }
          }

          if (items[i].days_remaining < 6) {
            if (items[i].quality < 50) {
              items[i].quality = items[i].quality + 1;
            }
          }
        }
      }
    }

    if (items[i].name != "Sulfuras, Hand of Ragnaros") {
      items[i].days_remaining = items[i].days_remaining - 1;
    }

    if (items[i].days_remaining < 0) {
      if (items[i].name != "Aged Brie") {
        if (items[i].name != "Backstage passes to a TAFKAL80ETC concert") {
          if (items[i].quality > 0) {
            if (items[i].name != "Sulfuras, Hand of Ragnaros") {
              items[i].quality = items[i].quality - 1;
            }
          }
        } else {
          items[i].quality = items[i].quality - items[i].quality;
        }
      } else {
        if (items[i].quality < 50) {
          items[i].quality = items[i].quality + 1;
        }
      }
    }
  }
}

bool GildedRose::IsSpecialItem(Item item) {
  return item.name == "Aged Brie" ||
         item.name == "Sulfuras, Hand of Ragnaros" ||
         item.name == "Backstage passes to a TAFKAL80ETC concert";
}

void GildedRose::UpdateNormalItem(Item &item) {
  item.days_remaining -= 1;
  item.quality = std::max(item.quality - 1, 0);

  if (item.days_remaining < 0) {
    item.quality = std::max(item.quality - 1, 0);
  }
}
