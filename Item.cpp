#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Item.h"
#include "Utilities.h"
size_t Item::field_width = 1;

Item::Item(const std::string& item) {
    description = "no detailed description";
    code = 1u;
    //Create vector of tokens, and a single token for extraction
    std::vector<std::string> tokens;
    //Create Utility object.
    Utilities u;
    bool incomplete = true; //this will keep the utility extracting tokens, until null byte is reached.
    size_t pos = 0; //position of the character in the string item.
    while (incomplete) {
        std::string token;
        token = u.nextToken(item, pos, incomplete);
        if (pos == item.size()) { incomplete = !incomplete; }
        tokens.emplace_back(move(token));
        field_width = (tokens.size() == 1 && u.getFieldWidth() > field_width) ? u.getFieldWidth() : field_width;
    }

    //Hardcoded for robustness
    std::vector<std::string> errors = {
            "Error: item name is empty",
            "Error: filler task is empty",
            "Error: remover task is empty",
    };

    if (tokens.at(0).empty()) throw std::string(errors.at(0));
    name = tokens.at(0);
    if (tokens.at(1).empty()) throw std::string(errors.at(1));
    filler = tokens.at(1);
    if (tokens.at(2).empty()) throw std::string(errors.at(2));
    remover = tokens.at(2);
    if (tokens.size() >= 4) {
        if (!tokens.at(3).empty()) { code = std::stoul(tokens.at(3)); }
        if (tokens.size() == 5 && !tokens.at(4).empty()) { description = tokens.at(4); }
    }
    tokens.clear();
}

//Empty check
bool Item::empty() const {
    return (name.empty() &&
            filler.empty() &&
            remover.empty() &&
            code == 1 &&
            description == "no detailed description");
}


Item& Item::operator++(int i) {
    ++code;
    return *this;
}

//Get Code
unsigned int Item::getCode() const {
    return code;
}


//Get Name
const std::string& Item::getName() const {
    return name;
}

//Get Filler
const std::string& Item::getFiller() const {
    return filler;
}

//Get Remover
const std::string& Item::getRemover() const {
    return remover;
}



//Display
void Item::display(std::ostream& os, bool full) const {

    if (!empty()) {
        os << std::setw(field_width) << std::left << name << " [" << std::setw(CODE_WIDTH) << std::right << std::setfill('0') << code << std::setfill('\0') << "] ";
        if (full) {
            os << "From " << std::setw(field_width) << std::left << name << " To " << remover << std::endl;
            os << std::setw(field_width) << std::left << " " << " " << std::setw(CODE_WIDTH) << " " << " : " << description;
        }
        std::cout << std::endl;
    }
}
