/*
 * StudentDb.h
 *
 *  Created on: 05-Jan-2024
 *      Author: zakisadique
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_


#include <map>
#include <memory>
#include "Student.h"
#include "Course.h"

/**
 * @brief The StudentDb class represents a database of students and courses.
 */
class StudentDb {
private:
    std::map<unsigned int, Student> students; /**< Map to store students by
    											matriculation number. */
    std::map<int, std::unique_ptr<const Course>> courses; /**< Map to store
															courses by ID. */

public:
    /**
     * @brief Default constructor for the StudentDb class.
     */
    StudentDb();

    /**
     * @brief Destructor for the StudentDb class.
     */
    ~StudentDb();

    /**
     * @brief Retrieves the courses in the database.
     * @return Map containing the courses.
     */
    const std::map<int, std::unique_ptr<const Course>>& getCourses() const;

    /**
     * @brief Retrieves the students in the database.
     * @return Map containing the students.
     */
    const std::map<unsigned int, Student>& getStudents() const;

    /**
     * @brief Adds a course to the database.
     * @param course Pointer to the course to add.
     */
    void addCourse(Course* course);

    /**
     * @brief Adds a student to the database.
     * @param matrikelNumber Matriculation number of the student.
     * @param student The student to add.
     */
    void addStudent(unsigned int matrikelNumber, Student& student);

    /**
     * @brief Adds an enrollment for a student.
     * @param matrikelNumber Matriculation number of the student.
     * @param enrollment The enrollment to add.
     */
    void addEnrollment(unsigned int matrikelNumber,
    		const Enrollment& enrollment);

    /**
     * @brief Edits the first name of a student.
     * @param matrikelNumber Matriculation number of the student.
     * @param firstName The new first name.
     */
    void editStudentFirstName(unsigned int matrikelNumber,
    		std::string firstName);

    /**
     * @brief Edits the last name of a student.
     * @param matrikelNumber Matriculation number of the student.
     * @param lastName The new last name.
     */
    void editStudentLastName(unsigned int matrikelNumber,
    		std::string lastName);

    /**
     * @brief Edits the date of birth of a student.
     * @param matrikelNumber Matriculation number of the student.
     * @param dateOfBirth The new date of birth.
     */
    void editStudentDateOfBirth(unsigned int matrikelNumber,
    		Poco::Data::Date dateOfBirth);

    /**
     * @brief Changes the grade of an enrollment.
     * @param matrikelNumber Matriculation number of the student.
     * @param enrollment The enrollment for which to change the grade.
     * @param grade The new grade.
     */
    void changeGrade(unsigned int matrikelNumber, const Enrollment& enrollment,
						float grade);

    /**
     * @brief Deletes an enrollment for a student.
     * @param matrikelNumber Matriculation number of the student.
     * @param enrollment The enrollment to delete.
     */
    void deleteEnrollment(unsigned int matrikelNumber,
					const Enrollment& enrollment);

    /**
     * @brief Changes the address of a student.
     * @param matrikelNumber Matriculation number of the student.
     * @param address The new address.
     */
    void changeAddress(unsigned int matrikelNumber, const Address& address);

    /**
     * @brief Writes the contents of the database to an output stream.
     * @param out The output stream to write to.
     */
    void write(std::ostream& out) const;

    /**
     * @brief Reads the contents of the database from an input stream.
     * @param in The input stream to read from.
     */
    void read(std::istream& in);
};

#endif /* STUDENTDB_H_ */
