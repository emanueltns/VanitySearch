#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include <string>
#include <random>
#include <sstream>


class StringGenerator {
public:
    StringGenerator(const std::string& initial, int count);
    std::string nextStr();
    void resetStr();

private:
    std::string initial_;
    int count_;
    std::string current_;
    std::string end_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> dis_;

    std::string toHex(unsigned long long num);
};

#endif /* STRING_GENERATOR_H */