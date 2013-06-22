#include <iostream>
#include <list>
#include "../include/Preferences.h"

using namespace std;

int Preferences::Verbosity = 0;
bool Preferences::Recursive = false;
list<string> Preferences::Objects = list<string>();
