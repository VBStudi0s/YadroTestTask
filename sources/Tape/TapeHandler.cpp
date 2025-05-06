#include "Tape/TapeHandler.h"
#include <fstream>
#include <stdexcept>
#include <thread>

// --- construction / destruction ---

TapeHandler::TapeHandler(const std::string& file_path,
                         const std::string& settings_path)
  : m_tape_file(file_path)
{
    // load settings if provided
    if (!settings_path.empty()) {
        try { read_settings(settings_path); }
        catch (...) {/* ignore, use defaults */}
    }

    // load initial tape contents as valid cells
    std::ifstream in(m_tape_file);
    if (in) {
        int v;
        while (in >> v) {
            m_tape_data.push_back(v);
            ++m_valid_len;
        }
        if (in.fail() && !in.eof())
            throw std::runtime_error("Error while reading tape file");
    }
    // position at start of valid area (if any)
    if (m_valid_len == 0) {
        // empty tape: leave deque empty, pos_index 0
        m_pos_index = 0;
    } else {
        m_pos_index = 0;
    }
}

TapeHandler::~TapeHandler() {
    // write only valid cells back to file
    std::ofstream out(m_tape_file);
    if (!out) return;
    for (size_t i = 0; i < m_valid_len; ++i) {
        out << m_tape_data[i] << '\n';
    }
}

// --- settings loader ---

void TapeHandler::read_settings(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Unable to open settings file");
    TapeSettings tmp;
    if (!(in >> tmp.write_delay
           >> tmp.read_delay
           >> tmp.move_delay)
        || tmp.write_delay < 0
        || tmp.read_delay  < 0
        || tmp.move_delay  < 0)
    {
        throw std::runtime_error("Corrupted settings data");
    }
    m_settings = tmp;
}

// --- tape operations ---

int TapeHandler::read() const {
    if (m_pos_index >= m_valid_len)
        throw std::out_of_range("Read beyond valid tape");
    std::this_thread::sleep_for(
        std::chrono::milliseconds(m_settings.read_delay));
    return m_tape_data[m_pos_index];
}

void TapeHandler::write(int data) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(m_settings.write_delay));

    // if writing beyond valid, extend valid area
    if (m_pos_index >= m_valid_len) {
        // ensure deque is large enough
        if (m_pos_index >= m_tape_data.size())
            m_tape_data.resize(m_pos_index + 1, 0);
        m_valid_len = m_pos_index + 1;
    }
    m_tape_data[m_pos_index] = data;
}

void TapeHandler::left() {
    if (m_pos_index == 0) {
        // extend at front: new blank cell becomes position 0
        m_tape_data.push_front(0);
        ++m_valid_len;
        // head stays at new cell 0
        m_pos_index = 0;
    } else {
        --m_pos_index;
    }
    std::this_thread::sleep_for(
        std::chrono::milliseconds(m_settings.move_delay));
}

void TapeHandler::right() {
    // if moving past current deque, add blank
    if (m_pos_index + 1 >= m_tape_data.size()) {
        m_tape_data.push_back(0);
    }
    ++m_pos_index;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(m_settings.move_delay));
}

// only consider valid cells for start/end

bool TapeHandler::is_start() const {
    return (m_valid_len > 0 && m_pos_index == 0);
}

bool TapeHandler::is_end() const {
    return (m_valid_len > 0
            && m_pos_index + 1 == m_valid_len);
}

bool TapeHandler::is_empty() const {
    return (m_valid_len == 0);
}
