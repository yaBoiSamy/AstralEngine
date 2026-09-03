#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <variant>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <ranges>
#include <functional>
#include <format>
#include <ranges>

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Astral/Misc/Log/Log.h"
#include <glm/glm.hpp>

namespace Astral {

    template<typename T, typename Deleter = std::default_delete<T>>
    using Box = std::unique_ptr<T, Deleter>;

    template<typename T>
    using Arc = std::shared_ptr<T>;

    using ByteBox = Box<std::byte, void(*)(std::byte*)>;

    template<typename T>
    ByteBox ToBytes(Box<T> ptr) {
        return ByteBox{
            reinterpret_cast<std::byte*>(ptr.release()),
            [](std::byte* p) {
                delete reinterpret_cast<T*>(p);
            }
        };
    }

    template<typename ArrayT>
    ByteBox ToBytesArray(Box<ArrayT> ptr) {
        return ByteBox{
            reinterpret_cast<std::byte*>(ptr.release()),
            [](std::byte* p) {
                delete[] reinterpret_cast<ArrayT*>(p);
            }
        };
    }

    template<typename ArrayT>
    ByteBox ToBytesArray(std::span<const ArrayT> data) {
        auto result = std::make_unique<ArrayT[]>(data.size());
        std::copy(data.begin(), data.end(), result.get());
		return ToBytesArray(std::move(result));
    }
}


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

