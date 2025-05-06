#pragma once

#include <deque>
#include <string>
#include "Tape/ITape.h"

struct TapeSettings {
    int write_delay = 0;
    int read_delay = 0;
    int move_delay = 0;
};

/*
 * Implements ITape by emulating a tape with a deque.
 * Supports automatic extension, but tracks valid length
 * so that is_start()/is_end() reflect only written cells.
 */
class TapeHandler : public ITape {
    std::string    m_tape_file;
    std::deque<int> m_tape_data;    // all cells (valid + buffer)
    size_t         m_pos_index{0};   // current head position
    size_t         m_valid_len{0};   // number of valid (written) cells
    TapeSettings   m_settings;

    void read_settings(const std::string& path);

public:
    TapeHandler(const std::string& file_path,
                const std::string& settings_path = "");
    ~TapeHandler() override;

    int  read() const override;
    void write(int data) override;
    void left() override;
    void right() override;
    bool is_start() const override;
    bool is_end()   const override;
    bool is_empty() const override;
};
