// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - ServiceCenter .h class

// Models the Service Center where students first enter
// Takes in file provided for input specs, methods to facilitate movement,
// and driver/simulator method

#ifndef ServiceCenter_H
#define ServiceCenter_H

#include "WG_ListQueue.h"
#include "Student.h"
#include "Office.h"

#include <iostream>
#include <string>

using namespace std;

class ServiceCenter{

  public:
    // overloaded constructor to read textFile and assign to variables
    ServiceCenter(std::string textFile);
    ~ServiceCenter();

    void queueArrivingStudents(); // queues arriving group
    void moveStudent(Student s); // facilitates student movement

    // methods for office business
      // checks if anyone needs to leave window
      // and moves them to next destination if so
    void CashierWindowBusiness(int t);
    void AssignToWindowAtCashier(int t);
    void FinAidWindowBusiness(int t);

    // methods for assigning student to available window
    void AssignToWindowAtFinAid(int t);
    void RegistrarWindowBusiness(int t);
    void AssignToWindowAtRegistrar(int t);

    // driver/simulator
    void Driver();

    // output stats methods
    void printStats();

  protected:
    int tick; // overall time tick

    // bool vars for if office queues are empty
    bool cashierQEmpty;
    bool FAQEmpty;
    bool registrarQEmpty;

    int CashierHolderWaitTime;
    int CashierLongestWaitTime;
    int CashierTotalWaitTime;

    int FinAidHolderWaitTime;
    int FinAidLongestWaitTime;
    int FinAidTotalWaitTime;

    int RegistrarHolderWaitTime;
    int RegistrarLongestWaitTime;
    int RegistrarTotalWaitTime;

    // vars for input file specs
      // converts string from getline, stores in separate int var
      // some vars used to create Student object
    string arrivalTime;
    int numArrivalTime;
    string studentsAtArrivalTime;
    int numStudentsAtArrivalTime;
    string WindowsR;
    string WindowsC;
    string WindowsFA;
    int numWindowsR;
    int numWindowsC;
    int numWindowsFA;
    int t1;
    int t2;
    int t3;
    char o1;
    char o2;
    char o3;

    // queues for each of the 3 offices, all students, and students who
    // completed all tasks and left the Service Center
    WG_ListQueue<Student>* cashierQueue;
    WG_ListQueue<Student>* finAidQueue;
    WG_ListQueue<Student>* registrarQueue;
    WG_ListQueue<Student>* allStudentsQueue;
    WG_ListQueue<Student>* leavingQueue;

    // models the 3 offices of type Office
    Office* cashier;
    Office* finAid;
    Office* registrar;

    // queues for arrival times and number of arriving students at a specific
    // arrival time as taken in from input file
    WG_ListQueue<int>* arrivalTimesQueue;
    WG_ListQueue<int>* numOfArrivingStudentsQueue;

    int totalStudents;

    int numWindowsIdleOver5MinAllOffices;
    int numStudentsOver10Min;

};

#endif
