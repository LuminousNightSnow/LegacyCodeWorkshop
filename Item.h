#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <string>
#include <vector>

class IItem {
public:
  IItem(const std::string &name, int days_remaining, int quality)
      : name_(name), days_remaining_(days_remaining), quality_(quality) {}

  virtual ~IItem() = default;

  virtual void Update() = 0;
  void DecreaseDaysRemaining() { days_remaining_ -= 1; }
  int GetDaysRemaining() const { return days_remaining_; }

  void DecreaseQuality() { quality_ = std::max(quality_ - 1, min_quality_); }
  void IncreaseQuality() { quality_ = std::min(quality_ + 1, max_quality_); }
  int GetQuality() const { return quality_; }

private:
  const int min_quality_{0};
  const int max_quality_{50};

  std::string name_;
  int days_remaining_;
  int quality_;

protected:
  void SetQualityToMin() { quality_ = min_quality_; }
};

class NormalItem : public IItem {
public:
  NormalItem(const std::string &name, int days_remaining, int quality)
      : IItem(name, days_remaining, quality) {}

  void Update() override;
};

class BrieItem : public IItem {
public:
  void Update() override;
  BrieItem(const std::string &name, int days_remaining, int quality)
      : IItem(name, days_remaining, quality) {}
};

class SulfurasItem : public IItem {
public:
  void Update() override;

  SulfurasItem(const std::string &name, int days_remaining, int quality)
      : IItem(name, days_remaining, quality) {}
};

class BackstagePassItem : public IItem {
public:
  void Update() override;

  BackstagePassItem(const std::string &name, int days_remaining, int quality)
      : IItem(name, days_remaining, quality) {}

private:
  const int days_close_to_sell_date_{10};
  const int days_very_close_to_sell_date_{5};
};

using ItemPointer = std::shared_ptr<IItem>;
using ItemContainer = std::vector<ItemPointer>;

#endif // ITEM_H
