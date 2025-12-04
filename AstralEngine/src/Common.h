#pragma once

#include <variant>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <format>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef AST_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;