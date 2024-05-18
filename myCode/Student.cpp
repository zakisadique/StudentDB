/*
 * Student.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#include "Student.h"
#include <iostream> // remove
#include <sstream>

Student::Student(std::string firstNanme, std::string lastName,
		Poco::Data::Date dateOfBirth, const Address &address) :
		matrikelNumber(NextMatrikelNummer), firstName(firstNanme), lastName(
				lastName), dateOfBirth(dateOfBirth), address(address)

{
	++NextMatrikelNummer;
}

Student::Student(unsigned int matrikelNumber, std::string firstNanme,
		std::string lastName, Poco::Data::Date dateOfBirth,
		const Address &address) :
		matrikelNumber(matrikelNumber), firstName(firstNanme), lastName(
				lastName), dateOfBirth(dateOfBirth), address(address) {
}

const Poco::Data::Date& Student::getDateOfBirth() const {
	return dateOfBirth;
}

const std::vector<Enrollment>& Student::getEnrollments() const {

	return enrollments;
}

const std::string& Student::getFirstName() const {
	return firstName;
}

const std::string& Student::getLastName() const {
	return lastName;
}

unsigned int Student::getMatrikelNumber() const {
	return matrikelNumber;
}



Student::Student() {
	matrikelNumber = 0;
	firstName = "";
	lastName = "";
}

unsigned int Student::getNextMatrikelNummer() {
	return NextMatrikelNummer;
}

Student::~Student() {
}

unsigned int Student::NextMatrikelNummer = 100000;

void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth) {
	this->dateOfBirth = dateOfBirth;
}

void Student::setFirstName(const std::string &firstName) {
	this->firstName = firstName;
}

void Student::setLastName(const std::string &lastName) {
	this->lastName = lastName;
}

void Student::addEnrollments(const Enrollment &enrollment) {
	this->enrollments.push_back(enrollment);

}

void Student::changeGrade(const Enrollment& enrollment, float grade) {
	for (auto &enrollmentIter : enrollments) {
		if (enrollmentIter.getCourse() == enrollment.getCourse()
				&& enrollmentIter.getSemester() == enrollment.getSemester()) {
			enrollmentIter.setGrade(grade);

		}
	}
}

const Address& Student::getAddress() const {
	return address;
}

void Student::setAddress(const Address &address) {
	this->address = address;
}

void Student::deleteEnrollment(const Enrollment &enrollment) {
	for (auto enrollmentIter = enrollments.begin();
			enrollmentIter != enrollments.end(); ++enrollmentIter) {
		if (enrollmentIter->getCourse() == enrollment.getCourse()
				&& enrollmentIter->getSemester() == enrollment.getSemester()) {

			enrollments.erase(enrollmentIter);
			return;
		}
	}
}

void Student::setNextMatrikelNummer(unsigned int nextMatrikelNummer) {
	NextMatrikelNummer = nextMatrikelNummer;
}

void Student::write(std::ostream &out) const {
	out << matrikelNumber << ";";
	out << lastName << ";";
	out << firstName << ";";
	out << dateOfBirth.day() << "." << dateOfBirth.month() << "."
			<< dateOfBirth.year() << ";";
	address.write(out);

}

Student Student::read(std::istream &in) {
	std::string inputLine;

	std::getline(in, inputLine, ';');
	unsigned int matrikelNumber = static_cast<unsigned int>(std::stoi(
				inputLine));


	std::getline(in, inputLine, ';');
	std::string firstName = inputLine;

	std::getline(in, inputLine, ';');
	std::string lastName = inputLine;

	std::getline(in, inputLine, ';');
	Poco::Data::Date dateOfBirth = Student::getDate(inputLine);

	Address address = Address::read(in);

	NextMatrikelNummer =
			matrikelNumber > NextMatrikelNummer ?
					matrikelNumber : NextMatrikelNummer;

	return Student(matrikelNumber, firstName, lastName, dateOfBirth,
					address);



}


const Poco::Data::Date Student::getDate(std::string &date) {

	std::istringstream dateStream(date);
	int day, month, year;
	char separator;
	dateStream >> day >> separator >> month >> separator >> year;
	return Poco::Data::Date (year, month, day);
}
