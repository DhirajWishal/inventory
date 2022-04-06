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
	class inventory : public inventory_interface
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
		std::vector<Type> &get_storage()
		{
			if (!is_registered<Type>())
				register_type<Type>();

			return static_cast<storage<Type, Callable> *>(m_Storage[get_index<Type>()].get())->container();
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

		/**
		 * @brief Replace the contents of the container.
		 *
		 * @tparam Type The type of the storage.
		 * @param count The number of elements.
		 * @param value The value to set.
		 */
		template <class Type>
		constexpr void assign(size_t count, const Type &value) { get_storage<Type>().assign(count, value); }

		/**
		 * @brief Replace the contents of the container.
		 *
		 * @tparam Type The type of the storage.
		 * @param first The first iterator.
		 * @param last The last iterator
		 */
		template <class Type, class Iterator>
		constexpr void assign(Iterator first, Iterator last) const { get_storage<Type>().assign(std::move(first), std::move(last)); }

		/**
		 * @brief Replace the contents of the container.
		 *
		 * @tparam Type The type of the storage.
		 * @param first The first iterator.
		 * @param last The last iterator
		 */
		template <class Type>
		constexpr void assign(std::initializer_list<Type> list) { get_storage<Type>().assign(std::move(list)); }

		/**
		 * @brief Get the allocator of a storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return allocator_type The storage's allocator.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) get_allocator() const noexcept { return get_storage<Type>().get_allocator(); }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) at(size_t pos) { return get_storage<Type>().at(pos); }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) at(size_t pos) const { return get_storage<Type>().at(pos); }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) operator[](size_t pos) { return get_storage<Type>()[pos]; }

		/**
		 * @brief Get an element from the given position.
		 *
		 * @tparam Type The type of the storage.
		 * @param pos The position to index.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) operator[](size_t pos) const { return get_storage<Type>()[pos]; }

		/**
		 * @brief Get the first element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) front() { return get_storage<Type>().front(); }

		/**
		 * @brief Get the first element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) front() const { return get_storage<Type>().front(); }

		/**
		 * @brief Get the last element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) back() { return get_storage<Type>().back(); }

		/**
		 * @brief Get the last element from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The type reference.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) back() const { return get_storage<Type>().back(); }

		/**
		 * @brief Get the data pointer from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The type pointer.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) data() { return get_storage<Type>().data(); }

		/**
		 * @brief Get the data pointer from the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The type pointer.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) data() const { return get_storage<Type>().data(); }

		/**
		 * @brief Get the begin iterator of the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) begin() noexcept { return get_storage<Type>().begin(); }

		/**
		 * @brief Get the begin iterator of the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) begin() const noexcept { return get_storage<Type>().begin(); }

		/**
		 * @brief Get the constant begin iterator of the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) cbegin() const noexcept { return get_storage<Type>().begin(); }

		/**
		 * @brief Check if the storage is empty.
		 *
		 * @tparam Type The type of the storage.
		 * @return true if the storage is empty.
		 * @return false if the storage is not empty.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) empty() const noexcept { return get_storage<Type>().empty(); }

		/**
		 * @brief Get the number of elements stored in the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The size of the storage.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) size() const noexcept { return get_storage<Type>().size(); }

		/**
		 * @brief Get the maximum number of elements that can be stored in the storage.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) The maximum size of the storage.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) max_size() const noexcept { return get_storage<Type>().max_size(); }

		/**
		 * @brief Reserve the storage memory.
		 *
		 * @tparam Type The type of the storage.
		 * @param new_cap The new capacity to set.
		 */
		template <class Type>
		constexpr void reserve(size_t new_cap) { get_storage<Type>().reserve(new_cap); }

		/**
		 * @brief Get the capacity of the current allocation.
		 *
		 * @tparam Type The type of the storage.
		 * @return constexpr decltype(auto) the size.
		 */
		template <class Type>
		constexpr INV_NODISCARD decltype(auto) capacity() const noexcept { return get_storage<Type>().capacity(); }

		/**
		 * @brief Shrink the container to fit the size.
		 *
		 * @tparam Type The type of the container.
		 */
		template <class Type>
		constexpr void shrink_to_fit() { get_storage<Type>().shrink_to_fit(); }

		/**
		 * @brief Clear the storage.
		 *
		 * @tparam Type The type of the container.
		 */
		template <class Type>
		constexpr void clear() noexcept { get_storage<Type>().shrink_to_fit(); }

		/**
		 * @brief Inserts elements at the specified location in the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @param pos The position to place the data.
		 * @param value The value to insert.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator>
		constexpr INV_NODISCARD decltype(auto) insert(ConstIterator pos, const Type &value) { return get_storage<Type>().insert(pos, value); }

		/**
		 * @brief Inserts elements at the specified location in the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @param pos The position to place the data.
		 * @param value The value to insert.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator>
		constexpr INV_NODISCARD decltype(auto) insert(ConstIterator pos, Type &&value) { return get_storage<Type>().insert(pos, std::forward<Type>(value)); }

		/**
		 * @brief Inserts elements at the specified location in the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @param pos The position to place the data.
		 * @param count The number of elements to set.
		 * @param value The value to insert.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator>
		constexpr INV_NODISCARD decltype(auto) insert(ConstIterator pos, size_t count, const Type &value) { return get_storage<Type>().insert(pos, count, value); }

		/**
		 * @brief Inserts elements at the specified location in the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @tparam Iterator Data iterator type.
		 * @param pos The position to place the data.
		 * @param first The first iterator.
		 * @param last The last iterator.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator, class Iterator>
		constexpr INV_NODISCARD decltype(auto) insert(ConstIterator pos, Iterator first, Iterator last) { return get_storage<Type>().insert(pos, first, last); }

		/**
		 * @briefInserts elements at the specified location in the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @param pos The position to place the data.
		 * @param ilist The initializer list.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator>
		constexpr INV_NODISCARD decltype(auto) insert(ConstIterator pos, std::initializer_list<Type> ilist) { return get_storage<Type>().insert(pos, ilist); }

		/**
		 * @brief Inserts a new element into the container directly before pos.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @tparam Types The variadic argument types.
		 * @param pos The position to place the data.
		 * @param args The arguments to pass.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator, class... Types>
		constexpr INV_NODISCARD decltype(auto) emplace(ConstIterator pos, Types &&...args) { return get_storage<Type>().emplace(pos, std::forward<Types>(args)...); }

		/**
		 * @brief Erases the specified elements from the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @param pos The position to erase.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator>
		constexpr INV_NODISCARD decltype(auto) erase(ConstIterator pos) { return get_storage<Type>().erase(pos); }

		/**
		 * @brief Erases the specified elements from the container.
		 *
		 * @tparam Type The value data type.
		 * @tparam ConstIterator The position iterator type.
		 * @param first The first iterator.
		 * @param last The last iterator.
		 * @return constexpr decltype(auto) The iterator.
		 */
		template <class Type, class ConstIterator>
		constexpr INV_NODISCARD decltype(auto) erase(ConstIterator first, ConstIterator last) { return get_storage<Type>().erase(first, last); }

		/**
		 * @brief Appends a new element to the end of the container
		 *
		 * @tparam Type The type of the storage.
		 * @tparam Types The types of the arguments.
		 * @param args The arguments.
		 * @return constexpr decltype(auto) The inserted value reference.
		 */
		template <class Type, class... Types>
		constexpr INV_NODISCARD decltype(auto) emplace_back(Types &&...args) { return get_storage<Type>().emplace_back(std::forward<Types>(args)...); }

		/**
		 * @brief Removes the last element of the container.
		 *
		 * @tparam Type The type of the storage.
		 */
		template <class Type>
		constexpr void pop_back() { get_storage<Type>().pop_back(); }

		/**
		 * @brief Resizes the container to contain count elements.
		 *
		 * @tparam Type The type of the storage.
		 * @param count The number of elements to resize to.
		 */
		template <class Type>
		constexpr void resize(size_t count) { get_storage<Type>().resize(count); }

		/**
		 * @brief Resizes the container to contain count elements.
		 *
		 * @tparam Type The type of the storage.
		 * @param count The number of elements to resize to.
		 * @param value The value to copy.
		 */
		template <class Type>
		constexpr void resize(size_t count, const Type &value) { get_storage<Type>().resize(count, value); }

		/**
		 * @brief Get the number of types stored in the internal storage.
		 *
		 * @return constexpr size_t The count.
		 */
		constexpr INV_NODISCARD decltype(auto) type_count() const { return m_Storage.size(); }

		/**
		 * @brief Get the total number of objects stored in the container.
		 *
		 * @return constexpr decltype(auto) The object count.
		 */
		constexpr INV_NODISCARD decltype(auto) object_count() const
		{
			size_t count = 0;
			for (auto &[index, pStorage] : m_Storage)
				count += pStorage->size();

			return count;
		}

	private:
		/**
		 * @brief Get the type index.
		 *
		 * @tparam Type The type to get the index of.
		 * @return std::type_index.
		 */
		template <class Type>
        INV_NODISCARD std::type_index get_index() const { return std::type_index(typeid(Type)); }

		/**
		 * @brief Check if a type is registered.
		 *
		 * @tparam Type The type to check if registered.
		 * @return true if the type is registered.
		 * @return false if the type is not registered.
		 */
		template <class Type>
        constexpr INV_NODISCARD bool is_registered() const { return m_Storage.contains(get_index<Type>()); }

		/**
		 * @brief Register a new type to the storage system.
		 *
		 * @tparam Type The type to store.
		 */
		template <class Type>
		constexpr void register_type() { m_Storage[get_index<Type>()] = std::make_unique<storage<Type, Callable>>(); }

	private:
		storage_map<Callable> m_Storage = {};
	};
}