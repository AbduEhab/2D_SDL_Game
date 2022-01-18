#pragma once

#include <assert.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>

// namespace Engine
// {
//     template <typename T>
//     using Ref = std::shared_ptr<T>;

//     template <typename T>
//     using Scope = std::unique_ptr<T>;
// }

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 30
#define FRAME_TIME_TARGET (1000.0f / FPS)

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::_V2::system_clock::time_point;

#ifdef DEBUG
#define Debug(x) x
#define DebugPrint(x) \
    std::cout << x << std::endl
#endif // DEBUG

#ifdef NDEBUG
#define Debug(x) ;
#define DebugPrint(x) ;
#endif // NDEBUG