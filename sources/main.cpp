#include <iostream>

#include "Tape/TapeHandler.h"

int main()
{
    std::cout<<"Hello, Yadro!\n";
    TapeHandler th("./test.txt");
    std::cout<<th.is_empty()<<'\n';
    th.write(12);
    th.left();
    th.write(11);
    std::cout<<"Goodbye!\n";
    return 0;
}