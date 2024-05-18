/*
 * Student.h
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <Poco/Data/Date.h>

#include "Address.h"
#include "Enrollment.h"

/**
 * @brief The Student class represents a student entity.
 */
class Student {
private:
	static unsigned int NextMatrikelNummer; /**< Static member to hold the next
									available student matriculation number. */
	unsigned int matrikelNumber; /**< Unique matriculation number of the
										student. */
	std::string firstName; /**< First name of the student. */
	std::string lastName; /**< Last name of the student. */
	Poco::Data::Date dateOfBirth; /**< Date of birth of the student. */
	std::vector<Enrollment> enrollments; /**< List of enrollments associated
												with the student. */
	Address address; /**< Address of the student. */

public:
	/**
	 * @brief Default constructor for the Student class.
	 */
	Student();

	/**
	 * @brief Constructs a new Student object with specified parameters.
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param dateOfBirth Date of birth of the student.
	 * @param address Address of the student.
	 */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, const Address &address);

	/**
	 * @brief Constructs a new Student object with specified parameters.
	 * @param matrikelNumber Matriculation number of the student.
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param dateOfBirth Date of birth of the student.
	 * @param address Address of the student.
	 */
	Student(unsigned int matrikelNumber, std::string firstName,
			std::string lastName, Poco::Data::Date dateOfBirth,
			const Address &address);

	/**
	 * @brief Destructor for the Student class.
	 */
	~Student();

	/**
	 * @brief Retrieves the next available matriculation number.
	 * @return The next available matriculation number.
	 */
	static unsigned int getNextMatrikelNummer();

	/**
	 * @brief Retrieves the matriculation number of the student.
	 * @return The matriculation number.
	 */
	unsigned int getMatrikelNumber() const;

	/**
	 * @brief Retrieves the first name of the student.
	 * @return The first name.
	 */
	const std::string& getFirstName() const;

	/**
	 * @brief Retrieves the last name of the student.
	 * @return The last name.
	 */
	const std::string& getLastName() const;

	/**
	 * @brief Retrieves the date of birth of the student.
	 * @return The date of birth.
	 */
	const Poco::Data::Date& getDateOfBirth() const;

	/**
	 * @brief Retrieves the enrollments associated with the student.
	 * @return The enrollments.
	 */
	const std::vector<Enrollment>& getEnrollments() const;

	/**
	 * @brief Retrieves the address of the student.
	 * @return The address.
	 */
	const Address& getAddress() const;

	/**
	 * @brief Sets the next available matriculation number.
	 * @param nextMatrikelNummer The next available matriculation number.
	 */
	static void setNextMatrikelNummer(unsigned int nextMatrikelNummer);

	/**
	 * @brief Sets the first name of the student.
	 * @param firstName The first name to set.
	 */
	void setFirstName(const std::string &firstName);

	/**
	 * @brief Sets the last name of the student.
	 * @param lastName The last name to set.
	 */
	void setLastName(const std::string &lastName);

	/**
	 * @brief Sets the date of birth of the student.
	 * @param dateOfBirth The date of birth to set.
	 */
	void setDateOfBirth(const Poco::Data::Date &dateOfBirth);

	/**
	 * @brief Sets the address of the student.
	 * @param address The address to set.
	 */
	void setAddress(const Address &address);

	/**
	 * @brief Adds an enrollment to the student's record.
	 * @param enrollment The enrollment to add.
	 */
	void addEnrollments(const Enrollment &enrollment);

	/**
	 * @brief Deletes an enrollment from the student's record.
	 * @param enrollment The enrollment to delete.
	 */
	void deleteEnrollment(const Enrollment &enrollment);

	/**
	 * @brief Changes the grade of an enrollment.
	 * @param enrollment The enrollment for which to change the grade.
	 * @param grade The new grade to assign.
	 */
	void changeGrade(const Enrollment &enrollment, float grade);

	/**
	 * @brief Writes student information to the output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream &out) const;

	/**
	 * @brief Reads a Student object from the input stream.
	 * @param in The input stream to read from.
	 * @return The read Student object.
	 */
	static Student read(std::istream &in);

	/**
	 * @brief Parses a date string and returns a Date object.
	 * @param date The date string to parse.
	 * @return The parsed Date object.
	 */
	static const Poco::Data::Date getDate(std::string &date);
};

#endif /* STUDENT_H_ */
