#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> &items) : items(items) {}

const std::string item1 = "Aged Brie";
const std::string item2 = "Backstage passes to a TAFKAL80ETC concert";
const std::string item3 = "Sulfuras, Hand of Ragnaros";

void GildedRose::updateQuality() {
  for (int i = 0; i < items.size(); i++) {
    if (items[i].t != item1 && items[i].t != item2) {
      if (items[i].v > 0) {
        if (items[i].t != item3) {
          items[i].v -= 1;
        }
      }
    } else {
      if (items[i].v < 50) {
        items[i].v = items[i].v + 1;

        if (items[i].t == item2) {
          if (items[i].d < 11) {
            if (items[i].v < 50) {
              items[i].v += 1;
            }
          }

          if (items[i].d < 6) {
            if (items[i].v < 50) {
              items[i].v++;
            }
          }
        }
      }
    }

    if (items[i].t != item3) {
      --items[i].d;
    }

    if (items[i].d < 0) {
      if (items[i].t != item1) {
        if (items[i].t != item2) {
          if (items[i].v > 0) {
            if (items[i].t != item3) {
              items[i].v = items[i].v - 1;
            }
          }
        } else {
          items[i].v = items[i].v - items[i].v;
        }
      } else {
        if (items[i].v < 50) {
          ++items[i].v;
        }
      }
    }
  }
}
