 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#ifndef TAKE_H
#define TAKE_H

using namespace std;

class Take
{
    public:
        Take(string Path);
        virtual ~Take();
    protected:
    private:
        bool Overtake(string path);
        bool Verify(string path);
        static int Callback(const char* path, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
        static void ChangeGroup(string path, gid_t owner);
        static void ChangeOwner(string path, uid_t owner);
        static bool CheckHL(string path);
        static bool CheckHL(struct stat info);
};

#endif // TAKE_H
