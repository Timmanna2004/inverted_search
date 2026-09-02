#include "inverted.h"
/*
 * Function to add a file name to the file linked list
 * if the file is not already present.
 */
static void add_to_list(F_node **head, char *filename)
{
     // Start traversing the existing file list
    F_node *temp = *head;

    // Check whether the file already exists in the list
    while (temp != NULL)
    {
        // Compare the current file name with the given file name
        if (strcmp(temp->f_name, filename) == 0)
        {
            return;  // File already exists, so no need to add it
        }

        temp = temp->link;   // Move to the next node
    }

    // Allocate memory for a new file node
    F_node *new_node = malloc(sizeof(F_node));

    // Check whether memory allocation was successful
    if (new_node == NULL)
    {
        printf("ERROR: Memory allocation failed\n");
        return;
    }

     // Store the file name in the new node
    strcpy(new_node->f_name, filename);
    // Initialize the link of the new node
    new_node->link = NULL;

    /*
     * If the file list is empty,
     * make the new node as the first node.
     */
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        // Traverse to the last node
        temp = *head;

        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new_node; // Add the new node at the end of the list
    }
}

/*
 * Function to update the inverted database
 * using a previously saved database file
 * and newly supplied input files.
 */
int update_database(hash *HT, F_node **head)
{
    char file[30];   // Array to store the saved database file name

     // Ask the user to enter the saved database file name
    printf("Enter the saved database file name: ");
    scanf("%29s", file);

    char *ptr = strrchr(file, '.');  // Find the last occurrence of '.' in the file name

    /*
     * Check whether the entered file
     * has a .txt extension.
     */
    if (ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("ERROR: %s is not a .txt file\n", file);
        return FAILURE;
    }

    FILE *fp = fopen(file, "r");  // Open the saved database file in read mode

    if (fp == NULL)    // Check whether the file was opened successfully
    {
        printf("ERROR: Unable to open %s\n", file);
        return FAILURE;
    }

    /* Validate database file */
    int ch = fgetc(fp);

    if (ch != '#')
    {
        printf("ERROR: Invalid database file\n");
        fclose(fp);
        return FAILURE;
    }

    rewind(fp);

    /*
     * Keep the NEW files before loading the old database.
     */
    F_node *new_files = *head;

    int index;
    int fcount;
    int wcount;

    char word[25];
    char filename[20];

    /*
     * Load OLD database.
     *
     * Space before # is IMPORTANT because every
     * database record after the first one starts
     * after a newline.
     */
    while (fscanf(fp, " #;%d;%24[^;];%d;",
                  &index, word, &fcount) == 3)
    {
        if (index < 0 || index >= 28)
        {
            printf("ERROR: Invalid hash index\n");
            fclose(fp);
            return FAILURE;
        }

        M_node *main_n = malloc(sizeof(M_node));

        if (main_n == NULL)
        {
            printf("ERROR: Memory allocation failed\n");
            fclose(fp);
            return FAILURE;
        }

        strcpy(main_n->word, word);
        main_n->file_count = fcount;
        main_n->sub_link = NULL;

        /*
         * Insert main node
         */
        main_n->main_link = HT[index].H_link;
        HT[index].H_link = main_n;

        S_node *last = NULL;

        /*
         * Read sub nodes
         */
        for (int i = 0; i < fcount; i++)
        {
            if (fscanf(fp, "%19[^;];%d;#",
                       filename, &wcount) != 2)
            {
                printf("ERROR: Corrupted database file\n");
                fclose(fp);
                return FAILURE;
            }

            S_node *sub_n = malloc(sizeof(S_node));

            if (sub_n == NULL)
            {
                printf("ERROR: Memory allocation failed\n");
                fclose(fp);
                return FAILURE;
            }

            strcpy(sub_n->filename, filename);
            sub_n->word_count = wcount;
            sub_n->sub_link = NULL;

            if (main_n->sub_link == NULL)
            {
                main_n->sub_link = sub_n;
            }
            else
            {
                last->sub_link = sub_n;
            }

            last = sub_n;
        }
    }

    fclose(fp);

    /*
     * Process ONLY newly supplied files.
     *
     * Example:
     * a.exe f3.txt
     *
     * new_files -> f3.txt
     */
    create_database(HT, new_files);

    printf("INFO: Database updated successfully\n");

    return SUCCESS;
}