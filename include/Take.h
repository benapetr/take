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
        static int Callback(const char* path, const struct stat *sb, int typeflag);
        static void ChangeGroup(string path, gid_t owner);
        static void ChangeOwner(string path, uid_t owner);
};

#endif // TAKE_H
