#pragma once

#include <QString>

#include <type_traits>

namespace ReflectionApi {
namespace SFINAE {

// Структура для проверки наличия оператора toString
template<typename T, typename = void>
struct has_to_string : std::false_type
{
};

template<typename T>
struct has_to_string<T, std::void_t<decltype(std::declval<T>().toString())>>
    : std::true_type
{
};

template<typename T>
constexpr bool has_to_string_v = has_to_string<T>::value;

// Структура для проверки наличия оператора fromString
template<typename T, typename = void>
struct has_from_string : std::false_type
{
};

template<typename T>
struct has_from_string<T, std::void_t<decltype(T::fromString(QString()))>>
    : std::true_type
{
};

template<typename T>
constexpr bool has_from_string_v = has_from_string<T>::value;

} // namespace SFINAE
} // namespace ReflectionApi
