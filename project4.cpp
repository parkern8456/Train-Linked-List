/*
+-------------------------------------------------------------------------------------------------+
| Author: Nathan Parker                                                                           |
| Originator: Prof. Pham                                                                          |
| Start Date: December 1, 2016                                                                    |
| Due Date: Tuesday, December 9, 2016 (by midnight)                                               |
| Course: CSC136 both sections 010 and 020	                                                      |
| Assignment: Project# (individual project)                                                       |
| File name: Project2.cpp                                                                         |
| Purpose: To load an input file of train cars and store them into a linked list of type rail     |
| then load a transaction file, edit the train, then display the final train and calculate the    |
| pull of the train.                                                                              |
+-------------------------------------------------------------------------------------------------+
*/

// LIBRARY DECLARATION
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// STRUCTURE DECLARATION
struct Rail {
	string type, name;
	int tonnage;
	Rail *coupling;
};

// GLOBAL VARIABLE DECLARATION
Rail *front, *rear;

// PROTOTYPE DECLARATION
void explainProjectPurpose();		   // Explain to the user the purpose of this program
void loadTrainInfo();				   // Request train data file from the user and load in the file contents
void loadFirstCar(ifstream&);		   // Load the first (front) node of the linked list of Rail cars
void loadOtherCar(ifstream&);		   // Load the remaining nodes to the linked list of Rail cars up to the last node (rear)
void displayTrain();				   // Display the contents of the train linked list
void loadTransactions();			   // Load and perform transactions based on the input text file
void calculatePull();				   // Calculate if the train can succesfully be pulled


/*******************************************************************************************/
/* Function name: MAIN                                                                     */
/* Description: This main function calls the explainProjectPurpose function to display the */
/*     purpose and instructions on how to use this application, calls a function to load   */
/*******************************************************************************************/
int main()	// This main function uses Procedural Abstraction (there's no codes just calling functions)
{
	explainProjectPurpose();
	loadTrainInfo();
	calculatePull();
	system("pause");
	return 0;
}

/*****************************************************************/
/* Function name: explainProjectPurpose                          */
/* Description: Explains to the user what this project is about. */
/*		Provide user of possible instructions.                   */
/* Parameters: none                                              */
/*****************************************************************/
void explainProjectPurpose()
{
	cout << "Welcome to TRAIN CAR LOADER 1.0!!!\n\n";
	cout << "---------------------------------------------------------------------------------------------\n";

	cout << "This program will load a train file provided by the user and store the data into our system.\n";
	cout << "Once you have succesfully loaded a train file, we will display your currently loaded train.\n";
	cout << "Next you will provide a transaction file for our system to examine.\n";
	cout << "Once you have succesfully loaded a transaction file, we will perform the transactions\n";
	cout << "and display the final version of the train in our system.\n";

	cout << "---------------------------------------------------------------------------------------------\n\n";
}

/*********************************************************************************/
/* Function name: loadTrainInfo                                                  */
/* Description: This function loads the train data file provided by the user.    */
/* Parameters: none		                                                         */
/*********************************************************************************/
void loadTrainInfo()
{
	ifstream inFile;
	string filename;

	cout << "Please enter the name of the train file you wish to load: ";
	cin >> filename;

	inFile.open(filename.c_str());

	if (inFile.fail()) {
		cerr << "You have provided a file name that is not in our system.\n" << endl;
		cout << "Now exiting the program...\n";
	}
	else
	{
		loadFirstCar(inFile);
		loadOtherCar(inFile);
		cout << "\nYour train data has been successfully loaded into the system!\n";
		displayTrain();
		loadTransactions();
	}
}

/*********************************************************************************/
/* Function name: loadFirstCar                                                   */
/* Description: This function loads only the first node into the linked list     */
/* Parameters: inf filestream                                                    */
/*********************************************************************************/
void loadFirstCar(ifstream& inf) {

	Rail *aRail;

	aRail = new Rail;
	getline(inf, aRail->type, ',');
	getline(inf, aRail->name, ',');
	inf >> aRail->tonnage;
	inf.ignore(100, '\n');

	front = aRail;
	rear = aRail;
}

/*********************************************************************************/
/* Function name: loadOtherCar                                                   */
/* Description: This function loads all the rest of the nodes into the linked list*/
/* Parameters: inf filestream                                                    */
/*********************************************************************************/
void loadOtherCar(ifstream& inf) {

	Rail *aRail;

	while (!inf.eof()) {
		aRail = new Rail;
		getline(inf, aRail->type, ',');
		getline(inf, aRail->name, ',');
		inf >> aRail->tonnage;
		inf.ignore(100, '\n');

		rear->coupling = aRail;
		rear = rear->coupling;
	}

	// Setting the rear node of the list's coupling to NULL (no nodes exist after rear)
	rear->coupling = NULL;
}

/*********************************************************************************/
/* Function name: displayTrain                                                   */
/* Description: This function displays the data from each node in the linked list*/
/* Parameters: none		                                                         */
/*********************************************************************************/
void displayTrain() {

	Rail *curRail;
	curRail = front;

	cout << "\nThe contents of your current train are: \n\n";

	while (curRail != rear->coupling) {
		cout << "Name: " << curRail->name << "\n";
		cout << "Type: " << curRail->type << "\n";
		cout << "Tonnage: " << curRail->tonnage << "\n\n";
		curRail = curRail->coupling;
	}

	cout << "---------------------------------------------------------------------------------------------\n\n";
}

/*********************************************************************************/
/* Function name: loadTransactions                                               */
/* Description: This function loads the transaction file and performs them	     */
/* Parameters: none		                                                         */
/*********************************************************************************/
void loadTransactions() {

	ifstream transIns;
	Rail *transRailcar, *railcar, *preRailcar, *transCar;
	string sCommand, railcarName, filename;
	char command;
	bool found, skipOnce; //skipOnce is used to make sure the preRailcar is one car behind.

	cout << "Enter the name of your train's transaction file you wish to load: ";
	cin >> filename;
	transIns.open(filename.c_str());  // tags the string as filename

	if (transIns.fail())
	{
		cout << "\nYou have provided a transaction file name that is not in our system.\n";
		cout << "Your train will remain unchanged.\n";
	}
	else
		while (!transIns.eof())
		{
			found = false, skipOnce = false;
			getline(transIns, sCommand, ';');
			command = sCommand[0];
			switch (command)
			{
			case 'A': // CASE-SWITCH will not take string
			{
				
				// Create a new railcar and assign the read-in values
				transRailcar = new Rail;
				getline(transIns, transRailcar->type, ',');	// Read in the type 
				getline(transIns, transRailcar->name, ',');	// Read in the name
				transIns >> transRailcar->tonnage;		    // Read in the tonnage
				transIns.ignore(100, '\n');			        // Clear the remaining buffer for that line/stream	

				rear->coupling = transRailcar;
				rear = rear->coupling;
				transRailcar->coupling = NULL;

				break;
			}
			case 'D':
			{
				// Create a new railcar and assign the read-in values
				transCar = new Rail;
				getline(transIns, transCar->name);	// Read in the name
				transIns.ignore(100, '\n');

				railcar = front;
				preRailcar = front;

				// If the front node is the railcar to be removed, simply move the front
				// node pointer to the second node in the linked list
				if (front->name == transCar->name) {
					front = front->coupling;
					found = true;
				}
				else
					railcar = front->coupling;				// If the first node is not to be removed, move railcar pointer to second node

				while (!found && railcar->coupling != NULL) {
					if (railcar->name == transCar->name) // Change found to true if there is a match to be removed
						found = true;
					else {
						railcar = railcar->coupling;			// Move railcar to next node if there is no match
						preRailcar = preRailcar->coupling;		// Move preRailcar to next node if there is no match
					}
				}

				// If the transRailcar is found in the list, remove the list by
				// taking the coupling of the previous node and attach it to the
				// following node's coupling.
				if (preRailcar == rear) {
					preRailcar->coupling = NULL;
					rear = preRailcar->coupling;
				}else
					preRailcar->coupling = railcar->coupling;

				break;
			}
			case 'R':
			{

				break;
			}
			default:
			{
				cerr << "\nUnrecognized transaction command " << command << "Command line ignored.\n";
			}
			}
		}

	displayTrain();
}

/*********************************************************************************/
/* Function name: loadTrainInfo                                                  */
/* Description: This function calculates if the current train can leave the yard */
/* Parameters: none		                                                         */
/*********************************************************************************/
void calculatePull()
{
	int totalHorsePower = 0, totalRailcarsTonnage = 0, calcPull = 0;
	bool pullable = false;

	Rail *curRail;
	curRail = front;

	while (curRail->coupling != NULL) {
		if (curRail->type == "engine")
			totalHorsePower += 3000;
		else
			totalRailcarsTonnage += curRail->tonnage;

		curRail = curRail->coupling;
	}

	// Display results
	calcPull = (totalHorsePower * 0.6);
	cout << "\nTotal horsepower is " << totalHorsePower;
	cout << "\nTotal pull capability (in tons) is " << calcPull;
	cout << "\nTotal train tonnage is " << totalRailcarsTonnage;
	if (calcPull>totalRailcarsTonnage)
		cout << "\n\nCongratulations, your engine(s) will be able to pull the train!\n" << "Please submit your timetable with the yardmaster of when your train can leave the railyard.\n\n";
	else
		cout << "\nSorry but you do not have sufficient horsepower to pull the railcars.  Please readjust your engine and/or railcars and resubmit your train file.\n";
}