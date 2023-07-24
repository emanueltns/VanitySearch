#include "StringGeneratorX.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>

StringGenerator::StringGenerator(const std::string& initial, int count)
    : initial_(initial), count_(count), gen_(std::random_device{}()), dis_(0, std::pow(16, count) - 1) {
    resetStr();
}

std::string StringGenerator::toHex(unsigned long long num) {
    std::stringstream ss;
    ss << std::hex << std::setw(count_) << std::setfill('0') << num;
    return ss.str();
}

void StringGenerator::resetStr() {
    unsigned long long start = dis_(gen_);
    unsigned long long end = dis_(gen_);
    if (start > end) std::swap(start, end);

    std::string middle_start = toHex(start);
    std::string middle_end = toHex(end);

    current_ = initial_ + middle_start + "00000000";
    end_ = initial_ + middle_end + "ffffffff";
}

std::string StringGenerator::nextStr() {
    if (current_ > end_) {
        resetStr();
    }

    // Convert suffix of current_ to an integer
    unsigned long long suffix = std::stoull(current_.substr(initial_.size()), nullptr, 16);

    // Increment the suffix
    suffix++;

    // Convert the suffix back to a string and update current_
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(8) << std::hex << suffix;
    current_.replace(initial_.size(), 8, ss.str());

    return current_;
}
