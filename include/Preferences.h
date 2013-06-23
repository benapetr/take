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

using namespace std;

class Preferences
{
    public:
        static uid_t euid;
        static uid_t uid;
        static gid_t guid;
        static int Verbosity;
        static bool StrictHL;
        static bool Group;
        static bool Recursive;
        static list<string> Objects;
        static unsigned int Device;
        static bool StrictDevice;
        static bool StrictGroup;
        static string Version;
        static int NumberOfGroups;
        static gid_t Groups[256];
};

#endif // PREFERENCES_H
