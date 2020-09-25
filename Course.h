class Course{
private:
  string name; //unique identifier.
  int credits; //betweeen 1 and 5
  string grade;

public:
  Course(){
    name = "";
    credits = 0;
    grade = "";
  }
  void setName(string name){
    this->name = name;
  }
  void setCredits(int credits){
    this->credits = credits;
  }
  void setGrade(string grade){
    this->grade = grade;
  }
  void setCourse(string name, int credits, string grade){
      this->name = name;
      this->credits = credits;
      this->grade = grade;
  }
  string getName(){
    return name;
  }
  int getCredits(){
    return credits;
  }
  string getGrade(){
    return grade;
  }

};
