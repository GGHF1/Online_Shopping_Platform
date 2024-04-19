#include <iostream>
#include "menu.hpp"

void MenuLog(){
    std::cout << "\n+---+------------------+---------------------+---+\n";
    std::cout << "|            WELCOME TO THE ONLINE SHOP!         |\n";
    std::cout << "+---+------------------+---------------------+---+\n";
    std::cout << "+---+------------------+---------------------+---+\n";
    std::cout << "| L |     Log in       |       Sign up       | S |\n";
    std::cout << "+---+------------------+---------------------+---+\n\n";

    std::cout << "+---+--------------------------------------------+\n";
    std::cout << "| C |           Change Your Password             |\n";
    std::cout << "+---+--------------------------------------------+\n";
}

void MenuMain(){
    std::cout << std::endl;
    std::cout << "+-----+-----------------------------------------------+\n";
    std::cout << "|  A  |                 Open Catalog                  |\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|  C  |               Your Cart / Order               |\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|  V  |             View Your Information             |\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|  B  |                 Your Balance                  |\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|  L  |              View Your Last Order             |\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|-----|-----------------------------------------------|\n";
    std::cout << "|  E  |                     EXIT                      |\n";
    std::cout << "+-----+-----------------------------------------------+\n";
}

void Back(){
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  B  |              Back To Menu              |\n";
    std::cout << "+-----+----------------------------------------+\n";
}

void removeMenu(){
    std::cout << "+-----++---------------++---------------++-----+" << std::endl;
    std::cout << "|  R  ||  Remove item  ||      Back     ||  B  |" << std::endl;
    std::cout << "+-----++---------------++---------------++-----+" << std::endl;
}

void OrderMenuOption(){
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  O  |              Make An Order             |\n";
    std::cout << "+-----+----------------------------------------+\n";
}

void checkOut(){
    std::cout << "+-----+------------------++-----------------+-----+\n";
    std::cout << "|  C  |     Checkout     ||     Main menu   |  M  |\n";
    std::cout << "+-----+------------------++-----------------+-----+\n";
}

void Fund(){
    std::cout << "+-----+------------------++-----------------+-----+\n";
    std::cout << "|  A  |     Add funds    ||      Back       |  B  |\n";
    std::cout << "+-----+------------------++-----------------+-----+\n";
}

void Filter(){
    std::cout << "\n+-----+----------------------------------------+\n";
    std::cout << "|  I  |              Item Catalog              |\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  V  |             Filter By Vendor           |\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  R  |          Filter By Price Range         |\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  C  |           Filter By Category           |\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  L  |      Sort By Price (Lowest First)      |\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  H  |      Sort By Price (Highest First)     |\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "+-----+----------------------------------------+\n";
    std::cout << "|  B  |              Back To Menu              |\n";
    std::cout << "+-----+----------------------------------------+\n";
}
