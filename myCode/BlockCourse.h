/*
 * BlockCourse.h
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"

#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

/**
 * @brief The BlockCourse class represents a course that occurs within a
 * specific block of time.
 */
class BlockCourse: public Course
{
private:
	Poco::Data::Date startDate; /**< Start date of the course. */
	Poco::Data::Date endDate; /**< End date of the course. */
	Poco::Data::Time startTime; /**< Start time of the course. */
	Poco::Data::Time endTime; /**< End time of the course. */

public:
	/**
	 * @brief Constructs a new BlockCourse object.
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param major Major associated with the course.
	 * @param creditPoints Credit points earned upon completion of the course.
	 * @param startDate Start date of the course.
	 * @param endDate End date of the course.
	 * @param startTime Start time of the course.
	 * @param endTime End time of the course.
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime);

	/**
	 * @brief Destructor for the BlockCourse class.
	 */
	~BlockCourse();

	/**
	 * @brief Retrieves the end date of the course.
	 * @return The end date of the course.
	 */
	const Poco::Data::Date& getEndDate() const;

	/**
	 * @brief Retrieves the end time of the course.
	 * @return The end time of the course.
	 */
	const Poco::Data::Time& getEndTime() const;

	/**
	 * @brief Retrieves the start date of the course.
	 * @return The start date of the course.
	 */
	const Poco::Data::Date& getStartDate() const;

	/**
	 * @brief Retrieves the start time of the course.
	 * @return The start time of the course.
	 */
	const Poco::Data::Time& getStartTime() const;

	/**
	 * @brief Retrieves additional information about the course.
	 * @return Additional information about the course.
	 * @details This method is overridden from the base class Course.
	 */
	const std::vector<std::string> getAdditionalInfo() const override;

	/**
	 * @brief Writes course information to the output stream.
	 * @param out The output stream to write to.
	 * @details This method is overridden from the base class Course.
	 */
	void write(std::ostream &out) const override;

	/**
	 * @brief Reads parameters of BlockCourse from the input stream and creates
	 * an object.
	 * @param in The input stream to read from.
	 * @return A pointer to the read BlockCourse object.
	 */
	static const Course* read(std::istream &in);

	/**
	 * @brief Parses a date string and returns a Date object.
	 * @param date The date string to parse.
	 * @return The parsed Date object.
	 */
	static const Poco::Data::Date getDate(std::string &date);

	/**
	 * @brief Parses a time string and returns a Time object.
	 * @param time The time string to parse.
	 * @return The parsed Time object.
	 */
	static const Poco::Data::Time getTime(std::string &time);

};

#endif /* BLOCKCOURSE_H_ */
