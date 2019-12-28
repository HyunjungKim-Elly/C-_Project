//Hyunjung Kim
//148297179

#ifndef SICT_STATION_H
#define SICT_STATION_H
#include "ItemSet.h"
#include "CustomerOrder.h"
#include "Utilities.h"
#include <deque>
namespace sict {
	class Station {
		std::deque<CustomerOrder> order_list;
		ItemSet *s_item;
	public:
		Station();
		Station(const std::string &);
		~Station();
		void display(std::ostream& os) const;
		void fill(std::ostream& os);
		const std::string& getName() const;
		bool hasAnOrderToRelease() const;
		Station& operator--();
		Station& operator+=(CustomerOrder&& order);
		bool pop(CustomerOrder& ready);
		void validate(std::ostream& os) const;
		Station(Station&) = delete;
		Station(Station&&) = delete;
		Station &operator = (Station&) = delete;
		Station &operator = (Station&&) = delete;
		bool isempty();

	};
}
#endif // !SICT_STATION_H
