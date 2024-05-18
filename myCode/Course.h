/*
 * Course.h
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <map>
#include <string>
#include <vector>

/**
 * @brief The Course class represents a generic course.
 */
class Course {
private:
	static std::map<unsigned char, std::string> majorById; /**< Static map to
	 store majors by their IDs. */
	unsigned int courseKey; /**< Unique identifier for the course. */
	std::string title; /**< Title of the course. */
	unsigned char major; /**< Major associated with the course. */
	float creditPoints; /**< Credit points earned upon completion of the
	 course. */

public:
	/**
	 * @brief Constructs a new Course object.
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param major Major associated with the course.
	 * @param creditPoints Credit points earned upon completion of the course.
	 */
	Course(unsigned int courseKey,
			std::string title,
			std::string major,
			float creditPoints);

	/**
	 * @brief Virtual destructor for the Course class.
	 */
	virtual ~Course() = 0;

	/**
	 * @brief Retrieves the course key.
	 * @return The course key.
	 */
	unsigned int getCourseKey() const;

	/**
	 * @brief Retrieves the credit points of the course.
	 * @return Credit points earned upon completion of the course.
	 */
	float getCreditPoints() const;

	/**
	 * @brief Retrieves the major associated with the course.
	 * @return The major associated with the course.
	 */
	std::string getMajor() const;

	/**
	 * @brief Retrieves the title of the course.
	 * @return The title of the course.
	 */
	const std::string& getTitle() const;

	/**
	 * @brief Retrieves additional information about the course.
	 * @return Additional information about the course.
	 * @details This method is pure virtual and must be implemented by derived
	 * classes.
	 */
	virtual const std::vector<std::string> getAdditionalInfo()
			const = 0;

	/**
	 * @brief Writes course information to the output stream.
	 * @param out The output stream to write to.
	 */
	virtual void write(std::ostream &out) const;

	/**
	 * @brief Converts an integer to a string.
	 *
	 * This function takes an integer value and converts it to its string representation.
	 *
	 * @param value The integer value to be converted.
	 * @return The string representation of the integer.
	 */
	std::string getString(int value) const;

};

#endif /* COURSE_H_ */
