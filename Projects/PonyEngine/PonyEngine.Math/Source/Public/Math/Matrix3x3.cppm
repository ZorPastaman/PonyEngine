/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix3x3;

import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;

import :Common;
import :Matrix2x2;
import :Vector3;

namespace PonyEngine::Math
{
	/// @brief Matrix3x3 implementation.
	/// @tparam T Component type.
	export template<Arithmetic T>
	class Matrix3x3 final
	{
	public:
		/// @brief Row access.
		class Row final
		{
		public:
			Row(const Row&) = delete;
			Row(Row&&) = delete;

			inline ~Row() noexcept = default;

			/// @brief Converts a row to a vector.
			[[nodiscard("Pure operator")]]
			inline operator Vector3<T>() const noexcept;

			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index.
			/// @return Component.
			[[nodiscard("Pure operator")]]
			inline T& operator [](std::size_t columnIndex) const noexcept;

			Row& operator =(const Row&) = delete;
			Row& operator =(Row&&) = delete;

		private:
			/// @brief Creates a row access.
			/// @param matrix Matrix.
			/// @param rowIndex Row index.
			[[nodiscard("Pure constructor")]]
			inline Row(Matrix3x3& matrix, std::size_t rowIndex) noexcept;

			Matrix3x3& m_matrix; /// @brief Matrix.
			const std::size_t m_rowIndex; /// @brief Row index.

			friend Matrix3x3;
		};

		/// @brief Const row access.
		class ConstRow final
		{
		public:
			ConstRow(const ConstRow&) = delete;
			ConstRow(ConstRow&&) = delete;

			constexpr inline ~ConstRow() noexcept = default;

			/// @brief Converts a row to a vector.
			[[nodiscard("Pure operator")]]
			constexpr inline operator Vector3<T>() const noexcept;

			/// @brief Gets a component in a row by a column index.
			/// @param columnIndex Column index.
			/// @return Component.
			[[nodiscard("Pure operator")]]
			constexpr inline const T& operator [](std::size_t columnIndex) const noexcept;

			ConstRow& operator =(const ConstRow&) = delete;
			ConstRow& operator =(ConstRow&&) = delete;

		private:
			/// @brief Creates a row access.
			/// @param matrix Matrix.
			/// @param rowIndex Row index.
			[[nodiscard("Pure constructor")]]
			constexpr inline ConstRow(const Matrix3x3& matrix, std::size_t rowIndex) noexcept;

			const Matrix3x3& m_matrix; /// @brief Matrix.
			const std::size_t m_rowIndex; /// @brief Row index.

			friend Matrix3x3;
		};

		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		/// @brief Creates a matrix and sets its components to zero.
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix3x3() noexcept;
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
		constexpr inline Matrix3x3(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) noexcept;
		/// @brief Creates a matrix and assigns its components from column vectors.
		/// @param column0 Column 0.
		/// @param column1 Column 1.
		/// @param column2 Column 2.
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix3x3(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix3x3(const Matrix3x3& other) noexcept = default;

		constexpr inline ~Matrix3x3() noexcept = default;

		/// @brief Gets component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		inline T& M00() noexcept;
		/// @brief Gets component 00.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M00() const noexcept;
		/// @brief Gets component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		inline T& M10() noexcept;
		/// @brief Gets component 10.
		/// @return Component 10.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M10() const noexcept;
		/// @brief Gets component 20.
		/// @return Component 20.
		[[nodiscard("Pure function")]]
		inline T& M20() noexcept;
		/// @brief Gets component 20.
		/// @return Component 20.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M20() const noexcept;
		/// @brief Gets component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		inline T& M01() noexcept;
		/// @brief Gets component 01.
		/// @return Component 01.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M01() const noexcept;
		/// @brief Gets component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		inline T& M11() noexcept;
		/// @brief Gets component 11.
		/// @return Component 11.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M11() const noexcept;
		/// @brief Gets component 21.
		/// @return Component 21.
		[[nodiscard("Pure function")]]
		inline T& M21() noexcept;
		/// @brief Gets component 21.
		/// @return Component 21.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M21() const noexcept;
		/// @brief Gets component 02.
		/// @return Component 02.
		[[nodiscard("Pure function")]]
		inline T& M02() noexcept;
		/// @brief Gets component 02.
		/// @return Component 02.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M02() const noexcept;
		/// @brief Gets component 12.
		/// @return Component 12.
		[[nodiscard("Pure function")]]
		inline T& M12() noexcept;
		/// @brief Gets component 12.
		/// @return Component 12.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M12() const noexcept;
		/// @brief Gets component 22.
		/// @return Component 00.
		[[nodiscard("Pure function")]]
		inline T& M22() noexcept;
		/// @brief Gets component 22.
		/// @return Component 22.
		[[nodiscard("Pure function")]]
		constexpr inline const T& M22() const noexcept;
		/// @brief Gets a data pointer - an array of 9 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		inline T* Data() noexcept;
		/// @brief Gets a data pointer - an array of 9 elements. The data is column-major.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		inline const T* Data() const noexcept;

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
		constexpr inline Matrix3x3 Transposed() const noexcept;
		/// @brief Transposes the matrix.
		inline void Transpose() noexcept;

		/// @brief Computes an inverse of the matrix.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Inversed() const noexcept;
		/// @brief Inverses the matrix.
		inline void Inverse() noexcept;

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
		inline void Set(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale @p Matrix to multiply by.
		void Scale(const Matrix3x3<T>& scale) noexcept;

		/// @brief Gets a row.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetRow(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row.
		/// @param rowIndex Row index.
		/// @param value Row components.
		void inline SetRow(std::size_t rowIndex, const Vector3<T>& value) noexcept;

		/// @brief Gets a column.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetColumn(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column.
		/// @param columnIndex Column index.
		/// @param value Column components.
		inline void SetColumn(std::size_t columnIndex, const Vector3<T>& value) noexcept;

		/// @brief Gets a diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetDiagonal() const noexcept;
		/// @brief Sets a diagonal.
		/// @param value Diagonal components.
		inline void SetDiagonal(const Vector3<T>& value) noexcept;

		/// @brief Gets a counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetCounterDiagonal() const noexcept;
		/// @brief Sets a counter-diagonal.
		/// @param value Counter-diagonal components.
		inline void SetCounterDiagonal(const Vector3<T>& value) noexcept;

		/// @brief Creates a string representing a state of a @p Matrix.
		///        The format is '(m00, m01, m02)(m10, m11, m12)(m20, m21, m22)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		inline std::string ToString() const;

		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		inline Row operator [](std::size_t rowIndex) noexcept;
		/// @brief Row access operator.
		/// @details Don't store it. Use the access like this matrix[1][1].
		/// @param rowIndex Row index.
		/// @return Row access.
		[[nodiscard("Pure operator")]]
		constexpr inline ConstRow operator [](std::size_t rowIndex) const noexcept;

		inline Matrix3x3& operator =(const Matrix3x3& other) noexcept = default;
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
		inline Matrix3x3& operator *=(const Matrix3x3& other) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		Matrix3x3& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix3x3& other) const noexcept = default;

		static const Matrix3x3 Identity; /// @brief Matrix2x2(1, 0, 0, 0, 1, 0, 0, 0, 1).
		static const Matrix3x3 Zero; /// @brief Matrix2x2(0, 0, 0, 0, 0, 0, 0, 0, 0).

		constexpr inline static const std::size_t RowCount = 3; /// @brief Row count. For any Matrix3x3 it's always 3.
		constexpr inline static const std::size_t ColumnCount = 3; /// @brief Column count. For any Matrix3x3 it's always 3.
		constexpr inline static const std::size_t ComponentCount = RowCount * ColumnCount; /// @brief Component count. For any Matrix3x3 it's always 9.

	private:
		std::array<T, ComponentCount> m_components; /// @brief Component array in order m00, m10, m20, m01, m11, m21, m02, m12, m22.
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Matrix.
	/// @param right Multiplier @p Matrix.
	/// @return Product @p Matrix.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	/// @brief Checks if two matrices are almost equal with a tolerance value.
	/// @tparam T Component type.
	/// @param left Left matrix.
	/// @param right Right matrix.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, typename Matrix3x3<T>::ComputationalType tolerance = typename Matrix3x3<T>::ComputationalType{0.00001}) noexcept;

	/// @brief Addition operator for two matrices.
	/// @tparam T Component type.
	/// @param left Augend.
	/// @param right Addend.
	/// @return Sum.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	/// @brief Negates the @p matrix.
	/// @tparam T Component type.
	/// @param matrix Matrix to negate.
	/// @return Negated matrix.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& matrix) noexcept;
	/// @brief Subtracts the @p right matrix from the @p left matrix.
	/// @tparam T Component type.
	/// @param left Minuend.
	/// @param right Subtrahend.
	/// @return Difference.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, T multiplier) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType multiplier) noexcept;
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix3x3<T> operator *(T multiplier, const Matrix3x3<T>& matrix) noexcept requires(std::is_integral_v<T>);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix3x3<T> operator *(typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept;
	/// @brief Multiplies two matrices.
	/// @tparam T Component type.
	/// @param left Multiplicand.
	/// @param right Multiplier.
	/// @return Product.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;
	/// @brief Multiplies the @p matrix by the @p vector.
	/// @tparam T Component type.
	/// @param matrix Matrix.
	/// @param vector Vector.
	/// @return Product vector.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept;

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType divisor) noexcept;

	/// @brief Puts matrix.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	export template<Arithmetic T>
	inline std::ostream& operator <<(std::ostream& stream, const Matrix3x3<T>& matrix);

	template<Arithmetic T>
	inline Matrix3x3<T>::Row::Row(Matrix3x3& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::Row::operator Vector3<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::Row::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.m_components[m_rowIndex + columnIndex * std::size_t{3}];
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::ConstRow::ConstRow(const Matrix3x3& matrix, const std::size_t rowIndex) noexcept :
		m_matrix{matrix},
		m_rowIndex{rowIndex}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::ConstRow::operator Vector3<T>() const noexcept
	{
		return m_matrix.GetRow(m_rowIndex);
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::ConstRow::operator [](const std::size_t columnIndex) const noexcept
	{
		return m_matrix.m_components[m_rowIndex + columnIndex * std::size_t{3}];
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::Matrix3x3() noexcept :
		Matrix3x3(T{}, T{}, T{}, T{}, T{}, T{}, T{}, T{}, T{})
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::Matrix3x3(const T m00, const T m10, const T m20, const T m01, const T m11, const T m21, const T m02, const T m12, const T m22) noexcept :
		m_components{m00, m10, m20, m01, m11, m21, m02, m12, m22}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::Matrix3x3(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept :
		Matrix3x3<T>(column0.X(), column0.Y(), column0.Z(), column1.X(), column1.Y(), column1.Z(), column2.X(), column2.Y(), column2.Z())
	{
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M20() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M20() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M01() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M01() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M11() noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M11() const noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M21() noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M21() const noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M02() noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M02() const noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M12() noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M12() const noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	inline T& Matrix3x3<T>::M22() noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	constexpr inline const T& Matrix3x3<T>::M22() const noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	inline T* Matrix3x3<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	inline const T* Matrix3x3<T>::Data() const noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	constexpr T Matrix3x3<T>::Determinant() const noexcept
	{
		return M00() * M11() * M22() + M01() * M12() * M20() + M02() * M10() * M21() - M02() * M11() * M20() - M01() * M10() * M22() - M00() * M12() * M21();
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Adjugate() const noexcept
	{
		const T minor00 = Matrix2x2(M11(), M21(), M12(), M22()).Determinant();
		const T minor10 = -Matrix2x2(M01(), M21(), M02(), M22()).Determinant();
		const T minor20 = Matrix2x2(M01(), M11(), M02(), M12()).Determinant();
		const T minor01 = -Matrix2x2(M10(), M20(), M12(), M22()).Determinant();
		const T minor11 = Matrix2x2(M00(), M20(), M02(), M22()).Determinant();
		const T minor21 = -Matrix2x2(M00(), M10(), M02(), M12()).Determinant();
		const T minor02 = Matrix2x2(M10(), M20(), M11(), M21()).Determinant();
		const T minor12 = -Matrix2x2(M00(), M20(), M01(), M21()).Determinant();
		const T minor22 = Matrix2x2(M00(), M10(), M01(), M11()).Determinant();

		return Matrix3x3(minor00, minor01, minor02, minor10, minor11, minor12, minor20, minor21, minor22);
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T> Matrix3x3<T>::Transposed() const noexcept
	{
		return Matrix3x3<T>(M00(), M01(), M02(), M10(), M11(), M12(), M20(), M21(), M22());
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::Transpose() noexcept
	{
		*this = Transposed();
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Inversed() const noexcept
	{
		return Adjugate() * (ComputationalType{1} / Determinant());
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::Inverse() noexcept
	{
		*this = Inversed();
	}

	template<Arithmetic T>
	bool Matrix3x3<T>::IsFinite() const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return std::isfinite(M00()) && std::isfinite(M10()) && std::isfinite(M20()) && std::isfinite(M01()) && std::isfinite(M11()) && std::isfinite(M21()) && std::isfinite(M02()) && std::isfinite(M12()) && std::isfinite(M22());
		}
		else
		{
			return true;
		}
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::Set(const T m00, const T m10, const T m20, const T m01, const T m11, const T m21, const T m02, const T m12, const T m22) noexcept
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
	void Matrix3x3<T>::Scale(const Matrix3x3<T>& scale) noexcept
	{
		M00() *= scale.M00();
		M10() *= scale.M10();
		M20() *= scale.M20();
		M01() *= scale.M01();
		M11() *= scale.M11();
		M21() *= scale.M21();
		M02() *= scale.M02();
		M12() *= scale.M12();
		M22() *= scale.M22();
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> Matrix3x3<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const T x = m_components[rowIndex];
		const T y = m_components[rowIndex + 3];
		const T z = m_components[rowIndex + 6];

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	void inline Matrix3x3<T>::SetRow(const std::size_t rowIndex, const Vector3<T>& value) noexcept
	{
		m_components[rowIndex] = value.X();
		m_components[rowIndex + 3] = value.Y();
		m_components[rowIndex + 6] = value.Z();
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> Matrix3x3<T>::GetColumn(const std::size_t columnIndex) const noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{3};

		const T x = m_components[begin];
		const T y = m_components[begin + 1];
		const T z = m_components[begin + 2];

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::SetColumn(const std::size_t columnIndex, const Vector3<T>& value) noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{3};

		m_components[begin] = value.X();
		m_components[begin + 1] = value.Y();
		m_components[begin + 2] = value.Z();
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> Matrix3x3<T>::GetDiagonal() const noexcept
	{
		return Vector3<T>(M00(), M11(), M22());
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::SetDiagonal(const Vector3<T>& value) noexcept
	{
		M00() = value.X();
		M11() = value.Y();
		M22() = value.Z();
	}

	template<Arithmetic T>
	constexpr inline Vector3<T> Matrix3x3<T>::GetCounterDiagonal() const noexcept
	{
		return Vector3<T>(M02(), M11(), M20());
	}

	template<Arithmetic T>
	inline void Matrix3x3<T>::SetCounterDiagonal(const Vector3<T>& value) noexcept
	{
		M02() = value.X();
		M11() = value.Y();
		M20() = value.Z();
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		const T m00 = left.M00() * right.M00();
		const T m10 = left.M10() * right.M10();
		const T m20 = left.M20() * right.M20();
		const T m01 = left.M01() * right.M01();
		const T m11 = left.M11() * right.M11();
		const T m21 = left.M21() * right.M21();
		const T m02 = left.M02() * right.M02();
		const T m12 = left.M12() * right.M12();
		const T m22 = left.M22() * right.M22();

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
	}

	template<Arithmetic T>
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, const typename Matrix3x3<T>::ComputationalType tolerance) noexcept
	{
		const Matrix3x3<T> diff = left - right;
		const T kindOfMagnitudeSquared = diff.M00() * diff.M00() + diff.M10() * diff.M10() + diff.M20() * diff.M20() + diff.M01() * diff.M01() + 
			diff.M11() * diff.M11() + diff.M21() * diff.M21() + diff.M02() * diff.M02() + diff.M12() * diff.M12() + diff.M22() * diff.M22();
		
		return kindOfMagnitudeSquared < tolerance * tolerance;
	}

	template<Arithmetic T>
	inline std::string Matrix3x3<T>::ToString() const
	{
		return std::format("({}, {}, {})({}, {}, {})({}, {}, {})", M00(), M01(), M02(), M10(), M11(), M12(), M20(), M21(), M22());
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::Row Matrix3x3<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row(*this, rowIndex);
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::ConstRow Matrix3x3<T>::operator [](const std::size_t rowIndex) const noexcept
	{
		return ConstRow(*this, rowIndex);
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator +=(const Matrix3x3& other) noexcept
	{
		M00() += other.M00();
		M10() += other.M10();
		M20() += other.M20();
		M01() += other.M01();
		M11() += other.M11();
		M21() += other.M21();
		M02() += other.M02();
		M12() += other.M12();
		M22() += other.M22();

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator -=(const Matrix3x3& other) noexcept
	{
		M00() -= other.M00();
		M10() -= other.M10();
		M20() -= other.M20();
		M01() -= other.M01();
		M11() -= other.M11();
		M21() -= other.M21();
		M02() -= other.M02();
		M12() -= other.M12();
		M22() -= other.M22();

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		M00() *= multiplier;
		M10() *= multiplier;
		M20() *= multiplier;
		M01() *= multiplier;
		M11() *= multiplier;
		M21() *= multiplier;
		M02() *= multiplier;
		M12() *= multiplier;
		M22() *= multiplier;

		return *this;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const ComputationalType multiplier) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() * multiplier);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() * multiplier);
		M20() = RoundToIntegralIfPossible<ComputationalType, T>(M20() * multiplier);
		M01() = RoundToIntegralIfPossible<ComputationalType, T>(M01() * multiplier);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() * multiplier);
		M21() = RoundToIntegralIfPossible<ComputationalType, T>(M21() * multiplier);
		M02() = RoundToIntegralIfPossible<ComputationalType, T>(M02() * multiplier);
		M12() = RoundToIntegralIfPossible<ComputationalType, T>(M12() * multiplier);
		M22() = RoundToIntegralIfPossible<ComputationalType, T>(M22() * multiplier);

		return *this;
	}

	template<Arithmetic T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator *=(const Matrix3x3& other) noexcept
	{
		return *this = *this * other;
	}

	template<Arithmetic T>
	Matrix3x3<T>& Matrix3x3<T>::operator /=(const ComputationalType divisor) noexcept
	{
		M00() = RoundToIntegralIfPossible<ComputationalType, T>(M00() / divisor);
		M10() = RoundToIntegralIfPossible<ComputationalType, T>(M10() / divisor);
		M20() = RoundToIntegralIfPossible<ComputationalType, T>(M20() / divisor);
		M01() = RoundToIntegralIfPossible<ComputationalType, T>(M01() / divisor);
		M11() = RoundToIntegralIfPossible<ComputationalType, T>(M11() / divisor);
		M21() = RoundToIntegralIfPossible<ComputationalType, T>(M21() / divisor);
		M02() = RoundToIntegralIfPossible<ComputationalType, T>(M02() / divisor);
		M12() = RoundToIntegralIfPossible<ComputationalType, T>(M12() / divisor);
		M22() = RoundToIntegralIfPossible<ComputationalType, T>(M22() / divisor);

		return *this;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		return Matrix3x3<T>(left.M00() + right.M00(), left.M10() + right.M10(), left.M20() + right.M20(), left.M01() + right.M01(), left.M11() + right.M11(), 
			left.M21() + right.M21(), left.M02() + right.M02(), left.M12() + right.M12(), left.M22() + right.M22());
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& matrix) noexcept
	{
		return Matrix3x3<T>(-matrix.M00(), -matrix.M10(), -matrix.M20(), -matrix.M01(), -matrix.M11(), -matrix.M21(), -matrix.M02(), -matrix.M12(), -matrix.M22());
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		return Matrix3x3<T>(left.M00() - right.M00(), left.M10() - right.M10(), left.M20() - right.M20(), left.M01() - right.M01(), left.M11() - right.M11(),
			left.M21() - right.M21(), left.M02() - right.M02(), left.M12() - right.M12(), left.M22() - right.M22());
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, const T multiplier) noexcept requires(std::is_integral_v<T>)
	{
		return Matrix3x3<T>(matrix.M00() * multiplier, matrix.M10() * multiplier, matrix.M20() * multiplier, matrix.M01() * multiplier, matrix.M11() * multiplier, 
			matrix.M21() * multiplier, matrix.M02() * multiplier, matrix.M12() * multiplier, matrix.M22() * multiplier);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, const typename Matrix3x3<T>::ComputationalType multiplier) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M00() * multiplier);
		const T m10 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M10() * multiplier);
		const T m20 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M20() * multiplier);
		const T m01 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M01() * multiplier);
		const T m11 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M11() * multiplier);
		const T m21 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M21() * multiplier);
		const T m02 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M02() * multiplier);
		const T m12 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M12() * multiplier);
		const T m22 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M22() * multiplier);

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const T multiplier, const Matrix3x3<T>& matrix) noexcept requires(std::is_integral_v<T>)
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T> operator *(const typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept
	{
		return matrix * multiplier;
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept
	{
		const T m00 = left.M00() * right.M00() + left.M01() * right.M10() + left.M02() * right.M20();
		const T m10 = left.M10() * right.M00() + left.M11() * right.M10() + left.M12() * right.M20();
		const T m20 = left.M20() * right.M00() + left.M21() * right.M10() + left.M22() * right.M20();
		const T m01 = left.M00() * right.M01() + left.M01() * right.M11() + left.M02() * right.M21();
		const T m11 = left.M10() * right.M01() + left.M11() * right.M11() + left.M12() * right.M21();
		const T m21 = left.M20() * right.M01() + left.M21() * right.M11() + left.M22() * right.M21();
		const T m02 = left.M00() * right.M02() + left.M01() * right.M12() + left.M02() * right.M22();
		const T m12 = left.M10() * right.M02() + left.M11() * right.M12() + left.M12() * right.M22();
		const T m22 = left.M20() * right.M02() + left.M21() * right.M12() + left.M22() * right.M22();

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
	}

	template<Arithmetic T>
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept
	{
		const T x = matrix.M00() * vector.X() + matrix.M01() * vector.Y() + matrix.M02() * vector.Z();
		const T y = matrix.M10() * vector.X() + matrix.M11() * vector.Y() + matrix.M12() * vector.Z();
		const T z = matrix.M20() * vector.X() + matrix.M21() * vector.Y() + matrix.M22() * vector.Z();

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, const typename Matrix3x3<T>::ComputationalType divisor) noexcept
	{
		const T m00 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M00() / divisor);
		const T m10 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M10() / divisor);
		const T m20 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M20() / divisor);
		const T m01 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M01() / divisor);
		const T m11 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M11() / divisor);
		const T m21 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M21() / divisor);
		const T m02 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M02() / divisor);
		const T m12 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M12() / divisor);
		const T m22 = RoundToIntegralIfPossible<Matrix3x3<T>::ComputationalType, T>(matrix.M22() / divisor);

		return Matrix3x3<T>(m00, m10, m20, m01, m11, m21, m02, m12, m22);
	}

	template<Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Matrix3x3<T>& matrix)
	{
		return stream << matrix.ToString();
	}

	template<Arithmetic T>
	const Matrix3x3<T> Matrix3x3<T>::Identity = Matrix3x3<T>(T{1}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{1});
	template<Arithmetic T>
	const Matrix3x3<T> Matrix3x3<T>::Zero = Matrix3x3<T>(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0});
}
