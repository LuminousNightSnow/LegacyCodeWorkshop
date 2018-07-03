#include "GildedRose.h"

std::ostream &operator<<(std::ostream &s, Item &item) {

  s << item.name_ << ", " << item.days_remaining << ", " << item.quality;
  return s;
}

Item::Item(const string &name, int days_remaining, int quality)
    : name_{name}, days_remaining{days_remaining}, quality{quality} {
  if (name == "Aged Brie") {
    item_type = Items::Aged_Brie;
  } else if (name == "Backstage passes to a TAFKAL80ETC concert") {
    item_type = Items::Backstage_passes_to_a_TAFKAL80ETC_concert;
  } else if (name == "Sulfuras, Hand of Ragnaros") {
    item_type = Items::Sulfuras_Hand_of_Ragnaros;
  } else {
    item_type = Items::Other;
  }
}

void GildedRose::updateQuality() {
  for (int i = 0; i < items_.size(); i++) {
    if (items_[i].item_type == Items::Other) {
      UpdateNormalItem(items_[i]);
      return;
    }
    if (items_[i].item_type == Items::Aged_Brie) {
      UpdateAgedBrieItem(items_[i]);
      return;
    }
    if (items_[i].item_type == Items::Sulfuras_Hand_of_Ragnaros) {
      return;
    }
    if (items_[i].item_type ==
        Items::Backstage_passes_to_a_TAFKAL80ETC_concert) {
      UpdateBackstagePassItem(items_[i]);
      return;
    }
  }
}

void GildedRose::addItem(const Item &item) { items_.push_back(item); }

void GildedRose::printItems(std::ostream &out_stream) {
  for (vector<Item>::iterator i = items_.begin(); i != items_.end(); i++) {
    out_stream << *i << std::endl;
  }
}

void GildedRose::UpdateNormalItem(Item &item) {
  item.days_remaining -= 1;
  DecreaseQuality(item);

  if (item.days_remaining < 0) {
    DecreaseQuality(item);
  }
}

void GildedRose::UpdateAgedBrieItem(Item &item) {
  item.days_remaining -= 1;
  IncreaseQuality(item);

  if (item.days_remaining < 0) {
    IncreaseQuality(item);
  }
}

void GildedRose::UpdateBackstagePassItem(Item &item) {
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

void GildedRose::IncreaseQuality(Item &item) const {
  item.quality = min(item.quality + 1, max_quality_);
}

void GildedRose::DecreaseQuality(Item &item) const {
  item.quality = max(item.quality - 1, min_quality_);
}
