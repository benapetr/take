#include <iostream>
#include "include/Preferences.h"
#include "include/Debugging.h"
#include "include/Parser.h"
#include "include/Take.h"

using namespace std;


int main(int argc, char * argv[])
{
    Parser* parser = new Parser(argc, argv);
    if (parser->Parse())
    {
        delete parser;
        return 0;
    }
    delete parser;
    if (Preferences::Verbosity > 0)
    {
        cout << "Verbosity: " << Preferences::Verbosity << endl;
        cout << "DEBUG: your uid: " << Preferences::uid << endl;
        cout << "DEBUG: your euid: " << Preferences::euid << endl;
    }

    if (Preferences::euid > 0)
    {
        Debugging::WarningLog("The binary is missing root suid!!!!!!!!");
    }

    if (Preferences::Group)
    {
        Debugging::DebugLog("Will change the group as well");
    }

    if (Preferences::Recursive)
    {
        Debugging::DebugLog("Operating in recursive mode for all files");
    }

    list<string>::iterator iter;

    for(iter = Preferences::Objects.begin(); iter != Preferences::Objects.end(); iter++)
    {
        Take *take = new Take(*iter);
        delete take;
    }

    return 0;
}
