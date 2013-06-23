 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#include <iostream>
#include <list>
#include <unistd.h>
#include <sys/stat.h>
#include "../include/Preferences.h"

using namespace std;

string Preferences::Version = "1.0.0";
// If this is true, the file which is going to be overtaken must match the user's group as well
bool Preferences::StrictGroup = true;
// If this is true, subfiles which are going to be overtaken must be on same filesystem as root file
bool Preferences::StrictDevice = true;
// If this is true, files with more than 1 hardlink are rejected
bool Preferences::StrictHL = true;
unsigned int Preferences::Device = 0;
gid_t Preferences::Groups[256];
int Preferences::NumberOfGroups = getgroups(sizeof(Preferences::Groups)/sizeof(Preferences::Groups[0]), Preferences::Groups);
int Preferences::Verbosity = 0;
bool Preferences::Recursive = false;
bool Preferences::Group = false;
int Preferences::RC = 0;
//list<FILE> Preferences::OpenFD = list<FILE>();
list<string> Preferences::Objects = list<string>();
gid_t Preferences::guid = getgid();
uid_t Preferences::uid = getuid();
uid_t Preferences::euid = geteuid();
