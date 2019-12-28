//Hyunjung Kim
//148297179
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;

namespace sict {

	char Utilities::delimiter;

	Utilities::Utilities() :f_width(1) {}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos) {

		std::string token;

		if (next_pos <= str.length()) {

			size_t location = str.find_first_of(delimiter, next_pos);

			if (location != std::string::npos) {
				token = str.substr(next_pos, location - next_pos);
				next_pos = location + 1;
			}
			else {
				token = str.substr(next_pos);
				next_pos = str.length() + 1;
			}

			if ((token.empty()) && (next_pos != str.length() + 1)) {
				next_pos = std::string::npos;
				throw str + +"<--Error: Token Failure";
			}

			if (f_width < token.length()) {
				f_width = token.length();
			}

			if (!(next_pos <= str.length())) {
				next_pos = std::string::npos;
			}
		}

		return token;
	}
	const char Utilities::getDelimiter() const {
		return delimiter;
	}
	size_t Utilities::getFieldWidth() const {

		return f_width;
	}
	void Utilities::setDelimiter(const char d) {
		delimiter = d;
	}
	void Utilities::setFieldWidth(size_t n) {
		f_width = n;
	}
}