#include <string.h>
#include "../include/Parser.h"
#include "../include/Preferences.h"
#include "../include/Debugging.h"

Parser::Parser(int c, char *v[])
{

}

void Parser::ShowHelp()
{

}

bool Parser::Parse()
{
    if (argc < 2)
    {
        Debugging::Log("Usage: take [-rhvg] [group] file1, file2, folder...");
    }

    int curr = 1;
    while (curr < argc)
    {
        string parameter = argv[curr];
        if (parameter == "-h" || parameter == "--help")
        {
            ShowHelp();
            continue;
        }
        if (parameter.size() > 2 && parameter.substr(0, 2) == "-v")
        {
            Preferences::Verbosity++;
            unsigned int c = 2;
            while (c < parameter.size())
            {
                if (parameter[c] != 'v' )
                {
                    break;
                }
                Preferences::Verbosity++;
                c++;
            }
            continue;
        }
        Preferences::Objects.push_back(parameter);
        curr++;
    }

    return false;
}

Parser::~Parser()
{

}
