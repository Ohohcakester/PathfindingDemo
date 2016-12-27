#ifndef _RANDOM_NUMBER_GENERATOR_H_
#define _RANDOM_NUMBER_GENERATOR_H_

#include <random>
#include <ctime>

class RNG {
    std::default_random_engine generator;

public:
    RNG(unsigned seed): generator(seed) {}

    // WARNING: INCLUSIVE OF BOTH a AND b
    inline int intRange(int a, int b) {
        std::uniform_int_distribution<int> dist(a,b);
        return dist(generator);
    }

    // Random integer between 0 and maxIndex-1
    inline size_t index(size_t maxIndex) {
        std::uniform_int_distribution<size_t> dist(0,maxIndex-1);
        return dist(generator);
    }

    inline float floatRange(float a, float b) {
        std::uniform_real_distribution<float> dist(a,b);
        return dist(generator);
    }

    inline bool bernoulli(float trueProbability) {
        std::bernoulli_distribution dist(trueProbability);
        return dist(generator);
    }
};

extern RNG global_rng;

#endif