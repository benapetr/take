 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <list>

#define DEFAULT_EC 1

using namespace std;

class Preferences
{
    public:
        static uid_t euid; // euid
        static uid_t uid; // uid
        static gid_t guid; // gid
        static int Verbosity; // verbosity
        static bool StrictHL; // strict check of hardlink
        static bool Group; // group should be changed
        static bool Recursive; // recursive
        static list<string> Objects; // objects that needs to be overtaken
        static unsigned int Device; // device the root folder live on
        static bool StrictDevice; // check if device is same for all files
        static bool StrictGroup; // strict check for user group
        static string Version; // version
        static int NumberOfGroups; // number of groups user is in
        static gid_t Groups[256]; // list of all groups user is in
        static int RC; // return code
};

#endif // PREFERENCES_H
