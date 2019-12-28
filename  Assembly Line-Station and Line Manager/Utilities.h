//Hyunjung Kim
//148297179
#ifndef SICT_UTILITIES_H
#define SICT_UTILITIES_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace sict {
	class Utilities {
		size_t f_width; //maximum field we need
		static char delimiter; //field delimiter character
	public:
		Utilities();
		const std::string extractToken(const std::string&, size_t&);
		const char getDelimiter() const;
		size_t getFieldWidth() const;
		static void setDelimiter(const char);
		void setFieldWidth(size_t);
	};
}
#endif // !SICT_UTILITIES_H
