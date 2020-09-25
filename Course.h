class Course{
private:
  string name; //unique identifier.
  int credits; //betweeen 1 and 5
  string grade;

public:
  void setName(string name){
    this->name = name;
  }
  void setCredits(int credits){
    this->credits = credits;
  }
};
