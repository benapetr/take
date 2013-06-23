 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#include <iostream>
#include <unistd.h>
#include <ftw.h>
#include <fnmatch.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

#include "../include/Debugging.h"
#include "../include/Preferences.h"
#include "../include/Take.h"

//! Number of total errors that happened during the run of take
unsigned int Take::Errors = 0;
//! Number of successful overtakes
unsigned int Take::Successful = 0;

//! Constructor for Take
//! @param Path The path of the file to be overtaken
Take::Take(string Path)
{
    Debugging::DebugLog("Taking " + Path);
    Take::FD fd = Lock(Path);
    if (fd < 0)
    {
        return;
    }
    struct stat s;
    if( fstat(fd,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            if (Preferences::Recursive)
            {
                // we need to overtake it recursively
                if (Preferences::StrictDevice)
                {
                    Preferences::Device = s.st_dev;
                }
                // attempt to overtake the root folder, which makes a check as well
                if (Overtake(Path, fd))
                {
                    Debugging::DebugLog("Resolving tree");
                    int flag = 0;
                    flag |= FTW_PHYS;
                    nftw(Path.c_str(), Callback, 1, flag);
                } else
                {
                    Preferences::RC = DEFAULT_EC;
                    Errors++;
                }
                return;
            }
            if (!Overtake(Path, fd))
            {
                Preferences::RC = DEFAULT_EC;
                Errors++;
            } else
            {
                Successful++;
            }
            return;
        }
        else if( s.st_mode & S_IFREG )
        {
            //it's a file
            if (Overtake(Path, fd))
            {
                Successful++;
            }
            else
            {
                Preferences::RC = DEFAULT_EC;
                Errors++;
            }
        }
    }
    else
    {
        //error
        Debugging::ErrorLog(Path + " not found!");
        Errors++;
        Preferences::RC = DEFAULT_EC;
    }
}

//! Desctuctor
Take::~Take()
{
    //dtor
}

//! This is a function that is called for each recursively found object
//! @param path Path of the file to overtake
//! @param sb instance of file stat so that it doesn't need to be called twice
//! @param typeflag type of file
//! @param ftwbuf Buffer of ftw
int Take::Callback(const char* path, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    string p = path;
    if (Preferences::Verbosity > 0)
    {
        Debugging::DebugLog("Recursively overtaking " + p);
    }
    Take::FD f = Lock(path);
    if ( f < 0 )
    {
        Preferences::RC = DEFAULT_EC;
        Errors++;
        return 0;
    }
    struct stat info;
    fstat(f, &info);
    if (Preferences::StrictDevice)
    {
        if (Preferences::Device != info.st_dev)
        {
            Debugging::ErrorLog("Not overtaking " + p + " because it lives on a different filesystem");
            Errors++;
            Preferences::RC = DEFAULT_EC;
            return 0;
        }
    }
    if (!CheckHL(info))
    {
        Debugging::ErrorLog("Not overtaking " + p + " because it has more than 1 hard link");
        Errors++;
        Preferences::RC = DEFAULT_EC;
        return 0;
    }
    if (!CheckGroups(info))
    {
        Debugging::ErrorLog("Not overtaking " + p + " because you aren't member of its group");
        Preferences::RC = DEFAULT_EC;
        Errors++;
        return 0;
    }
    ChangeOwner(p, Preferences::uid, f, Preferences::Group);
    Successful++;
    return 0;
}

//! Change owner of a file
//! @param path Path of a file to change owner for
//! @param owner uid of owner
//! @param fd instance of FD which is related to a file
//! @param ChangeGroup if this is true, the group of a file is changed to users's default group
void Take::ChangeOwner(string path, uid_t owner, Take::FD fd, bool ChangeGroup)
{
    if (!ChangeGroup)
    {
        if (Preferences::Verbosity > 0)
        {
            Debugging::DebugLog("Changing owner of " + path, 2);
        }
        if (fchown(fd, owner, (gid_t)-1) != 0)
        {
            Debugging::WarningLog("Unable to change owner of " + path + ": " + strerror(errno));
        }
        return;
    }
    if (Preferences::Verbosity > 0)
    {
        Debugging::DebugLog("Changing owner:group of " + path, 2);
    }
    if (fchown(fd, owner, Preferences::guid) != 0)
    {
        Debugging::WarningLog("Unable to change group or owner of " + path + ": " + strerror(errno));
    }
}

//! Check if user is a member of group which owns the file
//! @param path Path of a file to check
bool Take::CheckGroups(string path)
{
    if (!Preferences::StrictGroup)
    {
        return true;
    }
    struct stat info;
    stat(path.c_str(), &info);
    return CheckGroups(info);
}

//! Check if user is a member of group which owns the file
//! @param info stat of file to check
bool Take::CheckGroups(struct stat info)
{
    if (!Preferences::StrictGroup)
    {
        return true;
    }
    int curr = 0;
    while (curr < Preferences::NumberOfGroups)
    {
        if (info.st_gid == Preferences::Groups[curr])
        {
            return true;
        }
        curr++;
    }
    return false;
}

//! This function check if file has max 1 hard link
//! @param info Stat of file
bool Take::CheckHL(struct stat info)
{
    if (!Preferences::StrictHL)
    {
        return true;
    }
    if (!(info.st_mode & S_IFREG))
    {
        return true;
    }
    if (info.st_nlink < 2)
    {
        return true;
    }
    return false;
}

//! This function check if file has max 1 hard link
bool Take::CheckHL(string path)
{
    if (!Preferences::StrictHL)
    {
        return true;
    }
    struct stat info;
    stat(path.c_str(), &info);
    if (!(info.st_mode & S_IFREG))
    {
        return true;
    }
    if (info.st_nlink < 2)
    {
        return true;
    }
    return false;
}

//! This function attempt to overtake a file, it return true on success, otherwise false is returned
//! @param path Path of a file - this is only used for debugging, the file mentioned in FD is changed
//! @param fd File descriptor of a file which is supposed to be overtaken
bool Take::Overtake(string path, Take::FD fd)
{
    char * p = realpath(path.c_str(), NULL);

    if (p == NULL)
    {
        Debugging::ErrorLog(path + " doesn't exist!");
        return false;
    }

    string real = p;
    Take::FD RealFd = Lock(real);

    if (RealFd < 0)
    {
        RealFd.Close();
        return false;
    }

    if (Preferences::Verbosity > 0)
    {
        Debugging::DebugLog(path + " resolved to " + real);
    }
    if (this->Verify(real))
    {
        ChangeOwner(real, Preferences::uid, RealFd, Preferences::Group);
        RealFd.Close();
        return true;
    }
    Debugging::ErrorLog("Not taking the ownership of " + real + " because you don't meet the requirements");
    return false;
}

//! This function open a FD for a file so that it is prevented from change
//! @param path Path of a file to lock
Take::FD Take::Lock(string path)
{
    // We open the files and use the file descriptors exclusively
    // to avoid trickery and race conditions
    Take::FD fd = open(path.c_str(), O_RDONLY|O_NOFOLLOW);
    if (fd < 0)
    {
        if (errno == ELOOP)
        {
            Debugging::ErrorLog("Not overtaking " + path + " because it is a symlink");
            return fd;
        }
        Debugging::ErrorLog(path + ": " + strerror(errno));
    }
    return fd;
}

//! Check if user is eligible to overtake the file
//! @param path Path of a file
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
    if (!CheckHL(path))
    {
        Debugging::ErrorLog("File " + path + " contains more than 1 hardlink");
        return false;
    }
    if (Preferences::uid == info.st_uid)
    {
        if (Preferences::StrictGroup)
        {
            if (!CheckGroups(info))
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
