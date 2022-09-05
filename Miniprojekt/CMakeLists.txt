cmake_minimum_required (VERSION 3.8)
project ("Max3Sat")

add_executable(max3sat
"Clause.h" "CMax3SatProblem.h" "Constants.h" "Population.h" "Rand.h" "VariableAssignments.h" "VariableNeighbours.h"
 "Clause.cpp" "CMax3SatProblem.cpp" "Constants.cpp" "Max3Sat.cpp" "Population.cpp" "Rand.cpp" "VariableAssignments.cpp" "VariableNeighbours.cpp" "COptimizer.cpp" "COptimizer.h")
