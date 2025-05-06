#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Tape/ITape.h"

/*
* Class implementing ITape interface using typical files.
* Uses fstream to interact with file corresponding to tape.
* Implements RAII idioma, creating fstream object in constructor 
* and destroying it in destructor.
* It is consideted that one tape can be read or written
* only by one entity.
*/
class TapeHandler: public ITape
{
    std::fstream m_tape;    // fstream with corresponding tape file 
    std::vector<int> m_tape_data;   // data of the tape
    size_t m_pos = 0;   // current position on the tape
public:
    // Receives paths to files corresponding to the tape and settings
    TapeHandler(std::string file_path, std::string settings_path = "");

    // Reads data on current position
    virtual int read() const override;

    // Writes data on current position
    virtual void write(int data) override;

    // Moves one position left
    virtual void left() override;

    // Moves one position right
    virtual void right() override;

    // Returns true if it is start of the tape
    virtual bool is_start() const override;

    // Returns true if it is end of the tape
    virtual bool is_end() const override;

    // Returns true if tape in empty
    virtual bool is_empty() const override;

    // Writes data to the tape file
    ~TapeHandler();
};