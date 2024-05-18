/*
 * Enrollment.h
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include "Course.h"

/**
 * @brief The Enrollment class represents a student's enrollment in a course for
 * a specific semester.
 */
class Enrollment {
private:
    float grade; /**< Grade obtained in the course. */
    std::string semester; /**< Semester during which the course was enrolled.*/
    const Course* course; /**< Pointer to the enrolled course. */

public:
    /**
     * @brief Constructs a new Enrollment object with specified parameters.
     * @param semester Semester during which the course was enrolled.
     * @param course Pointer to the enrolled course.
     */
    Enrollment(std::string semester, const Course* course);

    /**
     * @brief Constructs a new Enrollment object with specified parameters.
     * @param grade Grade obtained in the course.
     * @param semester Semester during which the course was enrolled.
     * @param course Pointer to the enrolled course.
     */
    Enrollment(float grade, std::string semester, const Course* course);

    /**
     * @brief Copy constructor for the Enrollment class.
     * @param other The Enrollment object to copy.
     */
    Enrollment(const Enrollment& other);

    /**
     * @brief Destructor for the Enrollment class.
     */
    ~Enrollment();

    /**
     * @brief Retrieves the grade obtained in the course.
     * @return The grade obtained.
     */
    float getGrade() const;

    /**
     * @brief Retrieves the semester during which the course was enrolled.
     * @return The semester.
     */
    const std::string& getSemester() const;

    /**
     * @brief Retrieves the enrolled course.
     * @return Pointer to the enrolled course.
     */
    const Course* getCourse() const;

    /**
     * @brief Sets the grade obtained in the course.
     * @param grade The grade to set.
     */
    void setGrade(float grade);

    /**
     * @brief Writes enrollment information to the output stream.
     * @param out The output stream to write to.
     */
    void write(std::ostream& out) const;

    /**
     * @brief Reads an Enrollment object from the input stream.
     * @param in The input stream to read from.
     * @return The read Enrollment object.
     */
    static Enrollment read(std::istream& in);

    /**
     * @brief Sets the enrolled course.
     * @param course Pointer to the enrolled course.
     */
    void setCourse(const Course* course);
};

#endif /* ENROLLMENT_H_ */
