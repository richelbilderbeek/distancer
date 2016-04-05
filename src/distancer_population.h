#ifndef POPULATION_H
#define POPULATION_H

#include <map>
#include <vector>
#include "distancer_individual.h"
#include "distancer_sil.h"

using population = std::vector<individual>;

std::map<sil,int> tally_sils(const population& any_population) noexcept;

#endif // POPULATION_H
