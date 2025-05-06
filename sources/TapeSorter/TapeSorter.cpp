#include "TapeSorter/TapeSorter.h"
#include "Tape/TapeHandler.h"

#include <fstream>
#include <queue>
#include <stdexcept>
#include <filesystem>
#include <limits>
#include <algorithm>
#include <iostream>

TapeSorter::TapeSorter(std::unique_ptr<ITape> input, std::unique_ptr<ITape> output, size_t memory_limit): 
    m_input(std::move(input)), m_output(std::move(output)), m_memory_limit(memory_limit)
{
    if (m_memory_limit < sizeof(int))
        throw std::invalid_argument("Memory limit too small");
}

void TapeSorter::sort() 
{
    auto run_files = create_sorted_runs();
    merge_runs(run_files);
    m_output.reset();
}

std::vector<std::string> TapeSorter::create_sorted_runs() 
{
    std::vector<std::string> run_files;
    const size_t max_ints = m_memory_limit / sizeof(int);
    size_t run_index = 0;

    while (!m_input->is_end() && !m_input->is_empty()) 
    {
        std::vector<int> buffer;
        buffer.reserve(max_ints);

        while (!m_input->is_end() && buffer.size() < max_ints) 
        {
            buffer.push_back(m_input->read());
            if(!m_input->is_end())
                m_input->right();
        }


        std::sort(buffer.begin(), buffer.end());

        std::string run_path = temp_filename(run_index++);
        {
            TapeHandler run_tape(run_path);
            for (int val : buffer) 
            {
                if (run_tape.is_empty()) 
                {
                    run_tape.write(val);
                } 
                else 
                {
                    run_tape.right();
                    run_tape.write(val);
                }
            }
        }

        run_files.push_back(run_path);
    }


    return run_files;
}

void TapeSorter::merge_runs(const std::vector<std::string>& run_files) {
    struct TapeNode {
        ITape* tape;
        int value;
        size_t index;
        bool operator>(const TapeNode& other) const {
            return value > other.value;
        }
    };

    std::vector<std::unique_ptr<ITape>> tapes;
    for (auto const& path : run_files)
        tapes.emplace_back(std::make_unique<TapeHandler>(path));

    std::priority_queue<TapeNode,
                        std::vector<TapeNode>,
                        std::greater<>> min_heap;

    // initial fill
    for (size_t i = 0; i < tapes.size(); ++i) {
        if (!tapes[i]->is_empty()) {
            min_heap.push({ tapes[i].get(), tapes[i]->read(), i });
        }
    }

    bool first_write = true;
    while (!min_heap.empty()) {
        auto node = min_heap.top();
        min_heap.pop();

        if (first_write) {
            m_output->write(node.value);
            first_write = false;
        } else {
            m_output->right();
            m_output->write(node.value);
        }

        if (!node.tape->is_end()) {
            node.tape->right();
            int next_val = node.tape->read();
            min_heap.push({ node.tape, next_val, node.index });
        }
    }
}


std::string TapeSorter::temp_filename(size_t index) const 
{
    return "/tmp/run_" + std::to_string(index) + ".tape";
}

void TapeSorter::clear_tape(ITape& tape) 
{
    while (!tape.is_start()) 
        tape.left();
    while (!tape.is_end()) 
    {
        tape.write(0);  // Overwrite with default
        tape.right();
    }
}
