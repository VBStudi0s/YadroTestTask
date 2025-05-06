#include <stdexcept>
#include <fstream>
#include <iostream>
#include <thread>

#include "Tape/TapeHandler.h"

TapeHandler::TapeHandler(std::string file_path, std::string settings_path):
    m_tape_file(file_path)
{
    m_pos = m_tape_data.begin();
    
    // settings reading
    if(settings_path != "")
    {
        try
        {
            read_settings(settings_path);
        }
        catch(std::exception& e)
        {
            std::cerr<<e.what()<<"\nUsing default settings\n";
        }
    }

    // reading data from the date
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

void TapeHandler::read_settings(const std::string&settings_path)
{
    std::ifstream setts(settings_path);
    if(setts.is_open())
    {
        TapeSettings temp;
        if(!(setts>>temp.write_delay>>temp.read_delay>>temp.move_delay &&
            temp.write_delay >= 0 && temp.read_delay >= 0 && temp.move_delay >= 0))
            throw std::runtime_error("Corrupted settings file data");
        m_settings = temp;
    }
    else
    {
        throw std::runtime_error("Unable to open settings file");
    }
}

int TapeHandler::read() const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(m_settings.read_delay));
    return *m_pos;
}

void TapeHandler::write(int data)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(m_settings.write_delay));
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

    std::this_thread::sleep_for(std::chrono::milliseconds(m_settings.move_delay));
}

void TapeHandler::right()
{
    auto temp_pos = m_pos;
    if(++temp_pos == m_tape_data.end())
    {
        m_tape_data.emplace_back();
    }
    ++m_pos;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(m_settings.move_delay));
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