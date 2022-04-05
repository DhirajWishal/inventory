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
		 * @return std::storage<Type>& The storage.
		 */
		template <class Type>
		std::vector<Type>& get_storage()
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
		 * @return decltype(auto) The newly created object's reference.
		 */
		template <class Type, class... Types>
		decltype(auto) emplace_back(Types &&...arguments) { return get_storage<Type>().emplace_back(std::forward<Types>(arguments)...); }

		/**
		 * @brief Apply a callable functor to all the stored types.
		 *
		 * @param callable The callable functor.
		 */
		void apply(Callable& callable)
		{
			for (auto& [index, pStorage] : m_Storage)
				pStorage->apply(callable);
		}

		/**
		 * @brief Apply a callable functor to all the stored types.
		 *
		 * @param callable The callable functor.
		 */
		void apply(const Callable& callable) const
		{
			for (const auto& [index, pStorage] : m_Storage)
				pStorage->apply(callable);
		}

		/**
		 * @brief Replace the contents of the container.
		 *
		 * @tparam Type The type of the storage.
		 * @param count The number of elements.
		 * @param value The value to set.
		 */
		template<class Type>
		constexpr void assign(size_t count, const Type& value) { get_storage<Type>().assign(count, value); }

		/**
		 * @brief Replace the contents of the container.
		 *
		 * @tparam Type The type of the storage.
		 * @param first The first iterator.
		 * @param last The last iterator
		 */
		template<class Iterator>
		constexpr void assign(Iterator first, Iterator last) const { get_storage<Type>().assign(std::move(first), std::move(last)); }

		/**
		 * @brief Replace the contents of the container.
		 *
		 * @tparam Type The type of the storage.
		 * @param first The first iterator.
		 * @param last The last iterator
		 */
		template<class Type>
		constexpr void assign(std::initializer_list<Type> list) { get_storage<Type>().assign(std::move(list)); }

		/**
		 * @brief Get the allocator of a storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return allocator_type The storage's allocator.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) get_allocator() const noexcept { return get_storage<Type>().get_allocator(); }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) at(size_t pos) { return get_storage<Type>().at(pos); }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) at(size_t pos) const { return get_storage<Type>().at(pos); }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) operator[](size_t pos) { return get_storage<Type>()[pos]; }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) operator[](size_t pos) const { return get_storage<Type>()[pos]; }

		/**
		 * Get the first element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) front() { return get_storage<Type>().front(); }

		/**
		 * Get the first element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) front() const { return get_storage<Type>().front(); }

		/**
		 * Get the last element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) back() { return get_storage<Type>().back(); }

		/**
		 * Get the last element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The type reference.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) back() const { return get_storage<Type>().back(); }

		/**
		 * Get the data pointer from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The type pointer.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) data() { return get_storage<Type>().data(); }

		/**
		 * Get the data pointer from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The type pointer.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) data() const { return get_storage<Type>().data(); }

		/**
		 * Get the begin iterator of the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The iterator.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) begin() noexcept { return get_storage<Type>().begin(); }

		/**
		 * Get the begin iterator of the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The iterator.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) begin() const noexcept { return get_storage<Type>().begin(); }

		/**
		 * Get the constant begin iterator of the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The iterator.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) cbegin() const noexcept { return get_storage<Type>().begin(); }

		/**
		 * @brief Check if the storage is empty.
		 *
		 * @tparam Type The type of the storage.
		 * @return true if the storage is empty.
		 * @return false if the storage is not empty.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) empty() const noexcept { return get_storage<Type>().empty(); }

		/**
		 * @brief Get the number of elements stored in the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The size of the storage.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) size() const noexcept { return get_storage<Type>().size(); }

		/**
		 * @brief Get the maximum number of elements that can be stored in the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) The maximum size of the storage.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) max_size() const noexcept { return get_storage<Type>().max_size(); }

		/**
		 * @brief Reserve the storage memory.
		 * 
		 * @tparam Type The type of the storage.
		 * @param new_cap The new capacity to set.
		 */
		template<class Type>
		constexpr void reserve(size_t new_cap) { get_storage<Type>().reserve(new_cap); }

		/**
		 * @brief Get the capacity of the current allocation.
		 * 
		 * @tparam Type The type of the storage.
		 * @return decltype(auto) the size.
		 */
		template<class Type>
		constexpr [[nodiscard]] decltype(auto) capacity() const noexcept { return get_storage<Type>().capacity(); }

		/**
		 * @brief Shrink the container to fit the size.
		 * 
		 * @tparam Type The type of the container.
		 */
		template<class Type>
		constexpr void shrink_to_fit() { return get_storage<Type>().shrink_to_fit(); }

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