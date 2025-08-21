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
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	class Matrix final
	{
	public:
		using ValueType = T; ///< Component type.
		using ColumnType = Vector<T, RowCount>; ///< Column type.

		static constexpr std::size_t Rows = RowCount; ///< Row count.
		static constexpr std::size_t Columns = ColumnCount; ///< Column count.
		static constexpr std::size_t ComponentCount = Rows * Columns; ///< Component count.
		static constexpr bool IsSquare = Rows == Columns; ///< Is the matrix square?

		/// @brief Creates a zero matrix.
		[[nodiscard("Pure constructor")]]
		constexpr Matrix() noexcept = default;
		/// @brief Creates a matrix and sets each diagonal component to the @p value.
		/// @param value Diagonal component value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(T value) noexcept requires(RowCount == ColumnCount);
		/// @brief Creates a matrix and assigns its components from the arguments.
		/// @tparam Ts Component types.
		/// @param components Matrix components
		template<Type::Arithmetic... Ts> [[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(Ts... components) noexcept requires (sizeof...(Ts) == RowCount * ColumnCount);
		/// @brief Creates a matrix and assigns its columns from the arguments.
		/// @tparam Ts Column types.
		/// @param columns Matrix columns.
		template<typename... Ts> [[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(Ts&&... columns) noexcept requires (sizeof...(Ts) == ColumnCount && (std::is_convertible_v<Ts, Vector<T, RowCount>> && ...));
		/// @brief Creates a matrix and assigns its components from the @p span.
		/// @param span Components.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(std::span<const T, RowCount * ColumnCount> span) noexcept;
		/// @brief Creates a matrix and assigns its components from the @p span.
		/// @param span Components.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(std::mdspan<const T, std::extents<std::size_t, ColumnCount, RowCount>> span) noexcept;
		/// @brief Creates a matrix and assigns its columns from the @p span.
		/// @param span Columns.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Matrix(std::span<const Vector<T, RowCount>, ColumnCount> span) noexcept;
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
		static constexpr const Matrix& Identity() noexcept requires (RowCount == ColumnCount);

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
		std::span<T, RowCount * ColumnCount> Span() noexcept;
		/// @brief Gets the matrix span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<const T, RowCount * ColumnCount> Span() const noexcept;
		/// @brief Gets the matrix span.
		/// @remark The indexing of this span is [ColumnIndex, RowIndex].
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::mdspan<T, std::extents<std::size_t, ColumnCount, RowCount>> SpanMD() noexcept;
		/// @brief Gets the matrix span.
		/// @remark The indexing of this span is [ColumnIndex, RowIndex].
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::mdspan<const T, std::extents<std::size_t, ColumnCount, RowCount>> SpanMD() const noexcept;
		/// @brief Gets a column span.
		/// @param columnIndex Column index.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, RowCount> Span(std::size_t columnIndex) noexcept;
		/// @brief Gets a column span.
		/// @param columnIndex Column index.
		/// @return Span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, RowCount> Span(std::size_t columnIndex) const noexcept;

		/// @brief Gets a row by the @p rowIndex.
		/// @param rowIndex Row index.
		/// @return Row.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, ColumnCount> Row(std::size_t rowIndex) const noexcept;
		/// @brief Sets a row by the @p rowIndex.
		/// @param rowIndex Row index.
		/// @param value Row components.
		constexpr void Row(std::size_t rowIndex, const Vector<T, ColumnCount>& value) noexcept;
		/// @brief Gets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowCount>& Column(std::size_t columnIndex) noexcept;
		/// @brief Gets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @return Column.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, RowCount>& Column(std::size_t columnIndex) const noexcept;
		/// @brief Sets a column by the @p columnIndex.
		/// @param columnIndex Column index.
		/// @param value Column components.
		constexpr void Column(std::size_t columnIndex, const Vector<T, RowCount>& value) noexcept;

		/// @brief Gets the diagonal.
		/// @return Diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowCount> Diagonal() const noexcept requires (RowCount == ColumnCount);
		/// @brief Sets the diagonal.
		/// @param value Diagonal components.
		constexpr void Diagonal(const Vector<T, RowCount>& value) noexcept requires (RowCount == ColumnCount);
		/// @brief Gets the counter-diagonal.
		/// @return Counter-diagonal.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowCount> CounterDiagonal() const noexcept requires (RowCount == ColumnCount);
		/// @brief Sets the counter-diagonal.
		/// @param value Counter=diagonal components.
		constexpr void CounterDiagonal(const Vector<T, RowCount>& value) noexcept requires (RowCount == ColumnCount);

		/// @brief Computes a trace of the matrix.
		/// @return Trace of the matrix.
		[[nodiscard("Pure function")]]
		constexpr T Trace() const noexcept requires (RowCount == ColumnCount);
		/// @brief Computes a determinant of the matrix.
		/// @return Determinant.
		[[nodiscard("Pure function")]]
		constexpr T Determinant() const noexcept requires (RowCount == ColumnCount);

		/// @brief Computes a transpose of the matrix.
		/// @return Transpose.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, ColumnCount, RowCount> Transpose() const noexcept;
		/// @brief Computes a submatrix.
		/// @param rowIndex Index of a row to remove.
		/// @param columnIndex Index of a column to remove.
		/// @return Submatrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, std::max(RowCount - 1uz, 1uz), std::max(ColumnCount - 1uz, 1uz)> Submatrix(std::size_t rowIndex, std::size_t columnIndex) const noexcept requires (RowCount > 1uz && ColumnCount > 1uz);
		/// @brief Computes a submatrix.
		/// @param rowIndex Index of a row to remove.
		/// @return Submatrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, std::max(RowCount - 1uz, 1uz), ColumnCount> SubmatrixRow(std::size_t rowIndex) const noexcept requires (RowCount > 1uz);
		/// @brief Computes a submatrix.
		/// @param columnIndex Index of a column to remove.
		/// @return Submatrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix<T, RowCount, std::max(ColumnCount - 1uz, 1uz)> SubmatrixColumn(std::size_t columnIndex) const noexcept requires (ColumnCount > 1uz);

		/// @brief Computes a minor.
		/// @param rowIndex Minor row index.
		/// @param columnIndex Minor column index
		/// @return Minor.
		[[nodiscard("Pure function")]]
		constexpr T Minor(std::size_t rowIndex, std::size_t columnIndex) const noexcept requires (RowCount == ColumnCount && RowCount > 1uz);
		/// @brief Computes a minor.
		/// @param rowIndex Minor row index.
		/// @return Minor.
		[[nodiscard("Pure function")]]
		constexpr T Minor(std::size_t rowIndex) const noexcept requires (RowCount == ColumnCount + 1uz);
		/// @brief Computes a minor.
		/// @param columnIndex Minor column index
		/// @return Minor.
		[[nodiscard("Pure function")]]
		constexpr T Minor(std::size_t columnIndex) const noexcept requires (ColumnCount == RowCount + 1uz);
		/// @brief Computes a minor matrix.
		/// @return Minor matrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix MinorMatrix() const noexcept requires (RowCount == ColumnCount && RowCount > 1uz);
		/// @brief Computes a minor vector.
		/// @return Minor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowCount> MinorVector() const noexcept requires (RowCount == ColumnCount + 1uz);
		/// @brief Computes a minor vector.
		/// @return Minor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, ColumnCount> MinorVector() const noexcept requires (ColumnCount == RowCount + 1uz);
		/// @brief Computes a cofactor.
		/// @param rowIndex Cofactor row index.
		/// @param columnIndex Cofactor column index
		/// @return Cofactor.
		[[nodiscard("Pure function")]]
		constexpr T Cofactor(std::size_t rowIndex, std::size_t columnIndex) const noexcept requires (RowCount == ColumnCount && RowCount > 1uz);
		/// @brief Computes a cofactor.
		/// @param rowIndex Cofactor row index.
		/// @return Cofactor.
		[[nodiscard("Pure function")]]
		constexpr T Cofactor(std::size_t rowIndex) const noexcept requires (RowCount == ColumnCount + 1uz);
		/// @brief Computes a cofactor.
		/// @param columnIndex Cofactor column index
		/// @return Cofactor.
		[[nodiscard("Pure function")]]
		constexpr T Cofactor(std::size_t columnIndex) const noexcept requires (ColumnCount == RowCount + 1uz);
		/// @brief Computes a cofactor matrix.
		/// @return Cofactor matrix.
		[[nodiscard("Pure function")]]
		constexpr Matrix CofactorMatrix() const noexcept requires (RowCount == ColumnCount && RowCount > 1uz);
		/// @brief Computes a cofactor vector.
		/// @return Cofactor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, RowCount> CofactorVector() const noexcept requires (RowCount == ColumnCount + 1uz);
		/// @brief Computes a cofactor vector.
		/// @return Cofactor vector.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, ColumnCount> CofactorVector() const noexcept requires (ColumnCount == RowCount + 1uz);
		/// @brief Computes an adjugate of the matrix.
		/// @return Adjugate.
		[[nodiscard("Pure function")]]
		constexpr Matrix Adjugate() const noexcept requires (RowCount == ColumnCount && RowCount > 1uz);
		/// @brief Computes an inverse of the matrix.
		/// @return Inverse.
		[[nodiscard("Pure function")]]
		constexpr Matrix Inverse() const noexcept requires (std::is_floating_point_v<T> && RowCount == ColumnCount && RowCount > 1uz);

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
		constexpr bool IsIdentity() const noexcept requires (RowCount == ColumnCount);
		/// @brief Checks if this matrix is almost equal to the identity matrix with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if this matrix is almost equal to the identity matrix; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostIdentity(T tolerance = T{0.00001}) const noexcept requires (std::is_floating_point_v<T> && RowCount == ColumnCount);

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
		explicit constexpr operator Matrix<U, RowCount, ColumnCount>() const noexcept;

		/// @brief Gets a component by indices.
		/// @param rowIndex Row index. Must be in range [0, RowCount).
		/// @param columnIndex Column index. Must be in range [0, ColumnCount).
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
		constexpr Matrix& operator *=(const Matrix& other) noexcept requires (RowCount == ColumnCount);
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
		std::array<Vector<T, RowCount>, ColumnCount> columns; ///< Matrix columns.
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
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Matrix to check.
	/// @return @a True if all the components are finite; @a false otherwise.
	template<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure function")]]
	constexpr bool IsFinite(const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Multiplies the @p lhs matrix by the @p rhs matrix component-wise.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure function")]]
	constexpr Matrix<T, RowCount, ColumnCount> Multiply(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);
	/// @brief Divides the @p lhs matrix by the @p rhs matrix component-wise.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param lhs Dividend.
	/// @param rhs Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure function")]]
	constexpr Matrix<T, RowCount, ColumnCount> Divide(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Normalizes the columns of the @p matrix.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Matrix to normalize.
	/// @return Normalized matrix.
	template<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure function")]]
	Matrix<T, RowCount, ColumnCount> NormalizeColumns(const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Checks if the two matrices are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param lhs Left matrix.
	/// @param rhs Right matrix.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the matrices are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs, T tolerance = T{0.00001}) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Sums the @p lhs and @p rhs.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param lhs Augend.
	/// @param rhs Addend.
	/// @return Sum.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator +(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Negates the @p matrix.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Matrix to negate.
	/// @return Negated matrix.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator -(const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);
	/// @brief Subtracts the @p rhs matrix from the @p lhs matrix.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param lhs Minuend.
	/// @param rhs Subtrahend.
	/// @return Difference.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator -(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator *(const Matrix<T, RowCount, ColumnCount>& matrix, T multiplier) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam U Multiplier type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point U = double, std::integral T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator *(const Matrix<T, RowCount, ColumnCount>& matrix, U multiplier) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator *(T multiplier, const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);
	/// @brief Multiplies the @p matrix components by the @p multiplier.
	/// @tparam T Component type.
	/// @tparam U Multiplier type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point U = double, std::integral T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator *(U multiplier, const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Multiplies the @p lhs matrix by the @p rhs matrix.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @tparam RightColumnCount Right matrix column count.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, std::size_t RightColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, RightColumnCount> operator *(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, ColumnCount, RightColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz && RightColumnCount >= 1uz);
	/// @brief Multiplies the @p matrix by the @p vector.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Matrix.
	/// @param vector Vector.
	/// @return Product vector.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Vector<T, RowCount> operator *(const Matrix<T, RowCount, ColumnCount>& matrix, const Vector<T, ColumnCount>& vector) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator /(const Matrix<T, RowCount, ColumnCount>& matrix, T divisor) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);
	/// @brief Divides the @p matrix by the @p divisor.
	/// @tparam T Component type.
	/// @tparam U Divisor type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param matrix Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point U = double, std::integral T, std::size_t RowCount, std::size_t ColumnCount> [[nodiscard("Pure operator")]]
	constexpr Matrix<T, RowCount, ColumnCount> operator /(const Matrix<T, RowCount, ColumnCount>& matrix, U divisor) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz);

	/// @brief Outputs a string representation of the @p matrix.
	/// @tparam T Component type.
	/// @tparam RowCount Row count.
	/// @tparam ColumnCount Column count.
	/// @param stream Target.
	/// @param matrix Matrix.
	/// @return @p stream.
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	std::ostream& operator <<(std::ostream& stream, const Matrix<T, RowCount, ColumnCount>& matrix);
}

/// @brief Matrix formatter.
/// @tparam T Component type.
/// @tparam RowCount Row count.
/// @tparam ColumnCount Column count.
/// @note Parameters :m or :M produce a multiline string; without them, the result will be a single line string.
export template<PonyEngine::Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
struct std::formatter<PonyEngine::Math::Matrix<T, RowCount, ColumnCount>, char>
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

	auto format(const PonyEngine::Math::Matrix<T, RowCount, ColumnCount>& matrix, std::format_context& context) const
	{
		return std::ranges::copy(matrix.ToString(multiline), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>::Matrix(const T value) noexcept requires (RowCount == ColumnCount) :
		Matrix()
	{
		Diagonal(Vector<T, RowCount>(value));
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	template<Type::Arithmetic... Ts>
	constexpr Matrix<T, RowCount, ColumnCount>::Matrix(Ts... components) noexcept requires (sizeof...(Ts) == RowCount * ColumnCount) :
		Matrix(std::array<T, RowCount * ColumnCount>{ConvertTo<T>(components)...})
	{
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	template<typename... Ts>
	constexpr Matrix<T, RowCount, ColumnCount>::Matrix(Ts&&... columns) noexcept requires (sizeof...(Ts) == ColumnCount && (std::is_convertible_v<Ts, Vector<T, RowCount>> && ...)) :
		columns{{static_cast<Vector<T, RowCount>>(std::forward<Ts>(columns))...}}
	{
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>::Matrix(const std::span<const T, RowCount * ColumnCount> span) noexcept
	{
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnCount; ++i)
			{
				columns[i] = Vector<T, RowCount>(std::span<const T, RowCount>(span.data() + i * RowCount, RowCount));
			}
		}
		else
		{
			std::memcpy(columns.data(), span.data(), sizeof(columns));
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>::Matrix(const std::mdspan<const T, std::extents<std::size_t, ColumnCount, RowCount>> span) noexcept
	{
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnCount; ++i)
			{
				for (std::size_t j = 0uz; j < RowCount; ++j)
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

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>::Matrix(const std::span<const Vector<T, RowCount>, ColumnCount> span) noexcept
	{
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnCount; ++i)
			{
				columns[i] = span[i];
			}
		}
		else 
		{
			std::memcpy(columns.data(), span.data(), sizeof(columns));
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr const Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::Zero() noexcept
	{
		static constexpr auto ZeroMatrix = Matrix();

		return ZeroMatrix;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr const Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::Identity() noexcept requires (RowCount == ColumnCount)
	{
		static constexpr auto IdentityMatrix = Matrix(T{1});

		return IdentityMatrix;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T& Matrix<T, RowCount, ColumnCount>::Component(const std::size_t index) noexcept
	{
		return (*this)[index % RowCount, index / RowCount];
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr const T& Matrix<T, RowCount, ColumnCount>::Component(const std::size_t index) const noexcept
	{
		return (*this)[index % RowCount, index / RowCount];
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	std::span<T, RowCount * ColumnCount> Matrix<T, RowCount, ColumnCount>::Span() noexcept
	{
		return std::span<T, RowCount * ColumnCount>(reinterpret_cast<T*>(this), RowCount * ColumnCount);
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	std::span<const T, RowCount * ColumnCount> Matrix<T, RowCount, ColumnCount>::Span() const noexcept
	{
		return std::span<const T, RowCount * ColumnCount>(reinterpret_cast<const T*>(this), RowCount * ColumnCount);
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	std::mdspan<T, std::extents<std::size_t, ColumnCount, RowCount>> Matrix<T, RowCount, ColumnCount>::SpanMD() noexcept
	{
		return std::mdspan<T, std::extents<std::size_t, ColumnCount, RowCount>>(&columns[0][0], ColumnCount, RowCount);
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	std::mdspan<const T, std::extents<std::size_t, ColumnCount, RowCount>> Matrix<T, RowCount, ColumnCount>::SpanMD() const noexcept
	{
		return std::mdspan<const T, std::extents<std::size_t, ColumnCount, RowCount>>(&columns[0][0], ColumnCount, RowCount);
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr std::span<T, RowCount> Matrix<T, RowCount, ColumnCount>::Span(const std::size_t columnIndex) noexcept
	{
		return columns[columnIndex].Span();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr std::span<const T, RowCount> Matrix<T, RowCount, ColumnCount>::Span(const std::size_t columnIndex) const noexcept
	{
		return columns[columnIndex].Span();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, ColumnCount> Matrix<T, RowCount, ColumnCount>::Row(const std::size_t rowIndex) const noexcept
	{
		Vector<T, ColumnCount> answer;
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			answer[i] = (*this)[rowIndex, i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr void Matrix<T, RowCount, ColumnCount>::Row(const std::size_t rowIndex, const Vector<T, ColumnCount>& value) noexcept
	{
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			(*this)[rowIndex, i] = value[i];
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, RowCount>& Matrix<T, RowCount, ColumnCount>::Column(const std::size_t columnIndex) noexcept
	{
		return columns[columnIndex];
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr const Vector<T, RowCount>& Matrix<T, RowCount, ColumnCount>::Column(const std::size_t columnIndex) const noexcept
	{
		return columns[columnIndex];
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr void Matrix<T, RowCount, ColumnCount>::Column(const std::size_t columnIndex, const Vector<T, RowCount>& value) noexcept
	{
		columns[columnIndex] = value;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, RowCount> Matrix<T, RowCount, ColumnCount>::Diagonal() const noexcept requires (RowCount == ColumnCount)
	{
		Vector<T, RowCount> answer;
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			answer[i] = (*this)[i, i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr void Matrix<T, RowCount, ColumnCount>::Diagonal(const Vector<T, RowCount>& value) noexcept requires (RowCount == ColumnCount)
	{
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			(*this)[i, i] = value[i];
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, RowCount> Matrix<T, RowCount, ColumnCount>::CounterDiagonal() const noexcept requires (RowCount == ColumnCount)
	{
		Vector<T, RowCount> answer;
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			answer[i] = (*this)[RowCount - 1uz - i, i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr void Matrix<T, RowCount, ColumnCount>::CounterDiagonal(const Vector<T, RowCount>& value) noexcept requires (RowCount == ColumnCount)
	{
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			(*this)[RowCount - 1uz - i, i] = value[i];
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Trace() const noexcept requires (RowCount == ColumnCount)
	{
		return Diagonal().Sum();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Determinant() const noexcept requires (RowCount == ColumnCount)
	{
		if constexpr (RowCount == 1uz)
		{
			return (*this)[0, 0];
		}
		else if constexpr (RowCount == 2uz)
		{
			return (*this)[0, 0] * (*this)[1, 1] - (*this)[1, 0] * (*this)[0, 1];
		}
		else if constexpr (RowCount == 3uz)
		{
			const T term0 = (*this)[0, 0] * ((*this)[1, 1] * (*this)[2, 2] - (*this)[1, 2] * (*this)[2, 1]);
			const T term1 = (*this)[0, 1] * ((*this)[1, 0] * (*this)[2, 2] - (*this)[1, 2] * (*this)[2, 0]);
			const T term2 = (*this)[0, 2] * ((*this)[1, 0] * (*this)[2, 1] - (*this)[1, 1] * (*this)[2, 0]);

			return term0 - term1 + term2;
		}
		else if constexpr (RowCount == 4uz)
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
			for (std::size_t i = 0uz; i < ColumnCount; ++i)
			{
				answer += (*this)[0, i] * Cofactor(0uz, i);
			}

			return answer;
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, ColumnCount, RowCount> Matrix<T, RowCount, ColumnCount>::Transpose() const noexcept
	{
		Matrix<T, ColumnCount, RowCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[j, i] = (*this)[i, j];
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, std::max(RowCount - 1uz, 1uz), std::max(ColumnCount - 1uz, 1uz)> Matrix<T, RowCount, ColumnCount>::Submatrix(const std::size_t rowIndex, const std::size_t columnIndex) const noexcept requires (RowCount > 1uz && ColumnCount > 1uz)
	{
		Matrix<T, RowCount - 1uz, ColumnCount - 1uz> answer;
		if consteval
		{
			for (std::size_t i = 0uz; i < columnIndex; ++i)
			{
				std::ranges::copy(Span(i).begin(), Span(i).begin() + rowIndex, answer.Span(i).begin());
				std::ranges::copy(Span(i).begin() + rowIndex + 1uz, Span(i).begin() + RowCount, answer.Span(i).begin() + rowIndex);
			}
			for (std::size_t i = columnIndex + 1uz; i < ColumnCount; ++i)
			{
				std::ranges::copy(Span(i).begin(), Span(i).begin() + rowIndex, answer.Span(i - 1uz).begin());
				std::ranges::copy(Span(i).begin() + rowIndex + 1uz, Span(i).begin() + RowCount, answer.Span(i - 1uz).begin() + rowIndex);
			}
		}
		else
		{
			const T* source = reinterpret_cast<const T*>(this);
			T* destination = reinterpret_cast<T*>(&answer);
			for (std::size_t i = 0uz; i < columnIndex; ++i, source += RowCount, destination += RowCount - 1uz)
			{
				std::memcpy(destination, source, rowIndex * sizeof(T));
				std::memcpy(destination + rowIndex, source + rowIndex + 1uz, (RowCount - 1uz - rowIndex) * sizeof(T));
			}
			source += RowCount;
			for (std::size_t i = columnIndex + 1uz; i < ColumnCount; ++i, source += RowCount, destination += RowCount - 1uz)
			{
				std::memcpy(destination, source, rowIndex * sizeof(T));
				std::memcpy(destination + rowIndex, source + rowIndex + 1uz, (RowCount - 1uz - rowIndex) * sizeof(T));
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, std::max(RowCount - 1uz, 1uz), ColumnCount> Matrix<T, RowCount, ColumnCount>::SubmatrixRow(const std::size_t rowIndex) const noexcept requires (RowCount > 1uz)
	{
		Matrix<T, RowCount - 1uz, ColumnCount> answer;
		if consteval
		{
			for (std::size_t i = 0uz; i < ColumnCount; ++i)
			{
				std::ranges::copy(Span(i).begin(), Span(i).begin() + rowIndex, answer.Span(i).begin());
				std::ranges::copy(Span(i).begin() + rowIndex + 1uz, Span(i).begin() + RowCount, answer.Span(i).begin() + rowIndex);
			}
		}
		else
		{
			const T* source = reinterpret_cast<const T*>(this);
			T* destination = reinterpret_cast<T*>(&answer);
			for (std::size_t i = 0uz; i < ColumnCount; ++i, source += RowCount, destination += RowCount - 1uz)
			{
				std::memcpy(destination, source, rowIndex * sizeof(T));
				std::memcpy(destination + rowIndex, source + rowIndex + 1uz, (RowCount - 1uz - rowIndex) * sizeof(T));
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, std::max(ColumnCount - 1uz, 1uz)> Matrix<T, RowCount, ColumnCount>::SubmatrixColumn(const std::size_t columnIndex) const noexcept requires (ColumnCount > 1uz)
	{
		Matrix<T, RowCount, ColumnCount - 1uz> answer;
		if consteval
		{
			for (std::size_t i = 0uz; i < columnIndex; ++i)
			{
				answer.Column(i, Column(i));
			}
			for (std::size_t i = columnIndex + 1uz; i < ColumnCount; ++i)
			{
				answer.Column(i - 1uz, Column(i));
			}
		}
		else
		{
			const Vector<T, RowCount>* const source = reinterpret_cast<const Vector<T, RowCount>*>(this);
			Vector<T, RowCount>* const destination = reinterpret_cast<Vector<T, RowCount>*>(&answer);
			std::memcpy(destination, source, columnIndex * sizeof(Vector<T, RowCount>));
			std::memcpy(destination + columnIndex, source + columnIndex + 1uz, (ColumnCount - 1uz - columnIndex) * sizeof(Vector<T, RowCount>));
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Minor(const std::size_t rowIndex, const std::size_t columnIndex) const noexcept requires (RowCount == ColumnCount && RowCount > 1uz)
	{
		return Submatrix(rowIndex, columnIndex).Determinant();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Minor(const std::size_t rowIndex) const noexcept requires (RowCount == ColumnCount + 1uz)
	{
		return SubmatrixRow(rowIndex).Determinant();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Minor(const std::size_t columnIndex) const noexcept requires (ColumnCount == RowCount + 1uz)
	{
		return SubmatrixColumn(columnIndex).Determinant();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount> Matrix<T, RowCount, ColumnCount>::MinorMatrix() const noexcept requires (RowCount == ColumnCount && RowCount > 1uz)
	{
		Matrix answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = Minor(i, j);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, RowCount> Matrix<T, RowCount, ColumnCount>::MinorVector() const noexcept requires (RowCount == ColumnCount + 1uz)
	{
		Vector<T, RowCount> answer;
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			answer[i] = Minor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, ColumnCount> Matrix<T, RowCount, ColumnCount>::MinorVector() const noexcept requires (ColumnCount == RowCount + 1uz)
	{
		Vector<T, ColumnCount> answer;
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			answer[i] = Minor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Cofactor(const std::size_t rowIndex, const std::size_t columnIndex) const noexcept requires (RowCount == ColumnCount && RowCount > 1uz)
	{
		const T minor = Minor(rowIndex, columnIndex);

		return IsOdd(rowIndex + columnIndex) ? -minor : minor;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Cofactor(const std::size_t rowIndex) const noexcept requires (RowCount == ColumnCount + 1uz)
	{
		const T minor = Minor(rowIndex);

		return IsOdd(rowIndex) ? -minor : minor;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T Matrix<T, RowCount, ColumnCount>::Cofactor(const std::size_t columnIndex) const noexcept requires (ColumnCount == RowCount + 1uz)
	{
		const T minor = Minor(columnIndex);

		return IsOdd(columnIndex) ? -minor : minor;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount> Matrix<T, RowCount, ColumnCount>::CofactorMatrix() const noexcept requires (RowCount == ColumnCount && RowCount > 1uz)
	{
		Matrix answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = Cofactor(i, j);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, RowCount> Matrix<T, RowCount, ColumnCount>::CofactorVector() const noexcept requires (RowCount == ColumnCount + 1uz)
	{
		Vector<T, RowCount> answer;
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			answer[i] = Cofactor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Vector<T, ColumnCount> Matrix<T, RowCount, ColumnCount>::CofactorVector() const noexcept requires (ColumnCount == RowCount + 1uz)
	{
		Vector<T, ColumnCount> answer;
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			answer[i] = Cofactor(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount> Matrix<T, RowCount, ColumnCount>::Adjugate() const noexcept requires (RowCount == ColumnCount && RowCount > 1uz)
	{
		return CofactorMatrix().Transpose();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount> Matrix<T, RowCount, ColumnCount>::Inverse() const noexcept requires (std::is_floating_point_v<T> && RowCount == ColumnCount && RowCount > 1uz)
	{
		return Adjugate() * (T{1} / Determinant());
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr bool Matrix<T, RowCount, ColumnCount>::IsZero() const noexcept
	{
		return *this == Zero();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr bool Matrix<T, RowCount, ColumnCount>::IsAlmostZero(const T tolerance) const noexcept requires (std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Zero(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr bool Matrix<T, RowCount, ColumnCount>::IsIdentity() const noexcept requires (RowCount == ColumnCount)
	{
		return *this == Identity();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr bool Matrix<T, RowCount, ColumnCount>::IsAlmostIdentity(const T tolerance) const noexcept requires (std::is_floating_point_v<T> && RowCount == ColumnCount)
	{
		return AreAlmostEqual(*this, Identity(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr bool Matrix<T, RowCount, ColumnCount>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				if (!Math::IsFinite((*this)[i, j]))
				{
					return false;
				}
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr void Matrix<T, RowCount, ColumnCount>::Multiply(const Matrix& multiplier) noexcept
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] *= multiplier[i, j];
			}
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr void Matrix<T, RowCount, ColumnCount>::Divide(const Matrix& divisor) noexcept
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] /= divisor[i, j];
			}
		}
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	std::string Matrix<T, RowCount, ColumnCount>::ToString(const bool multiline) const
	{
		std::string answer;
		for (std::size_t i = 0uz; i < RowCount; ++i)
		{
			answer += '[';
			for (std::size_t j = 0uz; j < ColumnCount; ++j)
			{
				answer += std::format("{}", (*this)[i, j]);
				if (j < ColumnCount - 1uz)
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

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	template<Type::Arithmetic U>
	constexpr Matrix<T, RowCount, ColumnCount>::operator Matrix<U, RowCount, ColumnCount>() const noexcept
	{
		Matrix<U, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = static_cast<U>((*this)[i, j]);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr T& Matrix<T, RowCount, ColumnCount>::operator [](const std::size_t rowIndex, const std::size_t columnIndex) noexcept
	{
		return columns[columnIndex][rowIndex];
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr const T& Matrix<T, RowCount, ColumnCount>::operator [](const std::size_t rowIndex, const std::size_t columnIndex) const noexcept
	{
		return columns[columnIndex][rowIndex];
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator +=(const Matrix& other) noexcept
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] += other[i, j];
			}
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator -=(const Matrix& other) noexcept
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] -= other[i, j];
			}
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] *= multiplier;
			}
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	template<std::floating_point U>
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator *=(const U multiplier) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] = static_cast<T>((*this)[i, j] * multiplier);
			}
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator *=(const Matrix& other) noexcept requires (RowCount == ColumnCount)
	{
		return *this = *this * other;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator /=(const T divisor) noexcept
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] /= divisor;
			}
		}

		return *this;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount> requires (RowCount >= 1uz && ColumnCount >= 1uz)
	template<std::floating_point U>
	constexpr Matrix<T, RowCount, ColumnCount>& Matrix<T, RowCount, ColumnCount>::operator /=(const U divisor) noexcept requires (std::is_integral_v<T>)
	{
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				(*this)[i, j] = static_cast<T>((*this)[i, j] / divisor);
			}
		}

		return *this;
	}

	template<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr bool IsFinite(const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		return matrix.IsFinite();
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> Multiply(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = lhs[i, j] * rhs[i, j];
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> Divide(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = lhs[i, j] / rhs[i, j];
			}
		}

		return answer;
	}

	template<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount>
	Matrix<T, RowCount, ColumnCount> NormalizeColumns(const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			answer.Column(i, matrix.Column(i).Normalized());
		}

		return answer;
	}

	template<std::floating_point T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr bool AreAlmostEqual(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs, const T tolerance) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		const Matrix<T, RowCount, ColumnCount> diff = lhs - rhs;
		T magnitudeSquared = T{0};
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			magnitudeSquared += diff.Column(j).MagnitudeSquared();
		}

		return magnitudeSquared <= tolerance * tolerance;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator +(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = lhs[i, j] + rhs[i, j];
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator -(const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = -matrix[i, j];
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator -(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = lhs[i, j] - rhs[i, j];
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator *(const Matrix<T, RowCount, ColumnCount>& matrix, const T multiplier) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = matrix[i, j] * multiplier;
			}
		}

		return answer;
	}

	template<std::floating_point U, std::integral T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator *(const Matrix<T, RowCount, ColumnCount>& matrix, const U multiplier) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = static_cast<T>(matrix[i, j] * multiplier);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator *(const T multiplier, const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		return matrix * multiplier;
	}

	template<std::floating_point U, std::integral T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator *(const U multiplier, const Matrix<T, RowCount, ColumnCount>& matrix) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		return matrix * multiplier;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount, std::size_t RightColumnCount>
	constexpr Matrix<T, RowCount, RightColumnCount> operator *(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, ColumnCount, RightColumnCount>& rhs) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz && RightColumnCount >= 1uz)
	{
		const Matrix<T, ColumnCount, RowCount> lhsT = lhs.Transpose();

		Matrix<T, RowCount, RightColumnCount> answer;
		for (std::size_t j = 0uz; j < RightColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = Dot(lhsT.Column(i), rhs.Column(j));
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Vector<T, RowCount> operator *(const Matrix<T, RowCount, ColumnCount>& matrix, const Vector<T, ColumnCount>& vector) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		auto answer = Vector<T, RowCount>::Zero();
		for (std::size_t i = 0uz; i < ColumnCount; ++i)
		{
			answer += matrix.Column(i) * vector[i];
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator /(const Matrix<T, RowCount, ColumnCount>& matrix, const T divisor) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = matrix[i, j] / divisor;
			}
		}

		return answer;
	}

	template<std::floating_point U, std::integral T, std::size_t RowCount, std::size_t ColumnCount>
	constexpr Matrix<T, RowCount, ColumnCount> operator /(const Matrix<T, RowCount, ColumnCount>& matrix, const U divisor) noexcept requires (RowCount >= 1uz && ColumnCount >= 1uz)
	{
		Matrix<T, RowCount, ColumnCount> answer;
		for (std::size_t j = 0uz; j < ColumnCount; ++j)
		{
			for (std::size_t i = 0uz; i < RowCount; ++i)
			{
				answer[i, j] = static_cast<T>(matrix[i, j] / divisor);
			}
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t RowCount, std::size_t ColumnCount>
	std::ostream& operator <<(std::ostream& stream, const Matrix<T, RowCount, ColumnCount>& matrix)
	{
		return stream << matrix.ToString();
	}
}
