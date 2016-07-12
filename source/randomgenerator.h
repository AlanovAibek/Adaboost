#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

#include <random>
#include <chrono>

class RandomGenerator {
public:
    RandomGenerator(uint64_t seed=std::chrono::system_clock::now().time_since_epoch().count()):
    generator_(seed) {}
    
    uint64_t operator() ();
private:
    std::mt19937_64 generator_;
};

#endif  // RANDOMGENERATOR_H_