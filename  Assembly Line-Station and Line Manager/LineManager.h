//Hyunjung Kim
//148297179

#ifndef SICT_LINEMANAGER_H
#define SICT_LINEMANAGER_H
#include <vector>
#include "Station.h"
#include "CustomerOrder.h"
namespace sict {
	class LineManager {
		std::vector<Station*> station_l;
		std::vector<CustomerOrder> order_l;
		std::vector<size_t> next_station;
		std::deque<CustomerOrder> order_process;
		std::deque<CustomerOrder> completed;
		std::deque<CustomerOrder> incompleted;
		size_t first{ 0u };
		size_t last{ 0u };
	public:
		LineManager();
		LineManager(std::vector<Station*> &, std::vector<size_t>&, std::vector<CustomerOrder>&, size_t index, std::ostream&);
		void display(std::ostream& os) const;
		bool run(std::ostream& os);
	};
}

#endif // !SICT_LINEMANAGER_H
