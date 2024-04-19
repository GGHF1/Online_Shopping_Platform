#include "item.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <iomanip>


unsigned long Item::next_orderid = 1;

Item::Item() {
    order_id = next_orderid++;
}
Item::Item(std::string item_name, unsigned long price, std::string item_group, std::string vendor)
    : item_name(std::move(item_name)), price(price), item_group(std::move(item_group)), vendor(std::move(vendor)) {}

///////////////////////////////////////////////////////////////////////////////
//
//    write_to_file function writes selected items, including unsigned
//    long and string data, to the provided ofstream object using binary file
//    writing operations. It ensures that the data is written in a correct format
//    so it can be properly read back later when reading from the file.
//
///////////////////////////////////////////////////////////////////////////////
void Item::write_to_file(std::ofstream& ofs, Item& item) {
    
    ofs.write(reinterpret_cast<const char*>(&item.price), sizeof(item.price));
    write_string(ofs, item.item_name);
    write_string(ofs, item.item_group);
    write_string(ofs, item.vendor);
    
}

///////////////////////////////////////////////////////////////////////////////
//
//    write_string function writes a string to a binary file by first writing
//    the size of the string as an integer, followed by writing the characters
//    of the string to the file. This ensures that the string can be properly
//    reconstructed when reading from the file later.
//
///////////////////////////////////////////////////////////////////////////////
void Item::write_string(std::ofstream& ofs, const std::string& str) {
    size_t size = str.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    ofs.write(str.data(), size);
}

///////////////////////////////////////////////////////////////////////////////
//
//    read_from_file function reads selected items, including unsigned
//    long and string data, to the provided ifstream object using binary file
//    reading operations. It ensures that the data is read in a correct format
//    so it can be properly printed out later.
//
///////////////////////////////////////////////////////////////////////////////
void Item::read_from_file(std::ifstream& ifs, Item& item) {
    ifs.read(reinterpret_cast<char*>(&item.price), sizeof(item.price));
    item.item_name = read_string(ifs);
    item.item_group = read_string(ifs);
    item.vendor = read_string(ifs);
}

///////////////////////////////////////////////////////////////////////////////
//
//    read_string takes an ifstream object as input. The function first reads 
//    the size of the string from the file by using the read function of
//    the ifstream object and storing the result in a size_t variable. 
//    Then it creates string with specified size and reads 
//    the memory location of the first character of the string (&str[0]).
//
///////////////////////////////////////////////////////////////////////////////
std::string Item::read_string(std::ifstream& ifs) {
    size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::string str(size, '\0');
    ifs.read(&str[0], size);
    return str;
}

///////////////////////////////////////////////////////////////////////////////
//
//    readSelectedItemsFromFile function reads selected items from a binary file
//    and stores them in a vector of Item objects. It takes the filename of the
//    binary file and a reference to the selectedItems vector as parameters.
//    Function first opens the binary file for reading using an ifstream object.
//    If the file fails to open, a std::runtime_error is thrown with
//    an error message. Before reading the items, the function clears
//    the selectedItems vector. The function creates a loop that continues until
//    the end of the file is reached. Within the loop, it creates an Item object
//    and calls the read_from_file function to read the selected items
//    from the file. If an error is detected, a std::runtime_error is thrown with
//    an error message. If no error, the function adds the item to the
//    selectedItems vector using push_back and std::move to move the item
//    into the vector. File closes.
//
///////////////////////////////////////////////////////////////////////////////
void readSelectedItemsFromFile(const std::string& filename, std::vector<Item>& selectedItems) {
    std::ifstream ifs(filename, std::ios::binary);
    selectedItems.clear();
    if (!ifs) {
        throw std::runtime_error("Please, fill your cart before opening it!\n");
    }

    while (ifs.peek() != EOF) {
        Item item;
        item.read_from_file(ifs, item);

        if (!ifs) {
            throw std::runtime_error("Error occurred while reading item from file.\n");
        }

        selectedItems.push_back(std::move(item));
    }
    ifs.close();
}

///////////////////////////////////////////////////////////////////////////////
//
//    displaySelectedItems function is responsible for displaying selected
//    items. It takes vector with selectedItems. First it creats variable 
//    totalPrice to calculate total price for all selected items.
//    The function enters into the for loop where all selected items
//    information is printed out. During the loop, total price is
//    calculated. Within the loop, it prints out total price for 
//    selected items.
//
///////////////////////////////////////////////////////////////////////////////
void Item::displaySelectedItems(const std::vector<Item>& selectedItems) {
    unsigned long totalPrice = 0;
    std::cout << "Selected items:" << std::endl;
    for (const auto& item : selectedItems) {
        std::cout << "Item: " << item.item_name << std::endl;
        std::cout << "Price: " << item.price << "$" <<std::endl;
        std::cout << "Item Group: " << item.item_group << std::endl;
        std::cout << "Vendor: " << item.vendor << std::endl;
        std::cout << "-----------------------------" << std::endl;
        totalPrice += item.price;
    }
    std::cout << "Total Price: " << totalPrice << "$" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//
//    TotalPrice unsigned long function is being used for calculating
//    total price for selected items. It takes vector with items added
//    to it. Then function enters the loop, it takes price from each
//    item and calculates total price. In the end, totalPrice is returned.
//
///////////////////////////////////////////////////////////////////////////////
unsigned long Item::TotalPrice(const std::vector<Item>& selectedItems){
    unsigned long totalPrice = 0;
    for (const auto& item : selectedItems) {
        totalPrice += item.price;
    }
    return totalPrice;
}

///////////////////////////////////////////////////////////////////////////////
//
//    The removeSelectedItem function removes a specific item from a binary file
//    by creating a temporary file, copying all the items except the one to be
//    removed to the temporary file, and then replacing the original file with
//    the updated temporary file. It takes the filename of the binary file and
//    the item_name of the item to be removed as parameters. The function opens
//    the original binary file for reading using an ifstream object and creats
//    a temporary binary file (named "temp.bin") for writing using an ofstream.
//    Inside a loop that continues until the end of the file is reached,
//    the function reads an Item object from the original file using
//    read_from_file. If the item_name of the read item does not match
//    the item to be removed, it writes the item to the temporary file using
//    write_to_file. Both files close. The function then removes the original
//   binary file using std::remove function, which takes the filename as
//    a c-style string. Finally, it renames the temporary file to the original
//    filename using std::rename function, which also takes the filenames
//    as c-style strings.
//
///////////////////////////////////////////////////////////////////////////////
void Item::removeSelectedItem(const std::string& filename, std::string item_name) {
    std::ifstream ifs(filename, std::ios::binary);
    std::ofstream ofs("temp.bin", std::ios::binary); // Temporary file to write the updated items
    Item item;
    while (ifs.peek() != EOF) {
        item.read_from_file(ifs, item);
        if (item.item_name != item_name) {
            item.write_to_file(ofs, item);
        }
    }

    ifs.close();
    ofs.close();

    // Remove the original binary file
    std::remove(filename.c_str());

    // Rename the temporary file to the original filename
    std::rename("temp.bin", filename.c_str());
}

///////////////////////////////////////////////////////////////////////////////
//
//    The setNextOrderId function of the Item class sets the value of
//    the static variable next_orderid to the provided order ID.
//
///////////////////////////////////////////////////////////////////////////////
void Item::setNextOrderId(unsigned long order_id) {
    next_orderid = order_id;
}

///////////////////////////////////////////////////////////////////////////////
//
//    The getNextOrderId returns the value of the static variable
//    next_orderid, which represents the next available order ID.
//
///////////////////////////////////////////////////////////////////////////////
unsigned long Item::getNextOrderId() {
    return next_orderid;
}

///////////////////////////////////////////////////////////////////////////////
//
//    writeBuyerOrderId function is responsible for writing the order ID of
//    a buyer to a binary file. It takes two parameters: filename and order_id,
//    which is the order ID to be written. Opens the file in binary mode for
//    writing using an ofstream. It performs a check to ensure that the file
//    was successfully opened. If the file opening fails, an error message
//    is displayed and the function returns. If not, it writes the value of
//    the order_id variable to the file using the write function of the ofstream.
//    The reinterpret_cast is used to convert the address of order_id
//    to a const char*. File closes.    
//
///////////////////////////////////////////////////////////////////////////////
void Item::writeBuyerOrderId(const std::string& filename, unsigned long order_id) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file for writing order ID." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&order_id), sizeof(order_id));

    file.close();
}

///////////////////////////////////////////////////////////////////////////////
//
//    The readbuyer_orderId function is used to read the order ID of a buyer from
//    a binary file with filename parameter. Initializes the order_id variable
//    to 0, opens the filename file in binary mode for reading using an ifstream.
//    If file is opened, it reads the order ID from the file using
//    the read function. The reinterpret_cast is used to reinterpret the address
//    of order_id as a char* and the size of order_id is specified as the number
//    of bytes to read. File closes. If file failed to open, an error message is
//    printed out. Returns order id.
//
///////////////////////////////////////////////////////////////////////////////
unsigned long Item::readbuyer_orderId(const std::string& filename) {
    unsigned long order_id = 0;

    std::ifstream ifs(filename, std::ios::binary);
    if (ifs) {
        ifs.read(reinterpret_cast<char*>(&order_id), sizeof(order_id));
        ifs.close();
    } else {
        std::cerr << "Error opening file for reading order_id: " << filename << std::endl;
    }

    return order_id;
}

///////////////////////////////////////////////////////////////////////////////
//
//    writeOrderId function is used to write the next_orderid value to
//    a binary file. Creates a file for writing via ofstream with filename
//    parameter. If file failed to open, error message will be printed out.
//    If not, uses the write function of the ofstream object to write the
//    next_orderid value to the file. The reinterpret_cast is used to
//    reinterpret the address of next_orderid as a const char*, which is
//    the expected type for the write function. The size of next_orderid
//    is specified as the number of bytes to write. File closes.
//
///////////////////////////////////////////////////////////////////////////////
void Item::writeOrderId(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file for writing order ID." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&next_orderid), sizeof(next_orderid));

    file.close();
}

///////////////////////////////////////////////////////////////////////////////
//
//    readOrderId function is used to read the next_orderid value from
//    a binary file. Creates a file for reading via ofstream with filename
//    parameter. If file failed to open, error message will be printed out.
//    If not, uses the read function of the ifstream object to read the
//    next_orderid value from the file. The reinterpret_cast is used to
//    reinterpret the address of next_orderid as a char* and the size
//    of next_orderid is specified as the number of bytes to write. File closes.
//
///////////////////////////////////////////////////////////////////////////////
void Item::readOrderId(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file for reading order ID." << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&next_orderid), sizeof(next_orderid));

    file.close();
}

///////////////////////////////////////////////////////////////////////////////
//
//    The deleteFile function is used to delete a file from the file system.
//    It uses the std::remove function to delete the file. The std::remove
//    function takes a c_string as its argument, so filename.c_str() is used
//    to convert the filename string to a c_string. If value of std::remove
//    is equal to 0, it returns true. Else, returns false.
//
///////////////////////////////////////////////////////////////////////////////
bool Item::deleteFile(const std::string& filename) {
    if (std::remove(filename.c_str()) == 0) {
        // File deletion successful
        return true;
    } else {
        // File deletion failed
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//    filterItemsByVendor function takes a vector of Item objects and a vendor
//    name as input. If the vendor name matches, the item is added to the
//     ilteredItems vector using the push_back function. It filters the items
//    based on the vendor name and returns new vector containing only the items
//    from the specified vendor.
//
///////////////////////////////////////////////////////////////////////////////
std::vector<Item> filterItemsByVendor(const std::vector<Item>& items, const std::string& vendor) {
    std::vector<Item> filteredItems;
    for (const Item& item : items) {
        if (item.vendor == vendor) {
            filteredItems.push_back(item);
        }
    }
    return filteredItems;
}

///////////////////////////////////////////////////////////////////////////////
//
//    The printUniqueVendors function takes a vector of Item objects as input.
//    It iterates over the items and collects the unique vendor names using
//    a std::set. Then, it prints the unique vendor names to the console,
//    separated by spaces. This function provides a list of available vendors
//    for the user to choose from.
//
///////////////////////////////////////////////////////////////////////////////
void Item::printUniqueVendors(const std::vector<Item>& items) {
    std::set<std::string> uniqueVendors;

    // Collect unique vendors
    for (const auto& item : items) {
        uniqueVendors.insert(item.vendor);
    }

    // Print unique vendors
    std::cout << "\nChoose Unique Vendor:\n";
    for (const auto& vendor : uniqueVendors) {
        std::cout << vendor << "  ";
    }
    std::cout << "\n----------------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////
//
//    The filterItemsByPrice function takes a vector of Item objects and
//    a maximum price as input. It iterates over the items and checks if
//    the price of each item is less than or equal to the specified maximum
//    price. If it is, the item is added to the filteredItems vector.
//    Function returns the filteredItems vector containing the items
//    that meet the price criteria.
//
///////////////////////////////////////////////////////////////////////////////
std::vector<Item> filterItemsByPrice(const std::vector<Item>& items, int maxPrice) {
    std::vector<Item> filteredItems;
    for (const auto& item : items) {
        if (item.price <= static_cast<unsigned long>(maxPrice)) {
            filteredItems.push_back(item);
        }
    }
    return filteredItems;
}

///////////////////////////////////////////////////////////////////////////////
//
//    The printUniqueGroups function takes a vector of Item objects as input.
//    It creates a set called uniqueGroups to store unique group names.
//    The function then iterates over the items and inserts each item's
//    group name into the uniqueGroups set. This ensures that only unique group
//    names are stored in the set. The function prints the unique group names.
//
///////////////////////////////////////////////////////////////////////////////
void Item::printUniqueGroups(const std::vector<Item>& items) {
    std::set<std::string> uniqueGroups;

    // Collect unique groups
    for (const auto& item : items) {
        uniqueGroups.insert(item.item_group);
    }

    // Print unique groups
    std::cout << "\nChoose Unique Group:\n";
    for (const auto& item_group : uniqueGroups) {
        std::cout << item_group << "  ";
    }
    std::cout << "\n----------------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////
//
//    filterItemsByGroups function takes a vector of Item objects and
//    a item_group string as input. It creates an empty vector called
//    filteredItems to store the filtered items. The function then iterates
//    over each item in the input vector and checks if its item_group matches
//    the provided item_group string. If a match is found, the item is added to
//    the filteredItems vector. Finally, the function returns the vector of
//    filtered items. This function allows filtering items based on their group.
//
///////////////////////////////////////////////////////////////////////////////
std::vector<Item> filterItemsByGroups(const std::vector<Item>& items, const std::string& item_group) {
    std::vector<Item> filteredItems;
    for (const Item& item : items) {
        if (item.item_group == item_group) {
            filteredItems.push_back(item);
        }
    }
    return filteredItems;
}

///////////////////////////////////////////////////////////////////////////////
//
//    The function compares the prices of item1 and item2 using the <. If the
//    price of item1 is less than the price of item2, the function returns
//    true, indicating that item1 should be placed before item2 in the ordering.
//    If the prices are equal or if the price of item1 is greater than the price
//    of item2, the function returns false, indicating that item2 should
//    be placed before item1 in the ordering.
//
///////////////////////////////////////////////////////////////////////////////
bool Item::compareByPrice1(const Item& item1, const Item& item2) {
    return item1.price < item2.price;
}

///////////////////////////////////////////////////////////////////////////////
//
// Sorts the items vector by price (lowest to highest)
//
///////////////////////////////////////////////////////////////////////////////
void Item::sortByPrice1(std::vector<Item>& items) {
    std::sort(items.begin(), items.end(), compareByPrice1);
}

///////////////////////////////////////////////////////////////////////////////
//
//    The function compares the prices of item1 and item2 using the >. If the
//    price of item1 is higher than the price of item2, the function returns
//    true, indicating that item1 should be placed before item2 in the ordering.
//    If the prices are equal or if the price of item1 is less than the price
//    of item2, the function returns false, indicating that item2 should
//    be placed before item1 in the ordering.
//
///////////////////////////////////////////////////////////////////////////////
bool Item::compareByPrice2(const Item& item1, const Item& item2) {
    return item1.price > item2.price;
}

///////////////////////////////////////////////////////////////////////////////
//
// Sorts the items vector by price (lowest to highest)
//
///////////////////////////////////////////////////////////////////////////////
void Item::sortByPrice2(std::vector<Item>& items) {
    std::sort(items.begin(), items.end(), compareByPrice2);
}

///////////////////////////////////////////////////////////////////////////////
//
//    Function to merge the temporary file into the main file. Open the temporary
//    file for reading (tempIfs) and the main file for writing with the append
//    mode (mainOfs). Check if both file streams are successfully opened.
//    If either of them fails to open, an exception is thrown, indicating that
//    the merge operation has failed. Check if the temporary file is empty by
//    seeking to the end of the file (seekg(0, std::ios::end)) and checking the
//    file position (tellg()). If the file position is at the beginning of the
//    file (tellg() == 0), it means the file is empty. If the temporary file is
//    empty, lose both file streams and return from the function without
//    performing the merge operation. If the temporary file is not empty, seek
//    back to the beginning of the file (seekg(0, std::ios::beg)) to start
//    reading from the beginning. Copy the contents of the temporary file to 
//    the main file using the << stream insertion operator
//    (mainOfs << tempIfs.rdbuf()). This reads the content of the temporary file
//    and writes it to the main file. Both file closes.
//
///////////////////////////////////////////////////////////////////////////////
void Item::mergeFiles(const std::string& tempFilename, const std::string& mainFilename) {
    std::ifstream tempIfs(tempFilename, std::ios::binary);
    std::ofstream mainOfs(mainFilename, std::ios::binary | std::ios::app);

    if (!tempIfs || !mainOfs) {
        throw std::runtime_error("Failed to merge files.");
    }

    // Check if the temporary file is empty
    tempIfs.seekg(0, std::ios::end);
    if (tempIfs.tellg() == 0) {
        tempIfs.close();
        mainOfs.close();
        return;  // Don't merge if the temporary file is empty
    }
    tempIfs.seekg(0, std::ios::beg);

    // Copy the contents of the temporary file to the main file
    mainOfs << tempIfs.rdbuf();

    tempIfs.close();
    mainOfs.close();
}

void Item::printMenu(const std::vector<Item>& items) {
    std::cout << "+-----+------------------------+---------+---------------+------------+" << std::endl;
    std::cout << "|  #  |         Item           |  Price  |   Category    |   Vendor   |" << std::endl;
    std::cout << "+-----+------------------------+---------+---------------+------------+" << std::endl;
    int i = 1;
    for (const auto& item : items) {
        std::cout << "| " << std::setw(4) << std::right << i++ << "| "
                  << std::setw(23) << std::left << item.item_name << "|"
                  << std::setw(7) << std::right << item.price << "  | "
                   << std::setw(13) << std::left << item.item_group << " | "
                  << std::setw(10) << std::left << item.vendor << " |" << std::endl;
        std::cout << "+-----+------------------------+---------+---------------+------------+" << std::endl;
    }
}
