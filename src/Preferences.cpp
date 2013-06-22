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

bool Preferences::StrictGroup = false;
int Preferences::Verbosity = 0;
bool Preferences::Recursive = false;
bool Preferences::Group = false;
list<string> Preferences::Objects = list<string>();
gid_t Preferences::guid = getgid();
uid_t Preferences::uid = getuid();
uid_t Preferences::euid = geteuid();
