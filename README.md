take
====

Utility which allow you to take ownership of files (similar to sudo).
Take allows you to overtake ownership of all files or folders inside
of folder which you own.

For example, if there is a folder owned by user root in your own home,
you can execute

    take -gr folder

in order to overtake owner and group for all files recursively

Configuration
=============

There is a file src/Preferences.cpp that contains some static configuration,
which can be changed before you build it.

    bool Preferences::StrictGroup = false;
    bool Preferences::StrictDevice = false;
    bool Preferences::StrictHL = true;

StrictGroup will make a tool require the file group match the user's primary group
StrictDevice will require all subfiles during recursive mode to be on same filesystem
StrictHL will not overtake any file with more than 1 hardlink
