#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include "semester.h"
using namespace std;

void loadFiles(int &totalCredits,int &numSemesters,double &GPApoints,vector <Semester> &Semesters){
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
        cout << count+1 << ". "<<word << "\n";
        fileList.push_back(word);
        count++;
    }
    file.close();
    cout<<"\nWhich would you like choose ?: ";
    cin>>input;
    if(input < 0 || input > count){
      cout<<"Invalid input.\n";
      continue;
    }
    if(input == 0){
       cout<<"Proceeding to other menu.\n";
      return;
    }
    string chosenFile = fileList[input-1];
    break;
  }
  //Deal with inner file.

}

void saveToFile(int totalCredits,int numSemesters,double GPApoints,vector <Semester> Semesters){    //Save these value to csv file.
  cout<<"-------------------------Save Menu-----------------------------\n";
  cout<<"0. Don't want to save to a file (exit)\n";

}
