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
        return -2;
    }
    delete parser;
    return 0;
}
