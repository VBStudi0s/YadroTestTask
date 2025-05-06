#pragma once

#include <list>
#include <string>

#include "Tape/ITape.h"
#include "Tape/TapeSettings.h"

/*
* Class implementing ITape interface using typical files.
* Uses fstream to interact with file corresponding to tape.
* Rewrites info to file after working with the tape.
*/
class TapeHandler: public ITape
{
    std::string m_tape_file;    // file name of corresponding tape file 
    std::list<int> m_tape_data;   // data of the tape
    std::list<int>::iterator m_pos;   // current position on the tape
    TapeSettings m_settings;

    void read_settings(const std::string& settings_path);

public:
    // Receives paths to files corresponding to the tape and settings
    TapeHandler(std::string file_path, std::string settings_path = "");

    // Reads data on current position
    virtual int read() const override;

    // Writes data on current position
    virtual void write(int data) override;

    // Moves one position left
    // Adds new node if moving off the boundaries
    virtual void left() override;

    // Moves one position right
    // Adds new node if moving off the boundaries
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