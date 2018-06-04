#include "GildedRose.h"

using namespace std;


int main() {
    GildedRose app;

    app.addItem(Item("+5 Dexterity Vest", 10, 20));
    app.addItem(Item("Aged Brie", 2, 0));
    app.addItem(Item("Elixir of the Mongoose", 5, 7));
    app.addItem(Item("Sulfuras, Hand of Ragnaros", 0, 80));
    app.addItem(Item("Sulfuras, Hand of Ragnaros", -1, 80));
    app.addItem(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    app.addItem(Item("Backstage passes to a TAFKAL80ETC concert", 10, 49));
    app.addItem(Item("Backstage passes to a TAFKAL80ETC concert", 5, 49));

    cout << "OMGHAI!" << endl;

    for (int day = 0; day <= 30; day++) {
        cout << "-------- day " << day << " --------" << endl;
        app.printItems();
        cout << endl;

        app.updateQuality();
    }
}
