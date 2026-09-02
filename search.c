#include "inverted.h"
/*
 * Function to search for a given word
 * in the inverted database.
 */
int search_database(hash *HT)
{
    // Array to store the word entered by the user
    char word[50];

    // Ask the user to enter the word to search
    printf("Enter the word you want to search: ");
    scanf("%49s", word);

    unsigned int index = get_index(word); // Calculate the hash index using the first character of the word

     /*
     * Check whether the selected hash index
     * contains any main node.
     */
    if (HT[index].H_link == NULL)
    {
        printf("\"%s\" not found\n", word);
        return DATA_NOT_FOUND;
    }

    // Start traversing the main node list
    M_node *m_temp = HT[index].H_link;

    while (m_temp != NULL)
    {
        // Compare the searched word with the current main node word
        if (strcmp(m_temp->word, word) == 0)
        {
            int file_count = 0;  // Variable to count the number of files containing the word

             // Array to store the list of file names and word counts
            char file_list[500] = "";

            S_node *s_temp = m_temp->sub_link;  // Start traversing the sub node list

            while (s_temp != NULL)
            {
                char entry[70];   // Temporary array to store one file entry

                /*
                 * Create an entry containing the file name
                 * and the number of occurrences of the word.
                 */
                snprintf(entry, sizeof(entry),"%s%s(%d)",file_count > 0 ? ", " : "",s_temp->filename,s_temp->word_count);
                strncat(file_list, entry,sizeof(file_list) - strlen(file_list) - 1);

                file_count++;    // Increment the file count

                // Move to the next sub node
                s_temp = s_temp->sub_link;
            }

            printf("+---------+----------------------+------------+---------------------------+------------+\n");
            printf("| Index   | Word                 | File Count | File Name                 | Word Count |\n");
            printf("+---------+----------------------+------------+---------------------------+------------+\n");

            printf("| [%-3u]   | %-20s | %-10d | %-25s | %-10d |\n",index, m_temp->word, file_count, file_list, m_temp->file_count);

            printf("+---------+----------------------+------------+---------------------------+------------+\n");

            return SUCCESS;   // Return success when the word is found
        }

        m_temp = m_temp->main_link;    // Move to the next main node
    }

    printf("\"%s\" not found\n", word);   // Display message when the searched word is not found

    return DATA_NOT_FOUND;    // Return data not found status
}