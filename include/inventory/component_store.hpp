// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_store_base.hpp"

namespace inventory
{
	/**
	 * @brief Component store class.
	 * This class is the component store class and will contain the required components.
	 *
	 * @tparam Types The components to store.
	 */
	template <class... Types>
	class component_store : public component_store_base<Types...>
	{
	};

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The type of the object.
	 * @param pStore The storage pointer. Usually this would be `this`.
	 * @return constexpr Type& The component reference.
	 */
	template <class Component, class Object>
	constexpr inline Component &get_component(Object *pStore) { return pStore->template component_store_base<Component>::get(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The type of the object.
	 * @param pStore The storage pointer. Usually this would be `this`.
	 * @return constexpr const Type& The component reference.
	 */
	template <class Component, class Object>
	constexpr inline const Component &get_component(const Object *pStore) { return pStore->template component_store_base<Component>::get(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The type of the object.
	 * @param store The storage reference. Usually this would be `*this`.
	 * @return constexpr Type& The component reference.
	 */
	template <class Component, class Object>
	constexpr inline Component &get_component(Object &store) { return store.template component_store_base<Component>::get(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The type of the object.
	 * @param store The storage reference. Usually this would be `*this`.
	 * @return constexpr const Type& The component reference.
	 */
	template <class Component, class Object>
	constexpr inline const Component &get_component(const Object &store) { return store.template component_store_base<Component>::get(); }
}