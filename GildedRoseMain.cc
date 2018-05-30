#include "GildedRose.h"

using namespace std;

int main() {
  GildedRose app;

  app.addItem(Item("+5 Dexterity Vest", 10, 20));

  cout << "OMGHAI!" << endl;
  app.updateQuality();
  app.printItems();
}
