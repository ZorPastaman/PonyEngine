/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix2x2;

import <array>;
import <cmath>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import :Common;
import :Vector2;

export namespace PonyEngine::Math
{
	/// @brief Matrix2x2 implementation.
	/// @tparam T Component type.
	template<Arithmetic T>
	class Matrix2x2 final
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
			operator Vector2<T>() const noexcept;

			/// @brief Gets a component in a row by the @p columnIndex.
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

			friend Matrix2x2;
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
			constexpr operator Vector2<T>() const noexcept;

			/// @brief Gets a component in a row by the @p columnIndex.
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

			friend Matrix2x2;
		};

		using ValueType = T; ///< Component type.
		using ComputationalType = ComputationalFor<T>; ///< Floating point type used in functions that require a floating point type.

		/// @brief Creates a matrix and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2() noexcept;
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
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2(const Matrix2x2& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix2x2(Matrix2x2&& other) noexcept = default;

		constexpr ~Matrix2x2() noexcept = default;

		/// @brief Creates a Matrix2x2(1, 0, 0, 1).
		/// @return Identity matrix.
		///	@remark For non-constexpr execution use @p Matrix2x2::Identity variable.
		[[nodiscard("Pure function")]]
		static consteval Matrix2x2 CreateIdentity();
		/// @brief Creates a Matrix2x2(0, 0, 0, 0).
		/// @return Zero matrix.
		///	@remark For non-constexpr execution use @p Matrix2x2::Zero variable.
		[[nodiscard("Pure function")]]
		static consteval Matrix2x2 CreateZero();

		/// @brief Creates a rotation matrix for a @p Vector2.
		/// @param angle Rotation angle in radians.
		/// @return Rotation matrix.
		[[nodiscard("Pure function")]]
		static Matrix2x2 CreateRotation(T angle) noexcept requires(std::is_floating_point_v<T>);
		/// @brief Creates a rotation matrix for a @p Vector2.
		/// @param angle Rotation angle in degrees.
		/// @return Rotation matrix.
		[[nodiscard("Pure function")]]
		static Matrix2x2 CreateRotationDegrees(T angle) noexcept requires(std::is_floating_point_v<T>);

		/// @brief Creates a rotation matrix representing a rotation  from the vector @p fromDirection to the vector @p toDirection.
		/// @param fromDirection From direction. Must be normalized.
		/// @param toDirection To direction. Must be normalized.
		/// @return Rotation matrix.
		[[nodiscard("Pure function")]]
		static Matrix2x2 CreateByDirection(const Vector2<T>& fromDirection, const Vector2<T>& toDirection) noexcept requires(std::is_floating_point_v<T>);

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
		/// @brief Gets a data pointer - an array of 4 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 4 elements. The data is column-major.
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
		constexpr Matrix2x2 Adjugate() const noexcept;

		/// @brief Computes a transpose of the matrix.
		/// @return Transpose.
		[[nodiscard("Pure function")]]
		constexpr Matrix2x2 Transposed() const noexcept;
		/// @brief Transposes the matrix.
		void Transpose() noexcept;

		/// @brief Computes an inverse of the matrix.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix2x2 Inversed() const noexcept;
		/// @brief Inverses the matrix.
		void Inverse() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Assigns arguments to the matrix components.
		/// @param m00 Component 00.
		/// @param m10 Component 10.
		/// @param m01 Component 01.
		/// @param m11 Component 11.
		void Set(T m00, T m10, T m01, T m11) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale Matrix to multiply by.
		void Scale(const Matrix2x2& scale) noexcept;

		/// @brief Gets a row.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> GetRow(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row.
		/// @param rowIndex Row index.
		/// @param value Row components.
		void SetRow(std::size_t rowIndex, const Vector2<T>& value) noexcept;

		/// @brief Gets a column.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> GetColumn(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column.
		/// @param columnIndex Column index.
		/// @param value Column components.
		void SetColumn(std::size_t columnIndex, const Vector2<T>& value) noexcept;

		/// @brief Gets a diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> GetDiagonal() const noexcept;
		/// @brief Sets a diagonal.
		/// @param value Diagonal components.
		void SetDiagonal(const Vector2<T>& value) noexcept;

		/// @brief Gets a counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector2<T> GetCounterDiagonal() const noexcept;
		/// @brief Sets a counter-diagonal.
		/// @param value Counter-diagonal components.
		void SetCounterDiagonal(const Vector2<T>& value) noexcept;

		/// @brief Creates a string representing a state of the matrix.
		///        The format is '(m00, m01)(m10, m11)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this: matrix[1][1]; or vector = matrix[1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		Row operator [](std::size_t rowIndex) noexcept;
		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this: matrix[1][1]; or vector = matrix[1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr ConstRow operator [](std::size_t rowIndex) const noexcept;

		Matrix2x2& operator =(const Matrix2x2& other) noexcept = default;
		Matrix2x2& operator =(Matrix2x2&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Matrix to add.
		/// @return @a This.
		Matrix2x2& operator +=(const Matrix2x2& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Matrix to subtract.
		/// @return @a This.
		Matrix2x2& operator -=(const Matrix2x2& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		Matrix2x2& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		Matrix2x2& operator *=(ComputationalType multiplier) noexcept;
		/// @brief Multiplies @a this by the @p other.
		/// @param other Matrix to multiply by.
		/// @return @a This.
		Matrix2x2& operator *=(const Matrix2x2& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		Matrix2x2& operator /=(ComputationalType divisor) noexcept;

		/// @brief Checks if two matrices are equal.
		/// @param other The other matrix.
		/// @return @a True if they are equal; @a false otherwise.
		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix2x2& other) const noexcept;

		static const Matrix2x2 Identity; ///< Matrix2x2(1, 0, 0, 1).
		static const Matrix2x2 Zero; ///< Matrix2x2(0, 0, 0, 0).

		static constexpr std::size_t RowCount = 2; ///< Row count. For any Matrix2x2 it's always 2.
		static constexpr std::size_t ColumnCount = 2; ///< Column count. For any Matrix2x2 it's always 2.
		static constexpr std::size_t ComponentCount = RowCount * ColumnCount; ///< Component count. For any Matrix2x2 it's always 4.

	private:
		std::array<T, ComponentCount> m_components; ///< Component array in order m00, m10, m01, m11.
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept;

	/// @brief Checks if two matrices are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, typename Matrix2x2<T>::ComputationalType tolerance = typename Matrix2x2<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two matrices.
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
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, T multiplier) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, typename Matrix2x2<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(T multiplier, const Matrix2x2<T>& matrix) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix2x2<T> operator *(typename Matrix2x2<T>::ComputationalType multiplier, const Matrix2x2<T>& matrix) noexcept;
	/// @brief Multiplies two matrices.
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
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, typename Matrix2x2<T>::ComputationalType divisor) noexcept;

	/// @brief Puts matrix.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix);
}

namespace PonyEngine::Math
{
	template<Arithmetic T>
	Matrix2x2<T>::Row::Row(T* const row) noexcept :
		m_row{row}
	{
	}

	template<Arithmetic T>
	Matrix2x2<T>::Row::operator Vector2<T>() const noexcept
	{
		const T x = m_row[0];
		const T y = m_row[2];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	T& Matrix2x2<T>::Row::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_row[columnIndex * std::size_t{2}];
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::ConstRow::ConstRow(const T* const row) noexcept :
		m_row{row}
	{
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::ConstRow::operator Vector2<T>() const noexcept
	{
		const T x = m_row[0];
		const T y = m_row[2];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::ConstRow::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_row[columnIndex * std::size_t{2}];
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::Matrix2x2() noexcept :
		Matrix2x2(T{}, T{}, T{}, T{})
	{
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::Matrix2x2(const T m00, const T m10, const T m01, const T m11) noexcept :
		m_components{m00, m10, m01, m11}
	{
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T>::Matrix2x2(const Vector2<T>& column0, const Vector2<T>& column1) noexcept :
		Matrix2x2(column0.X(), column0.Y(), column1.X(), column1.Y())
	{
	}

	template<Arithmetic T>
	consteval Matrix2x2<T> Matrix2x2<T>::CreateIdentity()
	{
		return Matrix2x2(T{1}, T{0}, T{0}, T{1});
	}

	template<Arithmetic T>
	consteval Matrix2x2<T> Matrix2x2<T>::CreateZero()
	{
		return Matrix2x2(T{0}, T{0}, T{0}, T{0});
	}

	template<Arithmetic T>
	Matrix2x2<T> Matrix2x2<T>::CreateRotation(const T angle) noexcept requires(std::is_floating_point_v<T>)
	{
		const T angleSin = std::sin(angle);
		const T angleCos = std::cos(angle);

		return Matrix2x2(angleCos, angleSin, -angleSin, angleCos);
	}

	template<Arithmetic T>
	Matrix2x2<T> Matrix2x2<T>::CreateRotationDegrees(const T angle) noexcept requires(std::is_floating_point_v<T>)
	{
		return CreateRotation(angle * DegToRad<T>);
	}

	template<Arithmetic T>
	Matrix2x2<T> Matrix2x2<T>::CreateByDirection(const Vector2<T>& fromDirection, const Vector2<T>& toDirection) noexcept requires(std::is_floating_point_v<T>)
	{
		return CreateRotation(AngleSigned(fromDirection, toDirection));
	}

	template<Arithmetic T>
	T& Matrix2x2<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	T& Matrix2x2<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	T& Matrix2x2<T>::M01() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M01() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	T& Matrix2x2<T>::M11() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr const T& Matrix2x2<T>::M11() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	T* Matrix2x2<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr const T* Matrix2x2<T>::Data() const noexcept
	{
		return m_components.data();
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
	constexpr Matrix2x2<T> Matrix2x2<T>::Transposed() const noexcept
	{
		return Matrix2x2(M00(), M01(), M10(), M11());
	}

	template<Arithmetic T>
	void Matrix2x2<T>::Transpose() noexcept
	{
		*this = Transposed();
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Matrix2x2<T>::Inversed() const noexcept
	{
		return Adjugate() * (ComputationalType{1} / Determinant());
	}

	template<Arithmetic T>
	void Matrix2x2<T>::Inverse() noexcept
	{
		*this = Inversed();
	}

	template<Arithmetic T>
	bool Matrix2x2<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(M00()) && std::isfinite(M10()) && std::isfinite(M01()) && std::isfinite(M11());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	void Matrix2x2<T>::Set(const T m00, const T m10, const T m01, const T m11) noexcept
	{
		M00() = m00;
		M10() = m10;
		M01() = m01;
		M11() = m11;
	}

	template<Arithmetic T>
	void Matrix2x2<T>::Scale(const Matrix2x2<T>& scale) noexcept
	{
		M00() *= scale.M00();
		M10() *= scale.M10();
		M01() *= scale.M01();
		M11() *= scale.M11();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const T x = m_components[rowIndex];
		const T y = m_components[rowIndex + 2];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetRow(const std::size_t rowIndex, const Vector2<T>& value) noexcept
	{
		m_components[rowIndex] = value.X();
		m_components[rowIndex + 2] = value.Y();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::GetColumn(const std::size_t columnIndex) const noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{2};

		const T x = m_components[begin];
		const T y = m_components[begin + 1];

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetColumn(const std::size_t columnIndex, const Vector2<T>& value) noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{2};

		m_components[begin] = value.X();
		m_components[begin + 1] = value.Y();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::GetDiagonal() const noexcept
	{
		return Vector2<T>(M00(), M11());
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetDiagonal(const Vector2<T>& value) noexcept
	{
		M00() = value.X();
		M11() = value.Y();
	}

	template<Arithmetic T>
	constexpr Vector2<T> Matrix2x2<T>::GetCounterDiagonal() const noexcept
	{
		return Vector2<T>(M01(), M10());
	}

	template<Arithmetic T>
	void Matrix2x2<T>::SetCounterDiagonal(const Vector2<T>& value) noexcept
	{
		M01() = value.X();
		M10() = value.Y();
	}

	template<Arithmetic T>
	std::string Matrix2x2<T>::ToString() const
	{
		return std::format("({}, {})({}, {})", M00(), M01(), M10(), M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> Scale(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.M00() * right.M00(), left.M10() * right.M10(), left.M01() * right.M01(), left.M11() * right.M11());
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix2x2<T>& left, const Matrix2x2<T>& right, const typename Matrix2x2<T>::ComputationalType tolerance) noexcept
	{
		const Matrix2x2<T> diff = left - right;
		const T kindOfMagnitudeSquared = diff.M00() * diff.M00() + diff.M10() * diff.M10() + diff.M01() * diff.M01() + diff.M11() * diff.M11();

		return kindOfMagnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	typename Matrix2x2<T>::Row Matrix2x2<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row(Data() + rowIndex);
	}

	template<Arithmetic T>
	constexpr typename Matrix2x2<T>::ConstRow Matrix2x2<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return ConstRow(Data() + rowIndex);
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator +=(const Matrix2x2& other) noexcept
	{
		M00() += other.M00();
		M10() += other.M10();
		M01() += other.M01();
		M11() += other.M11();

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator -=(const Matrix2x2& other) noexcept
	{
		M00() -= other.M00();
		M10() -= other.M10();
		M01() -= other.M01();
		M11() -= other.M11();

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		M00() *= multiplier;
		M10() *= multiplier;
		M01() *= multiplier;
		M11() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() * multiplier);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() * multiplier);
		M01() = RoundToIntegralIfPossible<ComputationalType, T>(M01() * multiplier);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() * multiplier);

		return *this;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator *=(const Matrix2x2& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	Matrix2x2<T>& Matrix2x2<T>::operator /=(const ComputationalType divisor) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() / divisor);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() / divisor);
		M01() = RoundToIntegralIfPossible<ComputationalType, T>(M01() / divisor);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() / divisor);

		return *this;
	}

	template <Arithmetic T>
	constexpr bool Matrix2x2<T>::operator ==(const Matrix2x2& other) const noexcept
	{
		return m_components == other.m_components;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator +(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.M00() + right.M00(), left.M10() + right.M10(), left.M01() + right.M01(), left.M11() + right.M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& matrix) noexcept
	{
		return Matrix2x2<T>(-matrix.M00(), -matrix.M10(), -matrix.M01(), -matrix.M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator -(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		return Matrix2x2<T>(left.M00() - right.M00(), left.M10() - right.M10(), left.M01() - right.M01(), left.M11() - right.M11());
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		return Matrix2x2<T>(matrix.M00() * multiplier, matrix.M10() * multiplier, matrix.M01() * multiplier, matrix.M11() * multiplier);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType multiplier) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M00() * multiplier);
		const T m10 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M10() * multiplier);
		const T m01 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M01() * multiplier);
		const T m11 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M11() * multiplier);

		return Matrix2x2<T>(m00, m10, m01, m11);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const T multiplier, const Matrix2x2<T>& matrix) noexcept requires(std::is_integral_v<T>)
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const typename Matrix2x2<T>::ComputationalType multiplier, const Matrix2x2<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator *(const Matrix2x2<T>& left, const Matrix2x2<T>& right) noexcept
	{
		const T m00 = left.M00() * right.M00() + left.M01() * right.M10();
		const T m10 = left.M10() * right.M00() + left.M11() * right.M10();
		const T m01 = left.M00() * right.M01() + left.M01() * right.M11();
		const T m11 = left.M10() * right.M01() + left.M11() * right.M11();

		return Matrix2x2<T>(m00, m10, m01, m11);
	}

	template<Arithmetic T>
	constexpr Vector2<T> operator *(const Matrix2x2<T>& matrix, const Vector2<T>& vector) noexcept
	{
		const T x = matrix.M00() * vector.X() + matrix.M01() * vector.Y();
		const T y = matrix.M10() * vector.X() + matrix.M11() * vector.Y();

		return Vector2<T>(x, y);
	}

	template<Arithmetic T>
	constexpr Matrix2x2<T> operator /(const Matrix2x2<T>& matrix, const typename Matrix2x2<T>::ComputationalType divisor) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M00() / divisor);
		const T m10 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M10() / divisor);
		const T m01 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M01() / divisor);
		const T m11 = RoundToIntegralIfPossible<Matrix2x2<T>::ComputationalType, T>(matrix.M11() / divisor);

		return Matrix2x2<T>(m00, m10, m01, m11);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix2x2<T>& matrix)
	{
		return stream << matrix.ToString();
	}

	template<Arithmetic T>
	const Matrix2x2<T> Matrix2x2<T>::Identity = Matrix2x2(T{1}, T{0}, T{0}, T{1});
	template<Arithmetic T>
	const Matrix2x2<T> Matrix2x2<T>::Zero = Matrix2x2(T{0}, T{0}, T{0}, T{0});
}
