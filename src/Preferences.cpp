#include <iostream>
#include <list>
#include <unistd.h>
#include <sys/stat.h>
#include "../include/Preferences.h"

using namespace std;

bool Preferences::StrictGroup = false;
int Preferences::Verbosity = 0;
bool Preferences::Recursive = false;
bool Preferences::Group = false;
list<string> Preferences::Objects = list<string>();
gid_t Preferences::guid = getgid();
uid_t Preferences::uid = getuid();
uid_t Preferences::euid = geteuid();
