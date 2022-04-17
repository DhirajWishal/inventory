// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "components.hpp"

#include <inventory/system.hpp>
#include <inventory/entity_factory.hpp>
#include <inventory/registry.hpp>

namespace engine
{
	using registry = inventory::default_registry<
		model_component,
		camera_component,
		position_component>;
	using entity = typename registry::entity_index_type;
	using entity_factory = inventory::entity_factory<entity>;

	class engine final
	{
		registry m_Registry;
		registry::callback_index m_ModelCallbackIndex = 0;

	public:
		engine();
		~engine();

		registry &get_registry() { return m_Registry; }
		entity create_entity() { return m_Registry.create_entity(); }

		template <class Component>
		decltype(auto) register_to_system(entity &e)
		{
			if constexpr (std::is_same_v<Component, model_component>)
				return m_Registry.register_to_system<model_component>(e);

			else if constexpr (std::is_same_v<Component, camera_component>)
				return m_Registry.register_to_system<camera_component>(e);

			else if constexpr (std::is_same_v<Component, position_component>)
				return m_Registry.register_to_system<position_component>(e);
		}

		template <class Component>
		decltype(auto) get_component(const entity &e)
		{
			if constexpr (std::is_same_v<Component, model_component>)
				return m_Registry.get_component<model_component>(e);

			else if constexpr (std::is_same_v<Component, camera_component>)
				return m_Registry.get_component<camera_component>(e);

			else if constexpr (std::is_same_v<Component, position_component>)
				return m_Registry.get_component<position_component>(e);
		}

		template <class Component>
		void unregister_from_system(entity &e)
		{
			if constexpr (std::is_same_v<Component, model_component>)
				m_Registry.unregister_from_system<model_component>(e);

			else if constexpr (std::is_same_v<Component, camera_component>)
				m_Registry.unregister_from_system<camera_component>(e);

			else if constexpr (std::is_same_v<Component, position_component>)
				m_Registry.unregister_from_system<position_component>(e);
		}

		void update();
		void update_primitive();

		void update_component([[maybe_unused]] const model_component &component) const;
		void update_component([[maybe_unused]] const camera_component &component) const;
		void update_component([[maybe_unused]] const position_component &component) const;
	};
}