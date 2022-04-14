// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#if !defined(__APPLE__) && !defined(__MACH__)
#	define INV_USE_UNSEQ

#endif

#ifdef __clang__
#	define INV_NODISCARD

#else
#	define INV_NODISCARD 			[[nodiscard]]

#endif