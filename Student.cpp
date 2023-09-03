// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Student .cpp class

#include "Student.h"

#include <string>
#include <iostream>

// Models a student coming into Service Center

/*
a. overloaded constructor
b. does not return anything
c. takes in int timeEnter, 3 ints representing time to spend at each office
  // and 3 chars representing office visiting order
d. no known exeptions thrown
*/
Student::Student(int timeEnter, int t1, int t2, int t3, char o1, char o2, char o3){
  timeEnterSC = timeEnter;
  time1 = t1;
  time2 = t2;
  time3 = t3;
  office1 = o1;
  office2 = o2;
  office3 = o3;
  numWindowStudentAt = -1;
  cashierWaitTime = 0;
  finAidWaitTime = 0;
  registrarWaitTime = 0;

  timeQ = new WG_ListQueue<int>();
  officeQ = new WG_ListQueue<char>();
  if (time1 > 0){
    timeQ -> add(time1);
    officeQ -> add(office1);
  }
  if (time2 > 0){
    timeQ -> add(time2);
    officeQ -> add(office2);
  }
  if (time3 > 0){
    timeQ -> add(time3);
    officeQ -> add(office3);
  }
}

Student::Student(){
}

Student::~Student(){
}

/*
a. getNumWindowStudentAt method
b. returns int numWindowStudentAt
c. no parameters taken in
d. no known exeptions thrown
*/
int Student::getNumWindowStudentAt(){
  return numWindowStudentAt;
}

/*
a. setNumWindowStudentAt method
b. does not return anything
c. takes in int i representing window # student is at
d. no known exeptions thrown
*/
void Student::setNumWindowStudentAt(int i){
  numWindowStudentAt = i;
}

/*
a. getTimeEnterSC method
b. returns int timeEnterSC
c. no parameters taken in
d. no known exeptions thrown
*/
int Student::getTimeEnterSC(){
  return timeEnterSC;
}

/*
a. addCashierWaitTime, addFinAidWaitTime, addRegistrarWaitTime method
// just increments office wait time
b. does not return anything
c. no parameters taken in
d. no known exeptions thrown
*/
void Student::addCashierWaitTime(){
  cashierWaitTime += 1;
}

void Student::addFinAidWaitTime(){
  finAidWaitTime += 1;
}

void Student::addRegistrarWaitTime(){
  registrarWaitTime += 1;
}
