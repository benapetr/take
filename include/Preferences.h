#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <iostream>
#include <list>

using namespace std;

class Preferences
{
    public:
        static int Verbosity;
        static bool Recursive;
        static list<string> Objects;
};

#endif // PREFERENCES_H
