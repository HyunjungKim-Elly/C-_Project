//Hyunjung Kim
//148297179

#ifndef SICT_CUSTOMERORDER_H
#define SICT_CUSTOMERORDER_H
#include "ItemSet.h"
#include <vector>
//using namespace std;
namespace sict {

	class CustomerOrder {
		std::string c_name = "";
		std::string c_product = "";
		unsigned int count_item{ 0u };
		static unsigned f_width;

		struct InItem {
			std::string item_name;
			unsigned int serial_num;
			bool filled;
			InItem() :item_name(""), serial_num(0), filled(false) {}
			InItem(std::string src) : item_name(src), serial_num(0), filled(false) {};
		} *itemInfo = nullptr;

	public:
		CustomerOrder();
		CustomerOrder(const string&);
		~CustomerOrder();
		CustomerOrder(CustomerOrder&& src);
		CustomerOrder &operator=(CustomerOrder&& src);
		void fillItem(ItemSet& item, std::ostream& os);
		bool isFilled() const;
		bool isItemFilled(const std::string& item) const;
		std::string getNameProduct() const;
		void display(std::ostream& os, bool = false) const;
	};
}
#endif