#include "LinkedList.h"
int main(void)
{
	// to ensure proper scanf functionality
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//declare and initialize list
	LinkedList list;
	list.head = NULL;
	list.count = 0;

	uint16 id;

	// keeps the program running
	bool RunSimulation = true;
	Operation operation;
    uint32 choice;

	// main simulation loop
	while (RunSimulation)
	{
	    printf("\nEnter Required Operation:\n");
	    printf("1. Add a Student\n");
	    printf("2. Display All Students\n");
	    printf("3. Search for a Student by ID\n");
	    printf("4. Update Student Information\n");
	    printf("5. Delete a Student\n");
	    printf("6. Calculate Average GPA\n");
	    printf("7. Find Student with Highest GPA\n");
	    printf("8. Exit\n");
	    printf("Enter choice: ");
	    scanf("%d", &choice);

	    // Subtract 1 to match the enum which starts at 0
	    operation = (Operation)(choice - 1);

	    switch (operation)
	    {
	        case ADD:
				if (!AddStudent(&list))
				{
					printf("Student with the same ID exists already");
				}
	            break;

	        case DISPLAY:
	        	DisplayStudentInfo(&list);
	            break;

	        case SEARCH:
	        	printf("Enter ID for search: ");
	        	scanf("%hu",&id);
	        	SearchByID(&list , id);
	            break;

	        case UPDATE:
	        	printf("Enter ID for update: ");
	        	scanf("%hu",&id);
	            UpdateStudentInfo(&list, id);
	            break;

	        case DELETE:
	        	printf("Enter ID for delete: ");
	        	scanf("%hu",&id);
	            DeleteStudent(&list , id);
	            break;

	        case AVG_GPA:
	        	printf ("Average GPA is %f\n",GetAvgGPA(&list));
	            break;

	        case HIGHEST_GPA:
	        	printf ("Highest GPA student is :\n");
				printStudentInfo(FindHighestGPA(&list));
	            break;

	        case EXIT:
	            printf("Exiting the program.\n");
	            RunSimulation = false;
	            break;

	        default:
	            printf("Invalid choice. Please enter a number between 1 and 8.\n");
	    }
	}

	clear(&list);
}
