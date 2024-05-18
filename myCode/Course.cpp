/*
 * Course.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#include "Course.h"
#include <iostream>

Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints) :
		courseKey(courseKey), title(title), creditPoints(creditPoints)
{
	for (const auto &majorIter : majorById)
	{
		if (majorIter.second == major)
		{
			this->major = majorIter.first;
		}
	}
}

Course::~Course()
{
}

unsigned int Course::getCourseKey() const
{
	return courseKey;
}

float Course::getCreditPoints() const
{
	return creditPoints;
}

const std::string& Course::getTitle() const
{
	return title;
}

std::map<unsigned char, std::string> Course::majorById =
{
{ 'E', "Embedded" },
{ 'A', "Automation" },
{ 'C', "Communication" },
{ 'P', "Power" }, };

std::string Course::getMajor() const
{
	return majorById[major];
}

void Course::write(std::ostream &out) const
{
	out << courseKey << ";";
	out << title << ";";
	out << getMajor() << ";";
	out << creditPoints << ";";
}

std::string Course::getString(int value) const{
    std::string integerString = std::to_string(value);
    if (integerString.size() == 1) {
    	integerString =  "0" + integerString;
    }
	return integerString;

}
