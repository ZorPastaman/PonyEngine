/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Math:Matrix2x2;

import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <span>;
import <type_traits>;

import :Common;
import :Vector2;

export namespace PonyBase::Math
{
	/// @brief Matrix2x2 implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Matrix2x2 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		static constexpr std::size_t Dimension = 2; ///< Row and column count. For any Matrix2x2 it's always 2.
		static constexpr std::size_t ComponentCount = Dimension * Dimension; ///< Component count. For any Matrix2x2 it's always 4.

		struct Predefined; ///< Predefined matrices.

		/// @brief Row access.
		/// @tparam IsConstant Is the underlying value const?
		template<bool IsConstant>
		class RowAccess final
		{
		public:
			RowAccess(const RowAccess&) = delete;
			RowAccess(RowAccess&&) = delete;

			constexpr ~RowAccess() noexcept = default;

			/// @brief Converts the row to a vector.
			[[nodiscard("Pure operator")]]
			constexpr operator Vector2<T>() const noexcept;

			/// @brief Gets a component in the row by the @p columnIndex.
			/// @param columnIndex Column index. Must be in range [0, 1].
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr T& operator [](std::size_t columnIndex) noexcept requires (!IsConstant);
			/// @brief Gets a component in the row by the @p columnIndex.
			/// @param columnIndex Column index. Must be in range [0, 1].
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr const T& operator [](std::size_t columnIndex) const noexcept;

			RowAccess& operator =(const RowAccess&) = delete;
			RowAccess& operator =(RowAccess&&) = delete;

			/// @brief Assigns the row from the @p row.
			/// @param row Row to assign from.
			/// @return @a This.
			constexpr RowAccess& operator =(const Vector2<T>& row) noexcept requires (!IsConstant);

		private:
			using RowValueType = std::conditional_t<IsConstant, const T, T>; ///< @p const @p T or @p T depending on @p IsConstant.

			/// @brief Creates a row access.
			/// @param row First element in the row.
			[[nodiscard("Pure constructor")]]
			explicit constexpr RowAccess(RowValueType* row) noexcept;

			RowValueType* const matrixRow; ///< Row pointer.

			friend Matrix2x2;
		};

		/// @brief Creates a matrix and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2() noexcept = default;
		/// @brief Creates a matrix and assigns its components from the arguments.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2(T m00, T m10, T m01, T m11) noexcept;
		/// @brief Creates a matrix and assigns its components from column vectors.
		/// @param column0 Column 0.
		/// @param column1 Column 1.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2(const Vector2<T>& column0, const Vector2<T>& column1) noexcept;
		/// @brief Creates a matrix and assigns its components from the @p span.
		/// @param span Span. The matrix is column-major.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix2x2(std::span<const T, ComponentCount> span) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2(const Matrix2x2& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2(Matrix2x2&& other) noexcept = default;

		constexpr ~Matrix2x2() noexcept = default;

		/// @brief Gets the component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		constexpr T& M00() noexcept;
		/// @brief Gets the component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		constexpr const T& M00() const noexcept;
		/// @brief Gets the component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		constexpr T& M10() noexcept;
		/// @brief Gets the component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		constexpr const T& M10() const noexcept;
		/// @brief Gets the component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		constexpr T& M01() noexcept;
		/// @brief Gets the component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		constexpr const T& M01() const noexcept;
		/// @brief Gets the component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		constexpr T& M11() noexcept;
		/// @brief Gets the component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		constexpr const T& M11() const noexcept;
		/// @brief Gets the component by the @p index.
		/// @param index Component index.
		/// @return Component.
		[[nodiscard("Pure function")]]
		constexpr T& Component(std::size_t index) noexcept;
		/// @brief Gets the component by the @p index.
		/// @param index Component index.
		/// @return Component.
		[[nodiscard("Pure function")]]
		constexpr const T& Component(std::size_t index) const noexcept;
		/// @brief Gets the span. The data is column-major.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 4> Span() noexcept;
		/// @brief Gets the span. The data is column-major.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 4> Span() const noexcept;
		/// @brief Gets the column span.
		/// @param columnIndex Column index.
		/// @return Column span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 2> Span(std::size_t columnIndex) noexcept;
		/// @brief Gets the column span.
		/// @param columnIndex Column index.
		/// @return Column span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 2> Span(std::size_t columnIndex) const noexcept;

		/// @brief Gets a row by the @p rowIndex.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> Row(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row by the @p rowIndex.
		/// @param rowIndex Row index.
		/// @param value Row components.
		constexpr void Row(std::size_t rowIndex, const Vector2<T>& value) noexcept;

		/// @brief Gets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> Column(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @param value Column components.
		constexpr void Column(std::size_t columnIndex, const Vector2<T>& value) noexcept;

		/// @brief Gets the diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> Diagonal() const noexcept;
		/// @brief Sets the diagonal.
		/// @param value Diagonal components.
		constexpr void Diagonal(const Vector2<T>& value) noexcept;

		/// @brief Gets the counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> CounterDiagonal() const noexcept;
		/// @brief Sets the counter-diagonal.
		/// @param value Counter-diagonal components.
		constexpr void CounterDiagonal(const Vector2<T>& value) noexcept;

		/// @brief Computes a trace of the matrix.
		/// @return Trace of the matrix.
		[[nodiscard("Pure function")]]
		constexpr T Trace() const noexcept;

		/// @brief Computes a determinant of the matrix.
		/// @return Determinant.
		[[nodiscard("Pure function")]]
		constexpr T Determinant() const noexcept;

		/// @brief Computes an adjugate of the matrix.
		/// @return Adjugate.
		[[nodiscard("Pure function")]]
		constexpr Matrix2x2 Adjugate() const noexcept;

		/// @brief Computes a transpose of the matrix.
		/// @return Transpose.
		[[nodiscard("Pure function")]]
		constexpr Matrix2x2 Transpose() const noexcept;

		/// @brief Computes an inverse of the matrix.
		/// @note If the determinant is zero, the result is undefined.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix2x2 Inverse() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if this matrix is equal to the zero matrix.
		/// @return @a True if this matrix is equal to the zero matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsZero() const noexcept;
		/// @brief Checks if this matrix is almost equal to the zero matrix with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this matrix is almost equal to the zero matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostZero(T tolerance = T{0.00001}) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Checks if this matrix is equal to the identity matrix.
		/// @return @a True if this matrix is equal to the identity matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsIdentity() const noexcept;
		/// @brief Checks if this matrix is almost equal to the identity matrix with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this matrix is almost equal to the identity matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostIdentity(T tolerance = T{0.00001}) const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Assigns arguments to the matrix components.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		constexpr void Set(T m00, T m10, T m01, T m11) noexcept;
		/// @brief Assigns columns to the matrix.
		/// @param column0 Column 0 to assign.
		/// @param column1 Column 1 to assign.
		constexpr void Set(const Vector2<T>& column0, const Vector2<T>& column1) noexcept;
		/// @brief Assigns matrix components from the @p span.
		/// @param span Span. The matrix is column-major.
		constexpr void Set(std::span<const T, ComponentCount> span) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Matrix to multiply by.
		constexpr void Scale(const Matrix2x2& scale) noexcept;

		/// @brief Creates a string representing a state of the matrix.
		/// @remark The format is '(m00, m01)(m10, m11)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts all the components to the @p U and returns a new matrix with those components.
		/// @tparam U Target component type.
		template<Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Matrix2x2<U>() const noexcept;

		/// @brief Row access operator.
		/// @remark Don't store it. Use the access like this: matrix[1][1]; or vector = matrix[1].
		/// @param rowIndex Row index. Must be in range [0, 1].
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr RowAccess<false> operator [](std::size_t rowIndex) noexcept;
		/// @brief Row access operator.
		/// @remark Don't store it. Use the access like this: matrix[1][1]; or vector = matrix[1].
		/// @param rowIndex Row index. Must be in range [0, 1].
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr RowAccess<true> operator [](std::size_t rowIndex) const noexcept;

		constexpr Matrix2x2& operator =(const Matrix2x2& other) noexcept = default;
		constexpr Matrix2x2& operator =(Matrix2x2&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Matrix to add.
		/// @return @a This.
		constexpr Matrix2x2& operator +=(const Matrix2x2& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Matrix to subtract.
		/// @return @a This.
		constexpr Matrix2x2& operator -=(const Matrix2x2& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		constexpr Matrix2x2& operator *=(T multiplier) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		constexpr Matrix2x2& operator *=(ComputationalType multiplier) noexcept requires (std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p other.
		/// @param other Matrix to multiply by.
		/// @return @a This.
		constexpr Matrix2x2& operator *=(const Matrix2x2& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		constexpr Matrix2x2& operator /=(T divisor) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		constexpr Matrix2x2& operator /=(ComputationalType divisor) noexcept requires (std::is_integral_v<T>);

		/// @brief Checks if the two matrices are equal.
		/// @param other Other matrix.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix2x2& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order m00, m10, m01, m11.
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	/// @brief Checks if the two matrices are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Sums the @p left and @p right.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator +(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	/// @brief Negates the @p matrix.
	/// @tparam T Component type.
	/// @param matrix Matrix to negate.
	/// @return Negated matrix.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& matrix) noexcept;
	/// @brief Subtracts the @p right matrix from the @p left matrix.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, T multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, typename Matrix2x2<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(T multiplier, const Matrix2x2<T>& matrix) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(typename Matrix2x2<T>::ComputationalType multiplier, const Matrix2x2<T>& matrix) noexcept;
	/// @brief Multiplies the @p left by the @p right.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;
	/// @brief Multiplies the @p matrix by the @p vector.
	/// @tparam T Component type.
	/// @param matrix Matrix.
	/// @param vector Vector.
	/// @return Product vector.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector2<T> operator *(const Matrix2x2<T>& matrix, const Vector2<T>& vector) noexcept;

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, T divisor) noexcept;
	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, typename Matrix2x2<T>::ComputationalType divisor) noexcept;

	/// @brief Puts matrix.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix);

	template<Arithmetic T>
	struct Matrix2x2<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr auto Identity = Matrix2x2(T{1}, T{0}, T{0}, T{1}); ///< Identity matrix.
		static constexpr auto Zero = Matrix2x2(T{0}, T{0}, T{0}, T{0}); ///< Zero matrix.
	};
}

namespace PonyBase::Math
{
	/// @brief Flattens the matrices and treats them as vectors, and computes a dot product of those vectors.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr Matrix2x2<T>::RowAccess<IsConstant>::RowAccess(RowValueType* const row) noexcept :
		matrixRow{row}
	{
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr Matrix2x2<T>::RowAccess<IsConstant>::operator Vector2<T>() const noexcept
	{
		Vector2<T> row;
		for (std::size_t i = 0; i < Dimension; ++i)
		{
			row[i] = (*this)[i];
		}

		return row;
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr T& Matrix2x2<T>::RowAccess<IsConstant>::operator [](const std::size_t columnIndex) noexcept requires (!IsConstant)
	{
		return matrixRow[columnIndex * Dimension];
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr const T& Matrix2x2<T>::RowAccess<IsConstant>::operator [](const std::size_t columnIndex) const noexcept
	{
		return matrixRow[columnIndex * Dimension];
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr typename Matrix2x2<T>::template RowAccess<IsConstant>& Matrix2x2<T>::RowAccess<IsConstant>::operator =(const Vector2<T>& row) noexcept requires (!IsConstant)
	{
		for (std::size_t i = 0; i < Dimension; ++i)
		{
			(*this)[i] = row[i];
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::Matrix2x2(const T m00, const T m10, const T m01, const T m11) noexcept :
		components{m00, m10, m01, m11}
	{
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::Matrix2x2(const Vector2<T>& column0, const Vector2<T>& column1) noexcept
	{
		Set(column0, column1);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::Matrix2x2(const std::span<const T, ComponentCount> span) noexcept
	{
		Set(span);
	}

	template<Arithmetic T>
	constexpr T& Matrix2x2<T>::M00() noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M00() const noexcept
	{
		return components[0];
	}

	template<Arithmetic T>
	constexpr T& Matrix2x2<T>::M10() noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M10() const noexcept
	{
		return components[1];
	}

	template<Arithmetic T>
	constexpr T& Matrix2x2<T>::M01() noexcept
	{
		return components[2];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M01() const noexcept
	{
		return components[2];
	}

	template<Arithmetic T>
	constexpr T& Matrix2x2<T>::M11() noexcept
	{
		return components[3];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M11() const noexcept
	{
		return components[3];
	}

	template<Arithmetic T>
	constexpr T& Matrix2x2<T>::Component(const std::size_t index) noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::Component(const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<Arithmetic T>
	constexpr std::span<T, 4> Matrix2x2<T>::Span() noexcept
	{
		return components;
	}

	template<Arithmetic T>
	constexpr std::span<const T, 4> Matrix2x2<T>::Span() const noexcept
	{
		return components;
	}

	template<Arithmetic T>
	constexpr std::span<T, 2> Matrix2x2<T>::Span(const std::size_t columnIndex) noexcept
	{
		T* const column = components.data() + columnIndex * Dimension;

		return std::span<T, Dimension>(column, Dimension);
	}

	template<Arithmetic T>
	constexpr std::span<const T, 2> Matrix2x2<T>::Span(const std::size_t columnIndex) const noexcept
	{
		const T* const column = components.data() + columnIndex * Dimension;

		return std::span<const T, Dimension>(column, Dimension);
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::Row(const std::size_t rowIndex) const noexcept
	{
		return (*this)[rowIndex];
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Row(const std::size_t rowIndex, const Vector2<T>& value) noexcept
	{
		(*this)[rowIndex] = value;
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::Column(const std::size_t columnIndex) const noexcept
	{
		return Vector2<T>(Span(columnIndex));
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Column(const std::size_t columnIndex, const Vector2<T>& value) noexcept
	{
		std::ranges::copy(value.Span(), Span(columnIndex).data());
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::Diagonal() const noexcept
	{
		return Vector2<T>(M00(), M11());
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Diagonal(const Vector2<T>& value) noexcept
	{
		M00() = value.X();
		M11() = value.Y();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::CounterDiagonal() const noexcept
	{
		return Vector2<T>(M01(), M10());
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::CounterDiagonal(const Vector2<T>& value) noexcept
	{
		M01() = value.X();
		M10() = value.Y();
	}

	template<Arithmetic T>
	constexpr T Matrix2x2<T>::Trace() const noexcept
	{
		return Diagonal().Sum();
	}

	template<Arithmetic T>
	constexpr T Matrix2x2<T>::Determinant() const noexcept
	{
		return M00() * M11() - M01() * M10();
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Matrix2x2<T>::Adjugate() const noexcept
	{
		return Matrix2x2(M11(), -M10(), -M01(), M00());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Matrix2x2<T>::Transpose() const noexcept
	{
		return Matrix2x2(M00(), M01(), M10(), M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Matrix2x2<T>::Inverse() const noexcept requires (std::is_floating_point_v<T>)
	{
		return Adjugate() * (ComputationalType{1} / Determinant());
	}

	template<Arithmetic T>
	constexpr bool Matrix2x2<T>::IsZero() const noexcept
	{
		return *this == Predefined::Zero;
	}

	template<Arithmetic T>
	constexpr bool Matrix2x2<T>::IsAlmostZero(const T tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Zero, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Matrix2x2<T>::IsIdentity() const noexcept
	{
		return *this == Predefined::Identity;
	}

	template<Arithmetic T>
	constexpr bool Matrix2x2<T>::IsAlmostIdentity(const T tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Identity, tolerance);
	}

	template<Arithmetic T>
	bool Matrix2x2<T>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		for (const T component : components)
		{
			if (!std::isfinite(component))
			{
				return false;
			}
		}

		return true;
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Set(const T m00, const T m10, const T m01, const T m11) noexcept
	{
		M00() = m00;
		M10() = m10;
		M01() = m01;
		M11() = m11;
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Set(const Vector2<T>& column0, const Vector2<T>& column1) noexcept
	{
		Column(0, column0);
		Column(1, column1);
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Set(const std::span<const T, ComponentCount> span) noexcept
	{
		std::ranges::copy(span, components.data());
	}

	template<Arithmetic T>
	constexpr void Matrix2x2<T>::Scale(const Matrix2x2& scale) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) *= scale.Component(i);
		}
	}

	template<Arithmetic T>
	std::string Matrix2x2<T>::ToString() const
	{
		return std::format("({}, {})({}, {})", M00(), M01(), M10(), M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		Matrix2x2<T> scaled;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			scaled.Component(i) = left.Component(i) * right.Component(i);
		}

		return scaled;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, const T tolerance) noexcept
	{
		const Matrix2x2<T> diff = left - right;

		return Dot(diff, diff) < tolerance * tolerance;
	}

	template<Arithmetic T>
	constexpr T Dot(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return left.M00() * right.M00() + left.M10() * right.M10() + left.M01() * right.M01() + left.M11() * right.M11();
	}

	template<Arithmetic T>
	template<Arithmetic U>
	constexpr Matrix2x2<T>::operator Matrix2x2<U>() const noexcept
	{
		Matrix2x2<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast.Component(i) = static_cast<U>(Component(i));
		}

		return cast;
	}

	template<Arithmetic T>
	constexpr typename Matrix2x2<T>::template RowAccess<false> Matrix2x2<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return RowAccess<false>(components.data() + rowIndex);
	}

	template<Arithmetic T>
	constexpr typename Matrix2x2<T>::template RowAccess<true> Matrix2x2<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return RowAccess<true>(components.data() + rowIndex);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator +=(const Matrix2x2& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) += other.Component(i);
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator -=(const Matrix2x2& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) -= other.Component(i);
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) *= multiplier;
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator *=(const ComputationalType multiplier) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) = static_cast<T>(Component(i) * multiplier);
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator *=(const Matrix2x2& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) /= divisor;
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>& Matrix2x2<T>::operator /=(const ComputationalType divisor) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			Component(i) = static_cast<T>(Component(i) / divisor);
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Matrix2x2<T>::operator ==(const Matrix2x2& other) const noexcept
	{
		return components == other.components;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator +(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		Matrix2x2<T> sum;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			sum.Component(i) = left.Component(i) + right.Component(i);
		}

		return sum;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& matrix) noexcept
	{
		Matrix2x2<T> negated;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			negated.Component(i) = -matrix.Component(i);
		}

		return negated;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		Matrix2x2<T> difference;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			difference.Component(i) = left.Component(i) - right.Component(i);
		}

		return difference;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const T multiplier) noexcept
	{
		Matrix2x2<T> product;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			product.Component(i) = matrix.Component(i) * multiplier;
		}

		return product;
	}

	template<std::integral T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType multiplier) noexcept
	{
		Matrix2x2<T> product;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			product.Component(i) = static_cast<T>(matrix.Component(i) * multiplier);
		}

		return product;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const T multiplier, const Matrix2x2<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<std::integral T>
	constexpr Matrix2x2<T> operator *(const typename Matrix2x2<T>::ComputationalType multiplier, const Matrix2x2<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		Matrix2x2<T> product;
		product.M00() = left.M00() * right.M00() + left.M01() * right.M10();
		product.M10() = left.M10() * right.M00() + left.M11() * right.M10();
		product.M01() = left.M00() * right.M01() + left.M01() * right.M11();
		product.M11() = left.M10() * right.M01() + left.M11() * right.M11();

		return product;
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const Matrix2x2<T>& matrix, const Vector2<T>& vector) noexcept
	{
		Vector2<T> product;
		product.X() = matrix.M00() * vector.X() + matrix.M01() * vector.Y();
		product.Y() = matrix.M10() * vector.X() + matrix.M11() * vector.Y();

		return product;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, const T divisor) noexcept
	{
		Matrix2x2<T> quotient;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			quotient.Component(i) = matrix.Component(i) / divisor;
		}

		return quotient;
	}

	template<std::integral T>
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType divisor) noexcept
	{
		Matrix2x2<T> quotient;
		for (std::size_t i = 0; i < Matrix2x2<T>::ComponentCount; ++i)
		{
			quotient.Component(i) = static_cast<T>(matrix.Component(i) / divisor);
		}

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix)
	{
		return stream << matrix.ToString();
	}
}