/*
Ben Wasserman
2280906
wasse114@mail.chapman.edu
CPSC 350 Section 3
Assignment #5: Student and Faculty Database

Purpose of source file: This is the main source file. Basically, it just
initializes an instance of the menu class, checks to see if the studentTable
and facultyTable exist, and then it calls the method mainMenu. From here
the rest of the program is abstracted in Menu.
*/

#include <iostream>
#include <fstream>
#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"
#include "Menu.h"

using namespace std;

/*
This will initialize the menu class and call a couple methods. The first method
checks to see if studentTable and facultyTable exist, and it reads in those files
if they do. Then mainMenu is called, which runs the body of the program.
*/
int main()
{
  Menu q;
  q.checkFile();
  q.mainMenu();
}
