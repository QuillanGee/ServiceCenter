// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Office .h class

#ifndef OFFICE_H
#define OFFICE_H

#include "Window.h"
#include "Student.h"
#include <iostream>
#include <string>

// Models an office (cashier, registrar, finaid)

class Office{

  public:
    // overloaded constructor to assign # of windows to an office
    Office(int windows);
    ~Office();

    bool hasAvailableWindows(); // returns true if there are available windows
    void assignWindow(Student s, int entryTime); // assigns student to window at their entry time

    bool DoAnyStudentsHaveToLeaveWindow(int t); // checks if anyone is ready to go at tick t
    void setStudentAtAnReadyToGoOfficeWindow(int i); // sets student who's ready to go

    Student getStudentReadyTogo(); // gets student ready to go
    int getLongestWindowIdleTime(); // gets longest window idle time in office
    void checkIfWindowIsIdle();
    int getTotalWindowIdleTime();
    int getMeanWindowIdleTime();
    int getNumWindowsIdleOver5Min();

    int getWaitTime();

  private:
    // Student whose time is up at a window
    // and is ready to move to next office

    Student StudentReadyTogo;

    int numWindows; // total number of windows in an office
    int windowsAvail; // number of windows OPEN

    Window *windowArr; // array of windows for an office

    int totalWindowIdleTime;
    int longestWindowIdleTime; // longest window idle time
    int numWindowsIdleOver5Min;
    int waitTime;

};

#endif
