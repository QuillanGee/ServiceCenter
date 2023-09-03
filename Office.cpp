// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Office .cpp class

#include "Office.h"
#include "WG_ListQueue.h"
#include "Window.h"
#include "Student.h"

#include <string>
#include <fstream>
#include <iostream>

// Models an office (cashier, registrar, finaid)

/*
a. overloaded constructor
b. does not return anything
c. takes in int windows (total windows at office)
d. no known exeptions thrown
*/
Office::Office(int windows){
  // initialize all attributes/vars for an office
  numWindows = windows;
  windowsAvail = windows;
  windowArr = new Window[numWindows]; // create array of windows w size numWindows
  longestWindowIdleTime = -1;
  totalWindowIdleTime = -1;

  for (int i=0; i<numWindows; ++i){
    windowArr[i] = Window();
  }
}

Office::~Office(){
}

/*
a. hasAvailableWindows method
b. returns a boolean
c. no parameters taken in
d. no known exeptions thrown
*/
bool Office::hasAvailableWindows(){
  // checks if office has available windows
  if(windowsAvail > 0){
    return true;
  }else{
    return false;
  }
}

/*
a. assignWindow method
b. does not return anything
c. takes in Student s and int entryTime (time they enter window)
d. no known exeptions thrown
*/
void Office::assignWindow(Student s, int entryTime){
  // loop through windowArr in office
  // check if every window is closed
  bool incrWaitTime = true;
  for(int i = 0;i<numWindows;i++){
    if(windowArr[i].isOpen() == true){
      incrWaitTime = false;
      break;
    }
  }

  if (incrWaitTime == true){
    ++waitTime;
  }

  for(int i = 0;i<numWindows;i++){
    // if an open window is found, assign Student s to window
    if(windowArr[i].isOpen() == true){
      windowArr[i].setOpen(false);
      windowArr[i].setStudentAtWindow(s);
      windowArr[i].setEntryTime(entryTime);
      s.setNumWindowStudentAt(i); // save window # student is at
      windowsAvail -= 1; // decrement windows available
      break;
      // else, nothing happens and they remain in office queue
    }
  }
}

int Office::getWaitTime(){
  return waitTime;
}

/*
a. DoAnyStudentsHaveToLeaveWindow method
b. does not return anything
c. takes in Student s and int entryTime (time they enter window)
d. no known exeptions thrown
*/
bool Office::DoAnyStudentsHaveToLeaveWindow(int t){
  bool ret;
  // loop through all windows to check if student is ready to leave
  // checks if tick == entryTime + timespentAtWindow
  for(int i = 0;i<numWindows;i++){
    // only need to check if there's a student at window
    if(windowArr[i].isOpen() == false){
      // check if student is ready to leave window
      int isTimeUp = windowArr[i].getEntryTime() + windowArr[i].getTimeAtWindow();
      // if so, remove student from window and add to next queue
      if(t == isTimeUp){
        setStudentAtAnReadyToGoOfficeWindow(i); // set that student to StudentReadyTogo
        ret = true;
        windowArr[i].setOpen(true); // open window after student leaves
        ++windowsAvail;
        break;
      } else {
        ret = false;
      }
    }else{
      ret = false;
    }
  }
  return ret;
}

/*
a. setStudentAtAnReadyToGoOfficeWindow method
b. does not return anything
c. takes in int i (window index in windowArr)
d. no known exeptions thrown
*/
void Office::setStudentAtAnReadyToGoOfficeWindow(int i){
  // set StudentReadyTogo to student at window index i
  StudentReadyTogo = windowArr[i].getStudentAtWindow();
}

/*
a. getStudentReadyTogo method
b. returns Student
c. no parameters taken in
d. no known exeptions thrown
*/
Student Office::getStudentReadyTogo(){
  return StudentReadyTogo;
}

void Office::checkIfWindowIsIdle(){
  for (int i=0; i<numWindows; ++i){
    if (windowArr[i].isOpen() == true){
      windowArr[i].addWindowIdleTime();
      ++totalWindowIdleTime;
    }
  }
}

int Office::getTotalWindowIdleTime(){
  return totalWindowIdleTime;
}

int Office::getMeanWindowIdleTime(){
  return (totalWindowIdleTime/numWindows);
}

/*
a. getLongestWindowIdleTime method
b. returns int i (longest window idle time)
c. no parameters taken in
d. no known exeptions thrown
*/
int Office::getLongestWindowIdleTime(){
  for(int i = 0;i<numWindows;i++){
    if(windowArr[i].getWindowIdleTime() > longestWindowIdleTime){
      longestWindowIdleTime = windowArr[i].getWindowIdleTime();
    }
  }
  return longestWindowIdleTime;
}

int Office::getNumWindowsIdleOver5Min(){
  for(int i = 0;i<numWindows;i++){
    if(windowArr[i].getWindowIdleTime() > 5){
      ++numWindowsIdleOver5Min;
    }
  }
  return numWindowsIdleOver5Min;
}
