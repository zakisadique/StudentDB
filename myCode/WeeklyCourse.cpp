/*
 * WeeklyCourse.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#include "WeeklyCourse.h"
#include <iostream>
#include <sstream>

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course(courseKey, title, major, creditPoints) {

	this->dayOfWeek = dayOfWeek;
	this->startTime = startTime;
	this->endTime = endTime;
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDayOfWeek() const {
	return dayOfWeek;
}

const Poco::Data::Time& WeeklyCourse::getEndTime() const {
	return endTime;
}

const Poco::Data::Time& WeeklyCourse::getStartTime() const {
	return startTime;
}

WeeklyCourse::~WeeklyCourse() {

}


void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	out << dayOfWeek << ";";
	out << getString(startTime.hour()) << ":"
			<< getString(startTime.minute()) << ";";
	out << getString(endTime.hour()) << ":"
			<< getString(endTime.minute()) << "\n";
}

const Course* WeeklyCourse::read(std::istream &in) {

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
	Poco::DateTime::DaysOfWeek Courseday =
			(static_cast<Poco::DateTime::DaysOfWeek>(std::stoi(inputLine)));

	std::getline(in, inputLine, ';');
	Poco::Data::Time startTime = WeeklyCourse::getTime(inputLine);

		std::getline(in, inputLine);
		Poco::Data::Time endTime = WeeklyCourse::getTime(inputLine);

	return new WeeklyCourse(courseKey, courseTitle, courseMajor, courseCredits,
			Courseday, startTime, endTime);
}


const std::vector<std::string> WeeklyCourse::getAdditionalInfo() const {
	std::vector<std::string> additionalInfoVector;

	additionalInfoVector.push_back("Day: " + std::to_string(dayOfWeek));
	additionalInfoVector.push_back(
			"Start Time: " + getString(startTime.hour()) + ":"
					+ getString(startTime.minute()));
	additionalInfoVector.push_back(
			"End Time: " + getString(endTime.hour()) + ":"
					+ getString(endTime.minute()));

	return additionalInfoVector;
}

const Poco::Data::Date WeeklyCourse::getDate(std::string &date) {

	std::istringstream dateStream(date);
	int day, month, year;
	char separator;
	dateStream >> day >> separator >> month >> separator >> year;
	return Poco::Data::Date (year, month, day);
}

const Poco::Data::Time WeeklyCourse::getTime(std::string &time) {
	std::istringstream timeStream (time);
	int hour, min;
	char separator;
	timeStream >> hour >> separator >> min;
	return Poco::Data::Time (hour, min, 00);
}

