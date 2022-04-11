// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "components.hpp"

#include <entt/entt.hpp>

#include <inventory/system.hpp>
#include <inventory/entity_factory.hpp>

namespace engine
{
    using entity = inventory::entity<inventory::default_index_type>;
    using entity_factory = inventory::entity_factory<inventory::default_index_type>;

	class engine final
	{
		inventory::system<model_component> m_ModelComponents;
		inventory::system<camera_component> m_CameraComponents;
		inventory::system<position_component> m_PositionComponents;
		entity_factory m_Factory;

	public:
		engine() = default;

		entity &create_entity() { return m_Factory.create(); }

		template <class Component>
		decltype(auto) register_to_system(const entity &e)
		{
			if constexpr (std::is_same_v<Component, model_component>)
				return m_ModelComponents.register_entity(e);

			else if constexpr (std::is_same_v<Component, camera_component>)
				return m_CameraComponents.register_entity(e);

			else if constexpr (std::is_same_v<Component, position_component>)
				return m_PositionComponents.register_entity(e);
		}

		template <class Component>
		decltype(auto) get_component(const entity &e)
		{
			if constexpr (std::is_same_v<Component, model_component>)
				return m_ModelComponents.get(e);

			else if constexpr (std::is_same_v<Component, camera_component>)
				return m_CameraComponents.get(e);

			else if constexpr (std::is_same_v<Component, position_component>)
				return m_PositionComponents.get(e);
		}

		void update();

		void update_component([[maybe_unused]] const model_component &component) const;
		void update_component([[maybe_unused]] const camera_component &component) const;
		void update_component([[maybe_unused]] const position_component &component) const;
	};
}