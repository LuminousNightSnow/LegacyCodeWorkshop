#include "GildedRoseConditionals.h"

GildedRoseCond::GildedRoseCond(vector<ItemCond> &items) : items(items) {}

void GildedRoseCond::updateQuality() {
  for (int i = 0; i < items.size(); i++) {
    if (items[i].name != Items::Aged_Brie &&
        items[i].name != Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
      if (items[i].quality > 0) {
        if (items[i].name != Items::Sulfuras_Hand_of_Ragnaros) {
          items[i].quality = items[i].quality - 1;
        }
      }
    } else {
      if (items[i].quality < 50) {
        items[i].quality = items[i].quality + 1;

        if (items[i].name == Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
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

    if (items[i].name != Items::Sulfuras_Hand_of_Ragnaros) {
      items[i].days_remaining = items[i].days_remaining - 1;
    }

    if (items[i].days_remaining < 0) {
      if (items[i].name != Items::Aged_Brie) {
        if (items[i].name != Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
          if (items[i].quality > 0) {
            if (items[i].name != Items::Sulfuras_Hand_of_Ragnaros) {
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
