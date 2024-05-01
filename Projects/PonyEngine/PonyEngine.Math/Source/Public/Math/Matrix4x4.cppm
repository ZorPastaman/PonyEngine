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

import :Common;
import :Matrix3x3;
import :Vector4;

export namespace PonyEngine::Math
{
	template<Arithmetic T>
	class Matrix4x4 final
	{
	public:
		/// @brief Row access.
		class Row final
		{
		public:
			Row(const Row&) = delete;
			Row(Row&&) = delete;

			~Row() noexcept = default;

			/// @brief Converts a row to a vector.
			[[nodiscard("Pure operator")]]
			operator Vector4<T>() const noexcept;

			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index.
			/// @return Component.
			[[nodiscard("Pure operator")]]
			T& operator [](std::size_t columnIndex) const noexcept;

			Row& operator =(const Row&) = delete;
			Row& operator =(Row&&) = delete;

		private:
			/// @brief Creates a row access.
			/// @param row First element in a row.
			[[nodiscard("Pure constructor")]]
			explicit Row(T* row) noexcept;

			T* const m_row; ///< Row pointer.

			friend Matrix4x4;
		};

		/// @brief Const row access.
		class ConstRow final
		{
		public:
			ConstRow(const ConstRow&) = delete;
			ConstRow(ConstRow&&) = delete;

			constexpr ~ConstRow() noexcept = default;

			/// @brief Converts a row to a vector.
			[[nodiscard("Pure operator")]]
			constexpr operator Vector4<T>() const noexcept;

			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index.
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr const T& operator [](std::size_t columnIndex) const noexcept;

			ConstRow& operator =(const ConstRow&) = delete;
			ConstRow& operator =(ConstRow&&) = delete;

		private:
			/// @brief Creates a const row access.
			/// @param row First element in a row.
			[[nodiscard("Pure constructor")]]
			explicit constexpr ConstRow(const T* row) noexcept;

			const T* const m_row; ///< Row pointer.

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
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4(const Matrix4x4& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix4x4(Matrix4x4&& other) noexcept = default;

		constexpr ~Matrix4x4() noexcept = default;

		/// @brief Creates a Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).
		/// @return Identity matrix.
		///	@remark For non-constexpr execution use @p Matrix4x4::Identity variable.
		[[nodiscard("Pure function")]]
		static consteval Matrix4x4 IdentityConsteval();
		/// @brief Creates a Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0).
		/// @return Zero matrix.
		///	@remark For non-constexpr execution use @p Matrix4x4::Zero variable.
		[[nodiscard("Pure function")]]
		static consteval Matrix4x4 ZeroConsteval();

		/// @brief Gets a component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		T& M00() noexcept;
		/// @brief Gets a component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		constexpr const T& M00() const noexcept;
		/// @brief Gets a component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		T& M10() noexcept;
		/// @brief Gets a component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		constexpr const T& M10() const noexcept;
		/// @brief Gets a component 20.
		/// @return Component 20.
		[[nodiscard("Pure function")]]
		T& M20() noexcept;
		/// @brief Gets a component 20.
		/// @return Component 20.
		[[nodiscard("Pure function")]]
		constexpr const T& M20() const noexcept;
		/// @brief Gets a component 30.
		/// @return Component 30.
		[[nodiscard("Pure function")]]
		T& M30() noexcept;
		/// @brief Gets a component 30.
		/// @return Component 30.
		[[nodiscard("Pure function")]]
		constexpr const T& M30() const noexcept;
		/// @brief Gets a component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		T& M01() noexcept;
		/// @brief Gets a component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		constexpr const T& M01() const noexcept;
		/// @brief Gets a component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		T& M11() noexcept;
		/// @brief Gets a component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		constexpr const T& M11() const noexcept;
		/// @brief Gets a component 21.
		/// @return Component 21.
		[[nodiscard("Pure function")]]
		T& M21() noexcept;
		/// @brief Gets a component 21.
		/// @return Component 21.
		[[nodiscard("Pure function")]]
		constexpr const T& M21() const noexcept;
		/// @brief Gets a component 31.
		/// @return Component 31.
		[[nodiscard("Pure function")]]
		T& M31() noexcept;
		/// @brief Gets a component 31.
		/// @return Component 31.
		[[nodiscard("Pure function")]]
		constexpr const T& M31() const noexcept;
		/// @brief Gets a component 02.
		/// @return Component 02.
		[[nodiscard("Pure function")]]
		T& M02() noexcept;
		/// @brief Gets a component 02.
		/// @return Component 02.
		[[nodiscard("Pure function")]]
		constexpr const T& M02() const noexcept;
		/// @brief Gets a component 12.
		/// @return Component 12.
		[[nodiscard("Pure function")]]
		T& M12() noexcept;
		/// @brief Gets a component 12.
		/// @return Component 12.
		[[nodiscard("Pure function")]]
		constexpr const T& M12() const noexcept;
		/// @brief Gets a component 22.
		/// @return Component 22.
		[[nodiscard("Pure function")]]
		T& M22() noexcept;
		/// @brief Gets a component 22.
		/// @return Component 22.
		[[nodiscard("Pure function")]]
		constexpr const T& M22() const noexcept;
		/// @brief Gets a component 32.
		/// @return Component 32.
		[[nodiscard("Pure function")]]
		T& M32() noexcept;
		/// @brief Gets a component 32.
		/// @return Component 32.
		[[nodiscard("Pure function")]]
		constexpr const T& M32() const noexcept;
		/// @brief Gets a component 03.
		/// @return Component 03.
		[[nodiscard("Pure function")]]
		T& M03() noexcept;
		/// @brief Gets a component 03.
		/// @return Component 03.
		[[nodiscard("Pure function")]]
		constexpr const T& M03() const noexcept;
		/// @brief Gets a component 13.
		/// @return Component 13.
		[[nodiscard("Pure function")]]
		T& M13() noexcept;
		/// @brief Gets a component 13.
		/// @return Component 13.
		[[nodiscard("Pure function")]]
		constexpr const T& M13() const noexcept;
		/// @brief Gets a component 23.
		/// @return Component 23.
		[[nodiscard("Pure function")]]
		T& M23() noexcept;
		/// @brief Gets a component 23.
		/// @return Component 23.
		[[nodiscard("Pure function")]]
		constexpr const T& M23() const noexcept;
		/// @brief Gets a component 33.
		/// @return Component 33.
		[[nodiscard("Pure function")]]
		T& M33() noexcept;
		/// @brief Gets a component 33.
		/// @return Component 33.
		[[nodiscard("Pure function")]]
		constexpr const T& M33() const noexcept;
		/// @brief Gets a data pointer - an array of 16 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 16 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr const T* Data() const noexcept;

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
		constexpr Matrix4x4 Inverse() const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

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
		void Set(T m00, T m10, T m20, T m30, T m01, T m11, T m21, T m31, T m02, T m12, T m22, T m32, T m03, T m13, T m23, T m33) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Matrix to multiply by.
		void Scale(const Matrix4x4& scale) noexcept;

		/// @brief Gets a row.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetRow(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row.
		/// @param rowIndex Row index.
		/// @param value Row components.
		void SetRow(std::size_t rowIndex, const Vector4<T>& value) noexcept;

		/// @brief Gets a column.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetColumn(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column.
		/// @param columnIndex Column index.
		/// @param value Column components.
		void SetColumn(std::size_t columnIndex, const Vector4<T>& value) noexcept;

		/// @brief Gets a diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetDiagonal() const noexcept;
		/// @brief Sets a diagonal.
		/// @param value Diagonal components.
		void SetDiagonal(const Vector4<T>& value) noexcept;

		/// @brief Gets a counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector4<T> GetCounterDiagonal() const noexcept;
		/// @brief Sets a counter-diagonal.
		/// @param value Counter-diagonal components.
		void SetCounterDiagonal(const Vector4<T>& value) noexcept;

		/// @brief Creates a string representing a state of the matrix.
		///        The format is '(m00, m01, m02, m03)(m10, m11, m12, m13)(m20, m21, m22, m23)(m30, m31, m32, m33)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		Row operator [](std::size_t rowIndex) noexcept;
		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr ConstRow operator [](std::size_t rowIndex) const noexcept;

		Matrix4x4& operator =(const Matrix4x4& other) noexcept = default;
		Matrix4x4& operator =(Matrix4x4&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Matrix to add.
		/// @return @a This.
		Matrix4x4& operator +=(const Matrix4x4& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Matrix to subtract.
		/// @return @a This.
		Matrix4x4& operator -=(const Matrix4x4& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		Matrix4x4& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		Matrix4x4& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other.
		/// @param other Matrix to multiply.
		/// @return @a This.
		Matrix4x4& operator *=(const Matrix4x4& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		Matrix4x4& operator /=(ComputationalType divisor) noexcept;

		/// @brief Checks if two matrices are equal.
		/// @param other The other matrix.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix4x4& other) const noexcept;

		static const Matrix4x4 Identity; ///< Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).
		static const Matrix4x4 Zero; ///< Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0).

		static constexpr std::size_t RowCount = 4; ///< Row count. For any Matrix4x4 it's always 4.
		static constexpr std::size_t ColumnCount = 4; ///< Column count. For any Matrix4x4 it's always 4.
		static constexpr std::size_t ComponentCount = RowCount * ColumnCount; ///< Component count. For any Matrix4x4 it's always 16.

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
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix4x4<T>& left, const Matrix4x4<T>& right, typename Matrix4x4<T>::ComputationalType tolerance = typename Matrix4x4<T>::ComputationalType{0.00001}) noexcept;

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
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, T multiplier) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, typename Matrix4x4<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator *(T multiplier, const Matrix4x4<T>& matrix) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
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
	constexpr Vector3<T> operator *(const Matrix4x4<T>& matrix, const Vector4<T>& vector) noexcept;

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix4x4<T> operator /(const Matrix4x4<T>& matrix, typename Matrix4x4<T>::ComputationalType divisor) noexcept;

	/// @brief Puts matrix.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix4x4<T>& matrix);
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	Matrix4x4<T>::Row::Row(T* const row) noexcept :
		m_row(row)
	{
	}

	template<Arithmetic T>
	Matrix4x4<T>::Row::operator Vector4<T>() const noexcept
	{
		const T x = m_row[0];
		const T y = m_row[4];
		const T z = m_row[8];
		const T w = m_row[12];

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::Row::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_row[columnIndex * 4];
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>::ConstRow::ConstRow(const T* const row) noexcept :
		m_row{row}
	{
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T>::ConstRow::operator Vector4<T>() const noexcept
	{
		const T x = m_row[0];
		const T y = m_row[4];
		const T z = m_row[8];
		const T w = m_row[12];

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::ConstRow::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_row[columnIndex * 4];
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
	consteval Matrix4x4<T> Matrix4x4<T>::IdentityConsteval()
	{
		return Matrix4x4(T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0}, T{1});
	}

	template<Arithmetic T>
	consteval Matrix4x4<T> Matrix4x4<T>::ZeroConsteval()
	{
		return Matrix4x4(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0});
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M20() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M20() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M30() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M30() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M01() noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M01() const noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M11() noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M11() const noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M21() noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M21() const noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M31() noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M31() const noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M02() noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M02() const noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M12() noexcept
	{
		return m_components[9];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M12() const noexcept
	{
		return m_components[9];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M22() noexcept
	{
		return m_components[10];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M22() const noexcept
	{
		return m_components[10];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M32() noexcept
	{
		return m_components[11];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M32() const noexcept
	{
		return m_components[11];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M03() noexcept
	{
		return m_components[12];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M03() const noexcept
	{
		return m_components[12];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M13() noexcept
	{
		return m_components[13];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M13() const noexcept
	{
		return m_components[13];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M23() noexcept
	{
		return m_components[14];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M23() const noexcept
	{
		return m_components[14];
	}

	template<Arithmetic T>
	T& Matrix4x4<T>::M33() noexcept
	{
		return m_components[15];
	}

	template<Arithmetic T>
	constexpr const T& Matrix4x4<T>::M33() const noexcept
	{
		return m_components[15];
	}

	template<Arithmetic T>
	T* Matrix4x4<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Matrix4x4<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr T Matrix4x4<T>::Determinant() const noexcept
	{
		return M00() * (M11() * M22() * M33() + M12() * M23() * M31() + M13() * M21() * M32() - M13() * M22() * M31() - M12() * M21() * M33() - M11() * M23() * M32()) -
			M10() * (M01() * M22() * M33() + M02() * M23() * M31() + M03() * M21() * M32() - M03() * M22() * M31() - M02() * M21() * M33() - M01() * M23() * M32()) +
			M20() * (M01() * M12() * M33() + M02() * M13() * M31() + M03() * M11() * M32() - M03() * M12() * M31() - M02() * M11() * M33() - M01() * M13() * M32()) -
			M30() * (M01() * M12() * M23() + M02() * M13() * M21() + M03() * M11() * M22() - M03() * M12() * M21() - M02() * M11() * M23() - M01() * M13() * M22());
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Matrix4x4<T>::Adjugate() const noexcept
	{
		const T minor00 = Matrix3x3<T>(M11(), M21(), M31(), M12(), M22(), M32(), M13(), M23(), M33()).Determinant();
		const T minor10 = -Matrix3x3<T>(M01(), M21(), M31(), M02(), M22(), M32(), M03(), M23(), M33()).Determinant();
		const T minor20 = Matrix3x3<T>(M01(), M11(), M31(), M02(), M12(), M32(), M03(), M13(), M33()).Determinant();
		const T minor30 = -Matrix3x3<T>(M01(), M11(), M21(), M02(), M12(), M22(), M03(), M13(), M23()).Determinant();
		const T minor01 = -Matrix3x3<T>(M10(), M20(), M30(), M12(), M22(), M32(), M13(), M23(), M33()).Determinant();
		const T minor11 = Matrix3x3<T>(M00(), M20(), M30(), M02(), M22(), M32(), M03(), M23(), M33()).Determinant();
		const T minor21 = -Matrix3x3<T>(M00(), M10(), M30(), M02(), M12(), M32(), M03(), M13(), M33()).Determinant();
		const T minor31 = Matrix3x3<T>(M00(), M10(), M20(), M02(), M12(), M22(), M03(), M13(), M23()).Determinant();
		const T minor02 = Matrix3x3<T>(M10(), M20(), M30(), M11(), M21(), M31(), M13(), M23(), M33()).Determinant();
		const T minor12 = -Matrix3x3<T>(M00(), M20(), M30(), M01(), M21(), M31(), M03(), M23(), M33()).Determinant();
		const T minor22 = Matrix3x3<T>(M00(), M10(), M30(), M01(), M11(), M21(), M03(), M13(), M33()).Determinant();
		const T minor32 = -Matrix3x3<T>(M00(), M10(), M20(), M01(), M11(), M21(), M03(), M13(), M23()).Determinant();
		const T minor03 = -Matrix3x3<T>(M10(), M20(), M30(), M11(), M21(), M31(), M12(), M22(), M32()).Determinant();
		const T minor13 = Matrix3x3<T>(M00(), M20(), M30(), M01(), M21(), M31(), M02(), M22(), M32()).Determinant();
		const T minor23 = -Matrix3x3<T>(M00(), M10(), M30(), M01(), M11(), M31(), M02(), M12(), M32()).Determinant();
		const T minor33 = Matrix3x3<T>(M00(), M10(), M20(), M01(), M11(), M21(), M02(), M12(), M22()).Determinant();

		return Matrix4x4(minor00, minor01, minor02, minor03, minor10, minor11, minor12, minor13, minor20, minor21, minor22, minor23, minor30, minor31, minor32, minor33);
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Matrix4x4<T>::Transpose() const noexcept
	{
		return Matrix4x4(M00, M01, M02, M03(), M10(), M11(), M12(), M13(), M20(), M21(), M22(), M23(), M30(), M31(), M32(), M33());
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Matrix4x4<T>::Inverse() const noexcept
	{
		return Adjugate() * (ComputationalType{1} / Determinant());
	}

	template<Arithmetic T>
	bool Matrix4x4<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(M00()) && std::isfinite(M10()) && std::isfinite(M20()) && std::isfinite(M30()) &&
				std::isfinite(M01()) && std::isfinite(M11()) && std::isfinite(M21()) && std::isfinite(M31()) &&
				std::isfinite(M02()) && std::isfinite(M12()) && std::isfinite(M22()) && std::isfinite(M32()) &&
				std::isfinite(M03()) && std::isfinite(M13()) && std::isfinite(M23()) && std::isfinite(M33());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Matrix4x4<T>::Set(const T m00, const T m10, const T m20, const T m30, const T m01, const T m11, const T m21, const T m31, 
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
	void Matrix4x4<T>::Scale(const Matrix4x4& scale) noexcept
	{
		M00() *= scale.M00();
		M10() *= scale.M10();
		M20() *= scale.M20();
		M30() *= scale.M30();
		M01() *= scale.M01();
		M11() *= scale.M11();
		M21() *= scale.M21();
		M31() *= scale.M31();
		M02() *= scale.M02();
		M12() *= scale.M12();
		M22() *= scale.M22();
		M32() *= scale.M32();
		M03() *= scale.M03();
		M13() *= scale.M13();
		M23() *= scale.M23();
		M33() *= scale.M33();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const T x = m_components[rowIndex];
		const T y = m_components[rowIndex + 4];
		const T z = m_components[rowIndex + 8];
		const T w = m_components[rowIndex + 12];

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	void Matrix4x4<T>::SetRow(const std::size_t rowIndex, const Vector4<T>& value) noexcept
	{
		m_components[rowIndex] = value.X();
		m_components[rowIndex + 4] = value.Y();
		m_components[rowIndex + 8] = value.Z();
		m_components[rowIndex + 12] = value.W();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetColumn(const std::size_t columnIndex) const noexcept
	{
		const std::size_t begin = columnIndex * 4;

		const T x = m_components[begin];
		const T y = m_components[begin + 1];
		const T z = m_components[begin + 2];
		const T w = m_components[begin + 3];

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	void Matrix4x4<T>::SetColumn(const std::size_t columnIndex, const Vector4<T>& value) noexcept
	{
		const std::size_t begin = columnIndex * 4;

		m_components[begin] = value.X();
		m_components[begin + 1] = value.Y();
		m_components[begin + 2] = value.Z();
		m_components[begin + 3] = value.W();
	}

	template<Arithmetic T>
	constexpr Vector4<T> Matrix4x4<T>::GetDiagonal() const noexcept
	{
		return Vector4<T>(M00(), M11(), M22(), M33());
	}

	template<Arithmetic T>
	void Matrix4x4<T>::SetDiagonal(const Vector4<T>& value) noexcept
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
	void Matrix4x4<T>::SetCounterDiagonal(const Vector4<T>& value) noexcept
	{
		M03() = value.X();
		M12() = value.Y();
		M21() = value.Z();
		M30() = value.W();
	}

	template<Arithmetic T>
	std::string Matrix4x4<T>::ToString() const
	{
		return std::format("({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})", M00(), M01(), M02(), M03(), M10(), M11(), M12(), M13(), M20(), M21(), M22(), M23(), M30(), M31(), M32(), M33());
	}

	template<Arithmetic T>
	typename Matrix4x4<T>::Row Matrix4x4<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row(Data()[rowIndex]);
	}

	template<Arithmetic T>
	constexpr typename Matrix4x4<T>::ConstRow Matrix4x4<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return ConstRow(Data()[rowIndex]);
	}

	template<Arithmetic T>
	Matrix4x4<T>& Matrix4x4<T>::operator +=(const Matrix4x4& other) noexcept
	{
		M00() += other.M00();
		M10() += other.M10();
		M20() += other.M20();
		M30() += other.M30();
		M10() += other.M10();
		M11() += other.M11();
		M21() += other.M21();
		M31() += other.M31();
		M02() += other.M02();
		M12() += other.M12();
		M22() += other.M22();
		M32() += other.M32();
		M03() += other.M03();
		M13() += other.M13();
		M23() += other.M23();
		M33() += other.M33();

		return *this;
	}

	template<Arithmetic T>
	Matrix4x4<T>& Matrix4x4<T>::operator -=(const Matrix4x4& other) noexcept
	{
		M00() -= other.M00();
		M10() -= other.M10();
		M20() -= other.M20();
		M30() -= other.M30();
		M10() -= other.M10();
		M11() -= other.M11();
		M21() -= other.M21();
		M31() -= other.M31();
		M02() -= other.M02();
		M12() -= other.M12();
		M22() -= other.M22();
		M32() -= other.M32();
		M03() -= other.M03();
		M13() -= other.M13();
		M23() -= other.M23();
		M33() -= other.M33();

		return *this;
	}

	template<Arithmetic T>
	Matrix4x4<T>& Matrix4x4<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		M00() *= multiplier;
		M10() *= multiplier;
		M20() *= multiplier;
		M30() *= multiplier;
		M10() *= multiplier;
		M11() *= multiplier;
		M21() *= multiplier;
		M31() *= multiplier;
		M02() *= multiplier;
		M12() *= multiplier;
		M22() *= multiplier;
		M32() *= multiplier;
		M03() *= multiplier;
		M13() *= multiplier;
		M23() *= multiplier;
		M33() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Matrix4x4<T>& Matrix4x4<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() * multiplier);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() * multiplier);
		M20() = RoundToIntegralIfPossible<ComputationalType, T>(M20() * multiplier);
		M30() = RoundToIntegralIfPossible<ComputationalType, T>(M30() * multiplier);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() * multiplier);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() * multiplier);
		M21() = RoundToIntegralIfPossible<ComputationalType, T>(M21() * multiplier);
		M31() = RoundToIntegralIfPossible<ComputationalType, T>(M31() * multiplier);
		M02() = RoundToIntegralIfPossible<ComputationalType, T>(M02() * multiplier);
		M12() = RoundToIntegralIfPossible<ComputationalType, T>(M12() * multiplier);
		M22() = RoundToIntegralIfPossible<ComputationalType, T>(M22() * multiplier);
		M32() = RoundToIntegralIfPossible<ComputationalType, T>(M32() * multiplier);
		M03() = RoundToIntegralIfPossible<ComputationalType, T>(M03() * multiplier);
		M13() = RoundToIntegralIfPossible<ComputationalType, T>(M13() * multiplier);
		M23() = RoundToIntegralIfPossible<ComputationalType, T>(M23() * multiplier);
		M33() = RoundToIntegralIfPossible<ComputationalType, T>(M33() * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Matrix4x4<T>& Matrix4x4<T>::operator *=(const Matrix4x4& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	Matrix4x4<T>& Matrix4x4<T>::operator /=(const ComputationalType divisor) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() / divisor);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() / divisor);
		M20() = RoundToIntegralIfPossible<ComputationalType, T>(M20() / divisor);
		M30() = RoundToIntegralIfPossible<ComputationalType, T>(M30() / divisor);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() / divisor);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() / divisor);
		M21() = RoundToIntegralIfPossible<ComputationalType, T>(M21() / divisor);
		M31() = RoundToIntegralIfPossible<ComputationalType, T>(M31() / divisor);
		M02() = RoundToIntegralIfPossible<ComputationalType, T>(M02() / divisor);
		M12() = RoundToIntegralIfPossible<ComputationalType, T>(M12() / divisor);
		M22() = RoundToIntegralIfPossible<ComputationalType, T>(M22() / divisor);
		M32() = RoundToIntegralIfPossible<ComputationalType, T>(M32() / divisor);
		M03() = RoundToIntegralIfPossible<ComputationalType, T>(M03() / divisor);
		M13() = RoundToIntegralIfPossible<ComputationalType, T>(M13() / divisor);
		M23() = RoundToIntegralIfPossible<ComputationalType, T>(M23() / divisor);
		M33() = RoundToIntegralIfPossible<ComputationalType, T>(M33() / divisor);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Matrix4x4<T>::operator ==(const Matrix4x4& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> Scale(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		const T m00 = left.M00() * right.M00();
		const T m10 = left.M10() * right.M10();
		const T m20 = left.M20() * right.M20();
		const T m30 = left.M30() * right.M30();
		const T m01 = left.M01() * right.M01();
		const T m11 = left.M11() * right.M11();
		const T m21 = left.M21() * right.M21();
		const T m31 = left.M31() * right.M31();
		const T m02 = left.M02() * right.M02();
		const T m12 = left.M12() * right.M12();
		const T m22 = left.M22() * right.M22();
		const T m32 = left.M32() * right.M32();
		const T m03 = left.M03() * right.M03();
		const T m13 = left.M13() * right.M13();
		const T m23 = left.M23() * right.M23();
		const T m33 = left.M33() * right.M33();

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix4x4<T>& left, const Matrix4x4<T>& right, const typename Matrix4x4<T>::ComputationalType tolerance) noexcept
	{
		const Matrix4x4<T> diff = left - right;
		const T kindOfMagnitudeSquared = diff.M00() * diff.M00() + diff.M10() * diff.M10() + diff.M20() * diff.M20() + diff.M30() * diff.M30() + 
			diff.M01() * diff.M01() + diff.M11() * diff.M11() + diff.M21() * diff.M21() + diff.M31() * diff.M31() + 
			diff.M02() * diff.M02() + diff.M12() * diff.M12() + diff.M22() * diff.M22() + diff.M32() * diff.M32() +
			diff.M03() * diff.M03() + diff.M13() * diff.M13() + diff.M23() * diff.M23() + diff.M33() * diff.M33();

		return kindOfMagnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator +(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		const T m00 = left.M00() + right.M00();
		const T m10 = left.M10() + right.M10();
		const T m20 = left.M20() + right.M20();
		const T m30 = left.M30() + right.M30();
		const T m01 = left.M01() + right.M01();
		const T m11 = left.M11() + right.M11();
		const T m21 = left.M21() + right.M21();
		const T m31 = left.M31() + right.M31();
		const T m02 = left.M02() + right.M02();
		const T m12 = left.M12() + right.M12();
		const T m22 = left.M22() + right.M22();
		const T m32 = left.M32() + right.M32();
		const T m03 = left.M03() + right.M03();
		const T m13 = left.M13() + right.M13();
		const T m23 = left.M23() + right.M23();
		const T m33 = left.M33() + right.M33();

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator -(const Matrix4x4<T>& matrix) noexcept
	{
		return Matrix4x4(-matrix.M00(), -matrix.M10(), -matrix.M20(), -matrix.M30(), -matrix.M01(), -matrix.M11(), -matrix.M21(), -matrix.M31(), 
			-matrix.M02(), -matrix.M12(), -matrix.M22(), -matrix.M32(), -matrix.M03(), -matrix.M13(), -matrix.M23(), -matrix.M33());
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator -(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		const T m00 = left.M00() - right.M00();
		const T m10 = left.M10() - right.M10();
		const T m20 = left.M20() - right.M20();
		const T m30 = left.M30() - right.M30();
		const T m01 = left.M01() - right.M01();
		const T m11 = left.M11() - right.M11();
		const T m21 = left.M21() - right.M21();
		const T m31 = left.M31() - right.M31();
		const T m02 = left.M02() - right.M02();
		const T m12 = left.M12() - right.M12();
		const T m22 = left.M22() - right.M22();
		const T m32 = left.M32() - right.M32();
		const T m03 = left.M03() - right.M03();
		const T m13 = left.M13() - right.M13();
		const T m23 = left.M23() - right.M23();
		const T m33 = left.M33() - right.M33();

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<std::integral T>
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		const T m00 = matrix.M00() * multiplier;
		const T m10 = matrix.M10() * multiplier;
		const T m20 = matrix.M20() * multiplier;
		const T m30 = matrix.M30() * multiplier;
		const T m01 = matrix.M01() * multiplier;
		const T m11 = matrix.M11() * multiplier;
		const T m21 = matrix.M21() * multiplier;
		const T m31 = matrix.M31() * multiplier;
		const T m02 = matrix.M02() * multiplier;
		const T m12 = matrix.M12() * multiplier;
		const T m22 = matrix.M22() * multiplier;
		const T m32 = matrix.M32() * multiplier;
		const T m03 = matrix.M03() * multiplier;
		const T m13 = matrix.M13() * multiplier;
		const T m23 = matrix.M23() * multiplier;
		const T m33 = matrix.M33() * multiplier;

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& matrix, const typename Matrix4x4<T>::ComputationalType multiplier) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M00() * multiplier);
		const T m10 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M10() * multiplier);
		const T m20 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M20() * multiplier);
		const T m30 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M30() * multiplier);
		const T m01 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M01() * multiplier);
		const T m11 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M11() * multiplier);
		const T m21 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M21() * multiplier);
		const T m31 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M31() * multiplier);
		const T m02 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M02() * multiplier);
		const T m12 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M12() * multiplier);
		const T m22 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M22() * multiplier);
		const T m32 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M32() * multiplier);
		const T m03 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M03() * multiplier);
		const T m13 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M13() * multiplier);
		const T m23 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M23() * multiplier);
		const T m33 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M33() * multiplier);

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<std::integral T>
	constexpr Matrix4x4<T> operator *(const T multiplier, const Matrix4x4<T>& matrix) noexcept requires(std::is_integral_v<T>)
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator *(const typename Matrix4x4<T>::ComputationalType multiplier, const Matrix4x4<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator *(const Matrix4x4<T>& left, const Matrix4x4<T>& right) noexcept
	{
		const T m00 = left.M00() * right.M00() + left.M01() * right.M10() + left.M02() * right.M20() + left.M03() * right.M30();
		const T m10 = left.M10() * right.M00() + left.M11() * right.M10() + left.M12() * right.M20() + left.M13() * right.M30();
		const T m20 = left.M20() * right.M00() + left.M21() * right.M10() + left.M22() * right.M20() + left.M23() * right.M30();
		const T m30 = left.M30() * right.M00() + left.M31() * right.M10() + left.M32() * right.M20() + left.M33() * right.M30();
		const T m01 = left.M00() * right.M01() + left.M01() + right.M11() + left.M02() * right.M21() + left.M03() * right.M31();
		const T m11 = left.M10() * right.M01() + left.M11() * right.M11() + left.M12() * right.M21() + left.M13() * right.M31();
		const T m21 = left.M20() * right.M01() + left.M21() * right.M11() + left.M22() * right.M21() + left.M23() * right.M31();
		const T m31 = left.M30() * right.M01() + left.M31() * right.M11() + left.M32() * right.M21() + left.M33() * right.M31();
		const T m02 = left.M00() * right.M02() + left.M01() * right.M12() + left.M02() * right.M22() + left.M03() * right.M32();
		const T m12 = left.M10() * right.M02() + left.M11() * right.M12() + left.M12() * right.M22() + left.M13() * right.M32();
		const T m22 = left.M20() * right.M02() + left.M21() * right.M12() + left.M22() * right.M22() + left.M23() * right.M32();
		const T m32 = left.M30() * right.M02() + left.M31() * right.M12() + left.M32() * right.M22() + left.M33() * right.M32();
		const T m03 = left.M00() * right.M03() + left.M01() * right.M13() + left.M02() * right.M23() + left.M03() * right.M33();
		const T m13 = left.M10() * right.M03() + left.M11() * right.M13() + left.M12() * right.M23() + left.M13() * right.M33();
		const T m23 = left.M20() * right.M03() + left.M21() * right.M13() + left.M22() * right.M23() + left.M23() * right.M33();
		const T m33 = left.M30() * right.M03() + left.M31() * right.M13() + left.M32() * right.M23() + left.M33() * right.M33();

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const Matrix4x4<T>& matrix, const Vector4<T>& vector) noexcept
	{
		const T x = matrix.M00() * vector.X() + matrix.M01() * vector.Y() + matrix.M02() * vector.Z() + matrix.M03() * vector.W();
		const T y = matrix.M10() * vector.X() + matrix.M11() * vector.Y() + matrix.M12() * vector.Z() + matrix.M13() * vector.W();
		const T z = matrix.M20() * vector.X() + matrix.M21() * vector.Y() + matrix.M22() * vector.Z() + matrix.M23() * vector.W();
		const T w = matrix.M30() * vector.X() + matrix.M31() * vector.Y() + matrix.M32() * vector.Z() + matrix.M33() * vector.W();

		return Vector4<T>(x, y, z, w);
	}

	template<Arithmetic T>
	constexpr Matrix4x4<T> operator /(const Matrix4x4<T>& matrix, const typename Matrix4x4<T>::ComputationalType divisor) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M00() / divisor);
		const T m10 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M10() / divisor);
		const T m20 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M20() / divisor);
		const T m30 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M30() / divisor);
		const T m01 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M01() / divisor);
		const T m11 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M11() / divisor);
		const T m21 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M21() / divisor);
		const T m31 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M31() / divisor);
		const T m02 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M02() / divisor);
		const T m12 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M12() / divisor);
		const T m22 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M22() / divisor);
		const T m32 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M32() / divisor);
		const T m03 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M03() / divisor);
		const T m13 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M13() / divisor);
		const T m23 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M23() / divisor);
		const T m33 = RoundToIntegralIfPossible<Matrix4x4<T>::ComputationalType, T>(matrix.M33() / divisor);

		return Matrix4x4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix4x4<T>& matrix)
	{
		return stream << matrix.ToString();
	}

	template<Arithmetic T>
	const Matrix4x4<T> Matrix4x4<T>::Identity = Matrix3x3(T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0}, T{1});
	template<Arithmetic T>
	const Matrix4x4<T> Matrix4x4<T>::Zero = Matrix3x3(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0});
}
