#include "randomgenerator.h"

uint64_t RandomGenerator::operator() () {
    return generator_();
}