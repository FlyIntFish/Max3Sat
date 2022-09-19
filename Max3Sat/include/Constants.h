#pragma once
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <cstdint>
#include <unordered_map>

/**********************************
*
*		Random Number Generator mode -
*		define XORSHIFT_MODE to use xorshift
*		otherwise mt19937 is used instead
*
* 
**********************************/

#define XORSHIFT_MODE

#define firstVal val[0]
#define secondVal val[1]
#define thirdVal val[2]

#define firstPositive positive[0]
#define secondPositive positive[1]
#define thirdPositive positive[2]

#define callAssert(exp) if(!(exp)){\
std::cerr<<__FILE__<<" line:"<<__LINE__<<"\tassertion: "<<#exp;\
abort();}

using Integer = int16_t;
using UInteger = uint16_t;

template <typename T>
using Set = std::unordered_set<T>;

template <typename T, typename R>
using Map = std::unordered_map<T, R>;

constexpr UInteger AMOUNT_OF_POPULATIONS = 300;
constexpr UInteger AMOUNT_OF_GENERATIONS = 5;
constexpr UInteger DEFAULT_CONTAINER_SIZE = 500;
constexpr UInteger DEFAULT_CROSSING_PROBABILITY = 70;
constexpr UInteger DEFAULT_MUTATION_PROBABILITY = 75;
constexpr UInteger DEFAULT_AMOUNT_OF_GENES_TO_MUTATE = 20;
constexpr UInteger DEFAULT_MIGRATION_PROBABILITY = 0;
constexpr UInteger DEFAULT_TOURNAMENT_SIZE = 5;
constexpr UInteger DEFAULT_ELITISM_VARIABLE = 5;

UInteger fastAbs(Integer value);

#define absolute(x) fastAbs(x)



