// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#if defined(__APPLE__) || defined(__MACH__)
#	ifdef defined(__clang__)
#		define INV_NODISCARD
#	endif

#else
#	define INV_NODISCARD			[[nodiscard]]
#	define INV_USE_PARALLEL_UNSEQ

#endif