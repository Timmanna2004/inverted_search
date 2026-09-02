#include "inverted.h"
/*
 * Function to insert a new file name
 * at the end of the file linked list
 */
int insert_last(F_node **head, char *f_name)
{
    // Allocate memory for a new file node
    F_node*new_node=malloc(sizeof(F_node));

    // Check whether memory allocation was successful
    if(new_node==NULL)
    {
        return FAILURE;
    }
     // Copy the file name into the new node
    strcpy(new_node->f_name, f_name);

     // Initialize the link of the new node
    new_node->link=NULL;

     /*
     * If the list is empty,
     * make the new node as the first node
     */
    if(*head==NULL)
    {
        *head=new_node;
        return SUCCESS;
    }
 // Traverse the list to find the last node
    F_node*temp=*head;
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    // Link the new node at the end of the list
    temp->link=new_node;
    return SUCCESS;

}

/*
 * Function to check whether
 * the given file name already exists in the list
 */
int check_duplicates(F_node *head, char *f_name)
{
    // Start traversal from the first node
    F_node *temp = head;

    // Traverse through the complete file list
    while(temp != NULL)
    {
        // Compare the current file name with the given file name
        if(strcmp(temp->f_name, f_name) == 0)
        {
            return FAILURE;   // duplicate found
        }

        // Move to the next node
        temp = temp->link;
    }

    return SUCCESS;   // not duplicate
}

/*
 * Function to validate all input files
 * provided through command-line arguments
 */
void validate_files(char *argv[], F_node **head)
{
    // Start checking arguments from index 1
    int i = 1;

    // Continue until all command-line arguments are checked
    while(argv[i] != NULL)
    {
        // Find the last dot in the file name
        char *ptr = strrchr(argv[i], '.');

        /*
         * Check whether the file has a .txt extension
         */
        if(ptr == NULL || strcmp(ptr, ".txt") != 0)
        {
            printf("ERROR: %s is not a .txt file\n", argv[i]);
            i++;
            continue;
        }

        /* Check duplicate first */
        if(check_duplicates(*head, argv[i]) == FAILURE)
        {
            printf("ERROR: %s is duplicate file\n", argv[i]);
            i++;
            continue;
        }

        /* Open/create file */
        FILE *fp = fopen(argv[i], "a+");

        if(fp == NULL)
        {
            printf("ERROR: %s failed to open\n", argv[i]);
            i++;
            continue;
        }

        printf("INFO: %s opened successfully\n", argv[i]);

        /*
         * Insert the valid file name
         * into the file linked list
         */
        if(insert_last(head, argv[i]) == FAILURE)
        {
            printf("ERROR: File insertion failed\n");
            fclose(fp);
            i++;
            continue;
        }

        /* Check empty */
        fseek(fp, 0, SEEK_END);

        if(ftell(fp) == 0)
        {
            printf("ERROR: %s is empty\n", argv[i]);
            fclose(fp);
            i++;
            continue;
        }

        fclose(fp);

        printf("INFO: %s is a valid file\n", argv[i]);

        i++;  // Move to the next command-line argument
    }
}

/*
 * Function to calculate the hash index
 * based on the first character of the word
 */
int get_index(char *word)
{
    // Check whether the first character is an uppercase letter
    if(word[0]>='A' && word[0]<='Z')
    {

        return word[0] - 'A';  // Return index from 0 to 25 for A-Z
    }
    else if(word[0]>='a' && word[0]<='z')  // Check whether the first character is a lowercase letter
    {
        return word[0] - 'a';      // Return index from 0 to 25 for a-z
    }
    else if(word[0]>='0' && word[0]<='9')    // Check whether the first character is a digit
    {
        return 26;    // Index 26 is reserved for numbers
    }
    else
    {
        return 27;      // All other special characters use index 27
    }
}

