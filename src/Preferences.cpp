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

//! Version
string Preferences::Version = "1.0.0";
//! If this is true, the file which is going to be overtaken must match the user's group as well
bool Preferences::StrictGroup = true;
//! If this is true, subfiles which are going to be overtaken must be on same filesystem as root file
bool Preferences::StrictDevice = true;
//! If this is true, files with more than 1 hardlink are rejected
bool Preferences::StrictHL = true;
//! Device which is being used to store a root
unsigned int Preferences::Device = 0;
//! Information about groups of user
gid_t Preferences::Groups[256];
//! Number of groups the user is in
int Preferences::NumberOfGroups = getgroups(sizeof(Preferences::Groups)/sizeof(Preferences::Groups[0]), Preferences::Groups);
//! Verbosity
int Preferences::Verbosity = 0;
//! Recursive
bool Preferences::Recursive = false;
//! If groups should be restricted in order to take a file
bool Preferences::Group = false;
//! Return code
int Preferences::RC = 0;
//! List of files that we try to take
list<string> Preferences::Objects = list<string>();
//! Group id
gid_t Preferences::guid = getgid();
//! User id
uid_t Preferences::uid = getuid();
//! Effective uid
uid_t Preferences::euid = geteuid();
