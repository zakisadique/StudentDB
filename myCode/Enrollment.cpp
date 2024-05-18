/*
 * Enrollment.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#include "Enrollment.h"
#include <iostream>

Enrollment::Enrollment(std::string semester, const Course *course) :
		semester(semester), course(std::move(course)) {
	this->grade = 0.0;
}

Enrollment::Enrollment(float grade, std::string semester, const Course *course):
		grade(grade), semester(semester), course(std::move(course)) {
}

Enrollment::Enrollment(const Enrollment &other) :
		grade(other.grade), semester(other.semester), course(other.course) {
}

float Enrollment::getGrade() const {
	return grade;
}

void Enrollment::setGrade(float grade) {
	this->grade = grade;
}

const Course* Enrollment::getCourse() const {
	return course;
}

const std::string& Enrollment::getSemester() const {
	return semester;
}

Enrollment::~Enrollment() {
}

void Enrollment::write(std::ostream &out) const {

	out << course->getCourseKey() << ";" << semester << ";" << grade << "\n";
}

void Enrollment::setCourse(const Course *course) {
	this->course = course;
}

Enrollment Enrollment::read(std::istream &in) {
	std::string inputLine;

	std::getline(in, inputLine, ';');
	std::string semester = inputLine;

	std::getline(in, inputLine);
	float grade = std::stof(inputLine);



	 return Enrollment(grade, semester,
			nullptr);
}
