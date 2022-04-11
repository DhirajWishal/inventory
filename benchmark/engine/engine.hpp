// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "components.hpp"
#include <inventory/component_store.hpp>
#include <inventory/container.hpp>

namespace engine
{
	class engine final : public inventory::container<engine>
	{
	public:
		void update([[maybe_unused]] const model_component &component) const;
		void update([[maybe_unused]] const camera_component &component) const;
		void update([[maybe_unused]] const position_component &component) const;

		template <class... Types>
		void update_components(const inventory::component_store<Types...> &store) const { (update(inventory::get_component<Types>(store)), ...); }

		template <class Type>
		void operator()(Type &element)
		{
			//element.update();
			update_components(element);
			[[maybe_unused]] volatile int x = 0;
		}

		template <class Type>
		void operator()(const Type &element) const
		{
			update_components(element);
			[[maybe_unused]] volatile int x = 0;
		}
	};
}