#include <stdexcept>
#include <fstream>

#include "Tape/TapeHandler.h"

TapeHandler::TapeHandler(std::string file_path, std::string settings_path):
    m_tape_file(file_path)
{
    m_pos = m_tape_data.begin();
    // TODO: read settings

    std::ifstream tape(m_tape_file);
    if(tape.is_open())
    {
        int buf = 0;
        while(tape>>buf)
        {
            m_tape_data.push_back(buf);
        }
        if(tape.fail() && !tape.eof())
            throw std::runtime_error("Error while reading tape file");
    }
    tape.close();

    m_pos = m_tape_data.begin();
}

int TapeHandler::read() const
{
    // TODO: add delay
    return *m_pos;
}

void TapeHandler::write(int data)
{
    // TODO: add delay
    if(m_tape_data.empty())
    {
        m_tape_data.emplace_back(data);
        m_pos = m_tape_data.begin();
    }
    else
        *m_pos = data;
}

void TapeHandler::left()
{
    if(m_pos == m_tape_data.begin())
    {
        m_tape_data.emplace_front();
        m_pos = m_tape_data.begin();
    }
    else
        --m_pos;
    // TODO: add delay
}

void TapeHandler::right()
{
    auto temp_pos = m_pos;
    if(++temp_pos == m_tape_data.end())
    {
        m_tape_data.emplace_back();
    }
    ++m_pos;
    // TODO: add delay
}

bool TapeHandler::is_start() const
{
    return (m_pos == m_tape_data.begin()); 
}

bool TapeHandler::is_end() const
{
    auto temp_pos = m_pos;
    return (++temp_pos == m_tape_data.end());
}

bool TapeHandler::is_empty() const
{
    return (m_tape_data.empty());
}

TapeHandler::~TapeHandler()
{
    std::ofstream tape(m_tape_file);
    if(tape.is_open())
    {
        for(const auto& i: m_tape_data)
        {
            tape<<i<<' ';
        }
        tape.close();
    }
}