/*
 * StudentDb.cpp
 *
 *  Created on: 05-Jan-2024
 *      Author: zakisadique
 */

#include "StudentDb.h"
#include <iostream>
#include <sstream>
#include "BlockCourse.h"
#include "WeeklyCourse.h"

StudentDb::~StudentDb() {
}

StudentDb::StudentDb() {

}

void StudentDb::addCourse(Course *course) {

	std::unique_ptr<const Course> newCourse(course);
	courses[course->getCourseKey()] = std::move(newCourse);
}

void StudentDb::addStudent(unsigned int matrikelNumber, Student &student) {

	students[matrikelNumber] = student;
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses()
		const {
	return courses;
}

const std::map<unsigned int, Student>& StudentDb::getStudents() const {
	return students;
}

void StudentDb::addEnrollment(unsigned int matrikelNumber,
		const Enrollment &enrollment) {
	students.find(matrikelNumber)->second.addEnrollments(enrollment);
}

void StudentDb::editStudentFirstName(unsigned int matrikelNumber,
		std::string firstName) {
	students.find(matrikelNumber)->second.setFirstName(firstName);
}

void StudentDb::editStudentLastName(unsigned int matrikelNumber,
		std::string lastName) {
	students.find(matrikelNumber)->second.setLastName(lastName);
}

void StudentDb::editStudentDateOfBirth(unsigned int matrikelNumber,
		Poco::Data::Date dateOfBirth) {
	students.find(matrikelNumber)->second.setDateOfBirth(dateOfBirth);
}

void StudentDb::changeGrade(unsigned int matrikelNumber,
		const Enrollment &enrollment, float grade) {
	students.find(matrikelNumber)->second.changeGrade(enrollment, grade);
}

void StudentDb::deleteEnrollment(unsigned int matrikelNumber,
		const Enrollment &enrollment) {
	students.find(matrikelNumber)->second.deleteEnrollment(enrollment);
}

void StudentDb::changeAddress(unsigned int matrikelNumber,
		const Address &address) {
	students.find(matrikelNumber)->second.setAddress(address);
}

void StudentDb::write(std::ostream &out) const {

	out << courses.size() << "\n";
	for (const auto &course : courses) {
		course.second->write(out);
	}

	int numOfEnrollments = 0;
	out << students.size() << "\n";
	for (const auto &student : students) {
		student.second.write(out);
		numOfEnrollments += student.second.getEnrollments().size();
	}

	out << numOfEnrollments << "\n";
	for (const auto &student : students) {
		for (const auto &enrollment : student.second.getEnrollments()) {
			out << student.second.getMatrikelNumber() << ";";
			enrollment.write(out);
		}
	}
}

void StudentDb::read(std::istream &in) {

	// read courses

	std::string inputLine;
	std::getline(in, inputLine);
	int numOfCourses = std::stoi(inputLine);

	courses.clear();
	for (int i = 1; i <= numOfCourses; ++i) {

		std::getline(in, inputLine, ';');
		unsigned char courseType = inputLine[0];

		if (courseType == 'B') {

			std::unique_ptr<const Course> courseRead(
					BlockCourse::read(in));
			courses [courseRead->getCourseKey()] = std::move(courseRead);


		} else if (courseType == 'W') {
			std::unique_ptr<const Course> courseRead(
					WeeklyCourse::read(in));
			courses [courseRead->getCourseKey()] = std::move(courseRead);
		}

	}


	////// student
	students.clear();
	std::getline(in, inputLine);
	int numOfStudents = std::stoi(inputLine);

	for (int i = 1; i <= numOfStudents; ++i) {

		Student newStudent(Student::read(in));

		students[newStudent.getMatrikelNumber()] = newStudent;
	}

	///enrollments
	std::getline(in, inputLine);
	int numOfEnrollments = std::stoi(inputLine);

	for (int i = 1; i <= numOfEnrollments; ++i) {
		std::getline(in, inputLine, ';');
		unsigned int matrikelNumber = static_cast<unsigned int>(std::stoi(
						inputLine));


		std::getline(in, inputLine, ';');
		int courseKey = std::stoi(inputLine);

		Enrollment newEnrollment = Enrollment::read(in);

		newEnrollment.setCourse(courses.find(courseKey)->second.get());

		addEnrollment(matrikelNumber, newEnrollment);


	}
}

