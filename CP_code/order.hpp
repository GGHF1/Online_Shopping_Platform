#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <chrono>
#include <string>
#include "item.hpp"
#include "client.hpp"

class Order {
public:
    Item orderid; 
    Buyer buyerid;
    Buyer buyername;
    Buyer fundd;
    std::chrono::system_clock::time_point order_date;
    Buyer buyeraddress;

    Order();
    Order(const Item& orderId, const Buyer& buyerId,
          const std::chrono::system_clock::time_point& order_date,
          const Buyer& buyerAddress, const Buyer& buyerName,
          const Buyer& funD);

    void displayOrderInfo();
    unsigned long read_orderId(const std::string& filename);
    std::string readBuyerAddress(const std::string& filename);
    static std::string read_string(std::ifstream& ifs);
    static std::vector<Order> convertBuyersToOrders(const std::string& filename);
private:

};

#endif
