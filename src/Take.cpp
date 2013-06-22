 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

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
                if (Preferences::StrictDevice)
                {
                    struct stat info;
                    stat(Path.c_str(), &info);
                    Preferences::Device = info.st_dev;
                }
                if (Overtake(Path))
                {
                    Debugging::DebugLog("Resolving tree");
                    int flag = 0;
                    flag |= FTW_PHYS;
                    nftw(Path.c_str(), Callback, 1, flag);
                }
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

int Take::Callback(const char* path, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    string p = path;
    Debugging::DebugLog("Recursively overtaking " + p);
    if (Preferences::StrictDevice)
    {
        struct stat info;
        stat(path, &info);
        if (Preferences::Device != info.st_dev)
        {
            Debugging::WarningLog("Not overtaking " + p + " because it lives on a different filesystem");
            return 0;
        }
    }
    ChangeOwner(p, Preferences::uid);
    if (Preferences::Group)
    {
        ChangeGroup(p, Preferences::guid);
    }
    return 0;
}

void Take::ChangeGroup(string path, gid_t owner)
{
    Debugging::DebugLog("Changing group of " + path, 2);
    if (chown(path.c_str(), (uid_t)-1, owner) != 0)
    {
        Debugging::WarningLog("Unable to change group of " + path);
    }
}

void Take::ChangeOwner(string path, uid_t owner)
{
    Debugging::DebugLog("Changing owner of " + path, 2);
    if (chown(path.c_str(), owner, (gid_t)-1) != 0)
    {
        Debugging::WarningLog("Unable to change owner of " + path);
    }
}

bool Take::Overtake(string path)
{
    char * p = realpath(path.c_str(), NULL);

    if (p == NULL)
    {
        Debugging::ErrorLog(path + " doesn't exist!");
        return false;
    }

    string real = p;

    Debugging::DebugLog(path + " resolved to " + real);
    if (this->Verify(real))
    {
        ChangeOwner(real, Preferences::uid);
        if (Preferences::Group)
        {
            ChangeGroup(real, Preferences::guid);
        }
        return true;
    }
    Debugging::WarningLog("Not taking the ownership of " + real + " because you don't meet the requirements");
    return false;
}

bool Take::Verify(string path)
{
    string root;
    if (path[0] != '/' || path == "/")
    {
        Debugging::DebugLog("Invalid path (not allowed for security reasons) " + path);
        return false;
    }
    root = path.substr(0, path.find_last_of('/'));
    if (root == "")
    {
        Debugging::DebugLog("Invalid path (not allowed for security reasons) " + path);
        return false;
    }
    Debugging::DebugLog(path + " parent directory: " + root);
    struct stat info;
    stat(root.c_str(), &info);
    if (Preferences::uid == info.st_uid)
    {
        if (Preferences::StrictGroup)
        {
            if (Preferences::guid != info.st_gid)
            {
                Debugging::WarningLog("You aren't matching the group requirement");
                return false;
            }
        }
        return true;
    }
    Debugging::WarningLog("You aren't matching the user requirement");
    return false;
}
