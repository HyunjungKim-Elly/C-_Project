//Hyunjung Kim
//148297179

#include "LineManager.h"
#include "ItemSet.h"
#include "Utilities.h"
#include "AssemblyLine.h"
#include "CustomerOrder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
namespace sict {
	LineManager::LineManager() {};
	LineManager::LineManager(std::vector<Station*> &station, std::vector<size_t>& next, std::vector<CustomerOrder>&process, size_t index, std::ostream& os) {
		station_l = station;
		next_station = next;
		first = index;
		last = std::find(next.begin(), next.end(), 5) - next.begin();
		for (size_t i = 0; i < process.size(); i++)
		{
			order_process.push_front(std::move(process[i]));
		}

	}
	void LineManager::display(std::ostream& os) const {
		os << "COMPLETED ORDERS" << std::endl;
		for (auto &i : completed) {
			i.display(os, true);
		}
		os << "INCOMPLETED ORDERS" << std::endl;
		for (auto &i : incompleted) {
			i.display(os, true);
		}
	}
	bool LineManager::run(std::ostream& os) {
		CustomerOrder temp;
		if (!order_process.empty())
		{
			*station_l[first] += std::move(order_process.back());
			order_process.pop_back();
		}
		for_each(station_l.begin(), station_l.end(), [&](auto& station) {
			station->fill(os);
		});
		for (size_t i = 0; i < station_l.size(); i++)
		{
			if (station_l[i]->hasAnOrderToRelease())
			{
				if (i!=last)
				{
					station_l[i]->pop(temp);
					os << "--> " << temp.getNameProduct()
						<< " moved from " + station_l[i]->getName()
						<< " to " << station_l[next_station[i]]->getName()
						<< std::endl;
					*station_l[next_station[i]] += std::move(temp);
				}
				else
				{
					station_l[i]->pop(temp);
					if (temp.isFilled())
					{
						os << "--> " << temp.getNameProduct()
							<< " move from " + station_l[i]->getName() << " to " << "Completed Set" << std::endl;
						completed.push_back(std::move(temp));
					}
					else
					{
						os << "--> " << temp.getNameProduct()
							<< " moved from " + station_l[i]->getName() << " to " << "Incompleted Set" << std::endl;
						incompleted.push_back(std::move(temp));
					}
				}
			}
		}

		for (size_t i = 0; i < station_l.size(); i++)
		{
			if (!station_l[i]->isempty())
			{
				return false;
			}
		}
		return true;
	}

}