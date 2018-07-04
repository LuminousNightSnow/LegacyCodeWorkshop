//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_SULFURASITEM_H
#define CPP_SULFURASITEM_H

#include "IItem.h"

class SulfurasItem : public IItem {
public:
  SulfurasItem(const std::string &name, const int days_remaining,
               const int quality)
      : IItem(name, days_remaining, quality) {}

  void update() override {}
};
#endif // CPP_SULFURASITEM_H
