#include <stdexcept>

#include "Tape/TapeHandler.h"

TapeHandler::TapeHandler(std::string file_path, std::string settings_path):
    m_tape(file_path)
{
    // TODO: read settings

    // TODO: read data
}

int TapeHandler::read() const
{
    // TODO: add delay
    return m_tape_data.at(m_pos);
}

void TapeHandler::write(int data)
{
    // TODO: add delay
    m_tape_data.at(m_pos) = data;
}

void TapeHandler::left()
{
    if(m_pos == 0)
        throw std::runtime_error("Out of tape range movement while going left");
    --m_pos;
    // TODO: add delay
}

void TapeHandler::right()
{
    if(m_pos == m_tape_data.size() - 1)
        throw std::runtime_error("Out of tape range movement while going left");
    ++m_pos;
        // TODO: add delay
}

bool TapeHandler::is_start() const
{
    return (m_pos == 0); 
}

bool TapeHandler::is_end() const
{
    return (m_pos == m_tape_data.size() - 1);
}

bool TapeHandler::is_empty() const
{
    return (m_tape_data.empty());
}

TapeHandler::~TapeHandler()
{
    //TODO: write data
}