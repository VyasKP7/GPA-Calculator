#include <iostream>
#include<string.h>
#include "Course.h"
class Semester{
private:
  string name;      //name of semester, unique
  CDA <Course>
  int credits;
  float semesterGPA;
public:
  Semester(){
    this->name = "";
  }
  Semester(string name){
    this->name = name;
  }
  void setName(string name){
    this->name = name;
  }
  string getName(){
    return name;
  }
};
