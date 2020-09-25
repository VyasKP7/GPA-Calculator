#include <iostream>
#include <vector>
#include<string.h>
#include "Course.h"
class Semester{
private:
  string name;      //name of semester, unique
  vector <Course> courses;    //user input
  int numCourses;   //user input
  int credits;     //calculated
  float semesterGPA;  //calculated
public:
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
  void add_course(string Name,int Credits ,string Grade){
    Course temp;
    temp.setCourse(Name, Credits, Grade);
    courses.push_back(temp);
  }
};
