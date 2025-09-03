/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Matrix;

import std;

import PonyEngine.Type;

import :Common;
import :InternalUtility;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Matrix.
	/// @remark The matrix is column-major.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	class Matrix final
	{
	public:
		using ValueType = T; ///< Component type.
		using ColumnType = Vector<T, RowSize>; ///< Column type.

		static constexpr std::size_t RowCount = RowSize; ///< Row count.
		static constexpr std::size_t ColumnCount = ColumnSize; ///< Column count.
		static constexpr std::size_t ComponentCount = RowCount * ColumnCount; ///< Component count.
		static constexpr bool IsSquare = RowCount == ColumnCount; ///< Is the matrix square?

		/// @brief Creates a zero matrix.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix() noexcept = default;
		/// @brief Creates a matrix and sets each diagonal component to the @p value.
		/// @param value Diagonal component value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(T value) noexcept requires(RowSize == ColumnSize);
		/// @brief Creates a matrix and assigns its components from the arguments.
		/// @tparam Ts Component types.
		/// @param components Matrix components
		template<Type::Arithmetic... Ts> [[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(Ts... components) noexcept requires (sizeof...(Ts) == RowSize * ColumnSize);
		/// @brief Creates a matrix and assigns its columns from the arguments.
		/// @tparam Ts Column types.
		/// @param columns Matrix columns.
		template<typename... Ts> [[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(Ts&&... columns) noexcept requires (sizeof...(Ts) == ColumnSize && (std::is_convertible_v<Ts, Vector<T, RowSize>> && ...));
		/// @brief Creates a matrix and assigns its components from the @p span.
		/// @param span Components.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(std::span<const T, RowSize * ColumnSize> span) noexcept;
		/// @brief Creates a matrix and assigns its components from the @p span.
		/// @param span Components.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(std::mdspan<const T, std::extents<std::size_t, ColumnSize, RowSize>> span) noexcept;
		/// @brief Creates a matrix and assigns its columns from the @p span.
		/// @param span Columns.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(std::span<const Vector<T, RowSize>, ColumnSize> span) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix(const Matrix& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Matrix(Matrix&& other) noexcept = default;

		constexpr ~Matrix() noexcept = default;

		/// @brief Gets a zero matrix.
		/// @return Zero matrix.
		[[nodiscard("Pure function")]]
		static constexpr const Matrix& Zero() noexcept;
		/// @brief Gets an identity matrix.
		/// @return Identity matrix.
		[[nodiscard("Pure function")]]
		static constexpr const Matrix& Identity() noexcept requires (RowSize == ColumnSize);

		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in [0, ComponentCount).
		/// @return Component.
		[[nodiscard("Pure function")]]
		constexpr T& Component(std::size_t index) noexcept;
		/// @brief Gets a component by the @p index.
		/// @param index Component index. Must be in [0, ComponentCount).
		/// @return Component.
		[[nodiscard("Pure function")]]
		constexpr const T& Component(std::size_t index) const noexcept;
		/// @brief Gets the matrix span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<T, RowSize * ColumnSize> Span() noexcept;
		/// @brief Gets the matrix span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<const T, RowSize * ColumnSize> Span() const noexcept;
		/// @brief Gets the matrix span.
		/// @remark The indexing of this span is [ColumnIndex, RowIndex].
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::mdspan<T, std::extents<std::size_t, ColumnSize, RowSize>> SpanMD() noexcept;
		/// @brief Gets the matrix span.
		/// @remark The indexing of this span is [ColumnIndex, RowIndex].
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::mdspan<const T, std::extents<std::size_t, ColumnSize, RowSize>> SpanMD() const noexcept;
		/// @brief Gets a column span.
		/// @param columnIndex Column index.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, RowSize> Span(std::size_t columnIndex) noexcept;
		/// @brief Gets a column span.
		/// @param columnIndex Column index.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, RowSize> Span(std::size_t columnIndex) const noexcept;

		/// @brief Gets a row by the @p rowIndex.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, ColumnSize> Row(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row by the @p rowIndex.
		/// @param rowIndex Row index.
		/// @param value Row components.
		constexpr void Row(std::size_t rowIndex, const Vector<T, ColumnSize>& value) noexcept;
		/// @brief Gets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowSize>& Column(std::size_t columnIndex) noexcept;
		/// @brief Gets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, RowSize>& Column(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @param value Column components.
		constexpr void Column(std::size_t columnIndex, const Vector<T, RowSize>& value) noexcept;
		/// @brief Gets the columns.
		/// @return Columns.
		[[nodiscard("Pure function")]]
		constexpr std::span<Vector<T, RowSize>, ColumnSize> Columns() noexcept;
		/// @brief Gets the columns.
		/// @return Columns.
		[[nodiscard("Pure function")]]
		constexpr std::span<const Vector<T, RowSize>, ColumnSize> Columns() const noexcept;

		/// @brief Gets the diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowSize> Diagonal() const noexcept requires (RowSize == ColumnSize);
		/// @brief Sets the diagonal.
		/// @param value Diagonal components.
		constexpr void Diagonal(const Vector<T, RowSize>& value) noexcept requires (RowSize == ColumnSize);
		/// @brief Gets the counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowSize> CounterDiagonal() const noexcept requires (RowSize == ColumnSize);
		/// @brief Sets the counter-diagonal.
		/// @param value Counter=diagonal components.
		constexpr void CounterDiagonal(const Vector<T, RowSize>& value) noexcept requires (RowSize == ColumnSize);

		/// @brief Computes a trace of the matrix.
		/// @return Trace of the matrix.
		[[nodiscard("Pure function")]]
		constexpr T Trace() const noexcept requires (RowSize == ColumnSize);
		/// @brief Computes a determinant of the matrix.
		/// @return Determinant.
		[[nodiscard("Pure function")]]
		constexpr T Determinant() const noexcept requires (RowSize == ColumnSize);

		/// @brief Computes a transpose of the matrix.
		/// @return Transpose.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, ColumnSize, RowSize> Transpose() const noexcept;
		/// @brief Computes a submatrix.
		/// @param rowIndex Index of a row to remove.
		/// @param columnIndex Index of a column to remove.
		/// @return Submatrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, std::max(RowSize - 1uz, 1uz), std::max(ColumnSize - 1uz, 1uz)> Submatrix(std::size_t rowIndex, std::size_t columnIndex) const noexcept requires (RowSize > 1uz && ColumnSize > 1uz);
		/// @brief Computes a submatrix.
		/// @param rowIndex Index of a row to remove.
		/// @return Submatrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, std::max(RowSize - 1uz, 1uz), ColumnSize> SubmatrixRow(std::size_t rowIndex) const noexcept requires (RowSize > 1uz);
		/// @brief Computes a submatrix.
		/// @param columnIndex Index of a column to remove.
		/// @return Submatrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, RowSize, std::max(ColumnSize - 1uz, 1uz)> SubmatrixColumn(std::size_t columnIndex) const noexcept requires (ColumnSize > 1uz);

		/// @brief Computes a minor.
		/// @param rowIndex Minor row index.
		/// @param columnIndex Minor column index
		/// @return Minor.
		[[nodiscard("Pure function")]]
		constexpr T Minor(std::size_t rowIndex, std::size_t columnIndex) const noexcept requires (RowSize == ColumnSize && RowSize > 1uz);
		/// @brief Computes a minor.
		/// @param rowIndex Minor row index.
		/// @return Minor.
		[[nodiscard("Pure function")]]
		constexpr T Minor(std::size_t rowIndex) const noexcept requires (RowSize == ColumnSize + 1uz);
		/// @brief Computes a minor.
		/// @param columnIndex Minor column index
		/// @return Minor.
		[[nodiscard("Pure function")]]
		constexpr T Minor(std::size_t columnIndex) const noexcept requires (ColumnSize == RowSize + 1uz);
		/// @brief Computes a minor matrix.
		/// @return Minor matrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix MinorMatrix() const noexcept requires (RowSize == ColumnSize && RowSize > 1uz);
		/// @brief Computes a minor vector.
		/// @return Minor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowSize> MinorVector() const noexcept requires (RowSize == ColumnSize + 1uz);
		/// @brief Computes a minor vector.
		/// @return Minor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, ColumnSize> MinorVector() const noexcept requires (ColumnSize == RowSize + 1uz);
		/// @brief Computes a cofactor.
		/// @param rowIndex Cofactor row index.
		/// @param columnIndex Cofactor column index
		/// @return Cofactor.
		[[nodiscard("Pure function")]]
		constexpr T Cofactor(std::size_t rowIndex, std::size_t columnIndex) const noexcept requires (RowSize == ColumnSize && RowSize > 1uz);
		/// @brief Computes a cofactor.
		/// @param rowIndex Cofactor row index.
		/// @return Cofactor.
		[[nodiscard("Pure function")]]
		constexpr T Cofactor(std::size_t rowIndex) const noexcept requires (RowSize == ColumnSize + 1uz);
		/// @brief Computes a cofactor.
		/// @param columnIndex Cofactor column index
		/// @return Cofactor.
		[[nodiscard("Pure function")]]
		constexpr T Cofactor(std::size_t columnIndex) const noexcept requires (ColumnSize == RowSize + 1uz);
		/// @brief Computes a cofactor matrix.
		/// @return Cofactor matrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix CofactorMatrix() const noexcept requires (RowSize == ColumnSize && RowSize > 1uz);
		/// @brief Computes a cofactor vector.
		/// @return Cofactor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowSize> CofactorVector() const noexcept requires (RowSize == ColumnSize + 1uz);
		/// @brief Computes a cofactor vector.
		/// @return Cofactor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, ColumnSize> CofactorVector() const noexcept requires (ColumnSize == RowSize + 1uz);
		/// @brief Computes an adjugate of the matrix.
		/// @return Adjugate.
		[[nodiscard("Pure function")]]
		constexpr Matrix Adjugate() const noexcept requires (RowSize == ColumnSize && RowSize > 1uz);
		/// @brief Computes an inverse of the matrix.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix Inverse() const noexcept requires (std::is_floating_point_v<T> && RowSize == ColumnSize && RowSize > 1uz);

		/// @brief Checks if this matrix is equal to the zero matrix.
		/// @return @a True if this matrix is equal to the zero matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsZero() const noexcept;
		/// @brief Checks if this matrix is almost equal to the zero matrix with the tolerance value.
		/// @param tolerance Tolerance.
		/// @return @a True if this matrix is almost equal to the zero matrix; @a false otherwise.
		template<std::same_as<T> U = T> [[nodiscard("Pure function")]]
		constexpr bool IsAlmostZero(const Tolerance<U>& tolerance = Tolerance<U>()) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Checks if this matrix is equal to the identity matrix.
		/// @return @a True if this matrix is equal to the identity matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsIdentity() const noexcept requires (RowSize == ColumnSize);
		/// @brief Checks if this matrix is almost equal to the identity matrix with the tolerance value.
		/// @param tolerance Tolerance.
		/// @return @a True if this matrix is almost equal to the identity matrix; @a false otherwise.
		template<std::same_as<T> U = T> [[nodiscard("Pure function")]]
		constexpr bool IsAlmostIdentity(const Tolerance<U>& tolerance = Tolerance<U>()) const noexcept requires (std::is_floating_point_v<T> && RowSize == ColumnSize);

		/// @brief Checks if all the components are finite numbers.
		/// @return @a True if all the components are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Multiplies @a this by the @p multiplier component-wise.
		/// @param multiplier Multiplier.
		constexpr void Multiply(const Matrix& multiplier) noexcept;
		/// @brief Divides @a this by the @p divisor component-wise.
		/// @param divisor Divisor.
		constexpr void Divide(const Matrix& divisor) noexcept;

		/// @brief Creates a string representing a state of the matrix.
		/// @param multiline Should it print each line on different lines?
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString(bool multiline = false) const;

		/// @brief Casts all the components to the @p U.
		/// @tparam U Target component type.
		template<Type::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Matrix<U, RowSize, ColumnSize>() const noexcept;

		/// @brief Gets a component by indices.
		/// @param rowIndex Row index. Must be in range [0, RowSize).
		/// @param columnIndex Column index. Must be in range [0, ColumnSize).
		/// @return Component.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t rowIndex, std::size_t columnIndex) noexcept;
		/// @brief Gets a component by indices.
		/// @param rowIndex Row index.
		/// @param columnIndex Column index.
		/// @return Component.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t rowIndex, std::size_t columnIndex) const noexcept;

		constexpr Matrix& operator =(const Matrix& other) noexcept = default;
		constexpr Matrix& operator =(Matrix&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @param other Matrix to add.
		/// @return @a This.
		constexpr Matrix& operator +=(const Matrix& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @param other Matrix to subtract.
		/// @return @a This.
		constexpr Matrix& operator -=(const Matrix& other) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @param multiplier Multiplier.
		/// @return @a This.
		constexpr Matrix& operator *=(T multiplier) noexcept;
		/// @brief Multiplies @a this by the @p multiplier.
		/// @tparam U Multiplier type.
		/// @param multiplier Multiplier.
		/// @return @a This.
		template<std::floating_point U = double>
		constexpr Matrix& operator *=(U multiplier) noexcept requires (std::is_integral_v<T>);
		/// @brief Multiplies @a this by the @p other.
		/// @param other Matrix to multiply.
		/// @return @a This.
		constexpr Matrix& operator *=(const Matrix& other) noexcept requires (RowSize == ColumnSize);
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Divisor.
		/// @return @a This.
		constexpr Matrix& operator /=(T divisor) noexcept;
		/// @brief Divides @a this by the @p divisor.
		/// @tparam U Divisor type.
		/// @param divisor Divisor.
		/// @return @a This.
		template<std::floating_point U = double>
		constexpr Matrix& operator /=(U divisor) noexcept requires (std::is_integral_v<T>);

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Matrix& other) const noexcept = default;

	private:
		std::array<Vector<T, RowSize>, ColumnSize> columns; ///< Matrix columns.
	};

	/// @brief Matrix 1x1.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix1x1 = Matrix<T, 1uz, 1uz>;
	/// @brief Matrix 1x2.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix1x2 = Matrix<T, 1uz, 2uz>;
	/// @brief Matrix 2x2.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix2x2 = Matrix<T, 2uz, 2uz>;
	/// @brief Matrix 2x3.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix2x3 = Matrix<T, 2uz, 3uz>;
	/// @brief Matrix 3x3.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix3x3 = Matrix<T, 3uz, 3uz>;
	/// @brief Matrix 3x4.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix3x4 = Matrix<T, 3uz, 4uz>;
	/// @brief Matrix 4x4.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Matrix4x4 = Matrix<T, 4uz, 4uz>;

	/// @brief Checks if all the components are finite numbers.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Matrix to check.
	/// @return @a True if all the components are finite; @a false otherwise.
	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure function")]]
	constexpr bool IsFinite(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Multiplies the @p lhs matrix by the @p rhs matrix component-wise.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure function")]]
	constexpr Matrix<T, RowSize, ColumnSize> Multiply(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);
	/// @brief Divides the @p lhs matrix by the @p rhs matrix component-wise.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param lhs Dividend.
	/// @param rhs Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure function")]]
	constexpr Matrix<T, RowSize, ColumnSize> Divide(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Multiplies a transpose of the @p lhs matrix by the @p rhs matrix component-wise.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @tparam RightColumnSize Right matrix column count.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize, std::size_t RightColumnSize> [[nodiscard("Pure function")]]
	constexpr Matrix<T, RowSize, RightColumnSize> MultiplyTranspose(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Computes absolute values of the @p matrix components.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Source.
	/// @return Absolute matrix.
	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure function")]]
	constexpr Matrix<T, RowSize, ColumnSize> Abs(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Normalizes the columns of the @p matrix.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Matrix to normalize.
	/// @return Normalized matrix.
	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure function")]]
	Matrix<T, RowSize, ColumnSize> NormalizeColumns(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Checks if the two matrices are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param lhs Left matrix.
	/// @param rhs Right matrix.
	/// @param tolerance Tolerance.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Sums the @p lhs and @p rhs.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param lhs Augend.
	/// @param rhs Addend.
	/// @return Sum.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator +(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Negates the @p matrix.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Matrix to negate.
	/// @return Negated matrix.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator -(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);
	/// @brief Subtracts the @p rhs matrix from the @p lhs matrix.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param lhs Minuend.
	/// @param rhs Subtrahend.
	/// @return Difference.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator -(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator *(const Matrix<T, RowSize, ColumnSize>& matrix, T multiplier) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam U Multiplier type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point U = double, std::integral T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator *(const Matrix<T, RowSize, ColumnSize>& matrix, U multiplier) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator *(T multiplier, const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam U Multiplier type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point U = double, std::integral T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator *(U multiplier, const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Multiplies the @p lhs matrix by the @p rhs matrix.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @tparam RightColumnSize Right matrix column count.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize, std::size_t RightColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, RightColumnSize> operator *(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, ColumnSize, RightColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz && RightColumnSize >= 1uz);
	/// @brief Multiplies the @p matrix by the @p vector.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Matrix.
	/// @param vector Vector.
	/// @return Product vector.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Vector<T, RowSize> operator *(const Matrix<T, RowSize, ColumnSize>& matrix, const Vector<T, ColumnSize>& vector) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator /(const Matrix<T, RowSize, ColumnSize>& matrix, T divisor) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);
	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @tparam U Divisor type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point U = double, std::integral T, std::size_t RowSize, std::size_t ColumnSize> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowSize, ColumnSize> operator /(const Matrix<T, RowSize, ColumnSize>& matrix, U divisor) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz);

	/// @brief Outputs a string representation of the @p matrix.
	/// @tparam T Component type.
	/// @tparam RowSize Row count.
	/// @tparam ColumnSize Column count.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	std::ostream& operator <<(std::ostream& stream, const Matrix<T, RowSize, ColumnSize>& matrix);
}

/// @brief Matrix formatter.
/// @tparam T Component type.
/// @tparam RowSize Row count.
/// @tparam ColumnSize Column count.
/// @note Parameters :m or :M produce a multiline string; without them, the result will be a single line string.
export template<PonyEngine::Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
struct std::formatter<PonyEngine::Math::Matrix<T, RowSize, ColumnSize>, char>
{
private:
	bool multiline = false;

public:
	constexpr auto parse(std::format_parse_context& context)
	{
		auto it = context.begin();

		for (; it != context.end() && *it != '}'; ++it)
		{
			switch (*it)
			{
			case 'm':
			case 'M':
				multiline = true;
				break;
			default: [[unlikely]]
				throw std::format_error("Unexpected format specifier.");
			}
		}
		if (it == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}

		return it;
	}

	auto format(const PonyEngine::Math::Matrix<T, RowSize, ColumnSize>& matrix, std::format_context& context) const
	{
		return std::ranges::copy(matrix.ToString(multiline), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>::Matrix(const T value) noexcept requires (RowSize == ColumnSize) :
		Matrix()
	{
		Diagonal(Vector<T, RowSize>(value));
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<Type::Arithmetic... Ts>
	constexpr Matrix<T, RowSize, ColumnSize>::Matrix(Ts... components) noexcept requires (sizeof...(Ts) == RowSize * ColumnSize) :
		Matrix(std::array<T, RowSize * ColumnSize>{ConvertTo<T>(components)...})
	{
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<typename... Ts>
	constexpr Matrix<T, RowSize, ColumnSize>::Matrix(Ts&&... columns) noexcept requires (sizeof...(Ts) == ColumnSize && (std::is_convertible_v<Ts, Vector<T, RowSize>> && ...)) :
		columns{{static_cast<Vector<T, RowSize>>(std::forward<Ts>(columns))...}}
	{
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>::Matrix(const std::span<const T, RowSize * ColumnSize> span) noexcept
	{
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnSize; ++i)
			{
				columns[i] = Vector<T, RowSize>(std::span<const T, RowSize>(span.data() + i * RowSize, RowSize));
			}
		}
		else
		{
			std::memcpy(columns.data(), span.data(), sizeof(columns));
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>::Matrix(const std::mdspan<const T, std::extents<std::size_t, ColumnSize, RowSize>> span) noexcept
	{
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnSize; ++i)
			{
				for (std::size_t j = 0uz; j < RowSize; ++j)
				{
					columns[i][j] = span[i, j];
				}
			}
		}
		else
		{
			std::memcpy(columns.data(), span.data_handle(), sizeof(columns));
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>::Matrix(const std::span<const Vector<T, RowSize>, ColumnSize> span) noexcept
	{
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnSize; ++i)
			{
				columns[i] = span[i];
			}
		}
		else 
		{
			std::memcpy(columns.data(), span.data(), sizeof(columns));
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr const Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::Zero() noexcept
	{
		static constexpr auto ZeroMatrix = Matrix();

		return ZeroMatrix;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr const Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::Identity() noexcept requires (RowSize == ColumnSize)
	{
		static constexpr auto IdentityMatrix = Matrix(T{1});

		return IdentityMatrix;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T& Matrix<T, RowSize, ColumnSize>::Component(const std::size_t index) noexcept
	{
		return (*this)[index % RowSize, index / RowSize];
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr const T& Matrix<T, RowSize, ColumnSize>::Component(const std::size_t index) const noexcept
	{
		return (*this)[index % RowSize, index / RowSize];
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	std::span<T, RowSize * ColumnSize> Matrix<T, RowSize, ColumnSize>::Span() noexcept
	{
		return std::span<T, RowSize * ColumnSize>(reinterpret_cast<T*>(this), RowSize * ColumnSize);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	std::span<const T, RowSize * ColumnSize> Matrix<T, RowSize, ColumnSize>::Span() const noexcept
	{
		return std::span<const T, RowSize * ColumnSize>(reinterpret_cast<const T*>(this), RowSize * ColumnSize);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	std::mdspan<T, std::extents<std::size_t, ColumnSize, RowSize>> Matrix<T, RowSize, ColumnSize>::SpanMD() noexcept
	{
		return std::mdspan<T, std::extents<std::size_t, ColumnSize, RowSize>>(&columns[0][0], ColumnSize, RowSize);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	std::mdspan<const T, std::extents<std::size_t, ColumnSize, RowSize>> Matrix<T, RowSize, ColumnSize>::SpanMD() const noexcept
	{
		return std::mdspan<const T, std::extents<std::size_t, ColumnSize, RowSize>>(&columns[0][0], ColumnSize, RowSize);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr std::span<T, RowSize> Matrix<T, RowSize, ColumnSize>::Span(const std::size_t columnIndex) noexcept
	{
		return columns[columnIndex].Span();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr std::span<const T, RowSize> Matrix<T, RowSize, ColumnSize>::Span(const std::size_t columnIndex) const noexcept
	{
		return columns[columnIndex].Span();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, ColumnSize> Matrix<T, RowSize, ColumnSize>::Row(const std::size_t rowIndex) const noexcept
	{
		Vector<T, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer[i] = (*this)[rowIndex, i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr void Matrix<T, RowSize, ColumnSize>::Row(const std::size_t rowIndex, const Vector<T, ColumnSize>& value) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			(*this)[rowIndex, i] = value[i];
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, RowSize>& Matrix<T, RowSize, ColumnSize>::Column(const std::size_t columnIndex) noexcept
	{
		return columns[columnIndex];
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr const Vector<T, RowSize>& Matrix<T, RowSize, ColumnSize>::Column(const std::size_t columnIndex) const noexcept
	{
		return columns[columnIndex];
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr void Matrix<T, RowSize, ColumnSize>::Column(const std::size_t columnIndex, const Vector<T, RowSize>& value) noexcept
	{
		columns[columnIndex] = value;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr std::span<Vector<T, RowSize>, ColumnSize> Matrix<T, RowSize, ColumnSize>::Columns() noexcept
	{
		return columns;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr std::span<const Vector<T, RowSize>, ColumnSize> Matrix<T, RowSize, ColumnSize>::Columns() const noexcept
	{
		return columns;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, RowSize> Matrix<T, RowSize, ColumnSize>::Diagonal() const noexcept requires (RowSize == ColumnSize)
	{
		Vector<T, RowSize> answer;
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			answer[i] = (*this)[i, i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr void Matrix<T, RowSize, ColumnSize>::Diagonal(const Vector<T, RowSize>& value) noexcept requires (RowSize == ColumnSize)
	{
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			(*this)[i, i] = value[i];
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, RowSize> Matrix<T, RowSize, ColumnSize>::CounterDiagonal() const noexcept requires (RowSize == ColumnSize)
	{
		Vector<T, RowSize> answer;
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			answer[i] = (*this)[RowSize - 1uz - i, i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr void Matrix<T, RowSize, ColumnSize>::CounterDiagonal(const Vector<T, RowSize>& value) noexcept requires (RowSize == ColumnSize)
	{
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			(*this)[RowSize - 1uz - i, i] = value[i];
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Trace() const noexcept requires (RowSize == ColumnSize)
	{
		return Diagonal().Sum();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Determinant() const noexcept requires (RowSize == ColumnSize)
	{
		if constexpr (RowSize == 1uz)
		{
			return (*this)[0, 0];
		}
		else if constexpr (RowSize == 2uz)
		{
			return (*this)[0, 0] * (*this)[1, 1] - (*this)[1, 0] * (*this)[0, 1];
		}
		else if constexpr (RowSize == 3uz)
		{
			const T term0 = (*this)[0, 0] * ((*this)[1, 1] * (*this)[2, 2] - (*this)[1, 2] * (*this)[2, 1]);
			const T term1 = (*this)[0, 1] * ((*this)[1, 0] * (*this)[2, 2] - (*this)[1, 2] * (*this)[2, 0]);
			const T term2 = (*this)[0, 2] * ((*this)[1, 0] * (*this)[2, 1] - (*this)[1, 1] * (*this)[2, 0]);

			return term0 - term1 + term2;
		}
		else if constexpr (RowSize == 4uz)
		{
			const T subDet0 = (*this)[2, 2] * (*this)[3, 3] - (*this)[2, 3] * (*this)[3, 2];
			const T subDet1 = (*this)[2, 1] * (*this)[3, 3] - (*this)[2, 3] * (*this)[3, 1];
			const T subDet2 = (*this)[2, 1] * (*this)[3, 2] - (*this)[2, 2] * (*this)[3, 1];
			const T subDet3 = (*this)[2, 0] * (*this)[3, 3] - (*this)[2, 3] * (*this)[3, 0];
			const T subDet4 = (*this)[2, 0] * (*this)[3, 2] - (*this)[2, 2] * (*this)[3, 0];
			const T subDet5 = (*this)[2, 0] * (*this)[3, 1] - (*this)[2, 1] * (*this)[3, 0];

			const T det00 = (*this)[1, 1] * subDet0 - (*this)[1, 2] * subDet1 + (*this)[1, 3] * subDet2;
			const T det01 = (*this)[1, 0] * subDet0 - (*this)[1, 2] * subDet3 + (*this)[1, 3] * subDet4;
			const T det02 = (*this)[1, 0] * subDet1 - (*this)[1, 1] * subDet3 + (*this)[1, 3] * subDet5;
			const T det03 = (*this)[1, 0] * subDet2 - (*this)[1, 1] * subDet4 + (*this)[1, 2] * subDet5;

			return (*this)[0, 0] * det00 - (*this)[0, 1] * det01 + (*this)[0, 2] * det02 - (*this)[0, 3] * det03;
		}
		else
		{
			T answer = T{0};
			for (std::size_t i = 0uz; i < ColumnSize; ++i)
			{
				answer += (*this)[0, i] * Cofactor(0uz, i);
			}

			return answer;
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, ColumnSize, RowSize> Matrix<T, RowSize, ColumnSize>::Transpose() const noexcept
	{
		Matrix<T, ColumnSize, RowSize> answer;
		for (std::size_t j = 0uz; j < ColumnSize; ++j)
		{
			for (std::size_t i = 0uz; i < RowSize; ++i)
			{
				answer[j, i] = (*this)[i, j];
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, std::max(RowSize - 1uz, 1uz), std::max(ColumnSize - 1uz, 1uz)> Matrix<T, RowSize, ColumnSize>::Submatrix(const std::size_t rowIndex, const std::size_t columnIndex) const noexcept requires (RowSize > 1uz && ColumnSize > 1uz)
	{
		Matrix<T, RowSize - 1uz, ColumnSize - 1uz> answer;
		if consteval
		{
			for (std::size_t i = 0uz; i < columnIndex; ++i)
			{
				std::ranges::copy(Span(i).begin(), Span(i).begin() + rowIndex, answer.Span(i).begin());
				std::ranges::copy(Span(i).begin() + rowIndex + 1uz, Span(i).begin() + RowSize, answer.Span(i).begin() + rowIndex);
			}
			for (std::size_t i = columnIndex + 1uz; i < ColumnSize; ++i)
			{
				std::ranges::copy(Span(i).begin(), Span(i).begin() + rowIndex, answer.Span(i - 1uz).begin());
				std::ranges::copy(Span(i).begin() + rowIndex + 1uz, Span(i).begin() + RowSize, answer.Span(i - 1uz).begin() + rowIndex);
			}
		}
		else
		{
			const T* source = reinterpret_cast<const T*>(this);
			T* destination = reinterpret_cast<T*>(&answer);
			for (std::size_t i = 0uz; i < columnIndex; ++i, source += RowSize, destination += RowSize - 1uz)
			{
				std::memcpy(destination, source, rowIndex * sizeof(T));
				std::memcpy(destination + rowIndex, source + rowIndex + 1uz, (RowSize - 1uz - rowIndex) * sizeof(T));
			}
			source += RowSize;
			for (std::size_t i = columnIndex + 1uz; i < ColumnSize; ++i, source += RowSize, destination += RowSize - 1uz)
			{
				std::memcpy(destination, source, rowIndex * sizeof(T));
				std::memcpy(destination + rowIndex, source + rowIndex + 1uz, (RowSize - 1uz - rowIndex) * sizeof(T));
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, std::max(RowSize - 1uz, 1uz), ColumnSize> Matrix<T, RowSize, ColumnSize>::SubmatrixRow(const std::size_t rowIndex) const noexcept requires (RowSize > 1uz)
	{
		Matrix<T, RowSize - 1uz, ColumnSize> answer;
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnSize; ++i)
			{
				std::ranges::copy(Span(i).begin(), Span(i).begin() + rowIndex, answer.Span(i).begin());
				std::ranges::copy(Span(i).begin() + rowIndex + 1uz, Span(i).begin() + RowSize, answer.Span(i).begin() + rowIndex);
			}
		}
		else
		{
			const T* source = reinterpret_cast<const T*>(this);
			T* destination = reinterpret_cast<T*>(&answer);
			for (std::size_t i = 0uz; i < ColumnSize; ++i, source += RowSize, destination += RowSize - 1uz)
			{
				std::memcpy(destination, source, rowIndex * sizeof(T));
				std::memcpy(destination + rowIndex, source + rowIndex + 1uz, (RowSize - 1uz - rowIndex) * sizeof(T));
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, std::max(ColumnSize - 1uz, 1uz)> Matrix<T, RowSize, ColumnSize>::SubmatrixColumn(const std::size_t columnIndex) const noexcept requires (ColumnSize > 1uz)
	{
		Matrix<T, RowSize, ColumnSize - 1uz> answer;
		if consteval
		{
			for (std::size_t i = 0uz; i < columnIndex; ++i)
			{
				answer.Column(i, Column(i));
			}
			for (std::size_t i = columnIndex + 1uz; i < ColumnSize; ++i)
			{
				answer.Column(i - 1uz, Column(i));
			}
		}
		else
		{
			const Vector<T, RowSize>* const source = reinterpret_cast<const Vector<T, RowSize>*>(this);
			Vector<T, RowSize>* const destination = reinterpret_cast<Vector<T, RowSize>*>(&answer);
			std::memcpy(destination, source, columnIndex * sizeof(Vector<T, RowSize>));
			std::memcpy(destination + columnIndex, source + columnIndex + 1uz, (ColumnSize - 1uz - columnIndex) * sizeof(Vector<T, RowSize>));
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Minor(const std::size_t rowIndex, const std::size_t columnIndex) const noexcept requires (RowSize == ColumnSize && RowSize > 1uz)
	{
		return Submatrix(rowIndex, columnIndex).Determinant();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Minor(const std::size_t rowIndex) const noexcept requires (RowSize == ColumnSize + 1uz)
	{
		return SubmatrixRow(rowIndex).Determinant();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Minor(const std::size_t columnIndex) const noexcept requires (ColumnSize == RowSize + 1uz)
	{
		return SubmatrixColumn(columnIndex).Determinant();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize> Matrix<T, RowSize, ColumnSize>::MinorMatrix() const noexcept requires (RowSize == ColumnSize && RowSize > 1uz)
	{
		Matrix answer;
		for (std::size_t j = 0uz; j < ColumnSize; ++j)
		{
			for (std::size_t i = 0uz; i < RowSize; ++i)
			{
				answer[i, j] = Minor(i, j);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, RowSize> Matrix<T, RowSize, ColumnSize>::MinorVector() const noexcept requires (RowSize == ColumnSize + 1uz)
	{
		Vector<T, RowSize> answer;
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			answer[i] = Minor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, ColumnSize> Matrix<T, RowSize, ColumnSize>::MinorVector() const noexcept requires (ColumnSize == RowSize + 1uz)
	{
		Vector<T, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer[i] = Minor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Cofactor(const std::size_t rowIndex, const std::size_t columnIndex) const noexcept requires (RowSize == ColumnSize && RowSize > 1uz)
	{
		const T minor = Minor(rowIndex, columnIndex);

		return IsOdd(rowIndex + columnIndex) ? -minor : minor;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Cofactor(const std::size_t rowIndex) const noexcept requires (RowSize == ColumnSize + 1uz)
	{
		const T minor = Minor(rowIndex);

		return IsOdd(rowIndex) ? -minor : minor;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T Matrix<T, RowSize, ColumnSize>::Cofactor(const std::size_t columnIndex) const noexcept requires (ColumnSize == RowSize + 1uz)
	{
		const T minor = Minor(columnIndex);

		return IsOdd(columnIndex) ? -minor : minor;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize> Matrix<T, RowSize, ColumnSize>::CofactorMatrix() const noexcept requires (RowSize == ColumnSize && RowSize > 1uz)
	{
		Matrix answer;
		for (std::size_t j = 0uz; j < ColumnSize; ++j)
		{
			for (std::size_t i = 0uz; i < RowSize; ++i)
			{
				answer[i, j] = Cofactor(i, j);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, RowSize> Matrix<T, RowSize, ColumnSize>::CofactorVector() const noexcept requires (RowSize == ColumnSize + 1uz)
	{
		Vector<T, RowSize> answer;
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			answer[i] = Cofactor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Vector<T, ColumnSize> Matrix<T, RowSize, ColumnSize>::CofactorVector() const noexcept requires (ColumnSize == RowSize + 1uz)
	{
		Vector<T, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer[i] = Cofactor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize> Matrix<T, RowSize, ColumnSize>::Adjugate() const noexcept requires (RowSize == ColumnSize && RowSize > 1uz)
	{
		return CofactorMatrix().Transpose();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize> Matrix<T, RowSize, ColumnSize>::Inverse() const noexcept requires (std::is_floating_point_v<T> && RowSize == ColumnSize && RowSize > 1uz)
	{
		return Adjugate() * (T{1} / Determinant());
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr bool Matrix<T, RowSize, ColumnSize>::IsZero() const noexcept
	{
		return *this == Zero();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<std::same_as<T> U>
	constexpr bool Matrix<T, RowSize, ColumnSize>::IsAlmostZero(const Tolerance<U>& tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Zero(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr bool Matrix<T, RowSize, ColumnSize>::IsIdentity() const noexcept requires (RowSize == ColumnSize)
	{
		return *this == Identity();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<std::same_as<T> U>
	constexpr bool Matrix<T, RowSize, ColumnSize>::IsAlmostIdentity(const Tolerance<U>& tolerance) const noexcept requires (std::is_floating_point_v<T> && RowSize == ColumnSize)
	{
		return AreAlmostEqual(*this, Identity(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr bool Matrix<T, RowSize, ColumnSize>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			if (!Column(i).IsFinite())
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr void Matrix<T, RowSize, ColumnSize>::Multiply(const Matrix& multiplier) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i).Multiply(multiplier.Column(i));
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr void Matrix<T, RowSize, ColumnSize>::Divide(const Matrix& divisor) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i).Divide(divisor.Column(i));
		}
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	std::string Matrix<T, RowSize, ColumnSize>::ToString(const bool multiline) const
	{
		std::string answer;
		for (std::size_t i = 0uz; i < RowSize; ++i)
		{
			answer += '[';
			for (std::size_t j = 0uz; j < ColumnSize; ++j)
			{
				answer += std::format("{}", (*this)[i, j]);
				if (j < ColumnSize - 1uz)
				{
					answer += ", ";
				}
			}
			answer += ']';
			if (multiline)
			{
				answer += '\n';
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<Type::Arithmetic U>
	constexpr Matrix<T, RowSize, ColumnSize>::operator Matrix<U, RowSize, ColumnSize>() const noexcept
	{
		Matrix<U, RowSize, ColumnSize> answer;
		for (std::size_t j = 0uz; j < ColumnSize; ++j)
		{
			for (std::size_t i = 0uz; i < RowSize; ++i)
			{
				answer[i, j] = static_cast<U>((*this)[i, j]);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr T& Matrix<T, RowSize, ColumnSize>::operator [](const std::size_t rowIndex, const std::size_t columnIndex) noexcept
	{
		return columns[columnIndex][rowIndex];
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr const T& Matrix<T, RowSize, ColumnSize>::operator [](const std::size_t rowIndex, const std::size_t columnIndex) const noexcept
	{
		return columns[columnIndex][rowIndex];
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator +=(const Matrix& other) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i) += other.Column(i);
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator -=(const Matrix& other) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i) -= other.Column(i);
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i) *= multiplier;
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<std::floating_point U>
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator *=(const U multiplier) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i) *= multiplier;
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator *=(const Matrix& other) noexcept requires (RowSize == ColumnSize)
	{
		return *this = *this * other;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i) /= divisor;
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize> requires (RowSize >= 1uz && ColumnSize >= 1uz)
	template<std::floating_point U>
	constexpr Matrix<T, RowSize, ColumnSize>& Matrix<T, RowSize, ColumnSize>::operator /=(const U divisor) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			Column(i) /= divisor;
		}

		return *this;
	}

	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr bool IsFinite(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		return matrix.IsFinite();
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> Multiply(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = Multiply(lhs.Column(i), rhs.Column(i));
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> Divide(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = Divide(lhs.Column(i), rhs.Column(i));
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize, std::size_t RightColumnSize>
	constexpr Matrix<T, RowSize, RightColumnSize> MultiplyTranspose(const Matrix<T, ColumnSize, RowSize>& lhs, const Matrix<T, ColumnSize, RightColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz && RightColumnSize >= 1uz)
	{
		Matrix<T, RowSize, RightColumnSize> answer;
		for (std::size_t j = 0uz; j < RightColumnSize; ++j)
		{
			for (std::size_t i = 0uz; i < RowSize; ++i)
			{
				answer[i, j] = Dot(lhs.Column(i), rhs.Column(j));
			}
		}

		return answer;
	}

	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> Abs(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i, Abs(matrix.Column(i)));
		}

		return answer;
	}

	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize>
	Matrix<T, RowSize, ColumnSize> NormalizeColumns(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i, matrix.Column(i).Normalized());
		}

		return answer;
	}

	template<std::floating_point T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr bool AreAlmostEqual(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs, const Tolerance<T>& tolerance) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			if (!AreAlmostEqual(lhs.Column(i), rhs.Column(i), tolerance))
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator +(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = lhs.Column(i) + rhs.Column(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator -(const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = -matrix.Column(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator -(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, RowSize, ColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = lhs.Column(i) - rhs.Column(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator *(const Matrix<T, RowSize, ColumnSize>& matrix, const T multiplier) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = matrix.Column(i) * multiplier;
		}

		return answer;
	}

	template<std::floating_point U, std::integral T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator *(const Matrix<T, RowSize, ColumnSize>& matrix, const U multiplier) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = matrix.Column(i) * multiplier;
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator *(const T multiplier, const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		return matrix * multiplier;
	}

	template<std::floating_point U, std::integral T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator *(const U multiplier, const Matrix<T, RowSize, ColumnSize>& matrix) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		return matrix * multiplier;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize, std::size_t RightColumnSize>
	constexpr Matrix<T, RowSize, RightColumnSize> operator *(const Matrix<T, RowSize, ColumnSize>& lhs, const Matrix<T, ColumnSize, RightColumnSize>& rhs) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz && RightColumnSize >= 1uz)
	{
		return MultiplyTranspose(lhs.Transpose(), rhs);
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Vector<T, RowSize> operator *(const Matrix<T, RowSize, ColumnSize>& matrix, const Vector<T, ColumnSize>& vector) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		auto answer = Vector<T, RowSize>::Zero();
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer += matrix.Column(i) * vector[i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator /(const Matrix<T, RowSize, ColumnSize>& matrix, const T divisor) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = matrix.Column(i) / divisor;
		}

		return answer;
	}

	template<std::floating_point U, std::integral T, std::size_t RowSize, std::size_t ColumnSize>
	constexpr Matrix<T, RowSize, ColumnSize> operator /(const Matrix<T, RowSize, ColumnSize>& matrix, const U divisor) noexcept requires (RowSize >= 1uz && ColumnSize >= 1uz)
	{
		Matrix<T, RowSize, ColumnSize> answer;
		for (std::size_t i = 0uz; i < ColumnSize; ++i)
		{
			answer.Column(i) = matrix.Column(i) / divisor;
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowSize, std::size_t ColumnSize>
	std::ostream& operator <<(std::ostream& stream, const Matrix<T, RowSize, ColumnSize>& matrix)
	{
		return stream << matrix.ToString();
	}
}
