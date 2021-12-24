#pragma once

#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// namespace Engine
// {
//     template <typename T>
//     using Ref = std::shared_ptr<T>;

//     template <typename T>
//     using Scope = std::unique_ptr<T>;
// }

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 60
#define FRAME_TIME_TARGET (1000.0f / FPS)

#ifdef DEBUG
#define Debug(x) x;
#endif // DEBUG

#ifdef NDEBUG
#define Debug(x) ;
#endif // NDEBUG