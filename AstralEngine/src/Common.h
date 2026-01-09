#pragma once

#include <variant>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <format>
#include <ranges>

#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Astral/Logging/Log.h"


template<typename T, typename Deleter = std::default_delete<T>>
using ptr = std::unique_ptr<T, Deleter>;


#ifdef AST_PLATFORM_WINDOWS
    //#include <Windows.h>
#endif

#ifdef AST_DEBUG
    #define AST_CORE_ASSERT(expr, msg, ...) \
        do { \
            if (!(expr)) { \
                AST_CORE_ERROR("Assertion failed: " msg, __VA_ARGS__); \
                __debugbreak(); \
            } \
        } while (0)
#else
    #define AST_CORE_ASSERT(expr, ...) ((void)0)
#endif

// For variant overloading
template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

