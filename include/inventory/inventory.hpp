// Copyright (c) 2022 Dhiraj Wishal

#pragma once

#include "storage_map.hpp"

namespace inventory
{
	/**
	 * @brief Inventory interface class.
	 * This class is the base class of the inventory and acts as a polymorphic type for future abstraction.
	 */
	class inventory_interface
	{
	};

	/**
	 * @brief Inventory class.
	 * This class is the main storage class and this contains all the required data using the storage map.
	 *
	 * @tparam Callable The callable type.
	 */
	template <class Callable>
	class inventory final : public inventory_interface
	{
	public:
		/**
		 * @brief Construct a new inventory object.
		 */
		inventory() = default;

		/**
		 * @brief Destroy the inventory object.
		 */
		~inventory() = default;

		/**
		 * @brief Get the storage object.
		 *
		 * @tparam Type The type of the storage to get.
		 * @return std::vector<Type>& The storage vector.
		 */
		template <class Type>
		std::vector<Type> &get_storage()
		{
			if (!is_registered<Type>())
				register_type<Type>();
			return static_cast<storage<Type, Callable> *>(m_Storage[get_index<Type>()].get())->container();
		}

		/**
		 * @brief Emplace a new object at the back of the container.
		 *
		 * @tparam Type The type of the object to emplace.
		 * @tparam Types The constructor argument types.
		 * @param arguments The constructor arguments.
		 * @return Type& The newly created object's reference.
		 */
		template <class Type, class... Types>
		Type &emplace_back(Types &&...arguments)
		{
			auto &store = get_storage<Type>();
			store.emplace_back(std::forward<Types>(arguments)...);
			return store.back();
		}

		/**
		 * @brief Apply a callable functor to all the stored types.
		 *
		 * @param callable The callable functor.
		 */
		void apply(Callable &callable)
		{
			for (auto &[index, pStorage] : m_Storage)
				pStorage->apply(callable);
		}

		/**
		 * @brief Apply a callable functor to all the stored types.
		 *
		 * @param callable The callable functor.
		 */
		void apply(const Callable &callable) const
		{
			for (const auto &[index, pStorage] : m_Storage)
				pStorage->apply(callable);
		}

	private:
		/**
		 * @brief Get the type index.
		 *
		 * @tparam Type The type to get the index of.
		 * @return std::type_index.
		 */
		template <class Type>
		std::type_index get_index() const { return std::type_index(typeid(Type)); }

		/**
		 * @brief Check if a type is registered.
		 *
		 * @tparam Type The type to check if registered.
		 * @return true if the type is registered.
		 * @return false if the type is not registered.
		 */
		template <class Type>
		bool is_registered() const { return m_Storage.contains(get_index<Type>()); }

		/**
		 * @brief Register a new type to the storage system.
		 *
		 * @tparam Type The type to store.
		 */
		template <class Type>
		void register_type() { m_Storage[get_index<Type>()] = std::make_unique<storage<Type, Callable>>(); }

	private:
		storage_map<Callable> m_Storage = {};
	};
}