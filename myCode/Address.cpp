/*
 * Address.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#include "Address.h"

#include <iostream>

Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo) :
		street(street), postalCode(postalCode), cityName(cityName),
		additionalInfo(additionalInfo)
{
}

const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

const std::string& Address::getCityName() const
{
	return cityName;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

const std::string& Address::getStreet() const
{
	return street;
}

Address::~Address()
{
}

Address::Address()
{
	street = "";
	postalCode = 0;
	cityName = "";
	additionalInfo = "";
}

void Address::write(std::ostream &out) const
{
	out << street << ";";
	out << postalCode << ";";
	out << cityName << ";";
	out << additionalInfo << "\n";
}

Address Address::read(std::istream &in)
{
	std::string inputLine;

	std::getline(in, inputLine, ';');
	std::string streetName = inputLine;

	std::getline(in, inputLine, ';');
	unsigned short postalCode =
			static_cast<unsigned short>(std::stoi(inputLine));

	std::getline(in, inputLine, ';');
	std::string cityName = inputLine;

	std::getline(in, inputLine);
	std::string additionalInfo = inputLine;
	return Address(streetName, postalCode, cityName, additionalInfo);
}
