#ifndef MYRECORDDEF_HPP_
#define MYRECORDDEF_HPP_

#include <string>

struct MyRecord {
	long custid;
	std::string FirstName;
	std::string LastName;
	std::string Street;
	int HouseID;
	std::string City;
	std::string postcode;
	float amount;
};

#endif /* MYRECORDDEF_HPP_ */
