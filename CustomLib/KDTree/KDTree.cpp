#include <iostream>
#include <Array.h>
#include <Vector.h>
#include <Vector2.h>
#include <KDTree.h>
#include <string>

enum ItemType
{
    IT_HEALTH,
    IT_WELLNESS,
    IT_MONEY,
    IT_COUNT,
};

struct Item
{
    std::string name;
    ItemType type;
    Vector2 pos;

    struct FilterByType
    {
        ItemType itemType;
        bool operator()(const void* data)
        {
            const Item* item = (const Item*)data;
            return item->type == itemType;
        }
    };
};


int main()
{
    std::cout << "KDtree test!\n";
    Vector<Item> items;
    KDTree<float, 2> itemlocations;

    int maxItems = 100;
    items.Resize(maxItems);
    for (int i = 0; i < maxItems; ++i)
    {
        items[i].name = "ItemName" + std::to_string(i);
        items[i].type = (ItemType)(rand() % IT_COUNT);
        switch (items[i].type)
        {
        case IT_HEALTH: items[i].name += "Health"; break;
        case IT_WELLNESS: items[i].name += "Wellness"; break;
        case IT_MONEY: items[i].name += "Money"; break;
        default: break;
        }

        items[i].pos.x = (float)(rand() % 501);
        items[i].pos.y = (float)(rand() % 501);
        itemlocations.AddItem(&items[i].pos.x, &items[i]);
    }

    itemlocations.BuildTree();
    Vector2 minRange = { 200.0f, 200.0f };
    Vector2 maxRange = { 400.0f, 400.0f };
    Vector<const void*> itemsInRange;
    Item::FilterByType filter;
    itemlocations.FindInRange(itemsInRange, &minRange.x, &maxRange.x, filter);
    for (Vector<const void*>::Iterator iter = itemsInRange.Begin(); iter != itemsInRange.End(); ++iter)
    {
        const Item* item = (const Item*)(*iter);
        std::cout << "Item In Range: " << item->name << " (" << item->pos.x << "," << item->pos.y << ")\n";
    }

    itemlocations.Terminate();

}

