#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void loadFiles(int &totalCredits,int &numSemesters,double &GPApoints,vector <Semester> &Semesters){       //Loads Files from save file.
  ifstream myFile;
  string chosenFile;
  myFile.open("Save.txt", ios::binary);       //file that stores the list of saved files

  if (!myFile) {
    cerr << "Save.txt is empty";
    exit(1);   // call system to stop
  }
  myFile.seekg(0, ios::end);
  int file_size = myFile.tellg(); //if 0 then no files in Save.txt
  if(file_size == 0)
  {
    cout<<"There are no previous files that have been saved. Proceeding to other menu.\n";
    return;
  }
  myFile.close();

  while(1){
    int input;
    ifstream file;
    string word;
    vector <string> fileList;   //stores file list
    int count = 0;
    file.open("Save.txt");
    cout<<"-------------------------File Menu-----------------------------\n";
    cout<<"0. Don't want to load any of these files (exit)\n";
    while (file >> word) {      //prints the files one-by-one
        cout << count+1 << ". Load "<<word << "\n";
        fileList.push_back(word);
        count++;
    }
    file.close();
    cout<<"\nWhat would you like to do? : ";
    cin>>input;
    if(input < 0 || input > count){      //wrong input
      cout<<"Invalid input.\n";
      continue;
    }
    if(input == 0){
       cout<<"Proceeding to main menu.\n";
      return;
    }
    chosenFile = fileList[input-1];
    break;
  }

  ifstream file;
  file.open(chosenFile);
  string NumSemestersS;
  getline(file, NumSemestersS); //store first line only contains num semesters in the variable.
  int NumSemesters = stoi(NumSemestersS);

  for(int i=0;i<NumSemesters;i++){    //For each semesters
    string Fline;
    vector <string> resultS;
    getline(file, Fline);
    stringstream s_streamS(Fline);      //Handle line at top of semester
    while(s_streamS.good()) {
      string substr;
      getline(s_streamS, substr, ','); //get first string delimited by comma
      resultS.push_back(substr);
   }
   //cout<<"Over Here."<<resultS[0];
   //return;
   string semName = resultS[0];
   int numCourses = stoi(resultS[1]);
   Semester a;
   a.setName(semName);
   a.setNumCourses(numCourses);
   for(int j=0; j <numCourses ; j++){  //for each course in Semester
     string line;
     vector <string> resultC;
     getline(file, line);
     stringstream s_streamC(line);
     while(s_streamC.good()) {
       string substr;
       getline(s_streamC, substr, ','); //get first string delimited by comma
       resultC.push_back(substr);
    }
    string courseName = resultC[0];
    int numCredits = stoi(resultC[1]);
    string grade = resultC[2];
    a.add_course(courseName, numCredits, grade);
   }
   a.CalculateGPA();
   Semesters.push_back(a);
   numSemesters++;
   totalCredits += Semesters[numSemesters-1].getCredits();
   GPApoints += Semesters[numSemesters-1].getGPA();
  }
  file.close();
  cout<<"File loaded. Proceeding to Main Menu.\n";
  return;

}

void saveToFile(int totalCredits,int numSemesters,double GPApoints,vector <Semester> Semesters){    //Save these values to csv file.
  int input;

  while(1){
    cout<<"-------------------------Save Menu-----------------------------\n";
    cout<<"0. Don't want to save to a file (exit)\n";
    cout<<"1. Save to a new file\n";
    cout<<"2. Save to an existing file\n";
    cout<<"\nWhat would you like to do? : ";
    cin>>input;
    if(input < 0 || input > 2){     //wrong input
      cout<<"Invalid input.\n";
      continue;
    }
    if(input == 0){      //exit case
       cout<<"Proceeding back to main menu.\n";
      return;
    }
    if(input == 1){      //New file case.
      string fileName;
      cout<<"Enter the name you want to give the new file? : ";
      cin >> fileName;
      ofstream myFile(fileName);      //creates new file named fileName
      ifstream file;
      string word;
      vector <string> fileList;   //stores file list
      int count = 0;
      file.open("Save.txt");
      while (file >> word) {      //Stores the files one-by-one
          fileList.push_back(word);
          count++;
      }
      file.close();
      int found = 0;
      for(int i=0;i<count;i++){
        if(fileList[i] == fileName){
          cout<<"File already exists. Returning to Save menu\n";
          found=1;
        }
      }
      if(found==1)
        continue;

      myFile << numSemesters <<"\n";   //first line will store the number of semesters contained in the file.

      for(int i=0 ;i <numSemesters; i++) {    //write all semesters to file
        myFile << Semesters[i].getName()<<","<< Semesters[i].getNumCourses()<<"\n";      // First line of each semester contains Name and numCourses.
        for(int j=0; j <Semesters[i].getNumCourses();j++){    //write each course to file
          myFile << Semesters[i].courses[j].getName()<<","<< Semesters[i].courses[j].getCredits() << ","<< Semesters[i].courses[j].getGrade()<<"\n";
        }
      }
      cout<<"Written to file. Proceeding back to main menu.\n";

      myFile.close();


      //Add new file to Save.txt.

      ofstream oFile;
      oFile.open("Save.txt", ios::app);
      oFile<<fileName;

      oFile.close();

      return;
    }
    if(input == 2){
      ifstream myFile;
      myFile.open("Save.txt", ios::binary);       //file that stores the list of saved files

      if (!myFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
      }
      myFile.seekg(0, ios::end);
      int file_size = myFile.tellg(); //if 0 then no files in Save.txt
      if(file_size == 0)
      {
        cout<<"There are no previous files that have been saved.\n";
        continue;
      }
      myFile.close();

      while(1){ //inner loop to handle choice of files
        int choice;
        ifstream file;
        string word;
        vector <string> fileList;   //stores file list
        int count = 0;
        file.open("Save.txt");
        cout<<"-------------------------File Menu-----------------------------\n";
        cout<<"0. Don't want to save to any of these files (exit)\n";
        while (file >> word) {      //prints the files one-by-one
            cout << count+1 << ". Save to "<<word << "\n";
            fileList.push_back(word);
            count++;
        }
        file.close();
        cout<<"\nWhat would you like to do? : ";
        cin>>choice;
        if(choice < 0 || choice > count){      //wrong input
          cout<<"Invalid input.\n";
          continue;
        }
        if(choice == 0){
           cout<<"Returning to Save menu.\n";
          break;
        }
        string chosenFileName = fileList[choice-1];
        ofstream myFile(chosenFileName);      //creates new file named fileName

        myFile << numSemesters <<"\n";   //first line will store the number of semesters contained in the file.

        for(int i=0 ;i <numSemesters; i++) {    //write all semesters to file
          myFile << Semesters[i].getName()<<","<< Semesters[i].getNumCourses()<<"\n";      // First line of each semester contains Name and numCourses.
          for(int j=0; j <Semesters[i].getNumCourses();j++){    //write each course to file
            myFile << Semesters[i].courses[j].getName()<<","<< Semesters[i].courses[j].getCredits() << ","<< Semesters[i].courses[j].getGrade()<<"\n";
          }
        }
        cout<<"Written to file. Proceeding back to main menu.\n";
        myFile.close();

        return;
      }
    }
  }
}
