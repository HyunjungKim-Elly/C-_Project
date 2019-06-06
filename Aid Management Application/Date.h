// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name   Hyunjung Kim            Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>


#ifndef AID_DATE_H
#define AID_DATE_H


namespace aid {

	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int DAY_ERROR = 2;
	const int MON_ERROR = 3;
	const int YEAR_ERROR = 4;
	const int PAST_ERROR = 5;
	class Date {
		int p_year;
		int p_month;
		int p_day;
		int error;

		int total;
		//	  int comparetor() const;

		int mdays(int, int) const;
		void errCode(int errorCode);
		bool valid();
	public:
		Date();
		Date(int year, int month, int day);

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		int errCode() const;
		bool bad() const;

		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;

	};
	std::ostream& operator<<(std::ostream& out, const Date& ar);
	std::istream& operator>>(std::istream& in, Date& ar);
}
#endif
/*class Error {

  public:
};

class Good {

public:

};
class Perishable {
public:

};
class iGood {
public:

};*/
