/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.File:IWriteStream;

import std;

import :WriteMode;

export namespace PonyEngine::File
{
	/// @brief Write stream.
	class IWriteStream
	{
		INTERFACE_BODY(IWriteStream)

		/// @brief Gets the write mode.
		/// @return Write mode.
		[[nodiscard("Pure function")]]
		virtual WriteMode Mode() const noexcept = 0;

		/// @brief Gets the current stream position.
		/// @return Stream position.
		[[nodiscard("Pure function")]]
		virtual std::size_t Position() const noexcept = 0;
		/// @brief Computes the stream size.
		/// @return Stream size.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const = 0;

		/// @brief Moves the stream position to the given position.
		/// @param position Target position.
		virtual void Move(std::size_t position) = 0;
		/// @brief Moves the stream position to the beginning of the file.
		virtual void MoveBeginning() = 0;
		/// @brief Moves the stream position to the ending of the file.
		virtual void MoveEnding() = 0;

		/// @brief Finds the first occurrence of the given value from the current position and moves to it.
		///        Moves to the end if the value is not found.
		/// @param value Value to find.
		/// @return New position.
		/// @remark Must have read mode enabled.
		[[nodiscard("Pure function")]]
		virtual std::size_t Find(std::byte value) = 0;
		/// @brief Finds the first occurrence of the given symbol from the current position and moves to it.
		///        Moves to the end if the symbol is not found.
		/// @param symbol Symbol to find.
		/// @return New position.
		/// @remark Must have read mode enabled.
		[[nodiscard("Pure function")]]
		virtual std::size_t Find(char symbol) = 0;

		/// @brief Reads the stream data into the given buffer.
		/// @param data Data buffer.
		/// @return Read count.
		/// @remark Reads up to the @p data size bytes or the end of the file.
		/// @remark Must have read mode enabled.
		virtual std::size_t Read(std::span<std::byte> data) = 0;
		/// @brief Reads the stream data into the given buffer.
		/// @param data Data buffer.
		/// @return Read count.
		/// @remark Reads up to the @p data size bytes or the end of the file.
		/// @remark Must have read mode enabled.
		virtual std::size_t Read(std::span<char> data) = 0;
		/// @brief Reads the stream data into the given buffer until the delimiter is found.
		/// @param data Data buffer.
		/// @param delimiter Delimiter character.
		/// @return Read count.
		/// @remark Reads up to the @p data size bytes or the end of the file.
		/// @remark Must have read mode enabled.
		virtual std::size_t Read(std::span<char> data, char delimiter = '\n') = 0;

		/// @brief Writes the given data into the stream.
		/// @param data Data buffer.
		/// @return New position.
		virtual std::size_t Write(std::span<const std::byte> data) = 0;
		/// @brief Writes the given data into the stream.
		/// @param data Data buffer.
		/// @return New position.
		virtual std::size_t Write(std::span<const char> data) = 0;
	};
}
