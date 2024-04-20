#pragma once

#include <fstream>
#include <optional>

#include "../data/data.hpp"

bool serializeCar(std::ostream &os, const Car &car);
std::optional<Car> deserializeCar(std::istream &is);