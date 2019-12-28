//Hyunjung Kim
//148297179

#include "CustomerOrder.h"
#include "Utilities.h"
#include "ItemSet.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;
namespace sict {
	unsigned int CustomerOrder::f_width = 0;

	CustomerOrder::CustomerOrder() {
		c_name = "";
		c_product = "";
		itemInfo = nullptr;
		count_item = 0;

	}
	CustomerOrder::CustomerOrder(const string &src) {
		Utilities t_util;
		size_t next_pos = 0;
		size_t howmany = std::count(src.begin(), src.end(), t_util.getDelimiter());
		std::string temp_p = "";
		std::vector <std::string> l_items;

		for (size_t i = 0; i < (howmany + 1); i++)
		{
			try
			{
				if (i == 0) {
					c_name = t_util.extractToken(src, next_pos);
					if (f_width < t_util.getFieldWidth())
					{
						f_width = t_util.getFieldWidth();
					}
				}
				else if (i == 1) {
					c_product = t_util.extractToken(src, next_pos);
				}
				else if (i >= 2) {
					temp_p = t_util.extractToken(src, next_pos);
					l_items.push_back(temp_p);
					count_item++;
				}
			}
			catch (const char *err)
			{
				howmany--;
				i--;
				cout << err << endl;
			}
		}
		if (count_item < 3) {
			*this = CustomerOrder();
			throw "Not a valid order";
		}
		else
		{
			itemInfo = new InItem[count_item];

			for (size_t i = 0; i < count_item; i++)
			{
				itemInfo[i] = InItem(l_items[i]);
			}

		}



	}
	CustomerOrder::~CustomerOrder() {
		delete[] itemInfo;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) {
		*this = std::move(src);
	}

	CustomerOrder &CustomerOrder::operator=(CustomerOrder&& src) {
		if (this != &src)
		{

			delete[] itemInfo;

			c_name = src.c_name;
			c_product = src.c_product;
			count_item = src.count_item;
			itemInfo = src.itemInfo;

			src.c_name = "";
			src.c_product = "";
			src.count_item = 0;
			src.itemInfo = nullptr;
		}
		return *this;
	}
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {
		for (size_t i = 0; i < count_item; i++)
		{
			if (itemInfo[i].item_name == item.getName())
			{
				if (item.getQuantity() > 0 && (!itemInfo[i].filled))
				{
					itemInfo[i].item_name = item.getName();
					itemInfo[i].serial_num = item.getSerialNumber();
					itemInfo[i].filled = true;
					--item;
					os << "Filled " << c_name << " [" << c_product << "]" << "[" << itemInfo[i].item_name << "]" << "[" << itemInfo[i].serial_num << "]" << endl;
				}
				else if (item.getQuantity() < 1)
				{
					os << "Unable to fill " << c_name << " [" << c_product << "]" << "[" << itemInfo[i].item_name << "]" << "[" << itemInfo[i].serial_num << "]" << "out of stock" << endl;
				}
				else if (itemInfo[i].filled)
				{
					os << "Unable to fill " << c_name << " [" << c_product << "]" << "[" << itemInfo[i].item_name << "]" << "[" << itemInfo[i].serial_num << "]" << " already filled" << endl;
				}
			}

		}
	}

	bool CustomerOrder::isFilled() const {
		bool fill = true;
		for (size_t i = 0; i < count_item; i++)
		{
			if (!itemInfo[i].filled)
			{
				fill = false;
			}
		}
		return fill;
	}
	bool CustomerOrder::isItemFilled(const std::string& item) const {
		for (size_t i = 0; i < count_item; i++)
		{
			if (itemInfo[i].item_name == item && !itemInfo[i].filled)
			{
				return false;
			}
		}
		return true;
	}
	std::string CustomerOrder::getNameProduct() const {
		return  c_name + " " + "[" + c_product + "]";
	}
	void CustomerOrder::display(std::ostream& os, bool showDetail) const {
		size_t space = f_width - c_name.length();
		os << c_name + std::string(space, ' ') << "[" << c_product << "]" << endl;
		if (showDetail)
		{
			for (size_t i = 0; i < count_item; i++)
			{
				std::string s = (itemInfo[i].filled) ? "FILLED" : "MISSING";
				os << std::setw(f_width) << " "
					<< "[" << itemInfo[i].serial_num << "] " << itemInfo[i].item_name
					<< "-" << s << std::endl;
			}
		}
		else
		{
			for (size_t i = 0; i < count_item; i++)
			{
				os << std::setw(f_width) << " " << itemInfo[i].item_name << endl;
			}
		}
	}
}