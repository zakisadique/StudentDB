/*
 * Address.h
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

/**
 * @brief The Address class represents a physical address.
 */
class Address
{
private:
	std::string street; /**< Street of the address. */
	unsigned short postalCode; /**< Postal code of the address. */
	std::string cityName; /**< City name of the address. */
	std::string additionalInfo; /**< Additional information about the address.*/

public:
	/**
	 * @brief Default constructor for the Address class.
	 */
	Address();

	/**
	 * @brief Constructs a new Address object with specified parameters.
	 * @param street Street of the address.
	 * @param postalCode Postal code of the address.
	 * @param cityName City name of the address.
	 * @param additionalInfo Additional information about the address.
	 */
	Address(std::string street, unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	/**
	 * @brief Destructor for the Address class.
	 */
	~Address();

	/**
	 * @brief Retrieves the street of the address.
	 * @return The street of the address.
	 */
	const std::string& getStreet() const;

	/**
	 * @brief Retrieves the postal code of the address.
	 * @return The postal code of the address.
	 */
	unsigned short getPostalCode() const;

	/**
	 * @brief Retrieves the city name of the address.
	 * @return The city name of the address.
	 */
	const std::string& getCityName() const;

	/**
	 * @brief Retrieves additional information about the address.
	 * @return Additional information about the address.
	 */
	const std::string& getAdditionalInfo() const;

	/**
	 * @brief Writes address information to the output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream &out) const;

	/**
	 * @brief Reads an Address object from the input stream.
	 * @param in The input stream to read from.
	 * @return The read Address object.
	 */
	static Address read(std::istream &in);
};

#endif /* ADDRESS_H_ */
