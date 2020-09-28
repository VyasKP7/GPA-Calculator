
#include <vector>
#include <string.h>
#include <iomanip>
#include "Course.h"
using namespace std;
class Semester{
private:
  string name;      //name of semester, unique  
  int numCourses;   //user input
  int credits;     //calculated
  double semesterGPA;  //calculated
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
public:
  vector <Course> courses;    //user input
  Semester(){
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
  void set_courses(){
    for(int i=0; i<numCourses;i++){
      string Name, Grade;
      int Credits;
      cout<<"\nEnter course information for course "<<i+1<<endl;
      cout<<"Enter name of course: ";
      cin.ignore();
      getline(cin, Name);
      cout<<"Enter the number of credits for this course: ";
      cin>>Credits;
      cin.ignore();
      cout<<"Enter the grade recieved for this course: ";
      cin>> Grade;
      add_course(Name, Credits, Grade);
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
