// Name : hyunjung Kim  Student Number : 148297179
#include "Error.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace aid;

namespace aid {


	Error::Error(const char* errorMessage) {
		if (errorMessage == nullptr)
		{
			addMessage = nullptr;
		}
		else
		{
			char * c_str = nullptr;
			c_str = new char[strlen(errorMessage) + 1];

			strncpy(c_str, errorMessage, strlen(errorMessage));

			this->addMessage = c_str;
			this->addMessage[strlen(errorMessage)] = '\0';
			if (this->addMessage[0] == '\0')
			{
				clear();
			}

		}
	}

	Error::~Error() {
		clear();
	}
	void Error::clear() {
		delete[] addMessage;
		addMessage = nullptr;
	}
	bool Error::isClear() const {

		return addMessage == nullptr;
	}
	void Error::message(const char* str) {
		clear();

		if (str != nullptr)
		{
			
			addMessage = new char[strlen(str) + 1];

			strncpy(addMessage, str, strlen(str));

			addMessage[strlen(str)] = '\0';

			if (this->addMessage[0] == '\0')
			{
				clear();
			}

		}
		else if (str == nullptr || str[0] == '\0')
		{
			clear();
		}

	}
	const char* Error::message()const {
		if (!isClear())
		{
			return this->addMessage;

		}
		else
		{
			return nullptr;
		}

	}
	std::ostream& operator<<(std::ostream& out, const Error& errorMessage) {
		if (!errorMessage.isClear()) {
			return out << errorMessage.message();
		}
		else {
			return out;
		}
	}
}
