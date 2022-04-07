// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_store_base.hpp"

#include <tuple>

namespace inventory
{
	template <class... Types>
	class component_store;

	template <class Component, class Object>
	constexpr decltype(auto) get_component(Object *pStore);

	template <class Component, class Object>
	constexpr decltype(auto) get_component(const Object *pStore);

	template <class Component, class Object>
	constexpr decltype(auto) get_component(Object &store);

	template <class Component, class Object>
	constexpr decltype(auto) get_component(const Object &store);

	template <class... Components, class Object>
	constexpr decltype(auto) get_components(Object *pObject);

	template <class... Components, class Object>
	constexpr decltype(auto) get_components(const Object *pObject);

	template <class... Components, class Object>
	constexpr decltype(auto) get_components(Object &object);

	template <class... Components, class Object>
	constexpr decltype(auto) get_components(const Object &object);

	/**
	 * @brief Component store class.
	 * This class is the component store class and will contain the required components.
	 *
	 * @note If inheriting from this class, make sure that this class has public inheritance with the derived classes, so the helper getter functions
	 * would work freely.
	 *
	 * @tparam Types The components to store.
	 */
	template <class... Types>
	class component_store : public component_store_base<Types...>
	{
		template <class Component, class Object>
		friend constexpr decltype(auto) get_component(Object *pStore);

		template <class Component, class Object>
		friend constexpr decltype(auto) get_component(const Object *pStore);

		template <class Component, class Object>
		friend constexpr decltype(auto) get_component(Object &store);

		template <class Component, class Object>
		friend constexpr decltype(auto) get_component(const Object &store);

		template <class... Components, class Object>
		friend constexpr decltype(auto) get_components(Object *pObject);

		template <class... Components, class Object>
		friend constexpr decltype(auto) get_components(const Object *pObject);

		template <class... Components, class Object>
		friend constexpr decltype(auto) get_components(Object &object);

		template <class... Components, class Object>
		friend constexpr decltype(auto) get_components(const Object &object);

	public:
		/**
		 * @brief Construct a new component store object.
		 */
		component_store() = default;

		/**
		 * @brief Construct a new component store object.
		 *
		 * @param data The data to be passed to the components.
		 */
		explicit component_store(const Types &...data) : component_store_base<Types...>(std::forward<Types>(data)...) {}

		/**
		 * @brief Construct a new component store object.
		 *
		 * @param data The data to be passed to the components.
		 */
		explicit component_store(Types &&...data) : component_store_base<Types...>(std::forward<Types>(data)...) {}

	private:
		/**
		 * @brief Get the component object.
		 *
		 * @tparam Component The component type.
		 * @return constexpr decltype(auto) The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD decltype(auto) get_component() { return component_store_base<Component>::get(); }

		/**
		 * @brief Get the component object.
		 *
		 * @tparam Component The component type.
		 * @return constexpr decltype(auto) The component reference.
		 */
		template <class Component>
		constexpr INV_NODISCARD decltype(auto) get_component() const { return component_store_base<Component>::get(); }

		/**
		 * @brief Get multiple components from the store.
		 *
		 * @tparam Components The components to get.
		 * @return constexpr decltype(auto) The tuple of components.
		 */
		template <class... Components>
		constexpr INV_NODISCARD decltype(auto) get_components() { return std::tie(get_component<Components>()...); }

		/**
		 * @brief Get multiple components from the store.
		 *
		 * @tparam Components The components to get.
		 * @return constexpr decltype(auto) The tuple of components.
		 */
		template <class... Components>
		constexpr INV_NODISCARD decltype(auto) get_components() const { return std::make_tuple(get_component<Components>()...); }
	};

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The object type.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class Object>
	constexpr INV_NODISCARD decltype(auto) get_component(Object *pObject) { return pObject->template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The object type.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class Object>
	constexpr INV_NODISCARD decltype(auto) get_component(const Object *pObject) { return pObject->template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The object type.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class Object>
	constexpr INV_NODISCARD decltype(auto) get_component(Object &object) { return object.template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Object The object type.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class Object>
	constexpr INV_NODISCARD decltype(auto) get_component(const Object &object) { return object.template get_component<Component>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Object The object type.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class Object>
	constexpr INV_NODISCARD decltype(auto) get_components(Object *pObject) { return pObject->template get_components<Components...>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Object The object type.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class Object>
	constexpr INV_NODISCARD decltype(auto) get_components(const Object *pObject) { return pObject->template get_components<Components...>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Object The object type.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class Object>
	constexpr INV_NODISCARD decltype(auto) get_components(Object &object) { return object.template get_components<Components...>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Object The object type.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class Object>
	constexpr INV_NODISCARD decltype(auto) get_components(const Object &object) { return object.template get_components<Components...>(); }
}