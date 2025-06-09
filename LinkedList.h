#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdTypes.h"
#define MAX_NAME_LENGTH 64 // chosen for better memory alignment + sufficient length for any name

struct student
{
	uint8* name[MAX_NAME_LENGTH];
	float32 gpa;
	uint16 id;
	uint16 age;
}; //data members are ordered from biggest to smallest for efficient memory alignment

typedef struct student Student;

struct Node
{
	Student* data;
	struct Node* next;
};

typedef struct Node node;

struct linkedlist
{
	node* head;
	uint16 count;
};

typedef struct linkedlist LinkedList;

/*********************** SIMULATION METHODS **************************/

typedef enum
{
	ADD,
	DISPLAY,
	SEARCH,
	UPDATE,
	DELETE,
	AVG_GPA,
	HIGHEST_GPA,
	EXIT
}Operation;

inline void HeapOverFlowWarning();


/*********************** STUDENT METHODS **************************/

// prompts the user to enter required data to initialize the student
void SetupStudent(Student* myStudent);

// used to set the name for a student
void setName(Student* myStudent, const uint8* newName);

// edits chosen attribute of passed student
void EditStudentInfo(Student* myStudent);

// prints student info
void printStudentInfo(Student* myStudent);




/*********************** LINKED LIST METHODS **************************/
// add new student to linked list
bool AddStudent(LinkedList* L);

// display all students in the linked list
void DisplayStudentInfo(LinkedList* L);

// search for a student in linked list by id
Student* SearchByID(LinkedList* L, uint16 key_id);

// updates certain student's info
bool UpdateStudentInfo(LinkedList* L, uint16 key_id);

// calculates Average GPA of all students
float32 GetAvgGPA(LinkedList* L);

// finds student with highest GPA
Student* FindHighestGPA(LinkedList* L);

// deletes a student from the list
bool DeleteStudent(LinkedList* L, uint16 key_id);

#endif // LINKED_LIST_H


