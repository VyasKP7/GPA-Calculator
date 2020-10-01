
#include <vector>
#include <string.h>
#include <iomanip>
#include "Course.h"
using namespace std;
int errorCheck(string inp);
class Semester{
private:
  string name;      //name of semester, unique
  int numCourses;   //user input
  int credits;     //calculated
  double semesterGPA;  //calculated

public:
  vector <Course> courses;    //user input
  Semester(){        //Basic Constructor
    this->name = "";
    numCourses = 0;
    credits = 0;
    semesterGPA = 0.0;
  }
  void setName(string name){
    this->name = name;
  }
  void setNumCourses(int numCourses){
    this->numCourses = numCourses;
  }
  string getName(){
    return name;
  }
  int getNumCourses(){
    return numCourses;
  }
  int getCredits(){
    return credits;
  }
  double getGPA(){
    return semesterGPA;
  }
  void add_course(string Name,int Credits ,string Grade){     //Adds course to courses
    Course temp;
    temp.setCourse(Name, Credits, Grade);
    courses.push_back(temp);
  }
  void CalculateGPA(){
    semesterGPA = 0.0;
    credits = 0;
    for(int i=0; i < numCourses; i++){
      credits += courses[i].getCredits();
    }
    for(int i=0; i < numCourses; i++){
      semesterGPA += courses[i].getCredits()*courses[i].getGradef();
    }
  }
  void set_courses(){           //User Loop to input courses
    for(int i=0; i<numCourses;i++){
      string Name, Grade;
      int Credits;
      cout<<"\nEnter course information for course "<<i+1<<endl;
      cout<<"Enter name of course: ";
      cin.ignore();
      getline(cin, Name);
      cout<<"Enter the number of credits for this course: ";
      string NUMS;
      cin >> NUMS;
      Credits = errorCheck(NUMS);
      if(Credits != -1){
        cin.ignore();
        cout<<"Enter the grade recieved for this course: ";
        cin>> Grade;
      }
      add_course(Name, Credits, Grade);
      if(Credits == -1){
        return;
      }
    }
    CalculateGPA();
  }
  void printSemGPA(){
    cout << "Semester : " << name<< endl;
    for (int i=0; i <numCourses; i++){
      cout <<"Course "<< i+1<<". Name: "<<courses[i].getName()<<" Credits: "<<courses[i].getCredits()<<" GPA points:"<<courses[i].getGradef()<<endl;
    }
    cout<<"Semester Credits : "<< credits<<"        Semester GPA : "<< fixed<< setprecision(3)<< (double)semesterGPA/credits<<endl;
  }
};

int errorCheck(string inp){
  int num = 0;
  int badInput = 0;
  for (int i = 0; i < inp.size(); i++){
    if(!isdigit(inp[i])){
      badInput = 1;
      break;
    }
  }
  if(badInput == 1)
    return -1;
  num = stoi(inp);
  if(num < 1)
    return -1;

  return num;
}
