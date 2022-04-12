#pragma once

#include <cstdint>
#include <vector>

namespace inventory
{
	template <class Type>
	class sparse_array
	{
		using index_type = uint32_t;
		std::vector<Type> m_Container;
		std::vector<index_type> m_ReverseIndexes;

		index_type m_CurrentIndex = 0;

		struct byte_board
		{
			enum class position : uint8_t
			{
				One,
				Two,
				Three,
				Four,
				Five,
				Six,
				Seven,
				Eight
			};

			bool is_active(const position pos) const
			{
				switch (pos)
				{
				case position::One:
					return m_One;
				case position::Two:
					return m_Two;
				case position::Three:
					return m_Three;
				case position::Four:
					return m_Four;
				case position::Five:
					return m_Five;
				case position::Six:
					return m_Six;
				case position::Seven:
					return m_Seven;
				case position::Eight:
					return m_Eight;
				}

				return false;
			};

			bool m_One : 1;
			bool m_Two : 1;
			bool m_Three : 1;
			bool m_Four : 1;
			bool m_Five : 1;
			bool m_Six : 1;
			bool m_Seven : 1;
			bool m_Eight : 1;
		};

	public:
	};
} // namespace inventory
