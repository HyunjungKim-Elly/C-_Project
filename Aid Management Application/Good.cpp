//hyunjung Kim
//148297179
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Good.h"
#include "Error.h"
#include <memory>
#include <iomanip>
#include <fstream>
using namespace std;

namespace aid {
	void Good::name(const char* t_name) {
		g_name = nullptr;
		if (t_name != nullptr)
		{
			int length = strlen(t_name);
			g_name = new char[length + 1];
			strncpy(g_name, t_name, length);
			g_name[length] = '\0';
		}
	
	}
	const char* Good::name() const {
		return g_name;
		
	}
	const char* Good::sku() const {
		return g_sku;
	}
	const char* Good::unit() const {
		return g_unit;

	}
	bool Good::taxed() const {
		return taxable;
	}
	double Good::itemPrice() const {
		return g_price;
	}
	double Good::itemCost() const {
		if (taxed())
		{
			return g_price + (g_price*tax_rate);
		}
		else
		{
			return g_price;
		}

	}
	void Good::message(const char* message) {
		this->g_error.message(message);
	}
	bool Good::isClear() const {
		return g_error.isClear();
	}



	Good::Good(const char t) {
		g_type = t;
		g_sku[0] = '\0';
		g_unit[0] = '\0';

		g_name = nullptr;
		num_hand = 0;
		num_need = 0;
		g_price = 0.0;
		taxable = true;

		g_error.clear();
	}
	Good::Good(const char* sku, const char* na, const char* unit, int hand, bool tax, double pri, int need) {
		*this = Good();
		
		name(na);
		strncpy(g_sku, sku, max_sku_length);
		g_sku[max_sku_length] = '\0';
		strncpy(g_unit, unit, max_unit_length);
		g_unit[max_unit_length] = '\0';

		num_hand = hand;
		taxable = tax;
		g_price = pri;
		num_need = need;
	}
	Good::Good(const Good& Good) {
		g_name = nullptr;
		*this = Good;
	}
	Good& Good::operator=(const Good& good) {

		if (this != &good)
		{
			g_type = good.g_type;

			strncpy(g_sku, good.g_sku, max_sku_length);
			g_sku[max_sku_length] = '\0';

			strncpy(g_unit, good.g_unit, max_unit_length);
			g_unit[max_unit_length] = '\0';


			num_hand = good.num_hand;
			num_need = good.num_need;
			g_price = good.g_price;
			taxable = good.taxable;

			name(good.g_name);
			g_error.message(good.g_error.message());

		}
		return *this;
	}
	Good::~Good() {

		delete[] g_name;
	//	g_name = nullptr;

	}

	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		
			file << this->g_type << ','
				<< this->g_sku << ','
				<< this->g_name << ','
				<< this->g_unit << ','
				<< this->taxable << ','
				<< this->g_price << ','
				<< this->num_hand << ','
				<< this->num_need;
		

		if (newLine)
		{
			file << endl;
		}
		return file;
	}
	std::fstream& Good::load(std::fstream& file) {
		char temp_name[max_name_length + 1];
		char ctempTax;

		file.get(g_sku, max_sku_length + 1, ',');
		g_sku[max_sku_length] = '\0';
		file.ignore();

		file.get(temp_name, max_name_length + 1, ',');
		temp_name[max_name_length] = '\0';
		file.ignore();

		file.get(g_unit, max_unit_length + 1, ',');
		g_unit[max_unit_length] = '\0';
		file.ignore();

		file.get(ctempTax);
		file.ignore();
		file >> g_price;
		file.ignore();
		file >> num_hand;
		file.ignore();
		file >> num_need;
		file.ignore();

		if (ctempTax == '1')
			taxable = true;
		else
			taxable = false;

		name(temp_name);

		return file;
		
	}
	std::ostream& Good::write(std::ostream& os, bool linear) const {
		if (!g_error.isClear())
		{
			os << g_error;
		}

		if (g_error.isClear())
		{
			if (linear)

			{
				//os.fill(' ');
				os.setf(ios::left);
				os.width(max_sku_length);
				os << g_sku << '|';
				
				
				os.width(20);
				os << g_name << '|';
				
				
				os.unsetf(ios::left);
				os.setf(ios::right);
				
				
				os.width(7);
				os.setf(ios::fixed);
				os.precision(2);
				if (taxable)
				{
					os << itemCost() << '|';
				}
				else
				{
					os << itemPrice() << '|';
				}

				os.width(4);
				os << num_hand << '|';

				os.unsetf(ios::right);
				os.setf(ios::left);
				os.width(10);
				os << g_unit << '|';

				os.unsetf(ios::left);
				os.setf(ios::right);
				os.width(4);
				os << num_need << '|';
				os.unsetf(ios::right);

			}
			else
			{
				os << " Sku: " << g_sku << endl;
				os << " Name (no spaces): " << g_name << endl;
				os << " Price: " << g_price << endl;
				if (taxable)
				{
					os << " Price after tax: " << itemCost() << endl;
				}
				else
				{
					os << " Price after tax:  " << "N/A" << endl;
				}
				os << " Quantity on Hand: " << num_hand << ' ' << g_unit << endl;
				os << " Quantity needed: " << num_need;
			}
			//}

		}
		return os;

	}
	std::istream& Good::read(std::istream& is) {
		
			char sku[max_sku_length + 1];
			char t_name[max_name_length + 1];
			char unit[max_unit_length + 1];
			int hand;
			int need;
			double price;
			char check;

			g_error.clear();
			
			cout << " Sku: ";
			is >> sku;
			strncpy(g_sku, sku, max_sku_length);
			g_sku[max_sku_length] = '\0';

			cout << " Name (no spaces): ";
			is >> t_name;
			this->name(t_name);

			cout << " Unit: ";
			is >> unit;
			strncpy(g_unit, unit, max_unit_length);
			g_unit[max_unit_length] = '\0';

			cout << " Taxed? (y/n): ";
			is >> check;

			if (check == 'y' || check == 'Y')
			{
				taxable = true;
			}
			else if (check == 'n' || check == 'N')
			{
				taxable = false;
			}
			else
			{
				is.istream::setstate(std::ios::failbit);
				g_error.message("Only (Y)es or (N)o are acceptable");
					return is;
			}

				cout << " Price: ";
				is >> price;
			if (is.fail())
			{
				is.istream::setstate(std::ios::failbit);
				g_error.message("Invalid Price Entry");
				return is;
			}
			else
			{
				g_price = price;

			}
			

				cout << " Quantity on hand: ";
				is >> hand;
			if (is.fail())
			{
				is.istream::setstate(std::ios::failbit);
				g_error.message("Invalid Quantity Entry");
				return is;
			}
			else
			{
				num_hand = hand;
			}

				cout << " Quantity needed: ";
				is >> need;
			if (is.fail())
			{
				is.istream::setstate(std::ios::failbit);
				g_error.message("Invalid Quantity Needed Entry");
			}
			else
			{
				num_need = need;
			}
			

			if (!is.fail())
			{
				is.clear();
				is.ignore(1000, '\n');
				//Good t_good = Good(sku, n_ad, unit, hand, taxable, price, need);
				//*this = t_good;
				
			}
	
			return is;
			
	}
	bool Good::operator==(const char* sku) const {
		return strcmp(g_sku, sku) == 0;
	}
	double Good::total_cost() const {
		return (g_price * num_hand) * (1 + tax_rate);
	}
	void Good::quantity(int q) {
		if (q > 0)
		{
			num_hand = q;
		}
	}

	bool Good::isEmpty() const {
		bool empty = false;
		if (g_sku[0] == '\0' &&
			g_name == nullptr &&
			g_unit[0] == '\0' &&
			num_hand == 0 &&
			num_need == 0 &&
			g_price == 0 &&
			taxable == true)
		{
			empty = true;
		}
		return empty;

	}
	int Good::qtyNeeded() const {
		return num_need;
	}
	int Good::quantity() const {
		return num_hand;
	}
	bool Good::operator>(const char* sku) const {
		bool bigger = false;
		if (g_sku > sku)
		{
			bigger = true;
		}
		return bigger;
	}
	bool Good::operator>(const iGood& good) const {
		bool s = false;
		if (g_name > good.name())
		{
			s = true;
		}
		return s;
	}
	int Good::operator+=(int unit) {
		if (unit > 0)
		{
			return num_hand += unit;
		}
		else
		{
			return num_hand;

		}
	}




	std::ostream& operator<<(std::ostream&os, const iGood& good) {
		return good.write(os, true);
	}
	std::istream& operator>>(std::istream&is, iGood& good) {
		good.read(is);
		return is;
	}
	double operator+=(double& total, const iGood& o_good) {
		total = total + o_good.total_cost();
		return total;
	}
}