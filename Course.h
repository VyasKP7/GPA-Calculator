#include <iostream>
using namespace std;
class Course{
private:
  string name; //unique identifier.
  int credits; //betweeen 1 and 5
  string grade;
  float gradef;
  void setGradef();
public:
  Course(){
    name = "";
    credits = 0;
    grade = "";
    gradef = 0.0;
  }
  void setName(string name){
    this->name = name;
  }
  void setCredits(int credits){
    this->credits = credits;
  }
  void setGrade(string grade){
    this->grade = grade;
    setGradef();
  }
  void setCourse(string name, int credits, string grade){
      this->name = name;
      this->credits = credits;
      this->grade = grade;
      setGradef();
  }
  string getName(){
    return name;
  }
  int getCredits(){
    return credits;
  }
  float getGradef(){
    return gradef;
  }
};

void Course::setGradef(){
    if(grade == "A+"){
      gradef = 4.33;
    }
    else if(grade == "A"){
      gradef = 4.00;
    }
    else if(grade == "A-"){
      gradef = 3.67;
    }
    else if(grade == "B+"){
      gradef = 3.33;
    }
    else if(grade == "B"){
      gradef = 3.00;
    }
    else if(grade == "B-"){
      gradef = 2.67;
    }
    else if(grade == "C+"){
      gradef = 2.33;
    }
    else if(grade == "C"){
      gradef = 2.00;
    }
    else if(grade == "C-"){
      gradef = 1.67;
    }
    else if(grade == "D+"){
      gradef = 1.33;
    }
    else if(grade == "D"){
      gradef = 1.00;
    }
    else if(grade == "D-"){
      gradef = 0.67;
    }
    else
      gradef = 0.0;
}
