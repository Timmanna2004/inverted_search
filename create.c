#include "inverted.h"
/*
 * Function to create the inverted search database
 * using the list of input files.
 */
void create_database(hash *HT, F_node *head)
{
    // Temporary pointer to traverse the file linked list
    F_node *f_temp = head;

    // Process each file in the linked list
    while(f_temp != NULL)
    {
        // Open the current file in read mode
        FILE *fp = fopen(f_temp->f_name, "r");

        if(fp == NULL)     // Check whether the file was opened successfully
        {
            printf("ERROR: Unable to open %s\n", f_temp->f_name);
            f_temp = f_temp->link;  // Move to the next file
            continue;
        }

        char word[100];    // Array to store each word read from the file

        while(fscanf(fp, "%s", word) == 1)   // Read words from the file one by one
        {
            // Find the hash index for the current word
            int index = get_index(word);

            M_node *m_temp = HT[index].H_link;    // Start searching for the word in the hash table
            M_node *prev_m = NULL;                // Previous main node pointer

              /*
             * Search for the word in the main linked list
             * of the selected hash index.
             */
            while(m_temp != NULL)
            {
                // Check whether the word already exists
                if(strcmp(m_temp->word, word) == 0)
                {
                    break;
                }
                prev_m = m_temp;            // Move previous pointer to current node
                m_temp = m_temp->main_link;    // Move to the next main node
            }
             /*
             * If the word does not exist,
             * create a new main node.
             */
            if(m_temp == NULL)
            {
                M_node *new_m = malloc(sizeof(M_node));  // Allocate memory for a new main node

                // Check whether memory allocation was successful
                if(new_m == NULL)
                {
                    fclose(fp);
                    return;
                }
 
                strcpy(new_m->word, word);  // Store the word in the main node
                new_m->file_count = 1;       // First occurrence of the word
                new_m->main_link = NULL;     // Initialize main node link

                S_node *new_s = malloc(sizeof(S_node));   // Allocate memory for a new sub node

                if(new_s == NULL) // Check whether memory allocation was successful
                {
                    free(new_m);
                    fclose(fp);
                    return;
                }

                strcpy(new_s->filename, f_temp->f_name);  // Store the file name in the sub node
                new_s->word_count = 1;                  // First occurrence of the word in this file
                new_s->sub_link = NULL;                // Initialize sub node link

                new_m->sub_link = new_s;               // Link the sub node to the main node

                /*
                 * If the hash index is empty,
                 * insert the new main node as the first node.
                 */
                if(HT[index].H_link == NULL)
                {
                    HT[index].H_link = new_m;    
                }
                else
                {
                    prev_m->main_link = new_m;   // Insert the new main node at the end
                }
            }

             /*
             * If the word already exists in the main node,
             * search for the current file in its sub linked list.
             */
            else
            {
                // Start traversing the sub node list
                S_node *s_temp = m_temp->sub_link;
                S_node *prev_s = NULL;     // Previous sub node pointer

                while(s_temp != NULL)        // Search for the current file name
                {
                    // Check whether the file already exists
                    if(strcmp(s_temp->filename, f_temp->f_name) == 0)
                    {
                        break;
                    }

                    prev_s = s_temp;    // Move previous pointer to current node
                    s_temp = s_temp->sub_link;    // Move to the next sub node
                }


                /*
                 * If the file already contains the word,
                 * increment its word count.
                 */
                if(s_temp != NULL)
                {
                    s_temp->word_count++;
                }

                /*
                 * If the file is not present,
                 * create a new sub node for the file.
                 */
                else
                {
                    // Allocate memory for a new sub node
                    S_node *new_s = malloc(sizeof(S_node));

                    // Check whether memory allocation was successful
                    if(new_s == NULL)
                    {
                        fclose(fp);
                        return;
                    }

                    strcpy(new_s->filename, f_temp->f_name);   // Store the file name
                    new_s->word_count = 1;                   // First occurrence of the word in this file
                    new_s->sub_link = NULL;           // Initialize sub node link

                    /*
                     * If there is no sub node,
                     * make the new node the first sub node.
                     */
                    if(m_temp->sub_link == NULL)
                    {
                        m_temp->sub_link = new_s;
                    }
                    else
                    {
                        // Add the new sub node at the end
                        prev_s->sub_link = new_s;
                    }

                    m_temp->file_count++;   // Increase the number of files containing the word
                }
            }
        }
 
        fclose(fp);  // Close the current file

        f_temp = f_temp->link;    // Move to the next file in the file linked list
    }

    printf("INFO: Database created successfully\n");    // Display success message after database creation
}
