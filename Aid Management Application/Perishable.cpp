#include "Perishable.h"
using namespace std;
namespace aid {
	Perishable::Perishable() : Good('P') {

		expiry_date = Date();

	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, false);
		file << ',';
		expiry_date.write(file);
		
		if (newLine)
		{
			file << endl;
		}
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		expiry_date.read(file);
		file.get();

		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Good::write(os, linear);
		if (!isEmpty() && isClear())
		{
			if (linear)
			{
				expiry_date.write(os);
			}
			else
			{
				os << endl << " Expiry date: ";
				expiry_date.write(os);

			}
		}
		return os;

	}
	std::istream& Perishable::read(std::istream& is) {
		*this = Perishable();
		Good::read(is);

		if (!is.fail())
		{
			Date t_date;
			cout << " Expiry date (YYYY/MM/DD): ";
			t_date.read(is);

			int err = t_date.errCode();
			if (err)
			{
				if (err == CIN_FAILED)
				{
					this->message("Invalid Date Entry");

				}
				else if (err == YEAR_ERROR)
				{
					this->message("Invalid Year in Date Entry");
				}
				else if (err == MON_ERROR)
				{
					this->message("Invalid Month in Date Entry");
				}
				else if (err == DAY_ERROR)
				{
					this->message("Invalid Day in Date Entry");
				}
				else if(err == 5)
				{
					this->message("Invalid Expiry in Date Entry");
				}
				is.istream::setstate(std::ios::failbit);

			}
				else
				{
					g_error.clear();
					expiry_date = t_date;
				}
		}
		return is;

	}

	const Date & aid::Perishable::expiry() const
	{
		return expiry_date;
	}
}