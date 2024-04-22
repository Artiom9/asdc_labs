#include "serializer.hpp"

bool serializeCar(std::ostream &os, const Car &car)
{
    auto found = car.name.find(',');
    if (found != std::string::npos)
    {
        return false;
    }

    os << car.name << ',';
    os << static_cast<short>(car.color) << ',';
    os << car.horse_power << std::endl;
    return true;
}

std::optional<Car> deserializeCar(std::istream &is)
{
    Car car;

    std::getline(is, car.name, ',');

    std::string color;
    std::getline(is, color, ',');

    try
    {
        auto temp = stoi(color);
        // проверяем выход за диапозон Color
        if (temp < static_cast<int>(Color::RED) || temp > static_cast<int>(Color::GREEN))
        {
            return std::nullopt;
        }
        car.color = static_cast<Color>(temp);
    }
    catch (std::invalid_argument const &ex)
    {
        return std::nullopt;
    }

    std::string horse_power;
    std::getline(is, horse_power);

    try
    {
        car.horse_power = stoi(horse_power);
    }
    catch (std::invalid_argument const &ex)
    {
        return std::nullopt;
    }

    return car;
}