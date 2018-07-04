//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_NORMALITEM_H
#define CPP_NORMALITEM_H

#include "IItem.h"

class NormalItem : public IItem {
public:
  NormalItem(const std::string &name, int days_remaining, int quality)
      : IItem(name, days_remaining, quality) {}

  void update() override {
    DecreaseQuality();
    DecreaseDaysRemaining();
  }
};

#endif // CPP_NORMALITEM_H
