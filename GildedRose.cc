#include "GildedRose.h"

std::ostream &operator<<(std::ostream &s, Item &item) {

  s << item.name_ << ", " << item.d << ", " << item.v;
  return s;
}

void GildedRose::updateQuality() {
  for (int i = 0; i < items_.size(); i++) {
    if (items_[i].item_type != Items::Aged_Brie &&
        items_[i].item_type != Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
      if (items_[i].v > 0) {
        if (items_[i].item_type != Items::Sulfuras_Hand_of_Ragnaros) {
          items_[i].v -= 1;
        }
      }
    } else {
      if (items_[i].v < 50) {
        items_[i].v = items_[i].v + 1;
        if (items_[i].item_type == Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
          if (items_[i].d < 11) {
            if (items_[i].v < 50) {
              items_[i].v += 1;
            }
          }
          if (items_[i].d < 6) {
            if (items_[i].v < 50) {
              items_[i].v++;
            }
          }
        }
      }
    }
    if (items_[i].item_type != Items::Sulfuras_Hand_of_Ragnaros) {
      --items_[i].d;
    }
    if (items_[i].d < 0) {
      if (items_[i].item_type != Items::Aged_Brie) {
        if (items_[i].item_type != Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
          if (items_[i].v > 0) {
            if (items_[i].item_type != Items::Sulfuras_Hand_of_Ragnaros) {
              items_[i].v = items_[i].v - 1;
            }
          }
        } else {
          items_[i].v = items_[i].v - items_[i].v;
        }
      } else {
        if (items_[i].v < 50) {
          ++items_[i].v;
        }
      }
    }
  }
}

void GildedRose::addItem(const Item &item) { items_.push_back(item); }

void GildedRose::printItems(std::ostream &out_stream) {
  for (vector<Item>::iterator i = items_.begin(); i != items_.end(); i++) {
    out_stream << *i << std::endl;
  }
}
