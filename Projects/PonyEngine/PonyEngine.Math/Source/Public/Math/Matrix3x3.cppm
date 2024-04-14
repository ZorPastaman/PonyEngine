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
	export template<Arithmetic T>
	class Matrix3x3 final
	{
	public:
		class Row final
		{
		public:
			Row(const Row&) = delete;
			Row(Row&&) = delete;

			inline ~Row() noexcept = default;

			[[nodiscard("Pure operator")]]
			inline operator Vector3<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			inline T& operator [](std::size_t columnIndex) const noexcept;

			Row& operator =(const Row&) = delete;
			Row& operator =(Row&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			inline Row(Matrix3x3& matrix, std::size_t rowIndex) noexcept;

			Matrix3x3& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix3x3;
		};

		class ConstRow final
		{
		public:
			ConstRow(const ConstRow&) = delete;
			ConstRow(ConstRow&&) = delete;

			constexpr inline ~ConstRow() noexcept = default;

			[[nodiscard("Pure operator")]]
			constexpr inline operator Vector3<T>() const noexcept;

			[[nodiscard("Pure operator")]]
			constexpr inline const T& operator [](std::size_t columnIndex) const noexcept;

			ConstRow& operator =(const ConstRow&) = delete;
			ConstRow& operator =(ConstRow&&) = delete;

		private:
			[[nodiscard("Pure constructor")]]
			constexpr inline ConstRow(const Matrix3x3& matrix, std::size_t rowIndex) noexcept;

			const Matrix3x3& m_matrix;
			std::size_t m_rowIndex;

			friend Matrix3x3;
		};

		using ValueType = T; /// @brief Component type.
		using ComputationalType = ComputationalFor<T>; /// @brief Floating point type used in functions that require a floating point type.

		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr inline Matrix3x3(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix3x3(const Matrix3x3& other) noexcept = default;

		constexpr ~Matrix3x3() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr inline T& M00() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M00() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M10() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M10() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M20() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M20() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M01() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M01() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M11() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M11() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M21() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M21() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M02() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M02() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M12() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M12() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T& M22() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T& M22() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline T* Data() noexcept;
		[[nodiscard("Pure function")]]
		constexpr inline const T* Data() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Determinant() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Adjugate() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Transposed() const noexcept;
		inline void Transpose() noexcept;

		[[nodiscard("Pure function")]]
		constexpr Matrix3x3 Inversed() const noexcept;
		inline void Inverse() noexcept;

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		void Set(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) noexcept;

		/// @brief Multiplies @a this by the @p scale component-wise.
		/// @param scale @p Matrix to multiply by.
		void Scale(const Matrix3x3<T>& scale) noexcept;

		[[nodiscard("Pure function")]]
		Vector3<T> GetRow(std::size_t rowIndex) const noexcept;
		void SetRow(std::size_t rowIndex, const Vector3<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		Vector3<T> GetColumn(std::size_t columnIndex) noexcept;
		void SetColumn(std::size_t columnIndex, const Vector3<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetDiagonal() const noexcept;
		inline void SetDiagonal(const Vector3<T>& value) noexcept;

		[[nodiscard("Pure function")]]
		constexpr inline Vector3<T> GetCounterDiagonal() const noexcept;
		inline void SetCounterDiagonal(const Vector3<T>& value) noexcept;

		/// @brief Creates a string representing a state of a @p Matrix.
		///        The format is '(m00, m01, m02)(m10, m11, m12)(m20, m21, m22)'.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		[[nodiscard("Pure operator")]]
		inline Row operator [](std::size_t rowIndex) noexcept;
		[[nodiscard("Pure operator")]]
		inline ConstRow operator [](std::size_t rowIndex) const noexcept;

		Matrix3x3& operator =(const Matrix3x3& other) noexcept = default;
		Matrix3x3& operator +=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator -=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator *=(T multiplier) noexcept requires(std::is_integral_v<T>);
		Matrix3x3& operator *=(ComputationalType multiplier) noexcept;
		Matrix3x3& operator *=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator /=(ComputationalType divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix3x3& other) const noexcept = default;

		static const Matrix3x3 Identity;
		static const Matrix3x3 Zero;

		constexpr inline static const std::size_t RowCount = 3;
		constexpr inline static const std::size_t ColumnCount = 3;
		constexpr inline static const std::size_t ComponentCount = RowCount * ColumnCount;

	private:
		std::array<T, ComponentCount> m_components; /// @brief Component array in order m00, m10, m01, m11.
	};

	/// @brief Multiplies the @p left matrix by the @p right matrix component-wise.
	/// @tparam T Component type.
	/// @param left Multiplicand @p Matrix.
	/// @param right Multiplier @p Matrix.
	/// @return Product @p Matrix.
	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Matrix3x3<T> Scale(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix3x3<T>& left, const Matrix3x3<T>& right, typename Matrix3x3<T>::ComputationalType tolerance = typename Matrix3x3<T>::ComputationalType{0.00001}) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator +(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& matrix) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator -(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, T multiplier) noexcept requires(std::is_integral_v<T>);
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType multiplier) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix3x3<T> operator *(T multiplier, const Matrix3x3<T>& matrix) noexcept requires(std::is_integral_v<T>);
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr inline Matrix3x3<T> operator *(typename Matrix3x3<T>::ComputationalType multiplier, const Matrix3x3<T>& matrix) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator *(const Matrix3x3<T>& left, const Matrix3x3<T>& right) noexcept;
	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Vector3<T> operator *(const Matrix3x3<T>& matrix, const Vector3<T>& vector) noexcept;

	export template<Arithmetic T> [[nodiscard("Pure operator")]]
	constexpr Matrix3x3<T> operator /(const Matrix3x3<T>& matrix, typename Matrix3x3<T>::ComputationalType divisor) noexcept;

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
	constexpr Matrix3x3<T>::Matrix3x3() noexcept :
		Matrix3x3(T{}, T{}, T{}, T{}, T{}, T{}, T{}, T{}, T{})
	{
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T>::Matrix3x3(const T m00, const T m10, const T m20, const T m01, const T m11, const T m21, const T m02, const T m12, const T m22) noexcept :
		m_components{m00, m10, m20, m01, m11, m21, m02, m12, m22}
	{
	}

	template<Arithmetic T>
	constexpr inline Matrix3x3<T>::Matrix3x3(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2) noexcept :
		Matrix3x3<T>(column0.x, column0.y, column0.z, column1.x, column1.y, column1.z, column2.x, column2.y, column2.z)
	{
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M00() noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M00() const noexcept
	{
		return m_components[0];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M10() noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M10() const noexcept
	{
		return m_components[1];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M20() noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M20() const noexcept
	{
		return m_components[2];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M01() noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M01() const noexcept
	{
		return m_components[3];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M11() noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M11() const noexcept
	{
		return m_components[4];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M21() noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M21() const noexcept
	{
		return m_components[5];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M02() noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M02() const noexcept
	{
		return m_components[6];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M12() noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M12() const noexcept
	{
		return m_components[7];
	}

	template<Arithmetic T>
	inline constexpr T& Matrix3x3<T>::M22() noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	inline constexpr const T& Matrix3x3<T>::M22() const noexcept
	{
		return m_components[8];
	}

	template<Arithmetic T>
	inline constexpr T* Matrix3x3<T>::Data() noexcept
	{
		return m_components.data();
	}

	template<Arithmetic T>
	inline constexpr const T* Matrix3x3<T>::Data() const noexcept
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
		const T minor00Determinant = Matrix2x2(M11(), M21(), M12(), M22()).Determinant();
		const T minor10Determinant = -Matrix2x2(M01(), M21(), M02(), M22()).Determinant();
		const T minor20Determinant = Matrix2x2(M01(), M11(), M02(), M12()).Determinant();
		const T minor01Determinant = -Matrix2x2(M10(), M20(), M12(), M22()).Determinant();
		const T minor11Determinant = Matrix2x2(M00(), M20(), M02(), M22()).Determinant();
		const T minor21Determinant = -Matrix2x2(M00(), M10(), M02(), M12()).Determinant();
		const T minor02Determinant = Matrix2x2(M10(), M20(), M11(), M21()).Determinant();
		const T minor12Determinant = -Matrix2x2(M00(), M20(), M01(), M21()).Determinant();
		const T minor22Determinant = Matrix2x2(M00(), M10(), M01(), M11()).Determinant();

		return Matrix3x3(minor00Determinant, minor10Determinant, minor20Determinant, minor01Determinant, minor11Determinant, minor21Determinant, minor02Determinant, minor12Determinant, minor22Determinant);
	}

	template<Arithmetic T>
	constexpr Matrix3x3<T> Matrix3x3<T>::Transposed() const noexcept
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
		const Matrix3x3<T> transposed = Transposed();
		const Matrix3x3<T> adjugate = transposed.Adjugate();
		const T determinant = Determinant();

		return adjugate * (ComputationalType{1} / determinant);
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
	Vector3<T> Matrix3x3<T>::GetRow(const std::size_t rowIndex) const noexcept
	{
		const T x = m_components[rowIndex];
		const T y = m_components[rowIndex + 3];
		const T z = m_components[rowIndex + 6];

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetRow(const std::size_t rowIndex, const Vector3<T>& value) noexcept
	{
		m_components[rowIndex] = value.X();
		m_components[rowIndex + 3] = value.Y();
		m_components[rowIndex + 6] = value.Z();
	}

	template<Arithmetic T>
	Vector3<T> Matrix3x3<T>::GetColumn(const std::size_t columnIndex) noexcept
	{
		const std::size_t begin = columnIndex * std::size_t{3};

		const T x = m_components[begin];
		const T y = m_components[begin + 1];
		const T z = m_components[begin + 2];

		return Vector3<T>(x, y, z);
	}

	template<Arithmetic T>
	void Matrix3x3<T>::SetColumn(const std::size_t columnIndex, const Vector3<T>& value) noexcept
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
	std::string Matrix3x3<T>::ToString() const
	{
		return std::format("({}, {}, {})({}, {}, {})({}, {}, {})", M00(), M01(), M02(), M10(), M11(), M12(), M20(), M21(), M22());
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::Row Matrix3x3<T>::operator [](const std::size_t rowIndex) noexcept
	{
		return Row(*this, rowIndex);
	}

	template<Arithmetic T>
	inline Matrix3x3<T>::ConstRow Matrix3x3<T>::operator [](const std::size_t rowIndex) const noexcept
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
	Matrix3x3<T>& Matrix3x3<T>::operator *=(const Matrix3x3& other) noexcept
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
