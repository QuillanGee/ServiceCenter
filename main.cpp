// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - Main Class

// takes input file name as a command line argument
// and uses the SpeakerView class to compute the output

#include "ServiceCenter.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv){

  string file = argv[1];
  ServiceCenter* sc = new ServiceCenter(file);
  sc -> Driver();

  return 0;
}
