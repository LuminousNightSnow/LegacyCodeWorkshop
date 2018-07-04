//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_IITEM_H
#define CPP_IITEM_H

#include <memory>

class IItem {
public:
  IItem(const std::string &name, const int days_remaining, const int quality){};
  virtual void update() = 0;
  int getQuality() const {};
  int getDaysRemaining() const {};
};

using ItemPointer = std::unique_ptr<IItem>;

template <typename ItemType>
ItemPointer MakeItem(const std::string &name, const int days_remaining,
                     const int quality) {
  return std::make_unique<ItemType>(name, days_remaining, quality);
}

#endif // CPP_IITEM_H
