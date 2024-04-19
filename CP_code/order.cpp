#include "order.hpp"
#include <fstream>
#include <string>
#include <vector>
#include "client.hpp"

Order::Order() {
    buyername = Buyer();
    fundd = Buyer();
    orderid = Item();
    buyerid = Buyer();
    order_date = std::chrono::system_clock::now();
    buyeraddress = Buyer();
}

Order::Order(const Item& orderId, const Buyer& buyerId, const std::chrono::system_clock::time_point& order_date,
             const Buyer& buyerAddress, const Buyer& buyerName, const Buyer& funD)
    : orderid(orderId), buyerid(buyerId), buyername(buyerName), fundd(funD),
      order_date(order_date), buyeraddress(buyerAddress) {
}

///////////////////////////////////////////////////////////////////////////////
//
//  The function read_orderId reads a order ID from a binary file. Initializes
//  the order_id variable to 0. Check if the file was successfully opened.
//  If wasn't, print an error message and return the default order_id value
//  of 0. Read the file into the order_id variable using the read function.
//  The reinterpret_cast is used to interpret the memory of order_id as a
//  char* pointer to read the binary data correctly. The sizeof(order_id)
//  specifies the number of bytes to read. File closes and returns order id.
//
///////////////////////////////////////////////////////////////////////////////
unsigned long Order::read_orderId(const std::string& filename) {
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
//    The function readBuyerId reads a buyer ID from a binary file. Initializes
//    the buyer_id variable to 0. Check if the file was successfully opened.
//    If wasn't, print an error message and return the default buyer_id value
//    of 0. Read the file into the buyer_id variable using the read function.
//    The reinterpret_cast is used to interpret the memory of buyer_id as a
//    char* pointer to read the binary data correctly. The sizeof(buyer_id)
//    specifies the number of bytes to read. File closes and returns buyer id.
//
///////////////////////////////////////////////////////////////////////////////
unsigned long readBuyerId(const std::string& filename) {
    unsigned long buyer_id = 0;

    std::ifstream ifs(filename, std::ios::binary);
    if (ifs) {
        ifs.read(reinterpret_cast<char*>(&buyer_id), sizeof(buyer_id));
        ifs.close();
    } else {
        std::cerr << "Error opening file for reading buyer_id: " << filename << std::endl;
    }

    return buyer_id;
}

///////////////////////////////////////////////////////////////////////////////
//
//    convertBuyersToOrders function reads data from a binary file containing
//    buyer information and converts it into a vector of Order objects. At first,
//    it creates an empty vector to store the Order objects, opens the binary
//    file for reading. If the file fails to open, an error message is printed
//    and an empty vector is returned. Enters a loop that continues until the end
//    of the file is reached. Inside the loop, create a Buyer object to store
//    the buyer information. Read the buyer_id and funds from the binary file
//    and assign them to the corresponding fields in the Buyer object.
//    Read strings from the binary file using the read_string function and
//    assign them to the corresponding fields in the Buyer object. Create an
//    Order object and populate the buyeraddress, buyerid, buyername, and fundd
//    fields with the Buyer object. Add the Order object to the vector of orders
//    Closes the file and returns vector of orders.
//
///////////////////////////////////////////////////////////////////////////////
std::vector<Order> Order::convertBuyersToOrders(const std::string& filename) {
    std::vector<Order> orders;

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return orders;  // Return an empty vector
    }

    while (file.peek() != EOF) {
        Buyer buyer;

        // Read buyer_id
        file.read(reinterpret_cast<char*>(&buyer.buyer_id), sizeof(buyer.buyer_id));
        file.read(reinterpret_cast<char*>(&buyer.funds), sizeof(buyer.funds));
        // Read strings from binary file using the simplified read_string function
        buyer.username = Order::read_string(file);
        buyer.password = Order::read_string(file);
        buyer.buyer_name = Order::read_string(file);
        buyer.country = Order::read_string(file);
        buyer.phone_number = Order::read_string(file);
        buyer.buyer_address = Order::read_string(file);

        // Create an Order object and populate the buyeraddress field
        Order order;
        order.buyeraddress = buyer;
        order.buyerid = buyer;
        order.buyername = buyer;
        order.fundd = buyer;

        orders.push_back(order);
    }
    file.close();
    return orders;
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
std::string Order::read_string(std::ifstream& ifs) {
    size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::string str(size, '\0');
    ifs.read(&str[0], size);
    return str;
}



