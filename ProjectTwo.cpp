//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Madison Burnsworth
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project Two - ABCU Course Advising Program (Binary Search Tree)
//============================================================================

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

class BinarySearchTree {

private:
    struct Node {
        Course course;
        Node* left;
        Node* right;

        Node(Course aCourse) {
            course = aCourse;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    // insert a node into the tree
    Node* insertNode(Node* node, Course course);

    // search for a course by course number
    Node* searchNode(Node* node, string courseNumber);

    // print courses in order
    void inOrderPrint(Node* node);

    // delete all nodes
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    Course* Search(string courseNumber);
    void PrintAll();
    void Clear();
    bool IsEmpty();
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(BinarySearchTree::Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinarySearchTree::Clear() {
    destroyTree(root);
    root = nullptr;
}

bool BinarySearchTree::IsEmpty() {
    return root == nullptr;
}

BinarySearchTree::Node* BinarySearchTree::insertNode(BinarySearchTree::Node* node, Course course) {
    if (node == nullptr) {
        return new Node(course);
    }

    if (course.courseNumber < node->course.courseNumber) {
        node->left = insertNode(node->left, course);
    }
    else if (course.courseNumber > node->course.courseNumber) {
        node->right = insertNode(node->right, course);
    }

    return node;
}

void BinarySearchTree::Insert(Course course) {
    root = insertNode(root, course);
}

BinarySearchTree::Node* BinarySearchTree::searchNode(BinarySearchTree::Node* node, string courseNumber) {
    while (node != nullptr) {
        if (node->course.courseNumber == courseNumber) {
            return node;
        }
        else if (courseNumber < node->course.courseNumber) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return nullptr;
}

Course* BinarySearchTree::Search(string courseNumber) {
    Node* node = searchNode(root, courseNumber);
    if (node != nullptr) {
        return &(node->course);
    }
    return nullptr;
}

void BinarySearchTree::inOrderPrint(BinarySearchTree::Node* node) {
    if (node != nullptr) {
        inOrderPrint(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        inOrderPrint(node->right);
    }
}

void BinarySearchTree::PrintAll() {
    inOrderPrint(root);
}

// split a comma-separated line into tokens, skip empty fields
vector<string> tokenizeLine(string line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ',')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

// convert course number input to uppercase
string toUpperCase(string str) {
    for (unsigned i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

// check if a course number is in the list of all course numbers from the file
bool courseExists(vector<string>& allCourseNumbers, string courseNumber) {
    for (unsigned i = 0; i < allCourseNumbers.size(); i++) {
        if (allCourseNumbers[i] == courseNumber) {
            return true;
        }
    }
    return false;
}

// load courses from a csv file into the binary search tree
void loadCourses(string csvPath, BinarySearchTree* bst) {
    ifstream courseFile(csvPath);

    if (!courseFile.is_open()) {
        cout << "Unable to open file " << csvPath << endl;
        return;
    }

    bst->Clear();

    vector<string> fileLines;
    string line;

    while (getline(courseFile, line)) {
        if (!line.empty()) {
            fileLines.push_back(line);
        }
    }

    courseFile.close();

    vector<string> allCourseNumbers;

    // first pass - collect all course numbers for prerequisite checks
    for (unsigned i = 0; i < fileLines.size(); i++) {
        vector<string> tokens = tokenizeLine(fileLines[i]);
        if (tokens.size() < 2) {
            cout << "Invalid course line: " << fileLines[i] << endl;
        }
        else {
            allCourseNumbers.push_back(tokens[0]);
        }
    }

    // second pass - build course objects and insert into tree
    for (unsigned i = 0; i < fileLines.size(); i++) {
        vector<string> tokens = tokenizeLine(fileLines[i]);

        if (tokens.size() < 2) {
            continue;
        }

        Course newCourse;
        newCourse.courseNumber = tokens[0];
        newCourse.title = tokens[1];
        bool goodLine = true;

        for (unsigned p = 2; p < tokens.size(); p++) {
            if (!courseExists(allCourseNumbers, tokens[p])) {
                cout << "Prerequisite " << tokens[p] << " not found in file." << endl;
                goodLine = false;
                break;
            }
            newCourse.prerequisites.push_back(tokens[p]);
        }

        if (goodLine) {
            bst->Insert(newCourse);
        }
    }

    cout << fileLines.size() << " courses loaded." << endl;
}

// print one course and its prerequisite course numbers and titles
void printCourse(BinarySearchTree* bst, string courseNumber) {
    Course* course = bst->Search(courseNumber);

    if (course == nullptr) {
        cout << courseNumber << " not found." << endl;
        return;
    }

    cout << course->courseNumber << ", " << course->title << endl;

    if (course->prerequisites.size() > 0) {
        cout << "Prerequisites: ";
        for (unsigned i = 0; i < course->prerequisites.size(); i++) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;

        for (unsigned i = 0; i < course->prerequisites.size(); i++) {
            Course* prereq = bst->Search(course->prerequisites[i]);
            if (prereq != nullptr) {
                cout << prereq->courseNumber << ", " << prereq->title << endl;
            }
        }
    }
}

void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

int main() {

    BinarySearchTree* courseTree = new BinarySearchTree();
    string csvPath;
    string courseKey;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << choice << " is not a valid option." << endl;
            continue;
        }

        switch (choice) {

        case 1:
            cout << "What is the name of the input file? ";
            cin.ignore();
            getline(cin, csvPath);
            loadCourses(csvPath, courseTree);
            break;

        case 2:
            if (courseTree->IsEmpty()) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl;
                courseTree->PrintAll();
            }
            break;

        case 3:
            if (courseTree->IsEmpty()) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                cin.ignore();
                getline(cin, courseKey);
                courseKey = toUpperCase(courseKey);
                printCourse(courseTree, courseKey);
            }
            break;

        case 9:
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    cout << "Thank you for using the course planner!" << endl;

    delete courseTree;

    return 0;
}
