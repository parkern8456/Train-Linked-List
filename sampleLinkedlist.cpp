// This is a sample linked list program that takes the grades provided by the user
// and appends the information to the linked list and then displays the grades afterward.

#include <iostream>
using namespace std;

// LINKED LIST STRUCTURE
struct node
{
  int grade;
  node *next;
};

// INITIALIZE KEY VARIABLES
node *header, *tail;
int numGrades;
  
//PROTOTYPE
void getFirstGrade();
void getOtherGrades();
void getLastGrade();
void printGrades();

// MAIN PROGRAM
int main()
{
	getFirstGrade();
	getOtherGrades();
	getLastGrade();
	printGrades();
	
	return 0;
}

// This function asks for how many grades will be enter and asks for the first grade.
void getFirstGrade()
{
  int score;
  node *aGrade;
  
  cout << "\nHow many grades are in your list?" << endl;
  cin >> numGrades;
  
  cout << "Enter the first grade: " << endl;
  cin >> score;

  // Assign the first grade the entry score.
  aGrade = new node;
  aGrade->grade = score;
 
  // The linked list head and tail points to the first (and only) data.
  tail = aGrade;
  header = aGrade;
}

// This function asks for the other grades, except the last one.
void getOtherGrades()
{
	int score;
	node *aGrade;
	
	// Grab the next grade
	for (int i = 1; i<numGrades-1; i++)
	{
		cout << "Enter the next grade: " << endl;
		cin >> score;
		aGrade = new node;
		aGrade->grade = score;
		
		// Move the tail to the last grade.
		tail->next = aGrade;
		tail = tail-> next;
	}
}

// This function asks for the last grade.
void getLastGrade()
{
	int score;
	node * aGrade;
		
	cout << "Enter the last grade: " << endl;
	cin >> score;
	aGrade = new node;
	aGrade->grade = score;
	
	// Move the tail to the last grade and terminate the last grade's node->next with a NULL.
	tail->next = aGrade;
	aGrade->next = NULL;
}

//This function prints the grade from the linked list.
void printGrades()
{
	node *currentGrade;
	
	currentGrade = header;	// Reset the currentGrade to the beginning.
	cout << "\nYour list of grades are ";
  
	while (currentGrade!=NULL)
	{
		cout << currentGrade->grade << " ";
		currentGrade = currentGrade->next;
	}
	cout << endl;
}