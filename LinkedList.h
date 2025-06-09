 /**
  * @file LinkedList.h
  * @brief Header file for Student Management System using linked list
  *
  * This file defines the data structures and function prototypes used in the Student Management System.
  * The system supports operations such as adding, displaying, updating, deleting, and searching for student records.
  * It also includes utilities to calculate the average GPA and identify the student with the highest GPA.
  *
  * Core functionalities include:
  * - Managing a dynamic list of students.
  * - Input validation and memory-safe operations.
  * - Efficient search and update mechanisms based on student ID.
  *
  * @author Abdelrahman Samir
  * @date June 2025
  */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdTypes.h"

 /**
  * @def MAX_NAME_LENGTH
  * @brief Maximum length for student names (chosen for memory alignment)
  */
#define MAX_NAME_LENGTH 64

  /**
   * @struct student
   * @brief Structure representing a student record
   * @note Data members ordered from biggest to smallest for efficient memory alignment
   */
struct student
{
    uint8* name[MAX_NAME_LENGTH]; /**< Array of pointers for student name */
    float32 gpa;                 /**< Student's grade point average */
    uint16 id;                   /**< Unique student identifier */
    uint16 age;                  /**< Student's age */
};

typedef struct student Student; /**< Typedef for student structure */

/**
 * @struct Node
 * @brief Node structure for linked list implementation
 */
struct Node
{
    Student* data;      /**< Pointer to student data */
    struct Node* next;  /**< Pointer to next node in list */
};

typedef struct Node node; /**< Typedef for node structure */

/**
 * @struct linkedlist
 * @brief Container structure for linked list
 */
struct linkedlist
{
    node* head;     /**< Pointer to first node in list */
    uint16 count;   /**< Number of nodes in list */
};

typedef struct linkedlist LinkedList; /**< Typedef for linked list structure */

/**
 * @enum Operation
 * @brief Enumeration of possible operations in the system
 */
typedef enum
{
    ADD,        /**< Add a new student */
    DISPLAY,    /**< Display all students */
    SEARCH,     /**< Search for a student */
    UPDATE,     /**< Update student info */
    DELETE,     /**< Delete a student */
    AVG_GPA,    /**< Calculate average GPA */
    HIGHEST_GPA,/**< Find highest GPA */
    EXIT        /**< Exit the program */
} Operation;

/**
 * @brief Displays heap overflow warning and terminates program
 */
inline void HeapOverFlowWarning();

/*********************** STUDENT METHODS **************************/

/**
 * @brief Initializes a student record with user input
 * @param myStudent Pointer to student structure to initialize
 */
void SetupStudent(Student* myStudent);

/**
 * @brief Sets the name of a student record
 * @param myStudent Pointer to student structure
 * @param newName New name to assign
 */
void setName(Student* myStudent, const uint8* newName);

/**
 * @brief Edits specified attributes of a student record
 * @param myStudent Pointer to student structure to modify
 */
void EditStudentInfo(Student* myStudent);

/**
 * @brief Prints student information to standard output
 * @param myStudent Pointer to student structure to display
 */
void printStudentInfo(Student* myStudent);

/*********************** LINKED LIST METHODS **************************/

/**
 * @brief Adds a new student to the linked list
 * @param L Pointer to linked list structure
 * @return true if addition successful, false otherwise
 */
bool AddStudent(LinkedList* L);

/**
 * @brief Displays all students in the linked list
 * @param L Pointer to linked list structure
 */
void DisplayStudentInfo(LinkedList* L);

/**
 * @brief Searches for a student by ID
 * @param L Pointer to linked list structure
 * @param key_id ID to search for
 * @return Pointer to found student or NULL if not found
 */
Student* SearchByID(LinkedList* L, uint16 key_id);

/**
 * @brief Updates information for an existing student
 * @param L Pointer to linked list structure
 * @param key_id ID of student to update
 * @return true if update successful, false otherwise
 */
bool UpdateStudentInfo(LinkedList* L, uint16 key_id);

/**
 * @brief Calculates average GPA of all students
 * @param L Pointer to linked list structure
 * @return Calculated average GPA
 */
float32 GetAvgGPA(LinkedList* L);

/**
 * @brief Finds student with highest GPA
 * @param L Pointer to linked list structure
 * @return Pointer to student with highest GPA
 */
Student* FindHighestGPA(LinkedList* L);

/**
 * @brief Deletes a student from the list
 * @param L Pointer to linked list structure
 * @param key_id ID of student to delete
 * @return true if deletion successful, false otherwise
 */
bool DeleteStudent(LinkedList* L, uint16 key_id);

#endif // LINKED_LIST_H