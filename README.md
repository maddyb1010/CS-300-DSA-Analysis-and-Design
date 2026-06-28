# CS 300: Data Structures and Algorithms

### Project One: Runtime and Memory Analysis

**File:** `Project One.docx`

This document compares the vector, hash table, and binary search tree for the ABCU course advising program. It includes runtime charts for loading course data into each structure, memory analysis, and a recommendation for which data structure to use in Project Two. I recommended the binary search tree because ABCU needs both a sorted course list and lookup for individual courses.

### Project Two: Course List Code

**File:** `ProjectTwo.cpp`

This is the working C++ program for ABCU advisors. It uses a binary search tree to store course data. Menu option 2 prints all courses in alphanumeric order using inorder traversal on the tree. The program also loads course data from a CSV file, prints course information and prerequisites, and handles invalid menu input.

---

## Reflection

### What was the problem you were solving in the projects for this course?

The problem was building a program for ABC University so advisors could see all computer science courses in order and look up one course to view its title and prerequisites. Course data comes from a file where each line has a course number, title, and optional prerequisite course numbers. I needed to read that file, store the courses in a data structure, and give the user a menu to load data, print the full list, or search for one course.

### How did you approach the problem? Consider why data structures are important to understand.

I worked through three milestones first with pseudocode for a vector, hash table, and binary search tree using the same file format each time. Then in Project One I compared runtime and memory for loading data into each structure and picked one for Project Two. Data structures matter because the same program can run very differently depending on how you store data. A vector is easy but slow to search. A hash table is fast for lookup but not sorted. A BST keeps course numbers in order, which helped a lot for printing the full course list.

### How did you overcome any roadblocks you encountered while going through the activities or project?

In the labs, quicksort partition and linked list remove took extra time to get the logic right. For Project Two, Visual Studio gave compiler errors about the nested Node type until I used BinarySearchTree::Node in the function definitions outside the class. I also had to open the .slnx project file instead of just the folder, and copy the CSV into the Debug folder so the program could find it when I typed the filename. Using the same load and validation logic from my milestones made Project Two easier because I was not starting from scratch.

### How has your work on this project expanded your approach to designing software and developing programs?

I plan more before I write code now. Writing pseudocode for each data structure and doing Big O analysis in Project One helped me pick the BST for a reason instead of guessing. I also think about what the user actually needs to do—load once, print a sorted list, look up one course—and choose a structure that fits those actions.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I kept separate functions for loading, printing a course, and displaying the menu instead of putting everything in main. The Course struct holds data from one file line, and the BST class handles insert, search, and inorder print. I used short comments on the harder parts and the same names from my pseudocode like goodLine and loadCourses. If I had to change to a vector or hash table later, most of the file reading and menu code would still work.

---

## Files in This Repository

| File | Description |
|------|-------------|
| Project One.docx | Runtime and memory analysis (Project One) |
| ProjectTwo.cpp | ABCU course planner with sorted course list (Project Two) |
