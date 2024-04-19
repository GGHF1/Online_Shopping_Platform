#ifndef BUYER_H
#define BUYER_H

#include <string>
#include <fstream>

class Buyer {

public:
    unsigned long buyer_id;
    static unsigned long next_buyer_id;
    unsigned long funds;
    std::string username;
    std::string password;
    std::string buyer_name;
    std::string country;
    std::string phone_number;
    std::string buyer_address;
    std::string storedUsername;
    std::string storedPassword;

    Buyer();
    Buyer(unsigned long buyer_id, unsigned long funds, const std::string& username,
          const std::string& password, const std::string& buyer_name,
          const std::string& country, const std::string& phone_number,
          const std::string& buyer_address);
    
    void write_to_file(std::ofstream& ofs, Buyer& buyer);
    
    void read_from_file(std::ifstream& ifs, Buyer& buyer);
    
    void display_info();
    
    static void addFunds(Buyer& buyer, unsigned long amount);
    
    unsigned long getBalance();

    void signUp();

    static void changePassword(const std::string& username);

    static int getNextBuyerId();

    static void writeNextBuyerId(const std::string& filename);

    static void readNextBuyerId(const std::string& filename);

    static bool isValidFullName(const std::string& fullName) {
        for (char c : fullName) {
            if (!isalpha(c) && !isspace(c)) {
            return false;
            }
        }
        return true;
    }

    static bool isValidCountry(const std::string& country) {
        for (char c : country) {
            if (!isalpha(c) && !isspace(c)) {
                return false;
            }
        }
        return true;
    }

    static bool isValidPhoneNumber(const std::string& phoneNumber) {
        if (phoneNumber.empty() || phoneNumber[0] != '+') {
            return false;
        }

        for (char c : phoneNumber.substr(1)) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    void write_string(std::ofstream& ofs, const std::string& str);
    static std::string read_string(std::ifstream& ifs);
private:

};

#endif
