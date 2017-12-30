#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>
#include "CustomerOrder.h"
#include "CustomerItem.h"
#include "Utilities.h"
#include "Item.h"
size_t CustomerOrder::field_width = 1;



//Default Constructor
CustomerOrder::CustomerOrder(const std::string& customerOrder) : order(nullptr), nOrders(0) {
	
    std::vector<std::string> tokens;
    //Create Utilities object
    Utilities u;
    //Incomplete flag for parsing: if incomplete, continue parsing
    bool incomplete = true;
    size_t pos = 0;
    while (incomplete) {
        std::string token;
        token = u.nextToken(customerOrder, pos, incomplete);
        if (pos == customerOrder.size()) { incomplete = !incomplete; }
        tokens.emplace_back(std::move(token));
        if (tokens.size() >= 1 && tokens.size() <= 2) {
            field_width = (u.getFieldWidth() > field_width) ? u.getFieldWidth() : field_width;
        }
    }


    //Hardcoded for robustness
    std::vector<std::string> errors = {
            "Error: Customer name is empty",
            "Error: Customer product name is empty",
            "Error: Customer item name is empty",
    };

    if (tokens.at(0).empty()) throw std::string(errors.at(0));
    name = tokens.at(0);
    if (tokens.at(1).empty()) throw std::string(errors.at(1));
    product = tokens.at(1);

    //Check if any items are empty or not, and will throw exception if any item is empty.
    for (size_t i = 2; i < tokens.size(); i++) {
        if (tokens.at(i).empty()) throw errors.at(2);
        nOrders++; //Robustly ensures that no items are empty field.
    }
    //dynamically create array of Customer items, to store the items ordered by the customer.
    order = new CustomerItem[nOrders];

    //Go through the array of items again, and fill the values, assuming that they are all not empty
    //as checked previously.
    for (size_t token = 2, item = 0; item < nOrders; token++, item++) {
        std::unique_ptr<CustomerItem> cItem(new CustomerItem(tokens.at(token)));
        order[item] = std::move(*cItem);
    }
    tokens.clear();
}




//Move Constructor
CustomerOrder::CustomerOrder(CustomerOrder&& co) NOEXCEPT{
*this = std::move(co);
}

//Move Assignment
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& co) NOEXCEPT {
if (this != &co) {
name = co.name;
product = co.product;
order = co.order;
co.order = nullptr;
nOrders = co.nOrders;
co.nOrders = 0;
}
return std::move(*this);
}


//Destructor
CustomerOrder::~CustomerOrder() {
    if(order) delete[] order;
}

//Return number of Items
unsigned int CustomerOrder::noOrders() const {
    return nOrders;
}

//Retrieve Item from the customer order: Come back to this.
const std::string& CustomerOrder::operator[](unsigned int i) const {
    if (i >= nOrders) { throw std::string("Item requested out of range."); }
    return order[i].getName();
}


//Fill
void CustomerOrder::fill(Item& i) {
    for (size_t item = 0; item < nOrders; item++) {
        if (order[item].asksFor(i)) {
            if (!order[item].isFilled()) {
                order[item].fill(i.getCode());
                i++;
            }
        }
    }
}

//Remove
void CustomerOrder::remove(Item& i) {

}

//Empty check
bool CustomerOrder::empty() const {
    return (name.empty() && product.empty() && !order && nOrders == 0);
}

//Display
void CustomerOrder::display(std::ostream& os) const {
    os << std::setw(field_width) << std::left << name << " : " << product << std::endl;
    for (size_t i = 0; i < nOrders; i++) {
        order[i].display(os);
    }
}
