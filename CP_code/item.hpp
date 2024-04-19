#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>
#include <vector>

class Item {
public:
    std::string item_name;
    unsigned long price;
    std::string item_group;
    std::string vendor;
    unsigned long order_id;
    static unsigned long next_orderid;

    Item();
    Item(std::string item_name, unsigned long price, std::string item_group, std::string vendor);
    
    static void printMenu(const std::vector<Item>& items);

    void write_to_file(std::ofstream& ofs, Item& item);
    void read_from_file(std::ifstream& ifs, Item& item);
    static void displaySelectedItems(const std::vector<Item>& selectedItems);
    static void removeSelectedItem(const std::string& filename, std::string item_name);
    static void setNextOrderId(unsigned long order_id);
    static void printUniqueVendors(const std::vector<Item>& items);
    static void printUniqueGroups(const std::vector<Item>& items);

    static unsigned long getNextOrderId();

    static void writeOrderId(const std::string& filename);
    static void readOrderId(const std::string& filename);
    static void writeBuyerOrderId(const std::string& filename, unsigned long order_id);
    static void sortByPrice2(std::vector<Item>& items);
    static bool compareByPrice2(const Item& item1, const Item& item2);
    static void sortByPrice1(std::vector<Item>& items);
    static bool compareByPrice1(const Item& item1, const Item& item2);
    
    static void mergeFiles(const std::string& tempFilename, const std::string& mainFilename);
    unsigned long readbuyer_orderId(const std::string& filename);
    unsigned long TotalPrice(const std::vector<Item>& selectedItems);
    bool deleteFile(const std::string& filename);
    
    static std::vector<Item> filterItemsByGroups(const std::vector<Item>& items, const std::string& item_group) {
    std::vector<Item> filteredItems;
    for (const Item& item : items) {
        if (item.item_group == item_group) {
            filteredItems.push_back(item);
        }
    }
    return filteredItems;
    }
    
    static std::vector<Item> filterItemsByPrice(const std::vector<Item>& items, int maxPrice) {
    std::vector<Item> filteredItems;
    for (const auto& item : items) {
        if (item.price <= static_cast<unsigned long>(maxPrice)) {
            filteredItems.push_back(item);
        }
    }
    return filteredItems;
    }
    
    static std::vector<Item> filterItemsByVendor(const std::vector<Item>& items, const std::string& vendor) {
    std::vector<Item> filteredItems;
    for (const Item& item : items) {
        if (item.vendor == vendor) {
            filteredItems.push_back(item);
        }
    }
    return filteredItems;
}
private:
    void write_string(std::ofstream& ofs, const std::string& str);
    std::string read_string(std::ifstream& ifs);
};

void readSelectedItemsFromFile(const std::string& filename, std::vector<Item>& selectedItems);

#endif
