#include <iostream>
//#include <pwd.h>
//#include <grp.h>
#include <unistd.h>
#include <ftw.h>
#include <fnmatch.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../include/Debugging.h"
#include "../include/Preferences.h"
#include "../include/Take.h"

Take::Take(string Path)
{
    Debugging::DebugLog("Taking " + Path);
    struct stat s;
    if( stat(Path.c_str(),&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            if (Preferences::Recursive)
            {
                // we need to overtake it recursively
                return;
            }
            Overtake(Path);
            return;
        }
        else if( s.st_mode & S_IFREG )
        {
            //it's a file
            Overtake(Path);
        }
        else
        {
            //something else
            Debugging::ErrorLog(Path + " is of invalid type! Must be a directory, or file");
        }
    }
    else
    {
        //error
        Debugging::ErrorLog(Path + " not found!");
    }
    //ctor
}

Take::~Take()
{
    //dtor
}

int Take::Callback(const char* path, const struct stat *sb, int typeflag)
{
    return 0;
}

void Take::ChangeGroup(string path, int owner)
{

}

void Take::ChangeOwner(string path, int owner)
{

}

void Take::Overtake(string path)
{
    char * p = realpath(path.c_str(), NULL);

    if (p == NULL)
    {
        Debugging::ErrorLog(path + " doesn't exist!");
        return;
    }

    string real = p;

    Debugging::DebugLog(path + " resolved to " + real);
    if (this->Verify(real))
    {
        ChangeOwner(real, Preferences::uid);
        return;
    }
    Debugging::WarningLog("Not taking the ownership of " + real + " because you don't meet the requirements");
}

bool Take::Verify(string path)
{
    return false;
}
