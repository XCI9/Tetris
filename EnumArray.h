#pragma once

#include <array>
#include <algorithm>
#include "magic_enum.hpp"

template<typename Enumerator, class T>
class enumArray : public std::array<T, magic_enum::enum_count<Enumerator>()> {
public:
    constexpr T& operator[] (const Enumerator enumerator);

    const T& operator[] (const Enumerator enumerator) const;
};

template<typename Enumerator, class T>
constexpr T& enumArray<Enumerator, T>::operator[] (const Enumerator enumerator) {
    return std::array<T, magic_enum::enum_count<Enumerator>()>::operator[](magic_enum::enum_integer(enumerator));
}

template<typename Enumerator, class T>
const T& enumArray<Enumerator, T>::operator[] (const Enumerator enumerator) const {
    return std::array<T, magic_enum::enum_count<Enumerator>()>::operator[](magic_enum::enum_integer(enumerator));
}

template<typename Key, typename Value, std::size_t Size>
class ConstMap : public std::array<std::pair<Key, Value>, Size>{
public:
    ConstMap(const std::array<std::pair<Key,Value>,Size>& arr):
    std::array<std::pair<Key,Value>,Size>{arr}
    {}

    [[nodiscard]]constexpr Value operator[] (const Key& key);
};

template<typename Key, typename Value, std::size_t Size>
constexpr Value ConstMap<Key,Value,Size>::operator[] (const Key& key){
    const auto it{
        std::find_if(this->begin(),this->end(),
                     [&key](const auto& e){return e.first == key;})
    };

    if (it!=this->end())
        return it->second;
    else
        throw std::range_error("Key Not Found!");
}
