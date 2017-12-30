#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerItem.h"
#include "Item.h"

CustomerItem::CustomerItem(const std::string& customerItem) : name(customerItem),filled(false), code(0) {

}

//Asks For
bool CustomerItem::asksFor(const Item& i) const {
    return (name == i.getName());
}

//isFilled
bool CustomerItem::isFilled() const {
    return filled;
}

//Fill
void CustomerItem::fill(const unsigned int c) {
    code = c;
    filled = true;
}

//Clear
void CustomerItem::clear() {
    code = 0;
    filled = false;
}

//getName
const std::string& CustomerItem::getName() const {
    return name;
}

//display
void CustomerItem::display(std::ostream& os)const {

    const char f = (filled) ? '+' : '-';
   // const unsigned int t = (filled) ? code : 0;
    os << " " << f <<  " [" << std::setw(CODE_WIDTH) << std::setfill('0') << std::right << code << "] " << std::setfill('\0') << name << std::endl;

}
