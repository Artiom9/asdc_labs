#include <iostream>
#include <vector>
#include <span>

#include "../data/data.hpp"
#include "serializer.hpp"

template <typename T>
std::size_t linearSearch(std::span<T> arr, const T &key)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return SIZE_MAX;
}

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node *binarySearchTree(Node *root, int key)
{
    if (root == nullptr || root->data == key)
    {
        return root;
    }

    if (root->data < key)
    {
        return binarySearchTree(root->right, key);
    }

    return binarySearchTree(root->left, key);
}

template <typename T>
std::size_t binarySearch(std::span<T> arr, const T &key)
{
    std::size_t left = 0;
    std::size_t right = arr.size() - 1;

    while (left <= right)
    {
        auto mid = left + (right - left) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return SIZE_MAX;
}

template <typename T>
std::size_t interpolationSearch(std::span<T> arr, const T &key)
{
    std::size_t low = 0;
    std::size_t high = arr.size() - 1;

    while (low <= high && key >= arr[low] && key <= arr[high])
    {
        auto pos = low + ((key - arr[low]) * (high - low) / (arr[high] - arr[low]));

        if (arr[pos] == key)
        {
            return pos;
        }
        else if (arr[pos] < key)
        {
            low = pos + 1;
        }
        else
        {
            high = pos - 1;
        }
    }

    return SIZE_MAX;
}

std::vector<Car> readCsv(std::istream &is)
{
    std::vector<Car> cars{};
    while (not is.eof())
    {
        auto car = deserializeCar(is);
        if (not car.has_value())
        {
            std::cerr << "Не удалось десериализовать объект :(" << std::endl;
            continue;
        }
        cars.push_back(*car);
    }

    return cars;
}

bool writeCsv(std::ostream &os, std::vector<Car> &cars)
{
    bool noErrors = true;
    for (auto &car : cars)
    {
        if (not serializeCar(os, car))
        {
            std::cerr << "Не удалось сериализовать объект :(" << std::endl;
            noErrors = false;
        }
    }

    return noErrors;
}

int main()
{
    std::fstream file("data.txt");
    if (not file.is_open())
    {
        std::cerr << "Не удалось открыть файл :(" << std::endl;
        return 1;
    }

    auto cars = readCsv(file);

    if (cars.empty())
    {
        std::cerr << "Файл пустой :(" << std::endl;
        return 2;
    }
    else
    {
        cars[0].horse_power += 10;
    }

    cars.push_back({"Ferrari", Color::RED, 855});

    for (auto &car : cars)
    {
        std::cout << car.name << " " << static_cast<int>(car.color) << " " << car.horse_power << std::endl;
    }

    std::vector v {1, 2, 3, 4, 5, 7};
    const auto v_span = std::span(v);
    std::cout << "Index of value 4: " << linearSearch(v_span, 4) << std::endl;
    std::cout << "Index of value 4: " << binarySearch(v_span, 4) << std::endl;
    std::cout << "Index of value 4: " << interpolationSearch(v_span, 4) << std::endl;

    if (not writeCsv(file, cars))
    {
        std::cerr << "Не удалось сериализовать объекты :(" << std::endl;
        return 3;
    }

    file.close();

    return 0;
}