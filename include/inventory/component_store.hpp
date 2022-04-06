// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_store_base.hpp"

namespace inventory
{
	template <class... Types>
	class component_store;

	template <class Component, class... Components>
	constexpr Component &get_component(component_store<Components...> *pStore);

	template <class Component, class... Components>
	constexpr const Component &get_component(const component_store<Components...> *pStore);

	template <class Component, class... Components>
	constexpr Component &get_component(component_store<Components...> &store);

	template <class Component, class... Components>
	constexpr const Component &get_component(const component_store<Components...> &store);

	/**
	 * @brief Component store class.
	 * This class is the component store class and will contain the required components.
	 *
	 * @note Make sure that this class has public inheritance with the derived classes, so the helper getter functions
	 * would work freely.
	 *
	 * @tparam Types The components to store.
	 */
	template <class... Types>
	class component_store : public component_store_base<Types...>
	{
		template <class Component, class... Components>
		friend constexpr Component &get_component(component_store<Components...> *pStore);

		template <class Component, class... Components>
		friend constexpr const Component &get_component(const component_store<Components...> *pStore);

		template <class Component, class... Components>
		friend constexpr Component &get_component(component_store<Components...> &store);

		template <class Component, class... Components>
		friend constexpr const Component &get_component(const component_store<Components...> &store);

		/**
		 * @brief Get the component object.
		 *
		 * @tparam Component The component type.
		 * @return constexpr Component& The component reference.
		 */
		template <class Component>
		constexpr Component &get_component() { return component_store_base<Component>::get(); }

		/**
		 * @brief Get the component object.
		 *
		 * @tparam Component The component type.
		 * @return constexpr const Component& The component reference.
		 */
		template <class Component>
		constexpr const Component &get_component() const { return component_store_base<Component>::get(); }
	};

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Components The rest of the components.
	 * @param pStore The storage pointer. Usually this would be `this`.
	 * @return constexpr Type& The component reference.
	 */
	template <class Component, class... Components>
	constexpr Component &get_component(component_store<Components...> *pStore) { return pStore->template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Components The rest of the components.
	 * @param pStore The storage pointer. Usually this would be `this`.
	 * @return constexpr const Type& The component reference.
	 */
	template <class Component, class... Components>
	constexpr const Component &get_component(const component_store<Components...> *pStore) { return pStore->template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Components The rest of the components.
	 * @param store The storage reference. Usually this would be `*this`.
	 * @return constexpr Type& The component reference.
	 */
	template <class Component, class... Components>
	constexpr Component &get_component(component_store<Components...> &store) { return store.template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Components The rest of the components.
	 * @param store The storage reference. Usually this would be `*this`.
	 * @return constexpr const Type& The component reference.
	 */
	template <class Component, class... Components>
	constexpr const Component &get_component(const component_store<Components...> &store) { return store.template get_component<Component>(); }
}