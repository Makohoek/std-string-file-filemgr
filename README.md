Build instructions
------------------

After cloning the repo, you will need its dependencies (which are submodules)
This can be done with:

    git submodule update --init --recursive

After that, you can build with Make:

    make

Instructions
------------

Write a custom string class in C++11:
- support some operations: create, clear, append, convert to int, compare, copy, move, iterate over characters

Write a custom file reader/writer class in C++11:
- make use of the custom string class above by writing these strings into an actual file asynchronously, 1 string per line
- also be able to read data from the file as some collection of these strings, again, asynchronously

Finally, create a file system data structure that can support up to a few hundred files:
- be able to find any file by name in the file system
- support printing the size of each file
