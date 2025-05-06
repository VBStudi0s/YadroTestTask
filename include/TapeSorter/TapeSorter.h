#pragma once

#include <memory>
#include <string>
#include <vector>
#include <cstddef>
#include "../Tape/ITape.h"

/*
 * Class performing memory-constrained tape sort using k-way merge.
 */
class TapeSorter {
public:
    // Accepts input and output tapes and memory limit in bytes
    TapeSorter(std::unique_ptr<ITape> input,
               std::unique_ptr<ITape> output,
               size_t memory_limit);

    // Sorts input tape into output tape
    void sort();

private:
    std::unique_ptr<ITape> m_input;
    std::unique_ptr<ITape> m_output;
    size_t m_memory_limit;

    // Performs in-memory sorting and writes runs to temp tapes
    std::vector<std::string> create_sorted_runs();

    // Performs k-way merge on sorted temp tapes and writes to output
    void merge_runs(const std::vector<std::string>& run_files);

    // Creates temp tape filename
    std::string temp_filename(size_t index) const;

    // Clears content of a tape (used before final write)
    void clear_tape(ITape& tape);
};
