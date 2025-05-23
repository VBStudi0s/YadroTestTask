#include <iostream>
#include <fstream>

#include "TapeSorter/TapeSorter.h"
#include "Tape/TapeHandler.h"

int main()
{
    std::string testname("sort1.txt");
    std::ofstream file(testname);
    for(int i=10; i>0; i--)
        file<<i<<'\n';
    file.close();

    
    std::string ansname("ans1.txt");
    {
    auto inp =  std::make_unique<TapeHandler>(testname);
    auto outp = std::make_unique<TapeHandler>(ansname);

    TapeSorter s(std::move(inp), std::move(outp), 1000);
    s.sort();
    }
}