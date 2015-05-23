#include <stdlib.h>
#include <iostream>
#include <signal.h>

#include "ippapp.hpp"

ippapp* app;

void terminate(int)
{
    app->stop();
}

int main(int argc, char** argv)
{
    signal(SIGINT, terminate);
    unsigned short port = 80;
    if(argc == 2)
        port = atoi(argv[1]);
    std::cout << "Starting on " << port << std::endl;
    ippapp a(port);
    app=&a;

    a.join();
}
