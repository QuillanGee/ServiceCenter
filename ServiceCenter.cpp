// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - ServiceCenter .cpp class

// Models the Service Center where students first enter
// Takes in file provided for input specs, methods to facilitate movement,
// and driver/simulator method

#include "ServiceCenter.h"
#include "Office.h"
#include "Student.h"
#include "WG_ListQueue.h"

#include <string>
#include <fstream>
#include <iostream>

/*
a. overloaded constructor
b. does not return anything
c. takes in string textFile
d. no known exeptions thrown
*/
ServiceCenter::ServiceCenter(std::string textFile){
  // initialize tick var and following queues:
  tick = 0;
  allStudentsQueue = new WG_ListQueue<Student>();
  arrivalTimesQueue = new WG_ListQueue<int>();
  numOfArrivingStudentsQueue = new WG_ListQueue<int>();
  leavingQueue = new WG_ListQueue<Student>();

  std::ifstream inFile;
  inFile.open(textFile);

  if (inFile.is_open()){

    // get first 3 lines of file
    getline(inFile, WindowsR); // # windows in registrar office
    getline(inFile, WindowsC); // # windows in cashier office
    getline(inFile, WindowsFA); // # windows in finaid office

    numWindowsR = stoi(WindowsR);
    numWindowsC = stoi(WindowsC);
    numWindowsFA = stoi(WindowsFA);

    cashier = new Office(numWindowsC);
    finAid = new Office(numWindowsFA);
    registrar = new Office(numWindowsR);

    // get arrival time
    getline(inFile, arrivalTime);
    numArrivalTime = stoi(arrivalTime);
    arrivalTimesQueue -> add(numArrivalTime);

    // loop through to read rest of file till we reach 'END'
    while(arrivalTime != "END"){

      // get the number of students coming at an arrival time
      getline(inFile, studentsAtArrivalTime);

      numStudentsAtArrivalTime = stoi(studentsAtArrivalTime);
      numOfArrivingStudentsQueue -> add(numStudentsAtArrivalTime);

      // loop through # of arriving students to read/store their info
      for(int i = 0;i<numStudentsAtArrivalTime;i++){
        std::string tempString;
        // get temp string representing 1 student
        getline(inFile, tempString);
        std::string tempT1 = "";
        std::string tempT2 = "";
        std::string tempT3 = "";

        int first_space = tempString.find(" ");
        t1 = stoi(tempString.substr(0, first_space));

        // Find the second space character to extract the time at cashier
        int second_space = tempString.find(" ", first_space + 1);
        t2 = stoi(tempString.substr(first_space + 1, second_space - first_space - 1));

        // Find the third space character to extract the time at financial aid
        int third_space = tempString.find(" ", second_space + 1);
        t3 = stoi(tempString.substr(second_space + 1, third_space - second_space - 1));

        // Extract the order of offices by getting the substring after the last space character
        o1 = tempString[third_space + 1];
        o2 = tempString[third_space + 3];
        o3 = tempString[third_space + 5];

        // create new Student using specs from (parsed) tempString
        Student* myStudent = new Student(numArrivalTime, t1,t2,t3,o1,o2,o3);
        allStudentsQueue -> add(*myStudent);
      }
      // get the next arrival time
      getline(inFile,arrivalTime);
      if(arrivalTime == "END"){
        break;
      }
      numArrivalTime = stoi(arrivalTime);
      arrivalTimesQueue -> add(numArrivalTime);
    }

    // instantiate queues for each of the 3 offices
    cashierQueue = new WG_ListQueue<Student>();
    finAidQueue = new WG_ListQueue<Student>();
    registrarQueue = new WG_ListQueue<Student>();
    totalStudents = allStudentsQueue -> size();
  }
  inFile.close();
}

ServiceCenter::~ServiceCenter(){
}


/*
a. queueArrivingStudents method
  // puts arriving students into queue
b. does not return anything
c. does not take in parameters
d. no known exeptions thrown
*/
void ServiceCenter::queueArrivingStudents(){
  int currArrivalTime = 0;
  int numStudentsArriving = 0;

  // check if there is an arrival time
  if(arrivalTimesQueue -> size() > 0){
    currArrivalTime = arrivalTimesQueue -> peek();
    numStudentsArriving = numOfArrivingStudentsQueue -> peek();
  }

  // check if global tick == currArrivalTime
  if(tick == currArrivalTime){
    arrivalTimesQueue -> remove();
    numOfArrivingStudentsQueue -> remove();

    // loop through students arriving at currArrivalTime in allStudentsQueue
    for(int i = 0;i < numStudentsArriving;i++){
      Student s = allStudentsQueue -> remove(); // remove student from allStudentsQueue
      char officeToGoTo = s.officeQ -> remove(); // remove the office student is going to

      // check what office they are going to and add them to that office's queue
      if (officeToGoTo == 'C'){
        cashierQueue -> add(s);
      } else if (officeToGoTo == 'F'){
        finAidQueue -> add(s);
      } else if (officeToGoTo == 'R'){
        registrarQueue -> add(s);
      }
    }
  }
}

/*
a. CashierWindowBusiness method
b. does not return anything
c. takes in tick, int t
d. no known exeptions thrown
*/
void ServiceCenter::CashierWindowBusiness(int t){
  // check if any students are ready to leave window
  if (cashier -> DoAnyStudentsHaveToLeaveWindow(t) == true){
    // if so, move student to their next office destination's queue using moveStudent method
    moveStudent(cashier -> getStudentReadyTogo());
  }
}

/*
a. AssignToWindowAtCashier method
b. does not return anything
c. takes in tick, int t
d. no known exeptions thrown
*/
void ServiceCenter::AssignToWindowAtCashier(int t){
  // check if cashier has available windows
  if (cashierQueue -> size() > 0){
    if(cashier -> hasAvailableWindows() == true){
      cashier -> assignWindow(cashierQueue -> remove(),t);
      for(int i=0; i<cashierQueue -> size(); ++i){
        Student tempStudent = cashierQueue -> remove();
        tempStudent.addCashierWaitTime();
        cashierQueue -> add(tempStudent);
      }
    } else {
      for(int i=0; i<cashierQueue -> size(); ++i){
        Student tempStudent = cashierQueue -> remove();
        tempStudent.addCashierWaitTime();
        cashierQueue -> add(tempStudent);
      }
    }
  }
}

/*
a. FinAidWindowBusiness method
b. does not return anything
c. takes in tick, int t
d. no known exeptions thrown
*/
void ServiceCenter::FinAidWindowBusiness(int t){
  if (finAid -> DoAnyStudentsHaveToLeaveWindow(t) == true){
    moveStudent(finAid -> getStudentReadyTogo());
  }
}


/*
a. AssignToWindowAtFinAid method
b. does not return anything
c. takes in tick, int t
d. no known exeptions thrown
*/
void ServiceCenter::AssignToWindowAtFinAid(int t){
  if (finAidQueue -> size() > 0){
    if(finAid -> hasAvailableWindows() == true){
      finAid -> assignWindow(finAidQueue -> remove(),t);
      for(int i=0; i<finAidQueue -> size(); ++i){
        Student tempStudent = finAidQueue -> remove();
        tempStudent.addFinAidWaitTime();
        finAidQueue -> add(tempStudent);
      }
    } else {
      for(int i=0; i<finAidQueue -> size(); ++i){
        Student tempStudent = finAidQueue -> remove();
        tempStudent.addFinAidWaitTime();
        finAidQueue -> add(tempStudent);
      }
    }
  }
}

/*
a. RegistrarWindowBusiness method
b. does not return anything
c. takes in tick, int t
d. no known exeptions thrown
*/
void ServiceCenter::RegistrarWindowBusiness(int t){
  if (registrar -> DoAnyStudentsHaveToLeaveWindow(t) == true){
    moveStudent(registrar -> getStudentReadyTogo());
  }
}

/*
a. AssignToWindowAtRegistrar method
b. does not return anything
c. takes in tick, int t
d. no known exeptions thrown
*/
void ServiceCenter::AssignToWindowAtRegistrar(int t){
  if (registrarQueue -> size() > 0){
    if(registrar -> hasAvailableWindows() == true){
      registrar -> assignWindow(registrarQueue -> remove(),t);
      for(int i=0; i<registrarQueue -> size(); ++i){
        Student tempStudent = registrarQueue -> remove();
        tempStudent.addRegistrarWaitTime();
        registrarQueue -> add(tempStudent);
      }
    } else {
      for(int i=0; i<registrarQueue -> size(); ++i){
        Student tempStudent = registrarQueue -> remove();
        tempStudent.addRegistrarWaitTime();
        registrarQueue -> add(tempStudent);
      }
    }
  }
}

/*
a. moveStudent method
b. does not return anything
c. takes in Student s
d. no known exeptions thrown
*/
void ServiceCenter::moveStudent(Student s){
  // check if a student still has offices left to go to
  if (s.officeQ -> size() > 0){
    // if so, move them to their next office and add to that office's queue
    char officeToGoTo = s.officeQ -> remove();
    if (officeToGoTo == 'C'){
      cashierQueue -> add(s);
    } else if (officeToGoTo == 'F'){
      finAidQueue -> add(s);
    } else if (officeToGoTo == 'R'){
      registrarQueue -> add(s);
    }
  } else if (s.officeQ -> size() == 0){
    // else, a student completed all tasks and leaves Student Center
    leavingQueue -> add(s);
  }
}


/*
a. printStats method
b. does not return anything
c. no parameters taken in
d. no known exeptions thrown
*/
void ServiceCenter::printStats(){
  std::cout << std::endl <<"      Cashier's Office: " << std::endl;
  double meanCashierStudentWaitTime = (double)CashierTotalWaitTime/totalStudents;
  std::cout << "Mean student wait time: " << meanCashierStudentWaitTime << " ticks(s) "<< std::endl;
  std::cout << "Mean window idle time: " << cashier -> getMeanWindowIdleTime() << " tick(s) " << std::endl;
  std::cout << "Longest student wait time: " << CashierLongestWaitTime  << " ticks(s) "<< std::endl;
  std::cout << "Longest window idle time: " << cashier -> getLongestWindowIdleTime()  << " tick(s) " << std::endl;

  std::cout << std::endl << "       Financial Aid's Office: " << std::endl;
  double meanFinAidStudentWaitTime = (double)FinAidTotalWaitTime/totalStudents;
  std::cout << "Mean student wait time: " << meanFinAidStudentWaitTime << " ticks(s) "<< std::endl;
  std::cout << "Mean window idle time: " << finAid -> getMeanWindowIdleTime()  << " tick(s) " << std::endl;
  std::cout << "Longest student wait time: " << FinAidLongestWaitTime  << " ticks(s) "<< std::endl;
  std::cout << "Longest window idle time: " << finAid -> getLongestWindowIdleTime()  << " tick(s) " << std::endl;

  std::cout <<std::endl << "       Registrar's Office: " << std::endl;
  double meanRegistrarStudentWaitTime = (double)RegistrarTotalWaitTime/totalStudents;
  std::cout << "Mean student wait time: " << meanRegistrarStudentWaitTime << " ticks(s) "<< std::endl;
  std::cout << "Mean window idle time: " << registrar -> getMeanWindowIdleTime() << " tick(s) " << std::endl;
  std::cout << "Longest student wait time: " << RegistrarLongestWaitTime  << " ticks(s) "<< std::endl;
  std::cout << "Longest window idle time: " << registrar -> getLongestWindowIdleTime() << " tick(s) " << std::endl << std::endl;

  numWindowsIdleOver5MinAllOffices += cashier -> getNumWindowsIdleOver5Min();
  numWindowsIdleOver5MinAllOffices += finAid -> getNumWindowsIdleOver5Min();
  numWindowsIdleOver5MinAllOffices += registrar -> getNumWindowsIdleOver5Min();

  std::cout << "Number of students waiting over 10 minutes across all offices: " << numStudentsOver10Min << std::endl;
  std::cout << "Number of windows idle for over 5 minutes across all offices: " << numWindowsIdleOver5MinAllOffices << std::endl << std::endl;
}

/*
a. Driver method
b. does not return anything
c. no parameters taken in
d. no known exeptions thrown
*/
void ServiceCenter::Driver(){
  while(true){
    ++tick;
    queueArrivingStudents();
    CashierWindowBusiness(tick);
    FinAidWindowBusiness(tick);
    RegistrarWindowBusiness(tick);

    AssignToWindowAtCashier(tick);
    AssignToWindowAtFinAid(tick);
    AssignToWindowAtRegistrar(tick);

    cashier -> checkIfWindowIsIdle();
    finAid -> checkIfWindowIsIdle();
    registrar -> checkIfWindowIsIdle();

    int leavingQSize = leavingQueue -> size();

    if(leavingQueue -> size() == totalStudents){

      CashierLongestWaitTime = leavingQueue -> peek().cashierWaitTime;
      FinAidLongestWaitTime = leavingQueue -> peek().finAidWaitTime;
      RegistrarLongestWaitTime = leavingQueue -> peek().registrarWaitTime;

      for (int i=0; i<leavingQSize; ++i){
        CashierTotalWaitTime += leavingQueue -> peek().cashierWaitTime;
        FinAidTotalWaitTime += leavingQueue -> peek().finAidWaitTime;
        RegistrarTotalWaitTime += leavingQueue -> peek().registrarWaitTime;

        // check wait time over 5 min
        if (CashierLongestWaitTime < leavingQueue -> peek().cashierWaitTime){
          CashierLongestWaitTime = leavingQueue -> peek().cashierWaitTime;
        }

        if (FinAidLongestWaitTime < leavingQueue -> peek().finAidWaitTime){
          FinAidLongestWaitTime = leavingQueue -> peek().finAidWaitTime;
        }

        if (RegistrarLongestWaitTime < leavingQueue -> peek().registrarWaitTime){
          RegistrarLongestWaitTime = leavingQueue -> peek().registrarWaitTime;
        }

        // check students waiting over 10 min
        if (leavingQueue -> peek().cashierWaitTime > 10){
          ++numStudentsOver10Min;
        }

        if (leavingQueue -> peek().finAidWaitTime > 10){
          ++numStudentsOver10Min;
        }

        if (leavingQueue -> peek().registrarWaitTime > 10){
          ++numStudentsOver10Min;
        }

        leavingQueue -> remove();
      }

      printStats();
      break;
    }
  }
}
