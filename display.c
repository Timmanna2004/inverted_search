
#include "inverted.h"
/*
 * Function to display the complete inverted database
 * stored in the hash table.
 */
void display_database(hash *HT)
{
    printf("+---------+----------------------+------------+---------------------------+------------+\n");
    printf("| Index   | Word                 | File Count | File Name                 | Word Count |\n");
    printf("+---------+----------------------+------------+---------------------------+------------+\n");

    for(int i=0;i<28;i++)  // Traverse all 28 hash table indexes
    {
        // Skip the index if there is no main node
        if(HT[i].H_link==NULL)
        {
            continue;
        }

        // Start traversing the main node list
        M_node *m_temp = HT[i].H_link;
        while(m_temp!=NULL)
        {
            S_node *s_temp=m_temp->sub_link; // Start traversing the sub node list

            while(s_temp!=NULL)
            {
                /*
                 * Display hash index, word, number of files,
                 * file name and word count.
                 */

                printf("| [%-5d] | %-20s | %-10d | %-25s | %-10d |\n",
                       i, m_temp->word, m_temp->file_count, s_temp->filename, s_temp->word_count);


                s_temp = s_temp->sub_link; // Move to the next sub node
            }
            m_temp=m_temp->main_link;    // Move to the next main node
        }  
    }

    printf("+---------+----------------------+------------+---------------------------+------------+\n");
}