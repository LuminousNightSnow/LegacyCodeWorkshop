//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_BACKSTAGEPASSITEM_H
#define CPP_BACKSTAGEPASSITEM_H

#include "IItem.h"

class BackstagePassItem : public IItem {

public:
  BackstagePassItem(const std::string &name, const int days_remaining,
                    const int quality)
      : IItem(name, days_remaining, quality) {}

  void update() override;

private:
  void UpdateQuality();
};




#endif // CPP_BACKSTAGEPASSITEM_H
