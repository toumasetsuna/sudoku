//
// Created by 86138 on 2023/6/30.
//


#include <iostream>
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <getopt.h>
#include <cstring>
using namespace std;
int start(int argc, char* argv[]);
int main(int argc, char *argv[]) {
    argv[0]="sudoku";
    argv[1]="-c";
    argv[2]="1";
    argc=3;
    start(argc, argv);
}