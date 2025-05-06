#pragma once

/*
* Interface describes Tape operations:
* - read data on current position;
* - write data to current position;
* - move one position left;
* - move one position right;
* - see if it is tape start;
* - see if it is tape end;
* - see if tape is empty;
*/
class ITape
{
public:
    // Reads data on current position
    virtual int read() const = 0;

    // Writes data on current position
    virtual void write(int data) = 0;

    // Moves one position left
    virtual void left() = 0;

    // Moves one position right
    virtual void right() = 0;

    // Returns true if it is start of the tape
    virtual bool is_start() const = 0;

    // Returns true if it is end of the tape
    virtual bool is_end() const = 0;

    // Returns true if tape in empty
    virtual bool is_empty() const = 0;

    virtual ~ITape() = default;
};