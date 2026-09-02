#include "inverted.h"
/*
 * Function to save the complete inverted database
 * into a .txt file.
 */
void save_database(hash *HT)
{
    char F_name[100]; // Array to store the name of the file

    // Ask the user to enter the file name
    printf("Enter the file you want to save: ");
    scanf("%49s", F_name);

    // Find the last occurrence of '.' in the file name
    char *ptr = strrchr(F_name, '.');

    /*
     * Check whether the file name has a .txt extension
     */
    if (ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("ERROR: %s is not a .txt file\n", F_name);
        return;
    }

    FILE *fptr = fopen(F_name, "w");    // Open the file in write mode

     // Check whether the file was opened successfully
    if (fptr == NULL)
    {
        printf("ERROR: File open failed\n");
        return;
    }

    /*
     * Traverse all 28 indexes of the hash table
     * and save the database contents.
     */
    for (int i = 0; i < 28; i++)
    {
        // Skip the index if there is no main node
        if (HT[i].H_link == NULL)
        {
            continue;
        }

        // Start traversing the main node list
        M_node *m_temp = HT[i].H_link;

        while (m_temp != NULL)
        {
            /*
             * Save the hash index, word and
             * number of files containing the word.
             */
            fprintf(fptr, "#;%d;%s;%d;",i, m_temp->word, m_temp->file_count);

            S_node *s_temp = m_temp->sub_link;  // Start traversing the sub node list

            while (s_temp != NULL)
            {
                /*
                 * Save the file name and
                 * number of occurrences of the word.
                 */
                fprintf(fptr, "%s;%d;#", s_temp->filename, s_temp->word_count);

                s_temp = s_temp->sub_link;  // Move to the next sub node
            }

            fprintf(fptr, "\n");   // Move to the next line in the saved file

            m_temp = m_temp->main_link;   // Move to the next main node
        }
    }

    fclose(fptr);    // Close the saved database file

    printf("INFO: Database saved successfully\n"); // Display successful save message
}