/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix3x3;

import <algorithm>;
import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <ranges>;
import <string>;
import <type_traits>;

import :ArrayArithmetics;
import :Common;
import :Matrix2x2;
import :Vector3;

export namespace PonyEngine::Math
{
	/// @brief Matrix3x3 implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Matrix3x3 final
	{
	public:
		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		static constexpr std::size_t Dimension = 3; ///< Row and column count. For any Matrix3x3 it's always 3.
		static constexpr std::size_t ComponentCount = Dimension * Dimension; ///< Component count. For any Matrix3x3 it's always 9.

		/// @brief Row access.
		/// @tparam IsConstant Is the underlying value const?
		template<bool IsConstant>
		class Row final
		{
		public:
			using RowValueType = std::conditional_t<IsConstant, const T, T>; ///< @p const @p T or @p T depending on @p IsConstant.

			Row(const Row&) = delete;
			Row(Row&&) = delete;

			constexpr ~Row() noexcept = default;

			/// @brief Converts a row to a vector.
			[[nodiscard("Pure operator")]]
			constexpr operator Vector3<T>() const noexcept;

			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index.
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr RowValueType& operator [](std::size_t columnIndex) const noexcept;

			Row& operator =(const Row&) = delete;
			Row& operator =(Row&&) = delete;

			Row& operator =(const Vector3<T>& row) noexcept requires(!IsConstant);

		private:
			/// @brief Creates a row access.
			/// @param row First element in a row.
			[[nodiscard("Pure constructor")]]
			explicit constexpr Row(RowValueType* row) noexcept;

			RowValueType* const m_row; ///< Row pointer.

			friend Matrix3x3;
		};

		/// @brief Creates a matrix and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3() noexcept = default;
		/// @brief Creates a matrix and assigns its components from the arguments.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m20 Component 20.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		/// @param m21 Component 21.
		/// @param m02 Component 02.
		/// @param m12 Component 12.
		/// @param m22 Component 22.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) noexcept;
		/// @brief Creates a matrix and assigns its components from column vectors.
		/// @param column0 Column 0.
		/// @param column1 Column 1.
		/// @param column2 Column 2.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix3x3(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(const Matrix3x3& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(Matrix3x3&& other) noexcept = default;

		constexpr ~Matrix3x3() noexcept = default;

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
		/// @brief Gets a data pointer - a contiguous sequence of 9 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		constexpr T* Data() noexcept;
		/// @brief Gets a data pointer - a contiguous sequence of 9 elements. The data is column-major.
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
		constexpr Matrix3x3 Adjugate() const noexcept;

		/// @brief Computes a transpose of the matrix.
		/// @return Transpose.
		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Transpose() const noexcept;

		/// @brief Computes an inverse of the matrix.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Inverse() const noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to the matrix components.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m20 Component 20.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		/// @param m21 Component 21.
		/// @param m02 Component 02.
		/// @param m12 Component 12.
		/// @param m22 Component 22.
		void Set(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) noexcept;
		void Set(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept;
		void Set(const T* components) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Matrix to multiply by.
		void Scale(const Matrix3x3& scale) noexcept;

		/// @brief Gets a row.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector3<T> GetRow(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row.
		/// @param rowIndex Row index.
		/// @param value Row components.
		void SetRow(std::size_t rowIndex, const Vector3<T>& value) noexcept;

		/// @brief Gets a column.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector3<T> GetColumn(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column.
		/// @param columnIndex Column index.
		/// @param value Column components.
		void SetColumn(std::size_t columnIndex, const Vector3<T>& value) noexcept;

		/// @brief Gets a diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector3<T> GetDiagonal() const noexcept;
		/// @brief Sets a diagonal.
		/// @param value Diagonal components.
		void SetDiagonal(const Vector3<T>& value) noexcept;

		/// @brief Gets a counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector3<T> GetCounterDiagonal() const noexcept;
		/// @brief Sets a counter-diagonal.
		/// @param value Counter-diagonal components.
		void SetCounterDiagonal(const Vector3<T>& value) noexcept;

		/// @brief Creates a string representing a state of the matrix.
		///        The format is '(m00, m01, m02)(m10, m11, m12)(m20, m21, m22)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr Row<false> operator [](std::size_t rowIndex) noexcept;
		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr Row<true> operator [](std::size_t rowIndex) const noexcept;

		Matrix3x3& operator =(const Matrix3x3& other) noexcept = default;
		Matrix3x3& operator =(Matrix3x3&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Matrix to add.
		/// @return @a This.
		Matrix3x3& operator +=(const Matrix3x3& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Matrix to subtract.
		/// @return @a This.
		Matrix3x3& operator -=(const Matrix3x3& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		Matrix3x3& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		Matrix3x3& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other.
		/// @param other Matrix to multiply.
		/// @return @a This.
		Matrix3x3& operator *=(const Matrix3x3& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		Matrix3x3& operator /=(ComputationalType divisor) noexcept;

		/// @brief Checks if two matrices are equal.
		/// @param other The other matrix.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix3x3& other) const noexcept;

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order m00, m10, m20, m01, m11, m21, m02, m12, m22.
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	/// @brief Checks if two matrices are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, typename Matrix3x3<T>::ComputationalType tolerance = typename Matrix3x3<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two matrices.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	/// @brief Negates the @p matrix.
	/// @tparam T Component type.
	/// @param matrix Matrix to negate.
	/// @return Negated matrix.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& matrix) noexcept;
	/// @brief Subtracts the @p right matrix from the @p left matrix.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, T multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::integral T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(T multiplier, const Matrix3x3<T>& matrix) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept;
	/// @brief Multiplies two matrices.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;
	/// @brief Multiplies the @p matrix by the @p vector.
	/// @tparam T Component type.
	/// @param matrix Matrix.
	/// @param vector Vector.
	/// @return Product vector.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept;

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType divisor) noexcept;

	/// @brief Puts matrix.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix3x3<T>& matrix);

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3Identity = Matrix3x3(T{1}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{1});
	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3Zero = Matrix3x3(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0});
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	template<bool IsConstant>
	constexpr Matrix3x3<T>::Row<IsConstant>::Row(RowValueType* const row) noexcept :
		m_row{row}
	{
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr Matrix3x3<T>::Row<IsConstant>::operator Vector3<T>() const noexcept
	{
		Vector3<T> row;
		AssignWithSourceStep(row.Data(), m_row, Dimension, Dimension);

		return row;
	}

	template<Arithmetic T>
	template<bool IsConstant>
	constexpr typename Matrix3x3<T>::template Row<IsConstant>::RowValueType& Matrix3x3<T>::Row<IsConstant>::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_row[columnIndex * Dimension];
	}

	template<Arithmetic T>
	template<bool IsConstant>
	typename Matrix3x3<T>::template Row<IsConstant>& Matrix3x3<T>::Row<IsConstant>::operator =(const Vector3<T>& row) noexcept requires (!IsConstant)
	{
		AssignWithDestinationStep(m_row, row.Data(), Dimension, Dimension);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T>::Matrix3x3(const T m00, const T m10, const T m20, const T m01, const T m11, const T m21, const T m02, const T m12, const T m22) noexcept :
		m_components{m00, m10, m20, m01, m11, m21, m02, m12, m22}
	{
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T>::Matrix3x3(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept :
		Matrix3x3(column0.X(), column0.Y(), column0.Z(), column1.X(), column1.Y(), column1.Z(), column2.X(), column2.Y(), column2.Z())
	{
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T>::Matrix3x3(const T* components) noexcept
	{
		std::ranges::copy(components, ComponentCount, m_components.data());
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M20() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M20() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M01() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M01() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M11() noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M11() const noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M21() noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M21() const noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M02() noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M02() const noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M12() noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M12() const noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	constexpr T& Matrix3x3<T>::M22() noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	constexpr const T& Matrix3x3<T>::M22() const noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	constexpr T* Matrix3x3<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Matrix3x3<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr T Matrix3x3<T>::Determinant() const noexcept
	{
		return M00() * (M11() * M22() - M12() * M21()) + 
			M01() * (M12() * M20() - M10() * M22()) + 
			M02() * (M10() * M21() - M11() * M20());
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Adjugate() const noexcept
	{
		Matrix3x3 adjugate;
		adjugate.M00() = Matrix2x2(M11(), M21(), M12(), M22()).Determinant();
		adjugate.M10() = -Matrix2x2(M10(), M20(), M12(), M22()).Determinant();
		adjugate.M20() = Matrix2x2(M10(), M20(), M11(), M21()).Determinant();
		adjugate.M01() = -Matrix2x2(M01(), M21(), M02(), M22()).Determinant();
		adjugate.M11() = Matrix2x2(M00(), M20(), M02(), M22()).Determinant();
		adjugate.M21() = -Matrix2x2(M00(), M20(), M01(), M21()).Determinant();
		adjugate.M02() = Matrix2x2(M01(), M11(), M02(), M12()).Determinant();
		adjugate.M12() = -Matrix2x2(M00(), M10(), M02(), M12()).Determinant();
		adjugate.M22() = Matrix2x2(M00(), M10(), M01(), M11()).Determinant();

		return adjugate;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Transpose() const noexcept
	{
		return Matrix3x3(M00(), M01(), M02(), M10(), M11(), M12(), M20(), M21(), M22());
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Inverse() const noexcept
	{
		return Adjugate() * (ComputationalType{1} / Determinant());
	}

	template<Arithmetic T>
	bool Matrix3x3<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return Math::IsFinite(Data(), ComponentCount);
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Matrix3x3<T>::Set(const T m00, const T m10, const T m20, const T m01, const T m11, const T m21, const T m02, const T m12, const T m22) noexcept
	{
		M00() = m00;
		M10() = m10;
		M20() = m20;
		M01() = m01;
		M11() = m11;
		M21() = m21;
		M02() = m02;
		M12() = m12;
		M22() = m22;
	}

	template<Arithmetic T>
	void Matrix3x3<T>::Set(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept
	{
		Set(column0.X(), column0.Y(), column0.Z(), column1.X(), column1.Y(), column1.Z(), column2.X(), column2.Y(), column2.Z());
	}

	template<Arithmetic T>
	void Matrix3x3<T>::Set(const T* const components) noexcept
	{
		std::ranges::copy(components, components + ComponentCount, m_components.data());
	}

	template<Arithmetic T>
	void Matrix3x3<T>::Scale(const Matrix3x3& scale) noexcept
	{
		Multiply(Data(), scale.Data(), ComponentCount);
	}

	template<Arithmetic T>
	constexpr Vector3<T> Matrix3x3<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		return (*this)[rowIndex];
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetRow(const std::size_t rowIndex, const Vector3<T>& value) noexcept
	{
		(*this)[rowIndex] = value;
	}

	template<Arithmetic T>
	constexpr Vector3<T> Matrix3x3<T>::GetColumn(const std::size_t columnIndex) const noexcept
	{
		const T* const columnBegin = m_components.data() + columnIndex * Dimension;

		return Vector3<T>(columnBegin);
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetColumn(const std::size_t columnIndex, const Vector3<T>& value) noexcept
	{
		T* const columnBegin = m_components.data() + columnIndex * Dimension;
		std::ranges::copy(value.Data(), value.Data() + Dimension, columnBegin);
	}

	template<Arithmetic T>
	constexpr Vector3<T> Matrix3x3<T>::GetDiagonal() const noexcept
	{
		return Vector3<T>(M00(), M11(), M22());
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetDiagonal(const Vector3<T>& value) noexcept
	{
		M00() = value.X();
		M11() = value.Y();
		M22() = value.Z();
	}

	template<Arithmetic T>
	constexpr Vector3<T> Matrix3x3<T>::GetCounterDiagonal() const noexcept
	{
		return Vector3<T>(M02(), M11(), M20());
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetCounterDiagonal(const Vector3<T>& value) noexcept
	{
		M02() = value.X();
		M11() = value.Y();
		M20() = value.Z();
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		Matrix3x3<T> scaled;
		Multiply(scaled.Data(), left.Data(), right.Data(), Matrix3x3<T>::ComponentCount);

		return scaled;
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, const typename Matrix3x3<T>::ComputationalType tolerance) noexcept
	{
		const Matrix3x3<T> diff = left - right;
		const T magnitudeSquared = Dot(diff.Data(), Matrix3x3<T>::ComponentCount);
		
		return magnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	std::string Matrix3x3<T>::ToString() const
	{
		return std::format("({}, {}, {})({}, {}, {})({}, {}, {})", M00(), M01(), M02(), M10(), M11(), M12(), M20(), M21(), M22());
	}

	template<Arithmetic T>
	constexpr typename Matrix3x3<T>::template Row<false> Matrix3x3<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row<false>(Data() + rowIndex);
	}

	template<Arithmetic T>
	constexpr typename Matrix3x3<T>::template Row<true> Matrix3x3<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return Row<true>(Data() + rowIndex);
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator +=(const Matrix3x3& other) noexcept
	{
		Add(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator -=(const Matrix3x3& other) noexcept
	{
		Subtract(Data(), other.Data(), ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		Multiply(Data(), multiplier, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const Matrix3x3& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		Divide(Data(), divisor, ComponentCount);

		return *this;
	}

	template<Arithmetic T>
	constexpr bool Matrix3x3<T>::operator ==(const Matrix3x3& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		Matrix3x3<T> sum;
		Add(sum.Data(), left.Data(), right.Data(), Matrix3x3<T>::ComponentCount);

		return sum;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& matrix) noexcept
	{
		Matrix3x3<T> negated;
		Negate(negated.Data(), matrix.Data(), Matrix3x3<T>::ComponentCount);

		return negated;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		Matrix3x3<T> difference;
		Subtract(difference.Data(), left.Data(), right.Data(), Matrix3x3<T>::ComponentCount);

		return difference;
	}

	template<std::integral T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, const T multiplier) noexcept
	{
		Matrix3x3<T> product;
		Multiply(product.Data(), matrix.Data(), multiplier, Matrix3x3<T>::ComponentCount);

		return product;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, const typename Matrix3x3<T>::ComputationalType multiplier) noexcept
	{
		Matrix3x3<T> product;
		Multiply(product.Data(), matrix.Data(), multiplier, Matrix3x3<T>::ComponentCount);

		return product;
	}

	template<std::integral T>
	constexpr Matrix3x3<T> operator *(const T multiplier, const Matrix3x3<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		Matrix3x3<T> product;
		product.M00() = left.M00() * right.M00() + left.M01() * right.M10() + left.M02() * right.M20();
		product.M10() = left.M10() * right.M00() + left.M11() * right.M10() + left.M12() * right.M20();
		product.M20() = left.M20() * right.M00() + left.M21() * right.M10() + left.M22() * right.M20();
		product.M01() = left.M00() * right.M01() + left.M01() * right.M11() + left.M02() * right.M21();
		product.M11() = left.M10() * right.M01() + left.M11() * right.M11() + left.M12() * right.M21();
		product.M21() = left.M20() * right.M01() + left.M21() * right.M11() + left.M22() * right.M21();
		product.M02() = left.M00() * right.M02() + left.M01() * right.M12() + left.M02() * right.M22();
		product.M12() = left.M10() * right.M02() + left.M11() * right.M12() + left.M12() * right.M22();
		product.M22() = left.M20() * right.M02() + left.M21() * right.M12() + left.M22() * right.M22();

		return product;
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept
	{
		Vector3<T> product;
		product.X() = matrix.M00() * vector.X() + matrix.M01() * vector.Y() + matrix.M02() * vector.Z();
		product.Y() = matrix.M10() * vector.X() + matrix.M11() * vector.Y() + matrix.M12() * vector.Z();
		product.Z() = matrix.M20() * vector.X() + matrix.M21() * vector.Y() + matrix.M22() * vector.Z();

		return product;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, const typename Matrix3x3<T>::ComputationalType divisor) noexcept
	{
		Matrix3x3<T> quotient;
		Divide(quotient.Data(), matrix.Data(), divisor, Matrix3x3<T>::ComponentCount);

		return quotient;
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix3x3<T>& matrix)
	{
		return stream << matrix.ToString();
	}
}
