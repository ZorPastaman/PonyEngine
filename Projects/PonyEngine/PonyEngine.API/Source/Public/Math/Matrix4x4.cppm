/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix4x4;

import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :ArrayArithmetics;
import :Common;
import :Matrix3x3;
import :Vector4;

export namespace PonyEngine::Math
{
	template<Arithmetic T>
	class Matrix4x4 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		static constexpr std::size_t Dimension = 4; ///< Row and column count. For any Matrix4x4 it's always 4.
		static constexpr std::size_t ComponentCount = Dimension * Dimension; ///< Component count. For any Matrix4x4 it's always 16.

		struct Predefined; ///< Predefined matrices.

		/// @brief Row access.
		/// @tparam IsConstant Is the underlying value const?
		template<bool IsConstant>
		class Row final
		{
		public:
			Row(const Row&) = delete;
			Row(Row&&) = delete;

			constexpr ~Row() noexcept = default;

			/// @brief Converts a row to a vector.
			[[nodiscard("Pure operator")]]
			constexpr operator Vector4<T>() const noexcept;

			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index. Must be in range [0, 3].
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr T& operator [](std::size_t columnIndex) noexcept requires(!IsConstant);
			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index. Must be in range [0, 3].
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr const T& operator [](std::size_t columnIndex) const noexcept;

			Row& operator =(const Row&) = delete;
			Row& operator =(Row&&) = delete;

			/// @brief Assigns a row from the @p row.
			/// @param row Row to assign from.
			/// @return @a This.
			constexpr Row& operator =(const Vector4<T>& row) noexcept requires(!IsConstant);

		private:
			using RowValueType = std::conditional_t<IsConstant, const T, T>; ///< @p const @p T or @p T depending on @p IsConstant.

			/// @brief Creates a row access.
			/// @param row First element in a row.
			[[nodiscard("Pure constructor")]]
			explicit constexpr Row(RowValueType* row) noexcept;

			RowValueType* const m_row; ///< Row pointer.

			friend Matrix4x4;
		};

		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		/// @brief Creates a matrix and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4() noexcept = default;
		/// @brief Creates a matrix and assigns its components from the arguments.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m20 Component 20.
		/// @param m30 Component 30.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		/// @param m21 Component 21.
		/// @param m31 Component 31.
		/// @param m02 Component 02.
		/// @param m12 Component 12.
		/// @param m22 Component 22.
		/// @param m32 Component 32.
		/// @param m03 Component 03.
		/// @param m13 Component 13.
		/// @param m23 Component 23.
		/// @param m33 Component 33.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4(T m00, T m10, T m20, T m30, T m01, T m11, T m21, T m31, T m02, T m12, T m22, T m32, T m03, T m13, T m23, T m33) noexcept;
		/// @brief Creates a matrix and assigns its components from column vectors.
		/// @param column0 Column 0.
		/// @param column1 Column 1.
		/// @param column2 Column 2.
		/// @param column3 Column 3.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4(const Vector4<T>& column0, const Vector4<T>& column1, const Vector4<T>& column2, const Vector4<T>& column3) noexcept;
		/// @brief Creates a matrix and assigns its components from the @p components array.
		/// @param components Component array. Its length must be at least 16.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix4x4(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4(const Matrix4x4& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4(Matrix4x4&& other) noexcept = default;

		constexpr ~Matrix4x4() noexcept = default;

		/// @brief Gets a component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		constexpr T& M00() noexcept;
		/// @brief Gets a component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		constexpr const T& M00() const noexcept;
		/// @brief Gets a component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		constexpr T& M10() noexcept;
		/// @brief Gets a component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		constexpr const T& M10() const noexcept;
		/// @brief Gets a component 20.
		/// @return Component 20.
		[[nodiscard("Pure function")]]
		constexpr T& M20() noexcept;
		/// @brief Gets a component 20.
		/// @return Component 20.
		[[nodiscard("Pure function")]]
		constexpr const T& M20() const noexcept;
		/// @brief Gets a component 30.
		/// @return Component 30.
		[[nodiscard("Pure function")]]
		constexpr T& M30() noexcept;
		/// @brief Gets a component 30.
		/// @return Component 30.
		[[nodiscard("Pure function")]]
		constexpr const T& M30() const noexcept;
		/// @brief Gets a component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		constexpr T& M01() noexcept;
		/// @brief Gets a component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		constexpr const T& M01() const noexcept;
		/// @brief Gets a component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		constexpr T& M11() noexcept;
		/// @brief Gets a component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		constexpr const T& M11() const noexcept;
		/// @brief Gets a component 21.
		/// @return Component 21.
		[[nodiscard("Pure function")]]
		constexpr T& M21() noexcept;
		/// @brief Gets a component 21.
		/// @return Component 21.
		[[nodiscard("Pure function")]]
		constexpr const T& M21() const noexcept;
		/// @brief Gets a component 31.
		/// @return Component 31.
		[[nodiscard("Pure function")]]
		constexpr T& M31() noexcept;
		/// @brief Gets a component 31.
		/// @return Component 31.
		[[nodiscard("Pure function")]]
		constexpr const T& M31() const noexcept;
		/// @brief Gets a component 02.
		/// @return Component 02.
		[[nodiscard("Pure function")]]
		constexpr T& M02() noexcept;
		/// @brief Gets a component 02.
		/// @return Component 02.
		[[nodiscard("Pure function")]]
		constexpr const T& M02() const noexcept;
		/// @brief Gets a component 12.
		/// @return Component 12.
		[[nodiscard("Pure function")]]
		constexpr T& M12() noexcept;
		/// @brief Gets a component 12.
		/// @return Component 12.
		[[nodiscard("Pure function")]]
		constexpr const T& M12() const noexcept;
		/// @brief Gets a component 22.
		/// @return Component 22.
		[[nodiscard("Pure function")]]
		constexpr T& M22() noexcept;
		/// @brief Gets a component 22.
		/// @return Component 22.
		[[nodiscard("Pure function")]]
		constexpr const T& M22() const noexcept;
		/// @brief Gets a component 32.
		/// @return Component 32.
		[[nodiscard("Pure function")]]
		constexpr T& M32() noexcept;
		/// @brief Gets a component 32.
		/// @return Component 32.
		[[nodiscard("Pure function")]]
		constexpr const T& M32() const noexcept;
		/// @brief Gets a component 03.
		/// @return Component 03.
		[[nodiscard("Pure function")]]
		constexpr T& M03() noexcept;
		/// @brief Gets a component 03.
		/// @return Component 03.
		[[nodiscard("Pure function")]]
		constexpr const T& M03() const noexcept;
		/// @brief Gets a component 13.
		/// @return Component 13.
		[[nodiscard("Pure function")]]
		constexpr T& M13() noexcept;
		/// @brief Gets a component 13.
		/// @return Component 13.
		[[nodiscard("Pure function")]]
		constexpr const T& M13() const noexcept;
		/// @brief Gets a component 23.
		/// @return Component 23.
		[[nodiscard("Pure function")]]
		constexpr T& M23() noexcept;
		/// @brief Gets a component 23.
		/// @return Component 23.
		[[nodiscard("Pure function")]]
		constexpr const T& M23() const noexcept;
		/// @brief Gets a component 33.
		/// @return Component 33.
		[[nodiscard("Pure function")]]
		constexpr T& M33() noexcept;
		/// @brief Gets a component 33.
		/// @return Component 33.
		[[nodiscard("Pure function")]]
		constexpr const T& M33() const noexcept;
		/// @brief Gets a data pointer - an array of 16 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 16 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr const T* Data() const noexcept;
		/// @brief Gets a column data pointer - an array of 4 elements.
		/// @param columnIndex Column index.
		/// @return Column data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data(std::size_t columnIndex) noexcept;
		/// @brief Gets a column data pointer - an array of 4 elements.
		/// @param columnIndex Column index.
		/// @return Column data pointer.
		[[nodiscard("Pure function")]]
		constexpr const T* Data(std::size_t columnIndex) const noexcept;

		/// @brief Gets a row.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetRow(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row.
		/// @param rowIndex Row index.
		/// @param value Row components.
		constexpr void SetRow(std::size_t rowIndex, const Vector4<T>& value) noexcept;

		/// @brief Gets a column.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetColumn(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column.
		/// @param columnIndex Column index.
		/// @param value Column components.
		constexpr void SetColumn(std::size_t columnIndex, const Vector4<T>& value) noexcept;

		/// @brief Gets a diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetDiagonal() const noexcept;
		/// @brief Sets a diagonal.
		/// @param value Diagonal components.
		constexpr void SetDiagonal(const Vector4<T>& value) noexcept;

		/// @brief Gets a counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetCounterDiagonal() const noexcept;
		/// @brief Sets a counter-diagonal.
		/// @param value Counter-diagonal components.
		constexpr void SetCounterDiagonal(const Vector4<T>& value) noexcept;

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
		constexpr Matrix4x4 Adjugate() const noexcept;

		/// @brief Computes a transpose of the matrix.
		/// @return Transpose.
		[[nodiscard("Pure function")]]
		constexpr Matrix4x4 Transpose() const noexcept;

		/// @brief Computes an inverse of the matrix.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix4x4 Inverse() const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Checks if this matrix is equal to a zero matrix.
		/// @return @a True if this matrix is equal to a zero matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsZero() const noexcept;
		/// @brief Checks if this matrix is almost equal to a zero matrix with a tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this matrix is almost equal to a zero matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostZero(T tolerance = T{0.00001}) const noexcept requires(std::is_floating_point_v<T>);
		/// @brief Checks if this matrix is equal to an identity matrix.
		/// @return @a True if this matrix is equal to an identity matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsIdentity() const noexcept;
		/// @brief Checks if this matrix is almost equal to an identity matrix with a tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this matrix is almost equal to an identity matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostIdentity(T tolerance = T{0.00001}) const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires(std::is_floating_point_v<T>);

		/// @brief Assigns arguments to the matrix components.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m20 Component 20.
		/// @param m30 Component 30.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		/// @param m21 Component 21.
		/// @param m31 Component 31.
		/// @param m02 Component 02.
		/// @param m12 Component 12.
		/// @param m22 Component 22.
		/// @param m32 Component 32.
		/// @param m03 Component 03.
		/// @param m13 Component 13.
		/// @param m23 Component 23.
		/// @param m33 Component 33.
		constexpr void Set(T m00, T m10, T m20, T m30, T m01, T m11, T m21, T m31, T m02, T m12, T m22, T m32, T m03, T m13, T m23, T m33) noexcept;
		/// @brief Assigns columns to the matrix.
		/// @param column0 Column 0 to assign.
		/// @param column1 Column 1 to assign.
		/// @param column2 Column 2 to assign.
		/// @param column3 Column 3 to assign.
		constexpr void Set(const Vector4<T>& column0, const Vector4<T>& column1, const Vector4<T>& column2, const Vector4<T>& column3) noexcept;
		/// @brief Assigns matrix components from the @p components array.
		/// @param components Component array. Its length must be at least 16.
		constexpr void Set(const T* components) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Matrix to multiply by.
		constexpr void Scale(const Matrix4x4& scale) noexcept;

		/// @brief Creates a string representing a state of the matrix.
		///        The format is '(m00, m01, m02, m03)(m10, m11, m12, m13)(m20, m21, m22, m23)(m30, m31, m32, m33)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index. Must be in range [0, 3].
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr Row<false> operator [](std::size_t rowIndex) noexcept;
		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index. Must be in range [0, 3].
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr Row<true> operator [](std::size_t rowIndex) const noexcept;

		constexpr Matrix4x4& operator =(const Matrix4x4& other) noexcept = default;
		constexpr Matrix4x4& operator =(Matrix4x4&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Matrix to add.
		/// @return @a This.
		constexpr Matrix4x4& operator +=(const Matrix4x4& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Matrix to subtract.
		/// @return @a This.
		constexpr Matrix4x4& operator -=(const Matrix4x4& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		constexpr Matrix4x4& operator *=(T multiplier) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		constexpr Matrix4x4& operator *=(ComputationalType multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p other.
		/// @param other Matrix to multiply.
		/// @return @a This.
		constexpr Matrix4x4& operator *=(const Matrix4x4& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		constexpr Matrix4x4& operator /=(T divisor) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		constexpr Matrix4x4& operator /=(ComputationalType divisor) noexcept requires(std::is_integral_v<T>);

		/// @brief Checks if two matrices are equal.
		/// @param other The other matrix.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix4x4& other) const noexcept;

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33.
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix4x4<T> Scale(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept;

	/// @brief Checks if two matrices are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix4x4<T>& left, const Matrix4x4<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Addition operator for two matrices.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator +(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept;

	/// @brief Negates the @p matrix.
	/// @tparam T Component type.
	/// @param matrix Matrix to negate.
	/// @return Negated matrix.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator -(const Matrix4x4<T>& matrix) noexcept;
	/// @brief Subtracts the @p right matrix from the @p left matrix.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator -(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept;

	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, T multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, typename Matrix4x4<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(T multiplier, const Matrix4x4<T>& matrix) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(typename Matrix4x4<T>::ComputationalType multiplier, const Matrix4x4<T>& matrix) noexcept;
	/// @brief Multiplies two matrices.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept;
	/// @brief Multiplies the @p matrix by the @p vector.
	/// @tparam T Component type.
	/// @param matrix Matrix.
	/// @param vector Vector.
	/// @return Product vector.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector4<T> operator *(const Matrix4x4<T>& matrix, const Vector4<T>& vector) noexcept;

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator /(const Matrix4x4<T>& matrix, T divisor) noexcept;
	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator /(const Matrix4x4<T>& matrix, typename Matrix4x4<T>::ComputationalType divisor) noexcept;

	/// @brief Puts matrix.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix4x4<T>& matrix);

	template<Arithmetic T>
	struct Matrix4x4<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr Matrix4x4 Identity = Matrix4x4(T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0}, T{1}); ///< Identity matrix.
		static constexpr Matrix4x4 Zero = Matrix4x4(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}); ///< Zero matrix.
	};
}

namespace PonyEngine::Math
{
	/// @brief Flattens matrices and treats them as vectors, and computes a dot product of those vectors.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @return Dot product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept;

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr Matrix4x4<T>::Row<IsConstant>::Row(RowValueType* const row) noexcept :
		m_row{row}
	{
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr Matrix4x4<T>::Row<IsConstant>::operator Vector4<T>() const noexcept
	{
		Vector4<T> row;

		for (std::size_t i = 0; i < Dimension; ++i)
		{
			row[i] = (*this)[i];
		}

		return row;
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr T& Matrix4x4<T>::Row<IsConstant>::operator [](const std::size_t columnIndex) noexcept requires(!IsConstant)
	{
		return m_row[columnIndex * Dimension];
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr const T& Matrix4x4<T>::Row<IsConstant>::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_row[columnIndex * Dimension];
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr typename Matrix4x4<T>::template Row<IsConstant>& Matrix4x4<T>::Row<IsConstant>::operator =(const Vector4<T>& row) noexcept requires(!IsConstant)
	{
		for (std::size_t i = 0; i < Dimension; ++i)
		{
			(*this)[i] = row[i];
		}

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>::Matrix4x4(const T m00, const T m10, const T m20, const T m30, const T m01, const T m11, const T m21, const T m31, 
		const T m02, const T m12, const T m22, const T m32, const T m03, const T m13, const T m23, const T m33) noexcept :
		m_components{m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33}
	{
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>::Matrix4x4(const Vector4<T>& column0, const Vector4<T>& column1, const Vector4<T>& column2, const Vector4<T>& column3) noexcept :
		Matrix4x4(column0.X(), column0.Y(), column0.Z(), column0.W(), column1.X(), column1.Y(), column1.Z(), column1.W(), 
			column2.X(), column2.Y(), column2.Z(), column2.W(), column3.X(), column3.Y(), column3.Z(), column3.W())
	{
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>::Matrix4x4(const T* const components) noexcept
	{
		Set(components);
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M20() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M20() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M30() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M30() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M01() noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M01() const noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M11() noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M11() const noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M21() noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M21() const noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M31() noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M31() const noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M02() noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M02() const noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M12() noexcept
	{
		return m_components[9];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M12() const noexcept
	{
		return m_components[9];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M22() noexcept
	{
		return m_components[10];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M22() const noexcept
	{
		return m_components[10];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M32() noexcept
	{
		return m_components[11];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M32() const noexcept
	{
		return m_components[11];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M03() noexcept
	{
		return m_components[12];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M03() const noexcept
	{
		return m_components[12];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M13() noexcept
	{
		return m_components[13];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M13() const noexcept
	{
		return m_components[13];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M23() noexcept
	{
		return m_components[14];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M23() const noexcept
	{
		return m_components[14];
	}

	template<Arithmetic T>
	constexpr T& Matrix4x4<T>::M33() noexcept
	{
		return m_components[15];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M33() const noexcept
	{
		return m_components[15];
	}

	template<Arithmetic T>
	constexpr T* Matrix4x4<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Matrix4x4<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr T* Matrix4x4<T>::Data(const std::size_t columnIndex) noexcept
	{
		return Data() + columnIndex * Dimension;
	}

	template<Arithmetic T>
	constexpr const T* Matrix4x4<T>::Data(const std::size_t columnIndex) const noexcept
	{
		return Data() + columnIndex * Dimension;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		return (*this)[rowIndex];
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::SetRow(const std::size_t rowIndex, const Vector4<T>& value) noexcept
	{
		(*this)[rowIndex] = value;
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetColumn(const std::size_t columnIndex) const noexcept
	{
		return Vector4<T>(Data(columnIndex));
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::SetColumn(const std::size_t columnIndex, const Vector4<T>& value) noexcept
	{
		Copy(Data(columnIndex), value.Data(), Dimension);
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetDiagonal() const noexcept
	{
		return Vector4<T>(M00(), M11(), M22(), M33());
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::SetDiagonal(const Vector4<T>& value) noexcept
	{
		M00() = value.X();
		M11() = value.Y();
		M22() = value.Z();
		M33() = value.W();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetCounterDiagonal() const noexcept
	{
		return Vector4<T>(M03(), M12(), M21(), M30());
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::SetCounterDiagonal(const Vector4<T>& value) noexcept
	{
		M03() = value.X();
		M12() = value.Y();
		M21() = value.Z();
		M30() = value.W();
	}

	template<Arithmetic T>
	constexpr T Matrix4x4<T>::Trace() const noexcept
	{
		return GetDiagonal().Sum();
	}

	template<Arithmetic T>
	constexpr T Matrix4x4<T>::Determinant() const noexcept
	{
		return M00() * Matrix3x3<T>(M11(), M21(), M31(), M12(), M22(), M32(), M13(), M23(), M33()).Determinant() -
			M10() * Matrix3x3<T>(M01(), M21(), M31(), M02(), M22(), M32(), M03(), M23(), M33()).Determinant() +
			M20() * Matrix3x3<T>(M01(), M11(), M31(), M02(), M12(), M32(), M03(), M13(), M33()).Determinant() -
			M30() * Matrix3x3<T>(M01(), M11(), M21(), M02(), M12(), M22(), M03(), M13(), M23()).Determinant();
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Matrix4x4<T>::Adjugate() const noexcept
	{
		Matrix4x4 adjugate;
		adjugate.M00() = Matrix3x3<T>(M11(), M21(), M31(), M12(), M22(), M32(), M13(), M23(), M33()).Determinant();
		adjugate.M10() = -Matrix3x3<T>(M10(), M20(), M30(), M12(), M22(), M32(), M13(), M23(), M33()).Determinant();
		adjugate.M20() = Matrix3x3<T>(M10(), M20(), M30(), M11(), M21(), M31(), M13(), M23(), M33()).Determinant();
		adjugate.M30() = -Matrix3x3<T>(M10(), M20(), M30(), M11(), M21(), M31(), M12(), M22(), M32()).Determinant();
		adjugate.M01() = -Matrix3x3<T>(M01(), M21(), M31(), M02(), M22(), M32(), M03(), M23(), M33()).Determinant();
		adjugate.M11() = Matrix3x3<T>(M00(), M20(), M30(), M02(), M22(), M32(), M03(), M23(), M33()).Determinant();
		adjugate.M21() = -Matrix3x3<T>(M00(), M20(), M30(), M01(), M21(), M31(), M03(), M23(), M33()).Determinant();
		adjugate.M31() = Matrix3x3<T>(M00(), M20(), M30(), M01(), M21(), M31(), M02(), M22(), M32()).Determinant();
		adjugate.M02() = Matrix3x3<T>(M01(), M11(), M31(), M02(), M12(), M32(), M03(), M13(), M33()).Determinant();
		adjugate.M12() = -Matrix3x3<T>(M00(), M10(), M30(), M02(), M12(), M32(), M03(), M13(), M33()).Determinant();
		adjugate.M22() = Matrix3x3<T>(M00(), M10(), M30(), M01(), M11(), M31(), M03(), M13(), M33()).Determinant();
		adjugate.M32() = -Matrix3x3<T>(M00(), M10(), M30(), M01(), M11(), M31(), M02(), M12(), M32()).Determinant();
		adjugate.M03() = -Matrix3x3<T>(M01(), M11(), M21(), M02(), M12(), M22(), M03(), M13(), M23()).Determinant();
		adjugate.M13() = Matrix3x3<T>(M00(), M10(), M20(), M02(), M12(), M22(), M03(), M13(), M23()).Determinant();
		adjugate.M23() = -Matrix3x3<T>(M00(), M10(), M20(), M01(), M11(), M21(), M03(), M13(), M23()).Determinant();
		adjugate.M33() = Matrix3x3<T>(M00(), M10(), M20(), M01(), M11(), M21(), M02(), M12(), M22()).Determinant();

		return adjugate;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Matrix4x4<T>::Transpose() const noexcept
	{
		return Matrix4x4(M00(), M01(), M02(), M03(), M10(), M11(), M12(), M13(), M20(), M21(), M22(), M23(), M30(), M31(), M32(), M33());
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Matrix4x4<T>::Inverse() const noexcept requires(std::is_floating_point_v<T>)
	{
		return Adjugate() * (ComputationalType{1} / Determinant());
	}

	template<Arithmetic T>
	constexpr bool Matrix4x4<T>::IsZero() const noexcept
	{
		return *this == Predefined::Zero;
	}

	template<Arithmetic T>
	constexpr bool Matrix4x4<T>::IsAlmostZero(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Zero, tolerance);
	}

	template<Arithmetic T>
	constexpr bool Matrix4x4<T>::IsIdentity() const noexcept
	{
		return *this == Predefined::Identity;
	}

	template<Arithmetic T>
	constexpr bool Matrix4x4<T>::IsAlmostIdentity(const T tolerance) const noexcept requires(std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Predefined::Identity, tolerance);
	}

	template<Arithmetic T>
	bool Matrix4x4<T>::IsFinite() const noexcept requires(std::is_floating_point_v<T>)
	{
		return Math::IsFinite(Data(), ComponentCount);
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::Set(const T m00, const T m10, const T m20, const T m30, const T m01, const T m11, const T m21, const T m31,
		const T m02, const T m12, const T m22, const T m32, const T m03, const T m13, const T m23, const T m33) noexcept
	{
		M00() = m00;
		M10() = m10;
		M20() = m20;
		M30() = m30;
		M01() = m01;
		M11() = m11;
		M21() = m21;
		M31() = m31;
		M02() = m02;
		M12() = m12;
		M22() = m22;
		M32() = m32;
		M03() = m03;
		M13() = m13;
		M23() = m23;
		M33() = m33;
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::Set(const Vector4<T>& column0, const Vector4<T>& column1, const Vector4<T>& column2, const Vector4<T>& column3) noexcept
	{
		Set(column0.X(), column0.Y(), column0.Z(), column0.W(), column1.X(), column1.Y(), column1.Z(), column1.W(),
			column2.X(), column2.Y(), column2.Z(), column2.W(), column3.X(), column3.Y(), column3.Z(), column3.W());
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::Set(const T* const components) noexcept
	{
		Copy(Data(), components, ComponentCount);
	}

	template<Arithmetic T>
	constexpr void Matrix4x4<T>::Scale(const Matrix4x4& scale) noexcept
	{
		Multiply(Data(), scale.Data(), ComponentCount);
	}

	template<Arithmetic T>
	std::string Matrix4x4<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})", M00(), M01(), M02(), M03(), M10(), M11(), M12(), M13(), M20(), M21(), M22(), M23(), M30(), M31(), M32(), M33());
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Scale(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		Matrix4x4<T> scaled;
		Multiply(scaled.Data(), left.Data(), right.Data(), Matrix4x4<T>::ComponentCount);

		return scaled;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Matrix4x4<T>& left, const Matrix4x4<T>& right, const T tolerance) noexcept
	{
		const Matrix4x4<T> diff = left - right;

		return Dot(diff, diff) < tolerance * tolerance;
	}

	template<Arithmetic T>
	constexpr T Dot(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		return left.M00() * right.M00() + left.M10() * right.M10() + left.M20() * right.M20() + left.M30() * right.M30() +
			left.M01() * right.M01() + left.M11() * right.M11() + left.M21() * right.M21() + left.M31() * right.M31() +
			left.M02() * right.M02() + left.M12() * right.M12() + left.M22() * right.M22() + left.M32() * right.M32() +
			left.M03() * right.M03() + left.M13() * right.M13() + left.M23() * right.M23() + left.M33() * right.M33();
	}

	template<Arithmetic T>
	constexpr typename Matrix4x4<T>::template Row<false> Matrix4x4<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row<false>(Data() + rowIndex);
	}

	template<Arithmetic T>
	constexpr typename Matrix4x4<T>::template Row<true> Matrix4x4<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return Row<true>(Data() + rowIndex);
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator +=(const Matrix4x4& other) noexcept
	{
		Add(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator -=(const Matrix4x4& other) noexcept
	{
		Subtract(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator *=(const T multiplier) noexcept
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator *=(const ComputationalType multiplier) noexcept requires(std::is_integral_v<T>)
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator *=(const Matrix4x4& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator /=(const T divisor) noexcept
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>& Matrix4x4<T>::operator /=(const ComputationalType divisor) noexcept requires(std::is_integral_v<T>)
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Matrix4x4<T>::operator ==(const Matrix4x4& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator +(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		Matrix4x4<T> sum;
		Add(sum.Data(), left.Data(), right.Data(), Matrix4x4<T>::ComponentCount);

		return sum;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator -(const Matrix4x4<T>& matrix) noexcept
	{
		Matrix4x4<T> negated;
		Negate(negated.Data(), matrix.Data(), Matrix4x4<T>::ComponentCount);

		return negated;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator -(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		Matrix4x4<T> difference;
		Subtract(difference.Data(), left.Data(), right.Data(), Matrix4x4<T>::ComponentCount);

		return difference;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, const T multiplier) noexcept
	{
		Matrix4x4<T> product;
		Multiply(product.Data(), matrix.Data(), multiplier, Matrix4x4<T>::ComponentCount);

		return product;
	}

	template<std::integral T>
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, const typename Matrix4x4<T>::ComputationalType multiplier) noexcept
	{
		Matrix4x4<T> product;
		Multiply(product.Data(), matrix.Data(), multiplier, Matrix4x4<T>::ComponentCount);

		return product;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator *(const T multiplier, const Matrix4x4<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<std::integral T>
	constexpr Matrix4x4<T> operator *(const typename Matrix4x4<T>::ComputationalType multiplier, const Matrix4x4<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		Matrix4x4<T> product;
		product.M00() = left.M00() * right.M00() + left.M01() * right.M10() + left.M02() * right.M20() + left.M03() * right.M30();
		product.M10() = left.M10() * right.M00() + left.M11() * right.M10() + left.M12() * right.M20() + left.M13() * right.M30();
		product.M20() = left.M20() * right.M00() + left.M21() * right.M10() + left.M22() * right.M20() + left.M23() * right.M30();
		product.M30() = left.M30() * right.M00() + left.M31() * right.M10() + left.M32() * right.M20() + left.M33() * right.M30();
		product.M01() = left.M00() * right.M01() + left.M01() * right.M11() + left.M02() * right.M21() + left.M03() * right.M31();
		product.M11() = left.M10() * right.M01() + left.M11() * right.M11() + left.M12() * right.M21() + left.M13() * right.M31();
		product.M21() = left.M20() * right.M01() + left.M21() * right.M11() + left.M22() * right.M21() + left.M23() * right.M31();
		product.M31() = left.M30() * right.M01() + left.M31() * right.M11() + left.M32() * right.M21() + left.M33() * right.M31();
		product.M02() = left.M00() * right.M02() + left.M01() * right.M12() + left.M02() * right.M22() + left.M03() * right.M32();
		product.M12() = left.M10() * right.M02() + left.M11() * right.M12() + left.M12() * right.M22() + left.M13() * right.M32();
		product.M22() = left.M20() * right.M02() + left.M21() * right.M12() + left.M22() * right.M22() + left.M23() * right.M32();
		product.M32() = left.M30() * right.M02() + left.M31() * right.M12() + left.M32() * right.M22() + left.M33() * right.M32();
		product.M03() = left.M00() * right.M03() + left.M01() * right.M13() + left.M02() * right.M23() + left.M03() * right.M33();
		product.M13() = left.M10() * right.M03() + left.M11() * right.M13() + left.M12() * right.M23() + left.M13() * right.M33();
		product.M23() = left.M20() * right.M03() + left.M21() * right.M13() + left.M22() * right.M23() + left.M23() * right.M33();
		product.M33() = left.M30() * right.M03() + left.M31() * right.M13() + left.M32() * right.M23() + left.M33() * right.M33();

		return product;
	}

	template<Arithmetic T>
	constexpr Vector4<T> operator *(const Matrix4x4<T>& matrix, const Vector4<T>& vector) noexcept
	{
		Vector4<T> product;
		product.X() = matrix.M00() * vector.X() + matrix.M01() * vector.Y() + matrix.M02() * vector.Z() + matrix.M03() * vector.W();
		product.Y() = matrix.M10() * vector.X() + matrix.M11() * vector.Y() + matrix.M12() * vector.Z() + matrix.M13() * vector.W();
		product.Z() = matrix.M20() * vector.X() + matrix.M21() * vector.Y() + matrix.M22() * vector.Z() + matrix.M23() * vector.W();
		product.W() = matrix.M30() * vector.X() + matrix.M31() * vector.Y() + matrix.M32() * vector.Z() + matrix.M33() * vector.W();

		return product;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator /(const Matrix4x4<T>& matrix, const T divisor) noexcept
	{
		Matrix4x4<T> quotient;
		Divide(quotient.Data(), matrix.Data(), divisor, Matrix4x4<T>::ComponentCount);

		return quotient;
	}

	template<std::integral T>
	constexpr Matrix4x4<T> operator /(const Matrix4x4<T>& matrix, const typename Matrix4x4<T>::ComputationalType divisor) noexcept
	{
		Matrix4x4<T> quotient;
		Divide(quotient.Data(), matrix.Data(), divisor, Matrix4x4<T>::ComponentCount);

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix4x4<T>& matrix)
	{
		return stream << matrix.ToString();
	}
}
