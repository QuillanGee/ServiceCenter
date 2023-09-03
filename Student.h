// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Student .h class


#ifndef Student_H
#define Student_H
#include "WG_ListQueue.h"

#include <iostream>
#include <string>

// Models a student coming into Service Center

class Student{

  public:
    // overloaded constructor with their specs from file to create a Student
    Student(int timeEnter, int t1, int t2, int t3, char o1, char o2, char o3);
    Student();
    ~Student();

    void setNumWindowStudentAt(int i); // set window index a student is at if they're at a window
    int getNumWindowStudentAt(); // gets window index a student is at if they're at a window
    int getTimeEnterSC(); // gets time they enter student center

    void addCashierWaitTime();
    void addFinAidWaitTime();
    void addRegistrarWaitTime();

    void addNumOfficesVisited();

    // queue of a student's offices and queue of times
    // they need to spend at each office
    WG_ListQueue<char>* officeQ;
    WG_ListQueue<int>* timeQ;
    int cashierWaitTime;
    int finAidWaitTime;
    int registrarWaitTime;
    int timeEnterCashier;
    int timeEnterFinAid;
    int timeEnterRegistrar;


  protected:
    // member vars for student entering service center
    int timeEnterSC;
    int time1;
    int time2;
    int time3;
    char office1;
    char office2;
    char office3;
    int numWindowStudentAt;

    // their queue wait time is
    // (tick exit window - time spent at window)  - time entered office/ queue)

};

#endif
