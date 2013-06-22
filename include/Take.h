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
        void Overtake(string path);
        bool Verify(string path);
        int Callback(const char* path, const struct stat *sb, int typeflag);
        void ChangeGroup(string path, int owner);
        void ChangeOwner(string path, int owner);
};

#endif // TAKE_H
