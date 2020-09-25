# include <iostream>
#include <string.h>
# include "semester.h"
using namespace std;
int main(){


  vector <Semester> Semesters;    //will store info for all semesters.
  int inp = 0;
  while(1){
    cout<<"----------------------------Menu------------------------------\n";
    cout<<"\t\t1 -> Add a semester\n";
    cout<<"\t\t2 -> Calculate GPA\n";
    cout<<"\t\t3 -> Save to File\n";
    cout<<"\t\t4 -> Exit\n";
    cout<<"What would you like to do? :\n";
    cin>>inp;
    cin.ignore();
    switch(inp){
      case 1:
      {
        Semester a;
        string semName;
        int semNumCourses;
        cout<<"Enter a name for the semester:\n";
        getline(cin, semName);
        cout<<"Enter number of courses for the semester:\n";
        cin>>semNumCourses;
        a.setName(semName);
        a.setNumCourses(semNumCourses);
        a.set_courses();
        break;
      }
      case 2:
      {
        //Add later
        break;
      }
      case 3:
      {
        //Add later
        break;
      }
      case 4:
      {
        exit(0);
        break;
      }
      default:
        cout<<"Invalid input, valid inputs are (1,2,3 and 4).\n";

    }

  }
  return 0;
}
