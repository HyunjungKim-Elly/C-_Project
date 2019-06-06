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
#include "Date.h"
#include <iostream>
#include <cstring>
using namespace std;

namespace aid {

	// number of days in month mon and year year

	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode) {
		error = errorCode;

	}
	bool Date::valid() {
		int confirm = 1;
		int total = p_year * 372 + p_month * 31 + p_day;
		if (confirm != 0)
		{
			if (p_year < min_year || p_year > max_year)
			{
				error = YEAR_ERROR;
				confirm = 0;
			}

		}
		if (confirm != 0)
		{
			if (p_month < 1 || p_month > 12)
			{
				error = MON_ERROR;
				confirm = 0;
			}

		}
		if (confirm != 0)
		{
			if (p_day < 1 || p_day > mdays(p_month, p_year))
			{
				error = DAY_ERROR;
				confirm = 0;
			}
		}
		if (total < min_date)
		{
			confirm = 0;
			error = PAST_ERROR;
		}
		return confirm;
	}

	Date::Date() {
		p_year = 0;
		p_month = 0;
		p_day = 0;
		total = 0;
		error = NO_ERROR;
	}
	Date::Date(int year, int month, int day) {

		p_year = year;
		p_month = month;
		p_day = day;

		if (valid())
		{
			total = p_year * 372 + p_month * 31 + p_day;
			error = NO_ERROR;
		}
		else
		{
			*this = Date();

		}
	}

	bool Date::operator==(const Date& rhs) const {
		bool same = total == rhs.total ? true : false;
		return same;
	}
	bool Date::operator!=(const Date& rhs) const {
		return total != rhs.total;
	}
	bool Date::operator<(const Date& rhs) const {
		bool smaller = total < rhs.total ? true : false;
		return smaller;
	}
	bool Date::operator>(const Date& rhs) const {
		bool bigger = this->total > rhs.total ? true : false;
		return bigger;
	}
	bool Date::operator<=(const Date& rhs) const {
		bool s_equal = this->total <= rhs.total ? true : false;
		return s_equal;
	}
	bool Date::operator>=(const Date& rhs) const {
		bool b_equal = this->total >= rhs.total ? true : false;
		return b_equal;
	}

	int Date::errCode() const {
		return error;
	}
	bool Date::bad() const {
		bool bad = false;
		if (error != NO_ERROR)
		{
			bad = true;
		}
		return bad;
	}

	std::istream& Date::read(std::istream& istr) {
		int year;
		int month;
		int day;
		char c;

		istr >> year >> c >> month >> c >> day;

		if (istr.fail())
		{
			*this = Date();
			errCode(CIN_FAILED);
		}
		else if (year < min_year || year > max_year)
		{
			*this = Date();
			errCode(YEAR_ERROR);
		}
		else if (month < 1 || month > 12)
		{
			*this = Date();
			errCode(MON_ERROR);
		}
		else if (day < 0 || day > mdays(month, year))
		{
			*this = Date();
			errCode(DAY_ERROR);
		}
		else
		{
			p_year = year;
			p_month = month;
			p_day = day;
			total = year * 372 + month * 31 + day;
			if (total < min_date)
			{
				*this = Date();
				errCode(PAST_ERROR);
			}

		}



		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const {

		ostr << p_year << "/";

		if (p_month < 10)
		{
			ostr << "0" << p_month << "/";
		}
		else
		{
			ostr << p_month << "/";
		}

		if (p_day < 10)
		{
			ostr << "0" << p_day;
		}
		else
		{
			ostr << p_day;
		}
		return ostr;
	}

	std::ostream& operator<<(std::ostream& out, const Date& ar) {
		ar.write(out);
		return out;
	}
	std::istream& operator>>(std::istream& in, Date& ar) {
		ar.read(in);
		return in;

	}

}


