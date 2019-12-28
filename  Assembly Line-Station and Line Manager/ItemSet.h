//Hyunjung Kim
//148297179

#ifndef SICT_ITEMSET_H
#define SICT_ITEMSET_H
#include <iostream>
#include <string>

using namespace std;
namespace sict {
	class ItemSet {

		string my_name = "";
		string my_description;
		unsigned int serial{ 0u };
		unsigned int quantity{ 0u };
		static unsigned int field_width;

	public:
		ItemSet();
		ItemSet(const std::string&);
		const std::string& getName() const;
		const unsigned int getSerialNumber() const;
		const unsigned int getQuantity() const;
		ItemSet& operator--();
		void display(std::ostream&, bool) const;
	};
}
#endif