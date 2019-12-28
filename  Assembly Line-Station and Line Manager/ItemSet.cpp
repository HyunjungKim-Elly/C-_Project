//Hyunjung Kim
//148297179
#include <iostream>
#include <iomanip>
#include <string>

#include "ItemSet.h"
#include "Utilities.h"


using namespace std;

namespace sict {
	unsigned int ItemSet::field_width{ 0u };

	const unsigned int CODE_WIDTH = 5;
	const unsigned int QUAN_WIDTH = 3;

	ItemSet::ItemSet() {

		this->my_name.clear();
		this->my_description.clear();
	}

	ItemSet::ItemSet(const std::string& str) {
		Utilities myUtil;
		size_t next_pos = 0;

		if (!str.empty()) {
			my_name = myUtil.extractToken(str, next_pos);

			if (field_width < myUtil.getFieldWidth()) {
				field_width = (unsigned int)myUtil.getFieldWidth();
				//	cout << "[AG] " << field_width << endl;
			}

			if (next_pos != std::string::npos) {
				std::string tmp = myUtil.extractToken(str, next_pos);
				serial = atoi(tmp.c_str());
			}
			if (next_pos != std::string::npos) {
				std::string tmp = myUtil.extractToken(str, next_pos);
				quantity = atoi(tmp.c_str());
			}
			if (next_pos != std::string::npos) {
				my_description = myUtil.extractToken(str, next_pos);
			}
		}
	}

	const std::string& ItemSet::getName() const {
		return this->my_name;
	}
	const unsigned int ItemSet::getSerialNumber() const {
		return this->serial;
	}
	const unsigned int ItemSet::getQuantity() const {
		return this->quantity;
	}
	ItemSet& ItemSet::operator--() {

		if (quantity > 0) {

			serial++;
			quantity--;

		}
		return *this;
	}
	void ItemSet::display(std::ostream& os, bool full) const {
		os << setw(field_width) << std::setfill(' ') << std::left << my_name
			<< " "
			<< "[" << std::setw(CODE_WIDTH) << std::setfill('0') << std::right << serial << "]";

		if (full) {
			os << " " << "Quantity " << std::setw(QUAN_WIDTH) << std::setfill(' ') << left << quantity
				<< " Description: " << my_description;
		}
		os << std::endl;

	}
}