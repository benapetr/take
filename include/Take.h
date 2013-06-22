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
    struct FD
    {
        int fd;
        FD(int f): fd(f)                { };
        ~FD()                           { Close(); };
        void Close()                    { if(fd >= 0) close(fd); };
        operator int (void) const       { return fd; };
    };

    public:
        Take(string Path);
        virtual ~Take();
    protected:
    private:
        bool Overtake(string path, FD fd);
        bool Verify(string path);
        static int Callback(const char* path, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
        static void ChangeOwner(string path, uid_t owner, FD fd, bool ChangeGroup);
        static bool CheckGroups(struct stat info);
        static bool CheckHL(string path);
        static bool CheckHL(struct stat info);
        static bool CheckGroups(string path);
        static FD Lock(string path);
};

#endif // TAKE_H
