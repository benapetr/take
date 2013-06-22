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
        static bool Group;
        static bool Recursive;
        static list<string> Objects;
};

#endif // PREFERENCES_H
