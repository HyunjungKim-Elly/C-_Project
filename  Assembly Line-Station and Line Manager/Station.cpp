//Hyunjung Kim
//148297179

#include "Station.h"
#include <iostream>

using namespace std;
namespace sict {
	Station::Station() {
		s_item = nullptr;
	}
	Station::Station(const std::string &src){
		s_item = new ItemSet(src);
	}
	Station::~Station() {
		delete s_item;
	}
	void Station::display(std::ostream& os) const {
		s_item->display(os, true);
	}
	void Station::fill(std::ostream& os) {
		if (!order_list.empty())
		{
			order_list.back().fillItem(*s_item,os);
		}
	}
	const std::string& Station::getName() const {
		return s_item->getName();
	}
	bool Station::hasAnOrderToRelease() const {
		if (!order_list.empty())
		{
			if (order_list.front().isItemFilled(s_item->getName())||s_item->getQuantity()== 0)
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
		else {
			return false;
		}
	}
	Station& Station::operator--() {
		--(*s_item);

		return *this;
	}
	Station& Station::operator+=(CustomerOrder&& order) {
		order_list.push_back(move(order));
		return *this;
	}
	bool Station::pop(CustomerOrder& ready) {
		if (!order_list.empty())
		{
			ready = move(order_list.front());
			order_list.pop_front();
			return true;

			if (!hasAnOrderToRelease())
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	void Station::validate(std::ostream& os) const {
		os << "getNmae():" << s_item->getName() << endl;
		os << "getSerialNumber():" << s_item->getSerialNumber() << endl;
		os << "getQuantity():" << s_item->getQuantity() << endl;
	}
	bool Station::isempty() {

		if (!order_list.empty())
			return false;
		else
			return true;

	}
}