#include "inverted.h"
/* Main function: handles input files, initializes the hash table,
   displays the menu and performs the selected operations */
int main(int argc, char *argv[])
{
	// Head pointer for storing the list of input files
    F_node *head = NULL;
	// Declare hash table with 28 indexes
    hash HT[28];

	if(argc <= 1)    /* Check whether the user has provided at least one input file through command line */
    {
        printf("ERROR: No input files provided\n");
        return 0;
    }

    /* Initialize hash table */
    for(int i = 0; i < 28; i++)
    {
        HT[i].index = i;
        HT[i].H_link = NULL;
    }

    /* Validate and store input files */
    validate_files(argv, &head);

    int option;
    do
    {
    printf("\n\t\t\t:::Inverted Search Project:::\n");
	printf("Select your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : ");

	scanf("%d", &option);

	switch (option)
	{
	    case 1:
		create_database(HT, head);
		break;

	    case 2:
		display_database(HT);
		break;

	    case 3:
		save_database(HT);
		    break;

	    case 4:
		search_database(HT);
		break;

	    case 5:
		update_database(HT, &head);
		break;

	    case 6:
		break;

	    default:
		printf("INFO : Please enter the valid option\n");
	}
    }while( option != 6 );   // Continue until the user selects Exit

    // Successfully terminate the program

    return 0;
}
