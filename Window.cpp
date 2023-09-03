// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Office .h class

#include "Window.h"
#include "Student.h"

#include <string>
#include <iostream>

Window::Window(){
  open = true;
  windowIdleTime = -1;
  totalWindowIdleTime = -1;
}

Window::~Window(){
}

/*
a. isOpen method
b. returns bool open
c. no parameters taken in
d. no known exeptions thrown
*/
bool Window::isOpen(){
  return open;
}

/*
a. setOpen method
b. does not return anything
c. takes in bool b
d. no known exeptions thrown
*/
void Window::setOpen(bool b){
  open = b;
}


/*
a. getStudentAtWindow method
b. returns Student studentAtWindow
c. no parameters taken in
d. no known exeptions thrown
*/
Student Window::getStudentAtWindow(){
  return studentAtWindow;
}

/*
a. setStudentAtWindow method
b. does not return anything
c. takes in Student s
d. no known exeptions thrown
*/
void Window::setStudentAtWindow(Student s){
  studentAtWindow = s;
  timeAtWindow = s.timeQ -> remove();
}

/*
a. getTimeAtWindow method
b. returns int getTimeAtWindow
c. no parameters taken in
d. no known exeptions thrown
*/
int Window::getTimeAtWindow(){
  return timeAtWindow;
}

/*
a. getEntryTime method
b. returns int entryTime
c. no parameters taken in
d. no known exeptions thrown
*/
int Window::getEntryTime(){
  return entryTime;
}

/*
a. setEntryTime method
b. does not return anything
c. takes in int t (tick)
d. no known exeptions thrown
*/
void Window::setEntryTime(int t){
  entryTime = t;
}

/*
a. addWindowIdleTime method
b. does not return anything
c. no parameters taken in
d. no known exeptions thrown
*/
void Window::addWindowIdleTime(){
  windowIdleTime += 1;
}

/*
a. getWindowIdleTime method
b. returns int windowIdleTime
c. no parameters taken in
d. no known exeptions thrown
*/
int Window::getWindowIdleTime(){
  return windowIdleTime;
}

/*
a. getTotalWindowIdleTime method
b. returns int totalWindowIdleTime
c. no parameters taken in
d. no known exeptions thrown
*/
int Window::getTotalWindowIdleTime(){
  return totalWindowIdleTime;
}
