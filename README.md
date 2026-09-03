# Inverted Search

## 📌 Project Overview

The **Inverted Search** project is a file-based search system implemented in **C programming** using **Hash Tables and Linked Lists**.

The project creates an inverted index from multiple `.txt` files. Instead of searching every file whenever a word is queried, the program maintains a database containing each word and the files in which that word occurs.

This makes searching faster and demonstrates the practical use of **Data Structures, File Handling, Dynamic Memory Allocation, and Hashing** in C.

---

## 🎯 Objectives

* Create an inverted index from multiple text files.
* Store words efficiently using a **Hash Table**.
* Maintain file information using **Linked Lists**.
* Search for a word and display the files containing it.
* Display the complete database.
* Save the database into a file.
* Load/update the database from a previously saved file.
* Validate input files and avoid duplicate files.
* Practice dynamic memory allocation and file handling in C.

---

## 🛠️ Technologies Used

* **Programming Language:** C
* **Data Structures:**

  * Hash Table
  * Singly Linked List
* **Concepts:**

  * Pointers
  * Structures
  * Dynamic Memory Allocation
  * File Handling
  * String Handling
  * Hashing
  * Command Line Arguments
* **Compiler:** GCC
* **Platform:** Windows / Linux

---

## 📂 Project Structure

```text
Inverted_Search/
│
├── main.c
├── create_database.c
├── display_database.c
├── search_database.c
├── save_database.c
├── update_database.c
├── validate_files.c
├── insert_last.c
├── inverted.h
│
├── file1.txt
├── file2.txt
├── file3.txt
│
└── README.md
```

> File names may vary depending on the final project implementation.

---

## ⚙️ How the Project Works

The project mainly works in the following stages:

```text
             Input Text Files
                    │
                    ▼
          File Validation
                    │
                    ▼
           Create Database
                    │
                    ▼
              Hash Table
                    │
          ┌─────────┴─────────┐
          ▼                   ▼
       Word List          File List
          │                   │
          └─────────┬─────────┘
                    ▼
              Search / Display
                    │
                    ▼
             Save / Update
```

### 1. File Validation

The program accepts text files through command-line arguments.

Example:

```bash
a.exe file1.txt file2.txt file3.txt
```

The program checks:

* Whether the file has `.txt` extension.
* Whether the file can be opened.
* Whether the file is empty or valid.
* Whether the same file has already been provided.

---

### 2. Create Database

The program reads each word from the input files and stores it in a hash table.

Each hash table entry contains information such as:

```text
Index
  ↓
Word
  ↓
File Count
  ↓
File Name
  ↓
Word Count
```

For example:

```text
Word: hello

File Count: 2

File 1: file1.txt → 3 occurrences
File 2: file2.txt → 5 occurrences
```

If a word already exists in the database, its file and word counts are updated instead of creating a duplicate word entry.

---

## 🗃️ Database Representation

The project uses multiple linked-list structures to maintain the inverted index.

Conceptually:

```text
Hash Table
   │
   ├── Word
   │     │
   │     ├── File 1 → Word Count
   │     ├── File 2 → Word Count
   │     └── File 3 → Word Count
   │
   └── Word
         │
         ├── File 1 → Word Count
         └── File 2 → Word Count
```

This allows multiple files to be associated with the same word.

---

## 🔍 Search Operation

The user can search for a particular word.

Example:

```text
Enter the word to search: embedded
```

The program checks the corresponding hash-table index and displays the files containing that word.

Example output:

```text
Word: embedded
File count: 2

File Name       Word Count
--------------------------
file1.txt          3
file2.txt          5
```

If the word is not present:

```text
ERROR: Word not found in database
```

---

## 📊 Display Database

The **Display Database** option displays the complete inverted index.

Example:

```text
Index   Word       File Count       File Name       Word Count
----------------------------------------------------------------
0       apple          2            file1.txt          3
                                      file2.txt          2

1       embedded       2            file1.txt          4
                                      file3.txt          1
```

---

## 💾 Save Database

The database can be saved into a `.txt` file.

Example:

```text
Enter the file you want to save: database.txt
```

The database is stored in a structured format so that it can later be loaded using the **Update Database** operation.

Example saved format:

```text
#;0;apple;2;file1.txt;3;file2.txt;2;#
#;1;embedded;2;file1.txt;4;file3.txt;1;#
```

---

## 🔄 Update Database

The project also supports updating the database using a previously saved database file.

For example:

```text
Enter the saved database file name: database.txt
```

The program reads the saved database and reconstructs the inverted index.

This allows the user to continue working with a previously created database without creating everything from the beginning.

A new text file can then be added to the existing database.

---

## 📋 Menu

The application provides the following menu:

```text
        ::: Inverted Search Project :::

1. Create Database
2. Display Database
3. Save Database
4. Search
5. Update Database
6. Exit

Enter your choice:
```

### Option 1 — Create Database

Creates the inverted index from the input text files.

### Option 2 — Display Database

Displays the complete hash-table database.

### Option 3 — Save Database

Saves the current database into a `.txt` file.

### Option 4 — Search

Searches for a specific word in the database.

### Option 5 — Update Database

Loads a previously saved database and updates it with new information.

### Option 6 — Exit

Terminates the application.

---

## ▶️ Compilation

Compile all C source files using GCC:

```bash
gcc *.c
```

Or:

```bash
gcc *.c -o inverted_search
```

---

## 🚀 Running the Project

### Windows

```bash
a.exe file1.txt file2.txt file3.txt
```

### Linux

```bash
./inverted_search file1.txt file2.txt file3.txt
```

The files should be present in the current working directory.

---

## 🧪 Example

Suppose we have two files.

### file1.txt

```text
hello embedded systems
embedded c programming
```

### file2.txt

```text
hello world
embedded systems
```

After creating the database, searching for:

```text
embedded
```

may produce:

```text
Word: embedded
File count: 2

file1.txt → 2
file2.txt → 1
```

---

## ✨ Key Features

* ✅ Multiple file support
* ✅ Command-line file input
* ✅ `.txt` file validation
* ✅ Duplicate file detection
* ✅ Hash-table based indexing
* ✅ Linked-list based storage
* ✅ Word frequency counting
* ✅ Fast word searching
* ✅ Database display
* ✅ Database saving
* ✅ Database updating
* ✅ Dynamic memory allocation
* ✅ File handling
* ✅ Menu-driven application

---

## 🧠 Concepts Learned

Through this project, the following concepts are practically implemented:

* Hashing
* Hash Tables
* Linked Lists
* Structures
* Pointers
* Dynamic Memory Allocation
* String Manipulation
* File Handling
* Command Line Arguments
* Searching
* Database Creation
* Data Serialization
* Modular Programming

---

## 📈 Advantages

* Faster word searching compared to scanning every file individually.
* Efficient organization of word-to-file relationships.
* Supports multiple files.
* Database can be saved and reused.
* Demonstrates practical use of data structures.
* Reduces repeated file scanning during searches.

---

## 🔮 Future Enhancements

Possible improvements include:

* Case-insensitive searching.
* Support for more file formats.
* Phrase searching.
* Ranking files based on word frequency.
* Improved memory management.
* GUI-based interface.
* Search suggestions/autocomplete.
* Support for large-scale document indexing.

---

## 👨‍💻 Author

**Timmanna Kulagod**

### Project

**Inverted Search — C Programming / Data Structures**

---
