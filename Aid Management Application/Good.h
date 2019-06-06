//hyunjung Kim
//148297179
#ifndef _AID_GOOD_H
#define _AID_GOOD_H
#include<iostream>
#include <fstream>
#include "Error.h"
#include "iGood.h"
namespace aid {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good : public iGood{
	private:
		char g_type;
		char g_sku[max_sku_length + 1];
		char g_unit[max_unit_length + 1];
		char *g_name;
		int num_hand;
		int num_need;
		double g_price;
		bool taxable;


	protected:
		Error g_error;

		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Good(char type = 'N');
		Good(const char * sku, const char * name, const char * unit, int n_hand = 0, bool tax = true, double price = 0, int n_need = 0);
		Good(const Good& good);
		~Good();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		
		Good& operator=(const Good& good);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		int qtyNeeded() const;
		bool isEmpty() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);


	};
	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);
}
#endif // !_AID_GOOD_h
