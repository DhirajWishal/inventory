#pragma once

#if defined(__APPLE__) || defined(__MACH__)
#	define INV_NODISCARD

#else
#	define INV_NODISCARD	[[nodiscard]]

#endif