/*
 * SimlpeUI.cpp
 *
 *  Created on: 07-Jan-2024
 *      Author: zakisadique
 */

#include "SimpleUI.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/json/src.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "BlockCourse.h"
#include "WeeklyCourse.h"


SimpleUI::SimpleUI(StudentDb &studentDB) :
		studentDB(studentDB) {

}



void SimpleUI::run() const{

	printSolidLine();
	std::cout << "- - - - Welcome to Student Database - - - - " << std::endl;
	while (true) {
		printSolidLine();
		std::cout << "1: Add new course" << std::endl;
		std::cout << "2: List courses" << std::endl;
		std::cout << "3: Add new student" << std::endl;
		std::cout << "4: Add enrollment" << std::endl;
		std::cout << "5: Print Student" << std::endl;
		std::cout << "6: Search student" << std::endl;
		std::cout << "7: Update student" << std::endl;
		std::cout << "8: Write to file" << std::endl;
		std::cout << "9: Read from file" << std::endl;
		std::cout << "10: Get test data" << std::endl;
		std::cout << "0: Exit" << std::endl;
		printSolidLine();
		std::cout << "Please select an option to continue: ";

		int option = getInput<int>(0, 10);

		printSolidLine();
		switch (option) {
		case (1):
			addNewCourse();
			break;
		case (2):
			listAllCourses();
			break;
		case (3):
			addNewStudent();
			break;
		case (4):
			addEnrollment();
			break;
		case (5):
			printStudent();
			break;
		case (6):
			searchStudent();
			break;
		case (7):
			updateStudent();
			break;
		case (8):
			writeToFile();
			break;
		case (9):
			readFromFile();
			break;
		case (10):
			getDataFromServer();
			break;
		case (0):
			std::cout << "Bye Bye" << std::endl;
			printSolidLine();
			return;
		}
	}
}

void SimpleUI::addNewCourse() const{

	std::cout << "1. Block" << std::endl;
	std::cout << "2. Weekly" << std::endl;
	printDashLine();
	std::cout << "Please enter the type of the course: ";
	int courseType = getInput<int>(1, 2);


	printDashLine();

	std::cout << "Please enter the course key: ";
	unsigned int courseKey = getInput<unsigned int>(1, 99999);
	printDashLine();

	std::cout << "Please enter the course title: ";
	std::string courseTitle = getInput<std::string>();
	printDashLine();

	std::vector<std::string> majors = {
			"Embedded", "Power", "Automation", "Communication"
	};
	for (std::vector<std::string>::size_type i = 1; i <= majors.size(); ++i){
		std::cout << i << ". " << majors[i-1] << std::endl;
	}
	printDashLine();
	std::cout << "Please select major for the course: ";
	int majorSelection = getInput<int>(1, 4);
	std::string courseMajor;
	courseMajor = majors[majorSelection - 1];
	printDashLine();

	std::cout << "Please enter the course credit points: ";
	float courseCredits = getInput<float>(1.0, 5.0);
	printDashLine();

	std::cout << "Please enter the course start time (HH:MM): ";
	Poco::Data::Time startTime = getInput<Poco::Data::Time>();
	printDashLine();

	std::cout << "Please enter the course end time (HH:MM): ";
	Poco::Data::Time endTime = getInput<Poco::Data::Time>();
	printDashLine();

	if (courseType == 1) {
		std::cout << "Please enter the course start date (DD.MM.YYYY): ";
		Poco::Data::Date startDate = getInput<Poco::Data::Date>();
		printDashLine();

		std::cout << "Please enter the course end date (DD.MM.YYYY): ";
		Poco::Data::Date endDate = getInput<Poco::Data::Date>();

		if (studentDB.getCourses().find(courseKey)
				!= studentDB.getCourses().end()) {

			printDashLine();
			std::cout << "Error: Course already exists" << std::endl;

		} else {
			Course *newCourse = new BlockCourse(courseKey, courseTitle,
					courseMajor, courseCredits, startDate, endDate, startTime,
					endTime);

			studentDB.addCourse(newCourse);

			printDashLine();
			std::cout << "Course added successfully" << std::endl;
		}

	} else if (courseType == 2) {

		std::vector<std::string> daysOfWeek { "Sunday", "Monday", "Tuesday",
				"Wednesday", "Thursday", "Friday", "Saturday" };


		for (std::vector<std::string>::size_type i = 0; i < daysOfWeek.size(); ++i){
			std::cout << i << ". " << daysOfWeek[i] << std::endl;
		}
		printDashLine();
		std::cout << "Please enter the course day: ";
		int courseDay = getInput<int>(0, 6);

		Poco::DateTime::DaysOfWeek Courseday(
				static_cast<Poco::DateTime::DaysOfWeek>(courseDay));

		if (studentDB.getCourses().find(courseKey)
				!= studentDB.getCourses().end()) {
			printDashLine();
			std::cout << "Error: Course already exists" << std::endl;
			return;
		} else {
			Course *newCourse = new WeeklyCourse(courseKey, courseTitle,
					courseMajor, courseCredits, Courseday, startTime, endTime);

			studentDB.addCourse(newCourse);
			printDashLine();
			std::cout << "Course added successfully" << std::endl;
		}

	}
}

void SimpleUI::listAllCourses() const{

	if (studentDB.getCourses().empty()) {
		std::cout << "No courses available" << std::endl;
	} else {
		printDashLine();
		for (const auto &course : studentDB.getCourses()) {

			std::cout << "Course Key: " << course.second->getCourseKey()
					<< std::endl;
			std::cout << "Title: " << course.second->getTitle() << std::endl;
			std::cout << "Major: " << course.second->getMajor() << std::endl;
			std::cout << "Credit Points: " << course.second->getCreditPoints()
					<< std::endl;
			std::vector<std::string> additionalInfo =
					course.second->getAdditionalInfo();
			for (const auto &info : additionalInfo) {

				std::cout << info;

				std::cout << std::endl;
			}
			printDashLine();
		}

	}

}

void SimpleUI::addNewStudent() const{

	std::cout << "Please enter the first name: ";
	std::string firstName = getInput<std::string>();
	printDashLine();

	std::cout << "Please enter the last name: ";
	std::string lastName = getInput<std::string>();
	printDashLine();

	std::cout << "Please enter the date of birth (DD.MM.YYYY): ";
	Poco::Data::Date dateBirth = getInput<Poco::Data::Date>();
	printDashLine();

	std::cout << "Please enter street: ";
	std::string street = getInput<std::string>();
	printDashLine();

	std::cout << "Please enter Postal Code: ";
	unsigned short postalCode = getInput<unsigned short>(0, 65535);
	printDashLine();


	std::cout << "Please enter city name: ";
	std::string cityName = getInput<std::string>();
	printDashLine();

	std::cout << "Do you want to enter additional information?" << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;
	printDashLine();

	int addInfo = getInput<int>(1, 2);
	printDashLine();

	std::string additionalInfo;
	if (addInfo == 1) {
		std::cout << "Please enter additional info: ";
		additionalInfo = getInput<std::string>();
		printDashLine();

	} else if (addInfo == 2) {

		additionalInfo = "";
	}
	Address address = Address(street, postalCode, cityName, additionalInfo);
	Student newStudent(firstName, lastName, dateBirth, address);

	studentDB.addStudent(newStudent.getMatrikelNumber(), newStudent);


	std::cout << "Student added successfully" << ": "
								<< newStudent.getMatrikelNumber()
								<< " - " << newStudent.getFirstName() << " "
								<< newStudent.getLastName() << std::endl;

}

void SimpleUI::addEnrollment() const{

	std::cout << "Please enter the matrikel number: ";
	unsigned int matrikelNumber = getInput<unsigned int>(1, 999999);
	printDashLine();

	std::cout << "Please enter the course Key: ";
	unsigned int courseKey = getInput<unsigned int>(1, 999999);
	printDashLine();

	std::cout << "Please enter the semester: ";
	std::string semester = getInput<std::string>();
	printDashLine();

	if (studentDB.getStudents().find(matrikelNumber)
			== studentDB.getStudents().end()) {
		printDashLine();
		std::cout << "Error: Student not found" << std::endl;
		printDashLine();
	}

	if (studentDB.getCourses().find(courseKey)
			== studentDB.getCourses().end()) {
		printDashLine();
		std::cout << "Error: Course not found" << std::endl;
		printDashLine();
		return;
	}

	Enrollment newEnrollment(semester,
			studentDB.getCourses().find(courseKey)->second.get());
	studentDB.addEnrollment(matrikelNumber, newEnrollment);

	printDashLine();
	std::cout << "Enrollment added successfully" << std::endl;
}

void SimpleUI::printStudent() const{

	std::cout << "Please enter the matrikel number: ";
	unsigned int matrikelNumber = getInput<unsigned int>(1, 999999);

	const auto &student = studentDB.getStudents().find(matrikelNumber);

	if (student == studentDB.getStudents().end()) {
		printDashLine();
		std::cout << "Student not found" << std::endl;
		printDashLine();
	} else {
		printSolidLine();
		std::cout << "Matrikel Number: " << student->second.getMatrikelNumber()
				<< std::endl;
		std::cout << "First Name: " << student->second.getFirstName()
				<< std::endl;
		std::cout << "Last Name: " << student->second.getLastName()
				<< std::endl;
		std::cout << "Date of birth: " << student->second.getDateOfBirth().day()
				<< "." << student->second.getDateOfBirth().month() << "."
				<< student->second.getDateOfBirth().year() << std::endl;



		std::cout << "Address: " << student->second.getAddress().getStreet()
				<< ", " << student->second.getAddress().getCityName() << ", "
				<< student->second.getAddress().getPostalCode();
		if (student->second.getAddress().getAdditionalInfo().size() != 0) {
			std::cout << ", "
					<< student->second.getAddress().getAdditionalInfo();

		}
		std::cout << std::endl;

		printSolidLine();
		std::cout << "Enrollment details " << std::endl;
		printSolidLine();
		printDashLine();
		const auto &allEnrollments = student->second.getEnrollments();
		if (allEnrollments.empty()) {

			std::cout << "No Enrollments found" << std::endl;
			printDashLine();
		} else {
			for (const auto &enrollment : allEnrollments) {
				std::cout << "Course Key: "
						<< enrollment.getCourse()->getCourseKey() << std::endl;
				std::cout << "Course Name: "
						<< enrollment.getCourse()->getTitle() << std::endl;
				std::cout << "Course Credits: "
						<< enrollment.getCourse()->getCreditPoints()
						<< std::endl;
				std::cout << "Semester: " << enrollment.getSemester()
						<< std::endl;
				std::cout << "Grade: " << std::fixed << std::setprecision(1)
						<< enrollment.getGrade() << std::endl;
				printDashLine();
			}
		}

	}
}

void SimpleUI::searchStudent() const{

	std::cout << "Please enter student's name: ";
	std::string name = getInput<std::string>();
	name = toLowercase(name);
	bool studentFound = false;


	printSolidLine();

	for (const auto &student : studentDB.getStudents()) {
		std::string studentName = student.second.getFirstName()
				+ student.second.getLastName();
		studentName = toLowercase(studentName);

		if (studentName.find(name) != std::string::npos) {
			printDashLine();
			std::cout << "Matrikel Number: "
					<< student.second.getMatrikelNumber() << std::endl;
			std::cout << "First Name: " << student.second.getFirstName()
					<< std::endl;
			std::cout << "Last Name: " << student.second.getLastName()
					<< std::endl;

			studentFound = true;
		}
	}
	if (!studentFound) {
		printDashLine();
		std::cout << "Error: No student found" << std::endl;

	}

	printDashLine();
}

void SimpleUI::updateStudent() const{

	std::cout << "Please enter the matrikel number: ";
	unsigned int matrikelNumber = getInput<unsigned int>(1, 999999);

	if (studentDB.getStudents().find(matrikelNumber)
			== studentDB.getStudents().end()) {
		printDashLine();
		std::cout << "Error: Student not found" << std::endl;
		return;
	}
	printSolidLine();

	int option = -1;
	while (option != 0) {
		std::cout << "1: First Name" << std::endl;
		std::cout << "2: Last Name" << std::endl;
		std::cout << "3: Date of birth" << std::endl;
		std::cout << "4: Address" << std::endl;
		std::cout << "5: Enrollments" << std::endl;
		std::cout << "0: Cancel update" << std::endl;
		printSolidLine();
		std::cout << "Please select the property to update: ";
		int option = getInput<int>(0, 5);
		switch (option) {
		case (0):
			return;
			break;

		case (1): {

			std::cout << "Please enter new first name: ";
			std::string firstName = getInput<std::string>();
			studentDB.editStudentFirstName(matrikelNumber, firstName);
			printSolidLine();
			std::cout << "First name updated successfully" << std::endl;
			printSolidLine();
		}
			break;

		case (2): {

			std::cout << "Please enter new last name: ";
			std::string lastName = getInput<std::string>();
			studentDB.editStudentLastName(matrikelNumber, lastName);

			printSolidLine();
			std::cout << "Last name updated successfully" << std::endl;
			printSolidLine();
		}

			break;

		case (3): {

			std::cout << "Please enter the date of birth (DD.MM.YYYY): ";
			Poco::Data::Date dateBirth = getInput<Poco::Data::Date>();
			studentDB.editStudentDateOfBirth(matrikelNumber, dateBirth);
			printSolidLine();
			std::cout << "Date of birth updated successfully" << std::endl;
			printSolidLine();
		}
			break;

		case (4): {
			std::cout << "Please enter new street: ";
			std::string street = getInput<std::string>();

			std::cout << "Please enter new Postal Code: ";
			unsigned short postalCode = getInput<unsigned short>(0, 65535);

			std::cout << "Please enter new city name: ";
			std::string cityName = getInput<std::string>();

			std::cout << "Do you want to enter additional information?"
					<< std::endl;
			std::cout << "1. Yes" << std::endl;
			std::cout << "2. No" << std::endl;

			int addInfo = getInput<int>(1, 2);

			std::string additionalInfo;
			if (addInfo == 1) {
				std::cout << "Please enter additional info: ";
				additionalInfo = getInput<std::string>();

			} else if (addInfo == 2) {

				additionalInfo = "";
			}

			Address newAddress(street, postalCode, cityName, additionalInfo);

			studentDB.changeAddress(matrikelNumber, newAddress);

			printSolidLine();
			std::cout << "Address updated successfully" << std::endl;
			printSolidLine();
		}
			break;

		case (5): {

			std::vector<Enrollment> allEnrollments =
					studentDB.getStudents().find(matrikelNumber)
					->second.getEnrollments();

			if (allEnrollments.empty()) {
				printSolidLine();
				std::cout << "No enrollment found" << std::endl;
				printSolidLine();
				break;
			}
			int enrollmentNumber = 1;
			printSolidLine();
			std::cout << "List of enrollments" << std::endl;
			printDashLine();
			for (const auto &enrollment : allEnrollments) {
				std::cout << "Enrollment number: " << enrollmentNumber++
						<< std::endl
						<< "Course key: "
						<< enrollment.getCourse()->getCourseKey() << std::endl
						<< "Course Title: "
						<< enrollment.getCourse()->getTitle() << std::endl
						<< "Semester " << enrollment.getSemester() << std::endl
						<< "Grade " << std::setprecision(1)
						<< enrollment.getGrade() << std::endl;
				printDashLine();
			}
			printSolidLine();
			std::cout << "Choose enrollment Number: ";
			int enrollmentOption = getInput<int>(1, allEnrollments.size());
			printSolidLine();
			Enrollment enrollmentToChange = allEnrollments[enrollmentOption - 1];

			std::cout << "1. Change Grade" << std::endl;
			std::cout << "2. Delete enrollment" << std::endl;

			printSolidLine();
			std::cout << "Please select: ";

			enrollmentOption = getInput<int>(1, 2);
			printSolidLine();
			switch (enrollmentOption) {

			case (1): {

				std::cout << "Please enter new grade: ";
				float newGrade = getInput<float>(1.0, 5.0);
				studentDB.changeGrade(matrikelNumber, enrollmentToChange,
						newGrade);
				printSolidLine();
				std::cout << "Grade updated successfully" << std::endl;
				printSolidLine();

			}
				break;

			case (2): {
				studentDB.deleteEnrollment(matrikelNumber, enrollmentToChange);
				std::cout << "Enrollment deleted" << std::endl;
				printSolidLine();

			}
				break;

			}
		}
		}

	}

}

void SimpleUI::writeToFile() const{

	std::cout << "Please enter file name (example.txt): ";
	std::string fileName = getInput<std::string>();
	std::ofstream out;
	out.open (fileName);
	if (!out.is_open()) {
		std::cout << "File could not be opened" << std::endl;
		return;
	}
	studentDB.write(out);
	out.close();
	printDashLine();
	std::cout << "Data written to file successfully" << std::endl;
}
void SimpleUI::readFromFile() const{

	std::cout << "Please enter file name (example.txt): ";
	std::string fileName = getInput<std::string>();
	std::ifstream in;
	in.open (fileName);
	if (!in.is_open()) {
		std::cout << "File could not be opened" << std::endl;
		return;
	}
	studentDB.read(in);
	printDashLine();
	std::cout << "Data read from file successfully" << std::endl;

}

void SimpleUI::getDataFromServer() const{
	std::cout << "How many students do you want to add?: ";
	int numOfStudents = getInput<int>(1, 100);
	printDashLine();
	int currentCount = 0;
	while (currentCount < numOfStudents) {

		try {
			boost::asio::ip::tcp::iostream connectionServer(
					"www.hhs.users.h-da.cloud", "4242");

			if (!connectionServer) {
				std::cout << "Failed to connect to the server." << std::endl;

			}
			std::vector<std::string> serverResponse;
			connectionServer << "generate" << std::endl;
			connectionServer << "quit" << std::endl;
			std::string line;

			while (std::getline(connectionServer, line)) {
				serverResponse.push_back(line);
			}
			std::istringstream jsonStream(serverResponse[1]);

			/* References for parsing JSON
			 * 1. https://www.boost.org/doc/libs/master/boost/property_tree/
			 * 		json_parser.hpp
			 * 2. https://www.boost.org/doc/libs/1_68_0/doc/html/
			 * 		property_tree.html
			 * 3. https://www.cochoy.fr/boost-property-tree/
			 */
			boost::property_tree::ptree responseJson;
			boost::property_tree::read_json(jsonStream, responseJson);

			std::string firstName = responseJson.get<std::string>(
					"name.firstName");
			std::string lastName = responseJson.get<std::string>(
					"name.lastName");
			Poco::Data::Date dateOfBirth(
					responseJson.get<int>("dateOfBirth.year"),
					responseJson.get<int>("dateOfBirth.month"),
					responseJson.get<int>("dateOfBirth.date"));

			Address address(responseJson.get<std::string>("location.street"),
					static_cast<unsigned short>(responseJson.get<int>(
							"location.postCode")),
					responseJson.get<std::string>("location.city"), "");

			Student newStudent(firstName, lastName, dateOfBirth, address);
			studentDB.addStudent(newStudent.getMatrikelNumber(), newStudent);

			++currentCount;

			std::cout << "Added student : " << newStudent.getMatrikelNumber()
					<< " - " << newStudent.getFirstName() << " "
					<< newStudent.getLastName() << std::endl;
			printDashLine();

		}

		catch (...) {

		}

	}

}

std::string& SimpleUI::toLowercase(std::string &string) const{

	for (auto &i : string) {
		i = std::tolower(i);
	}
	return string;
}

void SimpleUI::printSolidLine() const {
	std::cout << "-------------------------------------------" << std::endl;
}

void SimpleUI::printDashLine() const {
	std::cout << "- - - - - - - - - - - - - - - - - - - - - -" << std::endl;
}

