#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <limits>

using namespace std;

void signUp();
void logIn();
void menu();

class Student
{
public:
    string sUsername;
    int sPassword;
    string sName;
    double sGpa;
    void studentSignUp(void);
    void studentLogIn(void);
};

void Student ::studentSignUp()
{
    cout << "Enter your name: " << endl;
    getline(cin, sName);

    cout << "Enter your username: " << endl;
    getline(cin, sUsername);

    cout << "Enter the password: " << endl;
    cin >> sPassword;

    ofstream studentFile("student.txt", ios::app);
    if (studentFile.is_open())
    {
        studentFile << sName << " " << sUsername << " "
                    << sPassword << endl;
        studentFile.close();
        cout << "New student added!" << endl;
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }

    studentLogIn();
}

void Student::studentLogIn()
{
    ifstream studentFile("student.txt");
    if (!studentFile.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }

    string name, username;
    int password;
    bool found = false;

    cout << "Enter your name: " << endl;
    getline(cin, sName);

    cout << "Enter your username: " << endl;
    getline(cin, sUsername);

    cout << "Enter the password: " << endl;
    cin >> sPassword;

    while (studentFile >> name >> username >> password)
    {
        if (name == sName && username == sUsername && password == sPassword)
        {
            found = true;
            break;
        }
    }

    studentFile.close();
    if (found)
    {
        cout << "Login successful!" << endl;
    }
    else
    {
        cout << "Invalid login. Please try again." << endl;
    }
}

class Teacher
{
private:
    string tUsername;
    int tPassword;

public:
    string tName;
    void teacherSignUp(void);
    void teacherLogIn(void);
    void teacherOptions(void);
    void setStudentGPA(void);
    void seeStudentGPA(void);
};

void Teacher::teacherSignUp()
{
    cout << "Enter your name: " << endl;
    getline(cin, tName);

    cout << "Enter your username: " << endl;
    getline(cin, tUsername);

    cout << "Enter the password: " << endl;
    cin >> tPassword;

    ofstream teacherFile("teacher.txt", ios::app);
    if (teacherFile.is_open())
    {
        teacherFile << tName << " "
                    << tUsername << " "
                    << tPassword << endl;
        teacherFile.close();
        cout << "New teacher added!\n Please log in.\n"
             << endl;
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }

    teacherLogIn();
}

void Teacher::teacherLogIn()
{
    ifstream teacherFile("teacher.txt");
    if (!teacherFile.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }

    string name, username;
    int password;
    bool found = false;

    cout << "Enter your name: " << endl;
    getline(cin, tName);

    cout << "Enter your username: " << endl;
    getline(cin, tUsername);

    cout << "Enter the password: " << endl;
    cin >> tPassword;

    while (teacherFile >> name >> username >> password)
    {
        if (name == tName && username == tUsername && password == tPassword)
        {
            found = true;
            break;
        }
    }

    teacherFile.close();
    if (found)
    {
        cout << "Login successful!" << endl;
        teacherOptions();
    }
    else
    {
        cout << "Invalid login. Please try again." << endl;
    }
}

void Teacher::teacherOptions()
{
    int num;
    cout << "what do you want to do? (1-3)\n1. Set sudent gpa\n2. See student gpa\n3. Go back to menu\n";
    cin >> num;
    switch (num)
    {
    case 1:
        setStudentGPA();
        break;
    case 2:
        seeStudentGPA();
        break;
    case 3:
        menu();
        break;
    default:
        cout << "Wrong option! Please try again.\n";
        teacherOptions();
        break;
    }
}

void Teacher::setStudentGPA()
{
    ifstream studentFile("student.txt");
    if (!studentFile.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }
    string studentName;
    cout << "Enter the student name: \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, studentName);

    string name, username;
    int password;
    double gpa;
    bool found = false;

    while (studentFile >> name >> username >> password >> gpa)
    {

        cout << "Checking: " << name
             << " against input: " << studentName << endl;
        if (name == studentName)
        {
            cout << "Student: " << name << ", GPA: " << gpa << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Student not found." << endl;
    }
    studentFile.close();
    teacherOptions();
}

void Teacher::seeStudentGPA()
{
    ifstream studentFile("student.txt");
    if (!studentFile.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }
    string studentname;
    cout << "Enter student name: \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, studentname);

    string name, username;
    int password;
    double gpa;
    bool found = false;

    while (studentFile >> name >> username >> password >> gpa)
    {
        if (name == studentname)
        {
            cout << "student: " << name << ", GPA:" << gpa << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Student not found. " << endl;
    }
    studentFile.close();
    teacherOptions();
}

int main()
{
    menu();
    return 0;
}

void menu()
{
    int num;
    cout << "Welcome to the school data management system\n";
    cout << "What do you want to do? (1-3)\n1. Sign up\n2. Log in\n3. Exit\n";
    cin >> num;
    switch (num)
    {
    case 1:
        signUp();
        break;
    case 2:
        logIn();
        break;
    case 3:
        cout << "Exiting program. Goodbye!\n";
        exit(0);
        break;
    default:
        cout << "Wrong option! Please try again.\n";
        break;
        menu();
    }
}

void signUp()
{
    char answer;
    cout << " Are you a teacher or student?(t/s) \n";
    cin >> answer;
    //--------------------------------
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (answer == 's')
    {
        Student student;
        student.studentSignUp();
    }
    else if (answer == 't')
    {
        Teacher teacher;
        teacher.teacherSignUp();
    }
    else
    {
        cout << "Invalid input. Please try again.\n";
        signUp();
    }
}

void logIn()
{
    char answer;
    cout << " Are you a teacher or student?(t/s) \n";
    cin >> answer;
    //--------------------------------
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (answer == 's')
    {
        Student student;
        student.studentLogIn();
    }

    else if (answer == 't')
    {
        Teacher teacher;
        teacher.teacherLogIn();
    }
    else
    {
        cout << "Invalid input. Please try again.\n";
        logIn();
    }
}
