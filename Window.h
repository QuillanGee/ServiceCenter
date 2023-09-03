// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Office .h class


#ifndef WINDOW_H
#define WINDOW_H


#include "Student.h"
#include <iostream>
#include <string>

// Models a single Window in an Office

class Window{

  public:
    Window();
    ~Window();
    // void setAvailable();
    // void setUnavailable();

    // getters and setters for window attributes
    int getTotalWindowIdleTime();
    Student getStudentAtWindow();
    void setStudentAtWindow(Student s);
    void setEntryTime(int t);
    int getEntryTime();
    int getTimeAtWindow();
    void addWindowIdleTime();
    int getWindowIdleTime();

    bool isOpen();
    void setOpen(bool b);

  protected:
    // open bool if a window is open
    bool open;

    int windowIdleTime;
    int totalWindowIdleTime;
    Student studentAtWindow;
    int entryTime;
    int timeAtWindow;

};

#endif
