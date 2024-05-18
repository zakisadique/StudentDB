/*
 * main.cpp
 *
 *  Created on: 04-Jan-2024
 *      Author: zakisadique
 */
/**
 * @mainpage Simple UI Implementation for a Student Database
 *
 * The SimpleUI class offers a straightforward user interface for
 * interacting with the database. It is instantiated with the student
 * database as an argument. The run method operates by continuously
 * listing available commands, prompting the user to select one by
 * entering the corresponding number, and executing the chosen command.
 * Execution of commands may require additional data input from the
 * user. Command execution is facilitated by invoking methods from
 * various classes.
 *
 * The implementation also provides the facility to write the data
 * present in the database in a file in a comma-separated format. The
 * UI can also take input from a file and populate the database with
 * corresponding data. Furthermore, the UI can fetch data from an online
 * server and create new students in the database.
 */


#include "SimpleUI.h"

int main() {


	StudentDb database;
	SimpleUI simpleUI(database);
	simpleUI.run();

	return 0;
}
