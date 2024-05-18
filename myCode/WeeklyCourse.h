/*
 * WeeklyCourse.h
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

/**
 * @brief The WeeklyCourse class represents a course that occurs weekly on a
 * specific day.
 */
class WeeklyCourse: public Course {
private:
    Poco::DateTime::DaysOfWeek dayOfWeek; /**< Day of the week when the course
    											occurs. */
    Poco::Data::Time startTime; /**< Start time of the course. */
    Poco::Data::Time endTime; /**< End time of the course. */

public:
    /**
     * @brief Constructs a new WeeklyCourse object.
     * @param courseKey Unique identifier for the course.
     * @param title Title of the course.
     * @param major Major associated with the course.
     * @param creditPoints Credit points earned upon completion of the course.
     * @param dayOfWeek Day of the week when the course occurs.
     * @param startTime Start time of the course.
     * @param endTime End time of the course.
     */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

    /**
     * @brief Destructor for the WeeklyCourse class.
     */
    ~WeeklyCourse();

    /**
     * @brief Retrieves the day of the week when the course occurs.
     * @return The day of the week.
     */
    Poco::DateTime::DaysOfWeek getDayOfWeek() const;

    /**
     * @brief Retrieves the end time of the course.
     * @return The end time of the course.
     */
    const Poco::Data::Time& getEndTime() const;

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
     * @brief Reads a WeeklyCourse object from the input stream.
     * @param in The input stream to read from.
     * @return A pointer to the read WeeklyCourse object.
     */
    static const Course* read(std::istream& in);

    /**
     * @brief Parses a date string and returns a Date object.
     * @param date The date string to parse.
     * @return The parsed Date object.
     */
    static const Poco::Data::Date getDate(std::string& date);

    /**
     * @brief Parses a time string and returns a Time object.
     * @param time The time string to parse.
     * @return The parsed Time object.
     */
    static const Poco::Data::Time getTime(std::string& time);
};

#endif /* WEEKLYCOURSE_H_ */
