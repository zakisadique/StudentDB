/*
 * BlockCourse.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#include "BlockCourse.h"
#include <iostream>
#include <sstream>
#include <vector>

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course(courseKey, title, major, creditPoints) {

	this->startDate = startDate;
	this->endDate = endDate;

	this->startTime = startTime;
	this->endTime = endTime;

}

BlockCourse::~BlockCourse() {

}

const Poco::Data::Date& BlockCourse::getEndDate() const {
	return endDate;
}

const Poco::Data::Time& BlockCourse::getEndTime() const {
	return endTime;
}

const Poco::Data::Date& BlockCourse::getStartDate() const {
	return startDate;
}

const Poco::Data::Time& BlockCourse::getStartTime() const {
	return startTime;
}



void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write(out);
	out << getString(startDate.day()) << "."
			<< getString(startDate.month()) << "."
			<< getString(startDate.year()) << ";";
	out << getString(endDate.day()) << "."
			<< getString(endDate.month()) << "."
			<< getString(endDate.year()) << ";";
	out << getString(startTime.hour()) << ":"
			<< getString(startTime.minute()) << ";"
			<< getString(endTime.hour()) << ":"
			<< getString(endTime.minute()) << "\n";
}

const Course* BlockCourse::read(std::istream &in) {
	std::string inputLine;


	std::getline(in, inputLine, ';');
	unsigned int courseKey = std::stoi(inputLine);

	std::getline(in, inputLine, ';');
	std::string courseTitle = inputLine;

	std::getline(in, inputLine, ';');
	std::string courseMajor = inputLine;

	std::getline(in, inputLine, ';');
	float courseCredits = std::stof(inputLine);

	std::getline(in, inputLine, ';');
	Poco::Data::Date startDate = BlockCourse::getDate(inputLine);

	std::getline(in, inputLine, ';');
	Poco::Data::Date endDate = BlockCourse::getDate(inputLine);

	std::getline(in, inputLine, ';');
	Poco::Data::Time startTime = BlockCourse::getTime(inputLine);

	std::getline(in, inputLine);
	Poco::Data::Time endTime = BlockCourse::getTime(inputLine);


	return new BlockCourse(courseKey, courseTitle, courseMajor, courseCredits,
			startDate, endDate, startTime, endTime);

}

const std::vector<std::string> BlockCourse::getAdditionalInfo() const {
	std::vector<std::string> additionalInfoVector;

	additionalInfoVector.push_back(
			"Start Date: " + getString(startDate.day()) + "."
					+ getString(startDate.month()) + "."
					+ getString(startDate.year()));

	additionalInfoVector.push_back(
			"End Date: " + getString(startDate.day()) + "."
					+ getString(startDate.month()) + "."
					+ getString(startDate.year()));

	additionalInfoVector.push_back(
			"Start Time: " + getString(startTime.hour()) + ":"
					+ getString(startTime.minute()));

	additionalInfoVector.push_back(
			"End Time: " + getString(endTime.hour()) + ":"
					+ getString(endTime.minute()));

	return additionalInfoVector;
}

const Poco::Data::Date BlockCourse::getDate(std::string &date) {

	std::istringstream dateStream(date);
	int day, month, year;
	char separator;
	dateStream >> day >> separator >> month >> separator >> year;
	return Poco::Data::Date (year, month, day);
}

const Poco::Data::Time BlockCourse::getTime(std::string &time) {
	std::istringstream timeStream (time);
	int hour, min;
	char separator;
	timeStream >> hour >> separator >> min;
	return Poco::Data::Time (hour, min, 00);
}
