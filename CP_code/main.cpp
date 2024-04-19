#include "client.hpp"
#include "item.hpp"
#include "order.hpp"
#include "menu.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>

int main() {

    MenuLog();
    std::string usernames;
    std::string passwords;
    Buyer::readNextBuyerId("buyer_id.bin");
    char option;
    Buyer buyer;
    Order order;
    Item item;
    std::cout << "\n--> ";
    std::cin >> option;
    option = toupper(option);
    switch(option){

        case 'L':{
            std::cout << "Enter your login username: ";
            std::cin >> usernames;
            std::ifstream ifs(usernames + ".bin", std::ios::binary);
            if(!ifs){
                std::cerr << "Username doesn't exist!\n";
                return 1;
            }
            buyer.read_from_file(ifs, buyer);
            ifs.close();
            std::cout << "Enter your login password: ";
            std::cin >> passwords;
            if (usernames != buyer.username || passwords != buyer.password) {
                std::cerr << "Incorrect username or password!" << std::endl;
                return 0;
            } 
            else {
                std::cout << "Login successful!" << std::endl;
            }
            break;
        }
        case 'S':{
            buyer.signUp();
            std::cout << "\n-------------------------------------\n";
            std::cout << "Please Log in into your account\n";
            std::cout << "Enter your login username: ";
            std::cin >> usernames;
            std::ifstream ifs(usernames + ".bin", std::ios::binary);
            if(!ifs){
                std::cerr << "Username doesn't exist!\n";
                return 1;
            }
            buyer.read_from_file(ifs, buyer);
            ifs.close();
            std::cout << "Enter your login password: ";
            std::cin >> passwords;
            if (usernames != buyer.username || passwords != buyer.password) {
                std::cerr << "Incorrect username or password!" << std::endl;
                return 0;
            } 
            else {
                std::cout << "Login successful!" << std::endl;
            }
            break;
        }
        case 'C':{
            std::cout << "Enter your login username: ";
            std::cin >> usernames;
            Buyer::changePassword(usernames);
            std::cout << "\nPlease, relog in!\n" << "Enter your login username: ";
            std::cin >> usernames;
            std::ifstream ifs(usernames + ".bin", std::ios::binary);
            if(!ifs){
                std::cerr << "Username doesn't exist!\n";
                return 1;
            }
            buyer.read_from_file(ifs, buyer);
            ifs.close();
            std::cout << "Enter your login password: ";
            std::cin >> passwords;
            if (usernames != buyer.username || passwords != buyer.password) {
                std::cerr << "Incorrect username or password!" << std::endl;
                return 0;
            } 
            else {
                std::cout << "Login successful!" << std::endl;
            }
            break;
        }
        default:
            std::cerr << "Incorrect input! Try again\n";
            return 1;
    }

    std::vector<Item> items; //List of items available
    items.push_back(Item("Iphone 14", 999, "Electronics", "Apple"));
    items.push_back(Item("Samsung S21", 799, "Electronics", "Samsung"));
    items.push_back(Item("Nike Air Max", 150, "Footwear", "Nike"));
    items.push_back(Item("Nike Air Force", 180, "Footwear", "Adidas"));
    items.push_back(Item("Sony WH-CH510", 349, "Electronics", "Sony"));
    items.push_back(Item("T-shirt", 30, "Clothes", "H&M"));
    items.push_back(Item("Laptop", 1200, "Electronics", "Dell"));
    items.push_back(Item("Canon EOS 80D", 1199, "Electronics", "Canon"));
    items.push_back(Item("Levi's Jeans", 60, "Clothes", "Levi's"));
    items.push_back(Item("Samsung Galaxy Watch", 349, "Electronics", "Samsung"));
    items.push_back(Item("Nike Air Jordan", 200, "Footwear", "Nike"));
    items.push_back(Item("Dress Shirt", 50, "Clothes", "Zara"));
    items.push_back(Item("Apple MacBook Pro", 1999, "Electronics", "Apple"));

    std::vector<Item> selectedItems; //Vector for storing selected items
    
    std::ifstream file("order_id.bin", std::ios::binary);
    if (!file.is_open()) {
        // If the file doesn't exist, set the initial order ID and create the file
        unsigned long initial_order_id = 1;
        Item::setNextOrderId(initial_order_id);
        Item::writeOrderId("order_id.bin");
    } else {
        // If the file exists, read the order ID from it
        file.close();
        Item::readOrderId("order_id.bin");
    }

    std::string formatted_order_date; // Variable to store the formatted order date
    unsigned long order_id = Item::getNextOrderId();

    MenuMain();
    std::cout << "\n-->  ";
    bool choose = true;
    char MenuOption;
    while(choose){
        std::cin >> MenuOption;
        MenuOption = toupper(MenuOption);
        switch(MenuOption) {
            
            case 'V': {
                std::ifstream ifs(buyer.username + ".bin", std::ios::binary);
                buyer.read_from_file(ifs, buyer);
                ifs.close();
                buyer.display_info();
                Back();
                char BacK;
                std::cout << "\n--> ";
                std::cin >> BacK;
                if (BacK == 'B'){
                    break;
                }
                else {
                    std::cerr << "Incorrect input!\n";
                    return 1;
                }
            }
            case 'E':
                std::cout << "Quitting\n";
                choose = false;
                return 0;
            
            case 'A':{
                std::ofstream ofs;
                std::string filename = buyer.username + "_item.bin";
                std::string tempFilename = "temp_" + buyer.username + "_item.bin";
                std::ofstream tempOfs(tempFilename, std::ios::binary);

                if (!tempOfs) {
                    throw std::runtime_error("Failed to create temporary file.");
                }

                Item item;
                Filter();
                char itemOption = 0;
                std::cout << "--> ";
                std::cin >> itemOption;
                itemOption = toupper(itemOption);
                    switch(itemOption){
                        case 'I':{
                            bool choosing = true;
                            while (choosing) {
                                int choice;
                                Item::printMenu(items);
                                std::cout << "\nSelect an item to add to your cart (Enter 0 to exit): ";
                                std::cin >> choice;
                                std::cin.ignore(); // Ignore the remaining newline character

                                if (choice == 0) {
                                    choosing = false;
                                }

                                if (static_cast<unsigned long>(choice) >= 1 && static_cast<unsigned long>(choice) <= items.size()) {
                                    Item selected = items[choice - 1];
                                    selectedItems.push_back(selected);
                                    
                                } else if (choice < 0) {
                                    std::cout << "Invalid choice. Please try again." << std::endl;
                                } 
                            }
                            
                            break;
                        }
                        case 'V':{
                            Item::printUniqueVendors(items);
                            std::string vend;
                            std::cout << "\n--> ";
                            std::cin >> vend;
                            std::vector<Item> filteredItems = item.filterItemsByVendor(items, vend);

                            bool choosing = true;
                            while (choosing) {
                                Item::printMenu(filteredItems);
                                int choice;
                                std::cout << "\nSelect an item to add to your cart (Enter 0 to exit): ";
                                std::cin >> choice;
                                std::cin.ignore(); // Ignore the remaining newline character

                                if (choice == 0) {
                                    choosing = false;
                                }

                                if (static_cast<unsigned long>(choice) >= 1 && static_cast<unsigned long>(choice) <= filteredItems.size()) {
                                    Item selected = filteredItems[choice - 1];
                                    selectedItems.push_back(selected);
                                    std::cout << "-----------------------\n"
                                    << "Item added to the cart." << "\n-----------------------\n\n";
                                } else if (choice < 0) {
                                    std::cout << "Invalid choice. Please try again." << std::endl;
                                } 
                            }
                            
                            break;
                        }
                        case 'R':{
                            int maxPrice;
                            std::cout << "Enter the maximum price: ";
                            std::cin >> maxPrice;
                            std::vector<Item> filteredItems = item.filterItemsByPrice(items, maxPrice);

                            bool choosing = true;
                            while (choosing) {
                                Item::printMenu(filteredItems);
                                int choice;
                                std::cout << "\nSelect an item to add to your cart (Enter 0 to exit): ";
                                std::cin >> choice;
                                std::cin.ignore(); // Ignore the remaining newline character

                                if (choice == 0) {
                                    choosing = false;
                                }

                                if (static_cast<unsigned long>(choice) >= 1 && static_cast<unsigned long>(choice) <= filteredItems.size()) {
                                    Item selected = filteredItems[choice - 1];
                                    selectedItems.push_back(selected);
                                    std::cout << "-----------------------\n"
                                    << "Item added to the cart." << "\n-----------------------\n\n";
                                } else if (choice < 0) {
                                    std::cout << "Invalid choice. Please try again." << std::endl;
                                } 
                            }
                            
                            break;

                        }
                        case 'C':{
                            Item::printUniqueGroups(items);
                            std::string group;
                            std::cout << "\n--> ";
                            std::cin >> group;
                            std::vector<Item> filteredItems = item.filterItemsByGroups(items, group);

                            bool choosing = true;
                            while (choosing) {
                                Item::printMenu(filteredItems);
                                int choice;
                                std::cout << "\nSelect an item to add to your cart (Enter 0 to exit): ";
                                std::cin >> choice;
                                std::cin.ignore(); // Ignore the remaining newline character

                                if (choice == 0) {
                                    choosing = false;
                                }

                                if (static_cast<unsigned long>(choice) >= 1 && static_cast<unsigned long>(choice) <= filteredItems.size()) {
                                    Item selected = filteredItems[choice - 1];
                                    selectedItems.push_back(selected);
                                    std::cout << "-----------------------\n"
                                    << "Item added to the cart." << "\n-----------------------\n\n";
                                } else if (choice < 0) {
                                    std::cout << "Invalid choice. Please try again." << std::endl;
                                } 
                            }
                           
                            break;
                        }
                        case 'L':{
                            std::vector<Item> sortedItem = items;
                            Item::sortByPrice1(sortedItem);

                            bool choosing = true;
                            while (choosing) {
                                Item::printMenu(sortedItem);
                                int choice;
                                std::cout << "\nSelect an item to add to your cart (Enter 0 to exit): ";
                                std::cin >> choice;
                                std::cin.ignore(); // Ignore the remaining newline character

                                if (choice == 0) {
                                    choosing = false;
                                }

                                if (static_cast<unsigned long>(choice) >= 1 && static_cast<unsigned long>(choice) <= sortedItem.size()) {
                                    Item selected = sortedItem[choice - 1];
                                    selectedItems.push_back(selected);
                                    std::cout << "-----------------------\n"
                                    << "Item added to the cart." << "\n-----------------------\n\n";
                                } else if (choice < 0) {
                                    std::cout << "Invalid choice. Please try again." << std::endl;
                                } 
                            }
                            
                            break;
                        }
                        case 'H':{
                            std::vector<Item> sortedItems = items;
                            Item::sortByPrice2(sortedItems);

                            bool choosing = true;
                            while (choosing) {
                                Item::printMenu(sortedItems);
                                int choice;
                                std::cout << "\nSelect an item to add to your cart (Enter 0 to exit): ";
                                std::cin >> choice;
                                std::cin.ignore(); // Ignore the remaining newline character

                                if (choice == 0) {
                                    choosing = false;
                                }

                                if (static_cast<unsigned long>(choice) >= 1 && static_cast<unsigned long>(choice) <= sortedItems.size()) {
                                    Item selected = sortedItems[choice - 1];
                                    selectedItems.push_back(selected);
                                    std::cout << "-----------------------\n"
                                    << "Item added to the cart." << "\n-----------------------\n\n";
                                } else if (choice < 0) {
                                    std::cout << "Invalid choice. Please try again." << std::endl;
                                } 
                            }
                            
                            break;
                        }
                        case 'B':
                            break;
                        default:
                            std::cerr << "Incorrect input!\n";
                            return 1;
                    }
                // Write the selected items to the file
                for (auto& item : selectedItems) {
                    item.write_to_file(tempOfs, item);
                }
                selectedItems.clear();
                tempOfs.close();
                Item::mergeFiles(tempFilename, filename);
                remove(tempFilename.c_str());
                        
                            
                unsigned long current_order_id = order_id;
                Item::writeBuyerOrderId(buyer.username + "_orderid.bin", current_order_id);
                Item::setNextOrderId(current_order_id + 1);
                Item::writeOrderId("order_id.bin");
                break;
            }
            case 'C':{
                readSelectedItemsFromFile(buyer.username + "_item.bin", selectedItems);
                Item::displaySelectedItems(selectedItems);  // Display the selected items to the user
                order_id = item.readbuyer_orderId(buyer.username + "_orderid.bin");
                std::cout << "Your order ID: " << order_id << std::endl;
                removeMenu();
                OrderMenuOption();          
                char rem = 0;
                std::cout << "\n-->  ";
                std::cin >> rem;
                rem = toupper(rem);
                switch(rem){
                   case 'R':{
                        std::string itemToRemove;
                        std::cout << "Enter the name of the item to remove: ";
                        std::getline(std::cin >> std::ws, itemToRemove);
                        Item::removeSelectedItem(buyer.username + "_item.bin", itemToRemove);
                        break;
                    }
                    case 'B':
                        break;
                    case 'O':{
                        std::stringstream ss;
                        std::time_t order_time = std::chrono::system_clock::to_time_t(order.order_date);
                        std::tm* order_tm = std::localtime(&order_time);
                        ss << std::put_time(order_tm, "%Y-%m-%d %H:%M:%S");
                        formatted_order_date = ss.str();
                        unsigned long totalPrice = item.TotalPrice(selectedItems);

                        //order.displayOrderInfo();
                        order.orderid.order_id = order.read_orderId(buyer.username + "_orderid.bin");
                        //order.buyerid.buyer_id = readBuyerId(buyer.username + ".bin");
                        std::vector<Order> orders = Order::convertBuyersToOrders(buyer.username + ".bin");
                        std::string address;
                        int buy_id;
                        std::string buy_name;
                        unsigned long fund_available;
                        for (const Order& order : orders) {
                            address = order.buyeraddress.buyer_address;
                            buy_id = order.buyerid.buyer_id;
                            buy_name = order.buyername.buyer_name;
                            fund_available = order.fundd.funds;
                        }
                        std::cout << "Order ID: " << order.orderid.order_id << std::endl;
                        std::cout << "Buyer ID: " << buy_id << std::endl;
                        std::cout << "Buyer's Full Name: " << buy_name << std::endl;
                        std::cout << "Order Date: " << formatted_order_date << std::endl;
                        std::cout << "Buyer Address: " << address << std::endl;
                        std::cout << "Total Price: " << totalPrice << "$\n";
                        std::cout << "Funds available: " << fund_available << "$\n";
                        std::cout << "----------------------------------\n";
                        std::cout << "Please, check your order before comfirming it!\n";
                        checkOut();
                        char confirm;
                        std::cout << "\n-> ";
                        std::cin >> confirm;
                        confirm = toupper(confirm);
                        switch(confirm){
                            case 'M':
                                break;
                            case 'C':{
                                unsigned long pay = 0;
                                if (totalPrice > fund_available){
                                    std::cout << "You have have enough balance to purchase these items!\n"
                                    << "Please, add funds to your balance.\n";
                                    break;
                                }
                                else{
                                    pay = fund_available - totalPrice;
                                    std::cout << "Thank you for your purchase!\n";
                                    std::ofstream ofs(buyer.username + "_last_order.bin", std::ios::binary);
                                    for (auto& item : selectedItems) {
                                        item.write_to_file(ofs, item);
                                    }
                                    ofs.close();
                                    item.deleteFile(buyer.username + "_item.bin");
                                    item.deleteFile(buyer.username + "_orderid.bin");
                                    buyer.funds = pay;
                                    std::ofstream file(buyer.username + ".bin", std::ios::binary);
                                    if(!file){
                                        std::cerr << "File doesn't exist!\n";
                                        return 1;
                                    }
                                    buyer.write_to_file(file, buyer);
                                    file.close();

                                }
                                break;
                            }
                            default:
                                std::cerr << "Incorrect input!\n";
                                return 1;
                        }
                        break;
                        
                    }
                    default:
                        std::cerr << "Error, incorrect input!\n";
                        return 1;        
                }
                break;
            }
            case 'B':{
                std::ifstream ifs(buyer.username + ".bin", std::ios::binary);
                if(!ifs){
                    std::cerr << "File doesn't exist!\n";
                    return 1;
                }
                buyer.read_from_file(ifs, buyer);
                ifs.close();
                std::cout << "Current Balance: " << buyer.getBalance() << "$" << std::endl;
                std::cout << "-----------------------------\n" << std::endl;
                Fund();
                //Buyer::addFunds();
                char fund_option;
                std::cout << "--> ";
                std::cin >> fund_option;
                fund_option = toupper(fund_option);
                switch(fund_option){
                    case 'A':{
                        unsigned long amount;
                        std::cout << "Enter the amount to add: ";
                        std::cin >> amount;
                        buyer.addFunds(buyer, amount);
                        std::ofstream ofs(buyer.username + ".bin", std::ios::binary);
                        if(!ofs){
                            std::cerr << "File doesn't exist!\n";
                            return 1;
                        }
                        buyer.write_to_file(ofs, buyer);
                        ofs.close();
                        std::cout << "Updated Balance: " << buyer.getBalance() << "$" << std::endl;
                        std::cout << "-----------------------------\n" << std::endl;
                        break;
                    }
                    case 'B':
                        break;   
                    default:
                        std::cerr << "Incorrect input!\n";
                        return 1;
                }
                break;
            }
            case 'L':{
                readSelectedItemsFromFile(buyer.username + "_last_order.bin", selectedItems);
                Item::displaySelectedItems(selectedItems); 
                Back();
                char BacK;
                std::cout << "\n--> ";
                std::cin >> BacK;
                if (BacK == 'B'){
                    break;
                }
                else {
                    std::cerr << "Incorrect input!\n";
                    return 1;
                }
            }
            default:
                std::cerr << "Incorrect input!\n";
                return 1;
        }
        MenuMain();
        std::cout << "\n--> ";
    }
}
