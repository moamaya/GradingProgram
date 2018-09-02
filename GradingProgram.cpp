//
//  project1.cpp
//  Project 1
//  Marlo Amaya

//  This program will take input of grades from a txt file and output a file named finalgrades.txt

//  *** Please change file paths before running ***
//  input file path is found in readGrades function parameters used within main()
//  output file path is found at end of file within the writeFinalGrades() function


#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//assign the global matrix for grades
double grades[100][100];

//setup prototype functions
void readGrades(string a,int b,int c);
void getWeights(double a[], int b);
void getAvgsOfExams(double a[], int b , int c);
void getAvgsOfStudents(double a[], double b[], int c, int d);
void writeFinalGrades(double a[], double b[],int c, int d);

// MAIN FUNCTION
int main()
{
    //Initialize the reference values
    int no_OfExams = 0;
    cout << "Enter the number of Exams: ";
    cin >> no_OfExams;
    
    int no_OfStudents;
    cout << "Enter the number of Students: ";
    cin >> no_OfStudents;
    
    double weights[no_OfExams];
    double examAvgs[no_OfExams];
    double studentAvgs[no_OfStudents];
    
    //Call the weights function to get user input
    getWeights(weights,no_OfExams);
    
    //read the file, and input known # of students and grades
    readGrades("/Users/MarloAmaya/Desktop/Grades.txt",no_OfStudents,no_OfExams);
    
    //Call the average function
    getAvgsOfExams(examAvgs,no_OfExams,no_OfStudents);
    //cout << examAvgs[2] <<"\n";
    
    //Call the get students averages function
    getAvgsOfStudents(studentAvgs, weights, no_OfExams, no_OfStudents);
    //cout << studentAvgs[0] << "\n";
    
    //Write the final grades to a new txt file
    writeFinalGrades(examAvgs, studentAvgs, no_OfExams, no_OfStudents);
    
    return 0;
}

// READ GRADES FUNCTION
void readGrades(string fileName, int numOfStudents, int numOfGrades)
{
    string s;
    string line[numOfStudents];
    ifstream inStream;
    // double grades[numOfStudents][numOfGrades]; (ignore this)
    
    inStream.open(fileName);
    
    if (inStream.fail())
    {
        cerr << "Unable to open file Grades.txt";
        exit(1);   // call system to stop
    }
    int i = 0;
    while (getline(inStream,s))
    {
        line[i] = s;
        i++;
    }
    
    int n;
    for (int i = 0; i<numOfStudents;i++)
    {
        stringstream ssin(line[i]);
        int j = 0;
        //cout << "\n" << endl;
        while(ssin >> n)
        {
            grades[i][j] = n;
            //cout << grades[i][j] << " ";
            j++;
        }
    }

    inStream.close();

}

// GET WEIGHTS FUNCTION (she gave us this in class)
void getWeights(double weight[], int no_ofexams)
{
    cout << "Enter weight value for each exam:\n";
    for (int i=0; i< no_ofexams; i++)
        cin >> weight[i];
}

// GET AVERAGE FUNCTION
void getAvgsOfExams(double examAvgs[], int numOfExams, int numOfStudents)
{
    for (int j=0; j<numOfExams; j++) {
        examAvgs[j] = 0;
        for (int i=0; i<numOfStudents; i++)
            examAvgs[j] = (examAvgs[j] + grades[i][j]);
        examAvgs[j] = examAvgs[j]/numOfStudents;
    }
}

// STUDENT FINAL AVERAGE GRADE USING WEIGHT ARRAY
void getAvgsOfStudents(double studentAvgs[], double weights[], int numOfExams, int numOfStudents)
{
    for (int i=0; i<numOfStudents; i++) {
        studentAvgs[i] = 0;
        int j = 0;
        while (j<numOfExams){
            //cout << studentAvgs[i]<<" " << weights[j]<< " " << grades[i][j]<<"\n";
            studentAvgs[i] = studentAvgs[i] + weights[j]*grades[i][j];
            j++;
        }
    }
}

//WRITE A NEW TXT FILE WITH FINAL GRADES
void writeFinalGrades(double examAvgs[], double studentGrades[],int numOfExams, int numOfStudents)
{
    ofstream outStream("/Users/MarloAmaya/Desktop/finalgrades.txt", ios::out);
    
    if (outStream.fail())
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }
    
    //First line
    int x = 0;
    outStream << "   Exam #: ";
    for (int i=1; i<=numOfExams; i++){
    outStream << i << "  ";
    }
    outStream << "Final Grade\n";
    
    //Print the grades along with final grade
    for (int i=1; i<= numOfStudents; i++){
        outStream << "Student " << i << ":";
        int y = 0;
        while (y<numOfExams){
            outStream << grades[x][y] << " ";
            y++;
        }
        outStream << " " << studentGrades[x] <<endl;
        x++;
    }
    
    //Last line, the avg for each exam
    outStream<< "Exam Avgs:";
    for (int i=0; i<numOfExams; i++){
        outStream << examAvgs[i] << " ";
    }
        
    
    outStream.close();

}

