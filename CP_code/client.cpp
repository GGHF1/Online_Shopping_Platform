#include "client.hpp"
#include <experimental/filesystem>
#include <iostream>

unsigned long Buyer::next_buyer_id = 1;

Buyer::Buyer() {
    buyer_id = getNextBuyerId();
    funds = 0;
}

Buyer::Buyer(unsigned long buyer_id, unsigned long funds, const std::string& username, const std::string& password, const std::string& buyer_name,
             const std::string& country, const std::string& phone_number, const std::string& buyer_address)
    : buyer_id(buyer_id),
      funds(funds),
      username(username),
      password(password),
      buyer_name(buyer_name),
      country(country),
      phone_number(phone_number),
      buyer_address(buyer_address) {}

///////////////////////////////////////////////////////////////////////////////
//
//    write_to_file function writes the buyer's information, including unsigned
//    long and string data, to the provided ofstream object using binary file
//    writing operations. It ensures that the data is written in a correct format
//    so it can be properly read back later when reading from the file.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::write_to_file(std::ofstream& ofs, Buyer& buyer) {
    if (!ofs) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    ofs.write(reinterpret_cast<const char*>(&buyer.buyer_id), sizeof(buyer.buyer_id));
    ofs.write(reinterpret_cast<const char*>(&buyer.funds), sizeof(buyer.funds));
    write_string(ofs, buyer.username);
    write_string(ofs, buyer.password);
    write_string(ofs, buyer.buyer_name);
    write_string(ofs, buyer.country);
    write_string(ofs, buyer.phone_number);
    write_string(ofs, buyer.buyer_address);
}

///////////////////////////////////////////////////////////////////////////////
//
//    read_from_file function read the buyer's information, including unsigned
//    long and string data, to the provided ifstream object using binary file
//    reading operations. It ensures that the data is read in a correct format
//    so it can be properly printed out later.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::read_from_file(std::ifstream& ifs, Buyer& buyer) {
    if (!ifs) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    // Read data from the file and populate the Buyer object
    ifs.read(reinterpret_cast<char*>(&buyer.buyer_id), sizeof(buyer.buyer_id));
    ifs.read(reinterpret_cast<char*>(&buyer.funds), sizeof(buyer.funds));

    buyer.username = read_string(ifs);
    buyer.password = read_string(ifs);
    buyer.buyer_name = read_string(ifs);
    buyer.country = read_string(ifs);
    buyer.phone_number = read_string(ifs);
    buyer.buyer_address = read_string(ifs);
}

///////////////////////////////////////////////////////////////////////////////
//
//    write_string function writes a string to a binary file by first writing
//    the size of the string as an integer, followed by writing the characters
//    of the string to the file. This ensures that the string can be properly
//    reconstructed when reading from the file later.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::write_string(std::ofstream& ofs, const std::string& str) {
    size_t size = str.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    ofs.write(str.data(), size);
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
std::string Buyer::read_string(std::ifstream& ifs) {
    size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::string str(size, '\0');
    ifs.read(&str[0], size);
    return str;
}

///////////////////////////////////////////////////////////////////////////////
//
//    Before this function, reading function reads data stored
//    in binary file and after display_info displays buyer's information.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::display_info(){
    std::cout << "Buyer info:" << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "ID: " << buyer_id << std::endl;
    std::cout << "Name: " << buyer_name << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Phone number: " << phone_number << std::endl;
    std::cout << "Address: " << buyer_address << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//
//   addFunds function receivces amount that user wants to add to his balance
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::addFunds(Buyer& buyer, unsigned long amount) {
    buyer.funds += amount;
}

///////////////////////////////////////////////////////////////////////////////
//
//    getBalance function returns funds that user has on his balance
//
///////////////////////////////////////////////////////////////////////////////
unsigned long Buyer::getBalance() {
    return funds;
}

///////////////////////////////////////////////////////////////////////////////
//
//    signUp function allow user to sign up his account.
//    The function prompts the user to enter their username,
//    password, full name, country, phone number, and address using the
//    std::getline function. It then sets the initial value of the funds member
//    variable to 0. opens a binary file with the name "username.bin" using an
//    ofstream object. If the file fails to open, an error message is displayed,
//    and the function returns. Otherwise, the function writes the buyer's
//    information to the file by sequentially calling the write function of
//    the ofstream object. It writes the buyer_id, funds, and each string field
//    using the write_string function. After writing the information,
//    the file is closes. The function then increments the next_buyer_id and
//    writes it to the "buyer_id.bin" file using the writeNextBuyerId function.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::signUp() {
    std::cout << "Enter your login username: ";
    std::getline(std::cin >> std::ws, username);

    std::cout << "Enter your login password: ";
    std::getline(std::cin >> std::ws, password);

    std::cout << "Enter your full name: ";
    std::getline(std::cin >> std::ws, buyer_name);
    while (!isValidFullName(buyer_name)) {
        std::cout << "Invalid full name.\nPlease enter a valid full name: ";
        std::getline(std::cin >> std::ws, buyer_name);
    }

    std::cout << "Enter the country you are living in: ";
    std::getline(std::cin >> std::ws, country);
    while (!isValidCountry(country)) {
        std::cout << "Invalid country.\nPlease enter a valid country: ";
        std::getline(std::cin >> std::ws, country);
    }

    std::cout << "Enter your phone number (including dialing code): ";
    std::getline(std::cin >> std::ws, phone_number);
    while (!isValidPhoneNumber(phone_number)) {
        std::cout << "Invalid phone number.\nPlease enter a valid phone number (including dialing code): ";
        std::getline(std::cin >> std::ws, phone_number);
    }

    std::cout << "Enter your address: ";
    std::getline(std::cin >> std::ws, buyer_address);

    funds = 0;
    // Write buyer information to username.bin
    std::ofstream ofs(username + ".bin", std::ios::binary | std::ios::app);
    if (!ofs.is_open()) {
        std::cout << "Error opening file for writing buyer information." << std::endl;
        return;
    }
    ofs.write(reinterpret_cast<const char*>(&buyer_id), sizeof(buyer_id));
    ofs.write(reinterpret_cast<const char*>(&funds), sizeof(funds));
    write_string(ofs, username);
    write_string(ofs, password);
    write_string(ofs, buyer_name);
    write_string(ofs, country);
    write_string(ofs, phone_number);
    write_string(ofs, buyer_address);

    ofs.close();
    // Increment and write next buyer ID to buyer_id.bin
    next_buyer_id++;
    writeNextBuyerId("buyer_id.bin");
}

bool isValidFullName(const std::string& fullName) {
    for (char c : fullName) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

bool isValidCountry(const std::string& country) {
    for (char c : country) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
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

///////////////////////////////////////////////////////////////////////////////
//
//    getNextBuyerIf function returns unique buyer id
//    for the next registered client
//
///////////////////////////////////////////////////////////////////////////////
int Buyer::getNextBuyerId() {
    return next_buyer_id;
}

///////////////////////////////////////////////////////////////////////////////
//
//    writeNextBuyerId function is responsible for writing the next buyer ID
//    to a binary file. It takes a filename parameter and function creates
//    an ofstream object and opens the file in binary mode. If the file fails
//    to open, an error message is displayed, and the function returns.
//    If file is opened, the function writes the value of the next_buyer_id
//    member variable to the file using the write function of the ofstream.
//    It uses reinterpret_cast to interpret the address of next_buyer_id as
//    a const char* for writing. In the end, file closes.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::writeNextBuyerId(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file for writing next buyer ID." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&next_buyer_id), sizeof(next_buyer_id));

    file.close();
}

///////////////////////////////////////////////////////////////////////////////
//
//    readNextBuyerId function is responsible for reading the next buyer ID
//    from a binary file. It takes a filename parameter. The function first
//    checks if the file specified by filename exists using the
//    std::filesystem::exists function. If the file doesn't exist, it means
//    there are no existing buyer IDs, so it initializes the next_buyer_id
//    member variable to 1 and returns. If the file exists, the function
//    creates an ifstream object and opens the file in binary mode for reading.
//    If the file fails to open, an error message is displayed, and the
//    function returns. If file doesn't fail to open, the function reads
//    the value of the next buyer ID from the file using the read function
//    of the ifstream. It uses reinterpret_cast to interpret the address
//    of next_buyer_id as a char* for reading. File closes.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::readNextBuyerId(const std::string& filename) {
    if (!std::experimental::filesystem::v1::exists(filename)) {
        // If the file doesn't exist, initialize the next buyer ID to 1
        next_buyer_id = 1;
        return;
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file for reading next buyer ID." << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&next_buyer_id), sizeof(next_buyer_id));

    file.close();
}

///////////////////////////////////////////////////////////////////////////////
//
//    changePassword function allows user to change account's password.
//    It takes username parameter. The function first prompts the user to enter
//    their full name and phone number to verify their identity. The input is
//    stored in fullName and phoneNumber variables. After that binary file with
//    the name of the username opens for reading using an ifstream object.
//    If the file fails to open, an error message is displayed and the function
//    returns. If the provided full name and phone number match the buyer's
//    stored information, the function prompts the user to enter their
//    new password and new password is stored in newPassword variable.
//    Next, it opens the same binary file for writing using an ofstream object.
//    If the file fails to open, an error message is displayed and the function
//    returns. The function updates client's password with the new password.
//    write_to_file writes the updated buyer information back to the binary file.
//    The file is then closed. If input is not incorrect, the error message 
//    will be printed out.
//
///////////////////////////////////////////////////////////////////////////////
void Buyer::changePassword(const std::string& username) {

    std::cout << "\nTo change the password, we need to make sure that the account is yours.\n";
    std::string fullName;
    std::cout << "Enter your full name: ";
    std::cin.ignore(); // Ignore any remaining newline characters
    std::getline(std::cin, fullName);

    std::string phoneNumber;
    std::cout << "Enter your phone number: ";
    std::getline(std::cin, phoneNumber);

    std::ifstream ifs(username + ".bin", std::ios::binary);
    if (!ifs) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }
    Buyer buyer;
    buyer.read_from_file(ifs, buyer);
    ifs.close();

    if (fullName == buyer.buyer_name && phoneNumber == buyer.phone_number) {

        std::string newPassword;
        std::cout << "Enter your new password: ";
        std::cin >> newPassword;
        buyer.password = newPassword;

        std::ofstream ofs(username + ".bin", std::ios::binary);
        if (!ofs) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        buyer.write_to_file(ofs, buyer);
        ofs.close();

        std::cout << "Password changed successfully!" << std::endl;
    } else {
        throw std::runtime_error("Incorrect information provided for password change!");
    }
}
