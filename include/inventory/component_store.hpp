// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "component_store_base.hpp"

#include <tuple>

namespace inventory
{
	template <class... Types>
	class component_store;

	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(component_store<Types...> *pObject);

	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(const component_store<Types...> *pObject);

	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(component_store<Types...> &object);

	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(const component_store<Types...> &object);

	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(component_store<Types...> *pObject);

	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(const component_store<Types...> *pObject);

	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(component_store<Types...> &object);

	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(const component_store<Types...> &object);

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
		template <class Component, class... _Types>
		friend constexpr decltype(auto) get_component(component_store<_Types...> *pObject);

		template <class Component, class... _Types>
		friend constexpr decltype(auto) get_component(const component_store<_Types...> *pObject);

		template <class Component, class... _Types>
		friend constexpr decltype(auto) get_component(component_store<_Types...> &object);

		template <class Component, class... _Types>
		friend constexpr decltype(auto) get_component(const component_store<_Types...> &object);

		template <class... Components, class... _Types>
		friend constexpr decltype(auto) get_components(component_store<_Types...> *pObject);

		template <class... Components, class... _Types>
		friend constexpr decltype(auto) get_components(const component_store<_Types...> *pObject);

		template <class... Components, class... _Types>
		friend constexpr decltype(auto) get_components(component_store<_Types...> &object);

		template <class... Components, class... _Types>
		friend constexpr decltype(auto) get_components(const component_store<_Types...> &object);

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
	 * @tparam Types The template arguments of the component store.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(component_store<Types...> *pObject) { return pObject->template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Types The template arguments of the component store.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(const component_store<Types...> *pObject) { return pObject->template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Types The template arguments of the component store.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(component_store<Types...> &object) { return object.template get_component<Component>(); }

	/**
	 * @brief Get the component object from an object which is inherited from the component_store.
	 *
	 * @tparam Component The type of the component.
	 * @tparam Types The template arguments of the component store.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The component reference.
	 */
	template <class Component, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_component(const component_store<Types...> &object) { return object.template get_component<Component>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Types The template arguments of the component store.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(component_store<Types...> *pObject) { return pObject->template get_components<Components...>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Types The template arguments of the component store.
	 * @param pObject The storage pointer. Usually this would be `this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(const component_store<Types...> *pObject) { return pObject->template get_components<Components...>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Types The template arguments of the component store.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(component_store<Types...> &object) { return object.template get_components<Components...>(); }

	/**
	 * @brief Get multiple components from an object which is inherited from the component_store.
	 *
	 * @tparam Components The component types.
	 * @tparam Types The template arguments of the component store.
	 * @param object The storage reference. Usually this would be `*this`.
	 * @return constexpr decltype(auto) The tuple.
	 */
	template <class... Components, class... Types>
	constexpr INV_NODISCARD decltype(auto) get_components(const component_store<Types...> &object) { return object.template get_components<Components...>(); }
}