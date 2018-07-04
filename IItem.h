//
// Created by q213677 on 04.07.2018.
//

#ifndef CPP_IITEM_H
#define CPP_IITEM_H

#include <memory>

class IItem {
public:
  IItem(const std::string &name, const int days_remaining, const int quality)
      : name_{name}, days_remaining_{days_remaining}, quality_{quality},
        min_quality_{0}, max_quality_{50} {};
  virtual void update() = 0;
  int GetQuality() const { return quality_; };
  int GetDaysRemaining() const { return days_remaining_; };
  std::string GetName() const { return name_; };

protected:
  void DecreaseQuality(int decrement = 1) {
    quality_ = std::max(quality_ - decrement, min_quality_);
  }
  void IncreaseQuality() { quality_ = std::min(quality_ + 1, max_quality_); }
  void SetQualityToMinValue() { quality_ = min_quality_; };
  void DecreaseDaysRemaining() { days_remaining_ -= 1; }

private:
  std::string name_;
  int days_remaining_;
  int quality_;
  const int min_quality_;
  const int max_quality_;
};

using ItemPointer = std::unique_ptr<IItem>;

template <typename ItemType>
ItemPointer MakeItem(const std::string &name, const int days_remaining,
                     const int quality) {
  return std::make_unique<ItemType>(name, days_remaining, quality);
}

#endif // CPP_IITEM_H
