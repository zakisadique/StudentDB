/*
 * SimlpeUI.h
 *
 *  Created on: 07-Jan-2024
 *      Author: zakisadique
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include <iostream>
#include <sstream>
#include <string>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include "StudentDb.h"



/**
 * @brief The SimpleUI class provides a simple user interface for interacting
 * with the Student Database.
 */
class SimpleUI {
private:
    StudentDb &studentDB; /**< Reference to the Student Database object. */

    /**
     * @brief Adds a new course to the database.
     */
    void addNewCourse() const;

    /**
     * @brief Lists all courses in the database.
     */
    void listAllCourses() const;

    /**
     * @brief Adds a new student to the database.
     */
    void addNewStudent() const;

    /**
     * @brief Adds an enrollment for a student.
     */
    void addEnrollment() const;

    /**
     * @brief Prints details of a student.
     */
    void printStudent() const;

    /**
     * @brief Searches for a student in the database.
     */
    void searchStudent() const;

    /**
     * @brief Updates details of a student.
     */
    void updateStudent() const;

    /**
     * @brief Writes database contents to a file.
     */
    void writeToFile() const;

    /**
     * @brief Reads database contents from a file.
     */
    void readFromFile() const;

    /**
     * @brief Retrieves data from the server.
     */
    void getDataFromServer() const;

    /**
     * @brief Converts a string to lowercase.
     * @param string The string to convert.
     * @return The converted string in lowercase.
     */
    std::string& toLowercase(std::string &string) const;

    /**
     * @brief Prints a solid line as a separator.
     */
    void printSolidLine() const;

    /**
     * @brief Prints a dashed line as a separator.
     */
    void printDashLine() const;

    /**
     * @brief Template function to get input within a range.
     * @tparam T The type of input.
     * @param min The minimum value of the range.
     * @param max The maximum value of the range.
     * @return The input value within the specified range.
     */
    template<typename T>
    T getInput(T min, T max) const;

    /**
     * @brief Template function to get input of any type.
     * @tparam T The type of input.
     * @return The input value.
     */
    template<typename T>
    T getInput() const;



public:
    /**
     * @brief Constructs a new SimpleUI object.
     * @param studentDB Reference to the Student Database.
     */
    SimpleUI(StudentDb &studentDB);

    /**
     * @brief Runs the SimpleUI application.
     */
    void run() const;
};

#endif // SIMPLEUI_H

/**
 * @brief Template specialization to get Poco Date input.
 * @return Poco Date input.
 */
template<>
Poco::Data::Date SimpleUI::getInput() const;

/**
 * @brief Template specialization to get Poco Time input.
 * @return Poco Time input.
 */
template<>
Poco::Data::Time SimpleUI::getInput() const;

template<typename T>
inline T SimpleUI::getInput(T min, T max) const {
	T input;
	bool validInput = false;
	while (!validInput) {
		if ((std::cin >> input) && !(input < min || input > max)
				&& (std::cin.peek() == '\n')) {

			validInput = true;
			continue;

		}

		std::cout << "Please enter a number between " << min << " and " << max
				<< ": ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}
	return input;
}

template<typename T>
inline T SimpleUI::getInput() const {
	std::string stringVariable;
	std::getline(std::cin >> std::ws, stringVariable);

	return stringVariable;
}

template<>
inline Poco::Data::Date SimpleUI::getInput() const {
	bool validInput = false;
	int day, month, year;
	Poco::Data::Date date;

	while (validInput == false) {
		std::string dateString;
		std::cin >> dateString;
		if (dateString.length() == 10) {
			std::istringstream dateStream(dateString);
			char separator;
			dateStream >> day >> separator;
			if (!(dateStream.fail()) && separator == '.') {
				dateStream >> month >> separator >> year;
				if (!(dateStream.fail()) && separator == '.'
						&& dateStream.peek() == EOF) {

					try {
						date = Poco::Data::Date(year, month, day);
						validInput = true;
						continue;
					} catch (...) {

					}

				}
			}

		}
		std::cout
				<< "Error: Please enter date in the correct format "
						"(DD.MM.YYYY): ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}

	return date;
}

template<>
inline Poco::Data::Time SimpleUI::getInput() const {
	bool success = false;
	int hour, minutes;
	Poco::Data::Time time;

	while (success == false) {

		std::string timeString;
		std::cin >> timeString;
		if (timeString.length() == 5) {
			std::istringstream timeStream(timeString);
			char separator;
			timeStream >> hour >> separator;
			if (!timeStream.fail() && separator == ':') {
				timeStream >> minutes;
				if (!timeStream.fail() && timeStream.peek() == EOF) {
					try {
						time = Poco::Data::Time(hour, minutes, 00);
						success = true;
						continue;
					} catch (...) {

					}

				}
			}

		}
		std::cout << "Error: Please enter date in the correct format "
				"(HH:MM): ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}
	return time;

}

