#include "LinkedList.h"
typedef enum
{
	NAME,
	ID,
	AGE,
	GPA,
}StudentAttribute;

void HeapOverFlowWarning()
{
    fprintf(stderr, "Error: heap.\n");
    exit(EXIT_FAILURE);
}

/*********************** STUDENT METHODS **************************/

// prompts the user to enter required data to initialize the student
void SetupStudent(Student* myStudent)
{
	char tempName[MAX_NAME_LENGTH];

	// Clear leftover input buffer (especially after scanf before calling this)
	// Seif : Done by chat gpt*
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Enter student name: ");
	fgets(tempName, MAX_NAME_LENGTH, stdin);

	// Remove trailing newline inserted by fgets
	tempName[strcspn(tempName, "\n")] = '\0';

	// Use setName to assign name to student
	setName(myStudent, (uint8*)tempName);

	printf("Enter ID: ");
	scanf("%hu", &(myStudent->id));

	printf("Enter Age: ");
	scanf("%hu", &(myStudent->age));

	while (myStudent->age > MAX_AGE_LIMIT || myStudent->age < MIN_AGE_LIMIT)
	{
		printf("Enter Age: ");
		scanf("%hu", &(myStudent->age));
	}

	printf("Enter GPA: ");
	scanf("%f", &(myStudent->gpa));

	while (myStudent->gpa > MAX_GPA_LIMIT)
	{
		printf("Invalid GPA!\n");
		printf("Enter GPA: ");
		scanf("%f", &(myStudent->gpa));
	}

}


// edits chosen attribute of passed student
void EditStudentInfo(Student* myStudent)
{
	//to finish edit
	bool exitFlag = false;

	//to hold the new name if a name edit is required
	char tempName[MAX_NAME_LENGTH];

	int ch;

	while (!exitFlag)
	{
		printf("Enter attribute to be modified : \n");
		printf("1) Name\n");
		printf("2) id\n");
		printf("3) age\n");
		printf("4) GPA\n");
		printf("5) exit edit\n");

		//
		uint32 tempChoice;
		scanf("%d",&tempChoice);

		StudentAttribute choice = (StudentAttribute)(tempChoice - 1);

		switch(choice)
		{
		case NAME:
			while ((ch = getchar()) != '\n' && ch != EOF);
			printf("Enter student name: ");
			fgets(tempName, MAX_NAME_LENGTH, stdin);

			// Remove trailing newline inserted by fgets
			tempName[strcspn(tempName, "\n")] = '\0';
			setName(myStudent, tempName);
			break;
		case ID:
			printf("Enter new id: ");
			scanf("%hu", &(myStudent->id));
			break;
		case AGE:
			printf("Enter new age: ");
			scanf("%hu", &(myStudent->age));
			while (myStudent->age > MAX_AGE_LIMIT || myStudent->age < MIN_AGE_LIMIT)
			{
				printf("Enter Age: ");
				scanf("%hu", &(myStudent->age));
			}
			break;
		case GPA:
			printf("Enter new GPA: ");
			scanf("%f", &(myStudent->gpa));
			while (myStudent->gpa > MAX_GPA_LIMIT)
			{
				printf("Invalid GPA!\n");
				printf("Enter GPA: ");
				scanf("%f", &(myStudent->gpa));
			}
			break;
		default:
			exitFlag = true;
			break;
		}
	}
}

// used to set the name for a student
void setName(Student* myStudent, const uint8* newName)
{
	uint8* oldNamePtr = myStudent->name;
	while ( ( *(oldNamePtr++) =  * (newName++) ) != '\0' );
}

void printStudentInfo(Student* myStudent)
{
	if (!myStudent)
		return;

	printf("Student's name : %s\n",myStudent->name);
	printf("ID  : %d\n",myStudent->id);
	printf("Age : %d\n",myStudent->age);
	printf("GPA : %0.2f\n",myStudent->gpa);
}


/*********************** LINKED LIST METHODS **************************/
// add new student to linked list
bool AddStudent(LinkedList* L)
{
	// create new student
	Student* newStudent = (Student*)malloc(sizeof(Student));
	if (!newStudent) { HeapOverFlowWarning(); }

	// setup its data members
	SetupStudent(newStudent);

	if (SearchByID(L, newStudent->id))
	{
		free(newStudent);
		return false;
	}
	//create new node
	node* newNode = (node*)malloc(sizeof(node));

	if (!newNode) { HeapOverFlowWarning(); }

	//prepare the node
	newNode->data = newStudent;
	newNode->next = NULL;

	// if the linked list is empty, insert at head
	if (L->count == 0)
	{
		//modify the head data pointer
		L->head = newNode;

		//modify the head next pointer
		L->head->next = NULL;
	}
	else //insert sorted by id (ascendingly)
	{
		//get pointer to first node
		node* ptr = L->head;

		//get pointer to last node with id less than input id
		while ( ptr->next != NULL && ptr->next->data->id < newStudent->id) { ptr = ptr->next; }

		newNode->next = ptr->next;
		ptr->next = newNode;
	}

	//increment count
	L->count++;

	return true;
}

// display all students in the linked list
void DisplayStudentInfo(LinkedList* L)
{
	node* ptr = L->head;

	while (ptr)
	{
		printStudentInfo(ptr->data);
		ptr = ptr->next;
	}
}


// search for a student in linked list by id
Student* SearchByID(LinkedList* L, uint16 key_id)
{
	//pointer to found student
	Student* found = NULL;

	//get pointer to the head
	node* ptr = L->head;

	//traverse searching for required id
	while ( (!found) && (ptr != NULL) )
	{
		if (ptr->data->id == key_id)
		{
			found = ptr->data;
			printStudentInfo(found);
			break;
		}
		else if (ptr->data->id > key_id)
		{
			//because the LinkedList is sorted ascendingly by id
			// if this line is true, the required id is not in the LL
			break;
		}
		else
		{
			// get pointer to next node
			ptr = ptr->next;
		}
	}
	return found;
}

// updates certain student's info
bool UpdateStudentInfo(LinkedList* L, uint16 key_id)
{

	Student* found = SearchByID(L, key_id);

	if (found) {  EditStudentInfo(found);  }
	else	   {  printf("Student with this ID doesn't exist! "); }

	return (bool)found;
}

// calculates Average GPA of all students
float32 GetAvgGPA(LinkedList* L)
{
	float sumGPA = 0;

	node* ptr = L->head;

	while (ptr)
	{
		sumGPA += ptr->data->gpa;
		ptr = ptr->next;
	}

	return (sumGPA/L->count);
}

// finds student with highest GPA
Student* FindHighestGPA(LinkedList* L)
{
	float highestGPA = 0;
	Student* found = NULL;
	node* ptr = L->head;

	while (ptr)
	{
		if (ptr->data->gpa > highestGPA)
		{
			//update the found student pointer
			found = ptr->data;

			//update highest GPA
			highestGPA = ptr->data->gpa;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	return found;
}

// deletes a student from the list
bool DeleteStudent(LinkedList* L, uint16 key_id)
{
	node* ptr = L->head;

	if (!ptr)
	{
		printf ("list is empty!");
		return false;
	}

	//if the required node is the head
	if (ptr->data->id == key_id)
	{
		L->head = ptr->next;
		free(ptr->data);
		ptr->next = NULL;
		free(ptr);
		ptr = NULL;
		L->count --;
		return true;
	}

	node* prev = ptr;
	ptr = ptr->next;

	// to check if we found student with the same input ID
	bool deleted = false;

	while (!deleted && ptr)
	{
		if (ptr->data->id == key_id)
		{
			prev->next = ptr->next;
			free(ptr->data);
			ptr->next = NULL;
			free(ptr);
			ptr = NULL;
			L->count--;
			deleted = true;
			return true;
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
	return deleted;
}

void clear(LinkedList* L)
{
	while (L->count > 0)
	{
		DeleteStudent(L, L->head->data->id);
	}
}