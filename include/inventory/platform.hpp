#pragma once

// We have to drop nodiscard for clang.
#if defined(__clang__)
#define INV_NODISCARD

#else
#define INV_NODISCARD [[nodiscard]]

#endif

// Also, make sure that we do not compile in anything less than C++20.
#if __cplusplus < 202002L
#error This library requires C++20!

#endif