#include <iostream>
#include <string.h>
#include <iomanip>
#include "semester.h"
#include "LoadFiles.h"

using namespace std;

void printGPASheet(vector <Semester>, int, double);

int main(){


  vector <Semester> Semesters;    //will store info for all semesters.
  int totalCredits = 0;
  int numSemesters = 0;
  double GPApoints = 0.0;
  int inp = 0;
  int choice = 0;
  cout<<"--------------------------Initial Menu-------------------------\n";
  cout<<"\t\t1 -> Start from Scratch\n";
  cout<<"\t\t2 -> Load from old file\n";
  cout<<"What would you like to do?: ";
  cin >> choice;
  if(choice == 2)
  {
    loadFiles(totalCredits, numSemesters, GPApoints, Semesters);
    choice = 1;
  }
  if(choice !=1){
    cout<<"Invalid entry\n";
    exit(0);
  }

  while(1){
    cout<<"------------------------Main Menu------------------------------\n";
    cout<<"\t\t1 -> Add a semester\n";
    cout<<"\t\t2 -> Show GPA sheet\n";
    cout<<"\t\t3 -> Save to File\n";
    cout<<"\t\t4 -> Exit\n";
    cout<<"What would you like to do? : ";
    cin>>inp;
    cin.ignore();
    switch(inp){
      case 1:
      {
        Semester a;
        string semName;
        int semNumCourses;
        cout<<"Enter a name for the semester: ";
        getline(cin, semName);
        cout<<"Enter number of courses for the semester: ";
        cin>>semNumCourses;
        a.setName(semName);
        a.setNumCourses(semNumCourses);
        a.set_courses();
        Semesters.push_back(a);
        numSemesters++;
        totalCredits += Semesters[numSemesters-1].getCredits();
        GPApoints += Semesters[numSemesters-1].getGPA();
        break;
      }
      case 2:
      {
        printGPASheet(Semesters, totalCredits, GPApoints);
        break;
      }
      case 3:
      {
        saveToFile(totalCredits, numSemesters, GPApoints, Semesters);
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
void printGPASheet(vector <Semester> semesters,int totalCredits, double GPApoints){
  cout<<"\n";
  for(int i = 0;i < semesters.size(); i++){
    semesters[i].printSemGPA();
    cout<<"\n";
  }
  if(totalCredits > 0){
    cout<<"\nTotal number of credits: "<< totalCredits <<" Total Quality points: "<<fixed<< setprecision(3)<< GPApoints<<endl;
    cout<<"Calculated GPA is "<<fixed<< setprecision(3)<< GPApoints/(double)totalCredits<<endl;
  }
  else{
    cout<<"\nTotal number of credits: 0  Total Quality points: 0.000\n";
    cout<<"Calculated GPA is N/A\n";
  }

}
