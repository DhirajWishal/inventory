#pragma once

#include "platform.hpp"
#include <array>

namespace inventory
{
	/**
	 * @brief Bit set class.
	 * This class is used to store a `Bits` number of bits. The main difference between this and the `std::bitset` is that, the `std::bitset` uses `bool`s to store
	 * its values whereas this uses actual bits to store values.
	 *
	 * @tparam Bits The number of bits.
	 */
	template <uint64_t Bits>
	class bit_set final
	{
		/**
		 * @brief Bit field structure.
		 * This contains 1 byte worth of 8 bits which can be accessed seperately.
		 */
		struct bit_field
		{
			union
			{
				struct
				{
					bool m_A : 1;
					bool m_B : 1;
					bool m_C : 1;
					bool m_D : 1;
					bool m_E : 1;
					bool m_F : 1;
					bool m_G : 1;
					bool m_H : 1;
				};

				uint8_t m_Value; // This variable is there to sum up the bits in the bit field and to easily compare and do other operations.
			};

			/**
			 * @brief Is equal to operator.
			 *
			 * @param other The other bit field.
			 * @return true if this is equal to the other.
			 * @return false if this is not equal to the other.
			 */
			constexpr INV_NODISCARD bool operator==(const bit_field other) const { return m_Value == other.m_Value; }

			/**
			 * @brief Is not equal to operator.
			 *
			 * @param other The other bit field.
			 * @return true if this is not equal to the other.
			 * @return false if this is equal to the other.
			 */
			constexpr INV_NODISCARD bool operator!=(const bit_field other) const { return m_Value != other.m_Value; }

			/**
			 * @brief Less than operator.
			 *
			 * @param other The other bit field to compare.
			 * @return true if this is less than the other.
			 * @return false if this is grater than or equal to the other.
			 */
			constexpr INV_NODISCARD bool operator<(const bit_field other) const { return m_Value < other.m_Value; }
		};

		/**
		 * @brief Resolve the array size.
		 *
		 * @tparam size The user defined size.
		 * @return constexpr uint64_t The array size to set.
		 */
		template <uint64_t size>
		static consteval INV_NODISCARD uint64_t resolve_array_size()
		{
			if constexpr (size % 8 == 0)
				return size / 8;
			else
				return (size / 8) + 1;
		}

	public:
		/**
		 * @brief Default constructor.
		 */
		constexpr bit_set() = default;

		/**
		 * @brief Access a bit in the given position.
		 *
		 * @param pos The position of the bit.
		 * @return true if the bit is 1.
		 * @return false if the bit is 0.
		 */
		constexpr INV_NODISCARD bool &access(const uint64_t pos)
		{
			const auto index = pos / 8;
			switch (pos % 8)
			{
			case 1:
				return m_Bytes[index].m_B;

			case 2:
				return m_Bytes[index].m_C;

			case 3:
				return m_Bytes[index].m_D;

			case 4:
				return m_Bytes[index].m_E;

			case 5:
				return m_Bytes[index].m_F;

			case 6:
				return m_Bytes[index].m_G;

			case 7:
				return m_Bytes[index].m_H;

			default:
				return m_Bytes[index].m_A;
			}
		}

		/**
		 * @brief Test a given position to check if the bit value is 1 or 0.
		 *
		 * @param pos The position of the bit.
		 * @return true if the bit is 1.
		 * @return false if the bit is 0.
		 */
		constexpr INV_NODISCARD bool test(const uint64_t pos) const
		{
			const auto field = m_Bytes[pos / 8];
			switch (pos % 8)
			{
			case 1:
				return field.m_B;

			case 2:
				return field.m_C;

			case 3:
				return field.m_D;

			case 4:
				return field.m_E;

			case 5:
				return field.m_F;

			case 6:
				return field.m_G;

			case 7:
				return field.m_H;

			default:
				return field.m_A;
			}
		}

		/**
		 * @brief Get the container that's actually holding the data.
		 *
		 * @return constexpr decltype(auto) The container.
		 */
		constexpr INV_NODISCARD decltype(auto) container() const { return m_Bytes; }

		/**
		 * @brief Index a single bit using the position of it.
		 *
		 * @param pos The position to access.
		 * @return true if the bit value is 1.
		 * @return false if the bit value is 0.
		 */
		constexpr INV_NODISCARD bool &operator[](const uint64_t pos) { return access(pos); }

		/**
		 * @brief Index a single bit using the position of it.
		 *
		 * @param pos The position to access.
		 * @return true if the bit value is 1.
		 * @return false if the bit value is 0.
		 */
		constexpr INV_NODISCARD bool operator[](const uint64_t pos) const { return test(pos); }

	private:
		std::array<bit_field, resolve_array_size<Bits>()> m_Bytes = {};
	};
} // namespace inventory
