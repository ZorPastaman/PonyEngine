/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Math:Color;

import std;

import :Common;
import :Vector;

namespace PonyEngine::Math
{
	/// @brief Color channel names.
	constexpr std::array<std::string_view, 5> ColorChannelNames
	{
		"None",
		"Red",
		"Green",
		"Blue",
		"Alpha"
	};
}

export namespace PonyEngine::Math
{
	/// @brief Color channel.
	enum class ColorChannel : std::uint8_t
	{
		None,
		Red,
		Green,
		Blue,
		Alpha
	};

	ENUM_VALUE_FEATURES(ColorChannel, ColorChannelNames)
}

export
{
	ENUM_VALUE_FORMATTER(PonyEngine::Math, ColorChannel)
}

export namespace PonyEngine::Math
{
	/// @brief The concept is satisfied if @p T is a floating point or unsigned integral type.
	template<typename T>
	concept ColorChannelType = std::is_floating_point_v<T> || std::is_unsigned_v<T>;

	/// @brief Color.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @note The none channel is used to indicate that the color has no channel of that type.
	/// @note The none channel can't be used in a gap between non-none channels.
	/// @note Floating point color channels are expected to be in the range [0, 1].
	/// @note Integral color channels are expected to be in the range [0, max].
	/// @note Integral color channels are considered normalized.
	/// @note Conversion from float to integer channels is done by rounding to the nearest integer.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel = ColorChannel::None, ColorChannel ThirdChannel = ColorChannel::None, ColorChannel FourthChannel = ColorChannel::None>
	class Color final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr ColorChannel FirstChannelType = FirstChannel; ///< First channel type.
		static constexpr ColorChannel SecondChannelType = SecondChannel; ///< Second channel type.
		static constexpr ColorChannel ThirdChannelType = ThirdChannel; ///< Third channel type.
		static constexpr ColorChannel FourthChannelType = FourthChannel; ///< Fourth channel type.

		/// @brief Channel count. It is the number of non-none channels.
		static constexpr std::size_t ChannelCount = (FirstChannel != ColorChannel::None) + (SecondChannel != ColorChannel::None) + (ThirdChannel != ColorChannel::None) + (FourthChannel != ColorChannel::None);
		static_assert(ChannelCount >= 1uz, "The color must have at least one channel.");
		static_assert(ChannelCount != 1uz || (FirstChannel != ColorChannel::None && SecondChannel == ColorChannel::None && ThirdChannel == ColorChannel::None && FourthChannel == ColorChannel::None), "The color channels mustn't have gaps.");
		static_assert(ChannelCount != 2uz || (FirstChannel != ColorChannel::None && SecondChannel != ColorChannel::None && ThirdChannel == ColorChannel::None && FourthChannel == ColorChannel::None), "The color channels mustn't have gaps.");
		static_assert(ChannelCount != 3uz || (FirstChannel != ColorChannel::None && SecondChannel != ColorChannel::None && ThirdChannel != ColorChannel::None && FourthChannel == ColorChannel::None), "The color channels mustn't have gaps.");
		static_assert(ChannelCount != 2uz || (FirstChannel != SecondChannel), "The channels must be unique");
		static_assert(ChannelCount != 3uz || (FirstChannel != SecondChannel && FirstChannel != ThirdChannel && SecondChannel != ThirdChannel), "The channels must be unique");
		static_assert(ChannelCount != 4uz || (FirstChannel != SecondChannel && FirstChannel != ThirdChannel && FirstChannel != FourthChannel && SecondChannel != ThirdChannel && SecondChannel != FourthChannel && ThirdChannel != FourthChannel), "The channels must be unique");

		using VectorType = Vector<T, ChannelCount>; ///< Vector type.
		using SpanType = std::span<T, ChannelCount>; ///< Span type.
		using ConstSpanType = std::span<const T, ChannelCount>; ///< Const span type.

		/// @brief Gets an index of the specified channel.
		/// @tparam Channel Channel.
		/// @return Channel index or std::nullopt if the channel is not present.
		template<ColorChannel Channel> [[nodiscard("Pure function")]]
		static constexpr std::optional<std::size_t> ChannelIndex() noexcept requires (Channel != ColorChannel::None);

		static constexpr std::optional<std::size_t> RedIndex = ChannelIndex<ColorChannel::Red>(); ///< Red channel index. It's std::nullopt if the channel is not present.
		static constexpr std::optional<std::size_t> GreenIndex = ChannelIndex<ColorChannel::Green>(); ///< Green channel index. It's std::nullopt if the channel is not present.
		static constexpr std::optional<std::size_t> BlueIndex = ChannelIndex<ColorChannel::Blue>(); ///< Blue channel index. It's std::nullopt if the channel is not present.
		static constexpr std::optional<std::size_t> AlphaIndex = ChannelIndex<ColorChannel::Alpha>(); ///< Alpha channel index. It's std::nullopt if the channel is not present.
		static constexpr bool HasRed = RedIndex.has_value(); ///< Whether the color has a red channel.
		static constexpr bool HasGreen = GreenIndex.has_value(); ///< Whether the color has a green channel.
		static constexpr bool HasBlue = BlueIndex.has_value(); ///< Whether the color has a blue channel.
		static constexpr bool HasAlpha = AlphaIndex.has_value(); ///< Whether the color has an alpha channel.
		static constexpr bool HasColor = HasRed || HasGreen || HasBlue; ///< Whether the color has at least one color channel.
		static constexpr bool HasFullColor = HasRed && HasGreen && HasBlue; ///< Whether the color has all color channels (red, green, blue).

		static constexpr T GammaValue = T(2.4); ///< Gamma value. It's used only for floating point colors.

		/// @brief Creates a zero color.
		[[nodiscard("Pure constructor")]]
		constexpr Color() noexcept = default;
		/// @brief Creates a color.
		/// @param firstChannel First channel value.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color(T firstChannel) noexcept requires (ChannelCount == 1);
		/// @brief Creates a color.
		/// @param firstChannel First channel value.
		/// @param secondChannel Second channel value.
		[[nodiscard("Pure constructor")]]
		constexpr Color(T firstChannel, T secondChannel) noexcept requires (ChannelCount == 2);
		/// @brief Creates a color.
		/// @param firstChannel First channel value.
		/// @param secondChannel Second channel value.
		/// @param thirdChannel Third channel value.
		[[nodiscard("Pure constructor")]]
		constexpr Color(T firstChannel, T secondChannel, T thirdChannel) noexcept requires (ChannelCount == 3);
		/// @brief Creates a color.
		/// @param firstChannel First channel value.
		/// @param secondChannel Second channel value.
		/// @param thirdChannel Third channel value.
		/// @param fourthChannel Fourth channel value.
		[[nodiscard("Pure constructor")]]
		constexpr Color(T firstChannel, T secondChannel, T thirdChannel, T fourthChannel) noexcept requires (ChannelCount == 4);
		/// @brief Creates a color.
		/// @param span Channel values.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color(std::span<const T, ChannelCount> span) noexcept;
		/// @brief Creates a color.
		/// @param vector Channel values.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Color(const VectorType& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Color(const Color& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Color(Color&& other) noexcept = default;

		constexpr ~Color() noexcept = default;

		/// @brief Gets a red color.
		/// @return Red color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Red() noexcept requires (HasRed);
		/// @brief Gets a green color.
		/// @return Green color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Green() noexcept requires (HasGreen);
		/// @brief Gets a blue color.
		/// @return Blue color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Blue() noexcept requires (HasBlue);
		/// @brief Gets a black color.
		/// @return Black color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Black() noexcept;
		/// @brief Gets a white color.
		/// @return White color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& White() noexcept requires (HasFullColor);
		/// @brief Gets a clear (transparent black) color.
		/// @return Clear color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Clear() noexcept requires (HasAlpha);
		/// @brief Gets a gray color.
		/// @return Gray color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Gray() noexcept requires (HasFullColor);
		/// @brief Gets a yellow color.
		/// @return Yellow color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Yellow() noexcept requires (HasRed && HasGreen);
		/// @brief Gets a magenta color.
		/// @return Magenta color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Magenta() noexcept requires (HasRed && HasBlue);
		/// @brief Gets a cyan color.
		/// @return Cyan color.
		[[nodiscard("Pure function")]]
		static constexpr const Color& Cyan() noexcept requires (HasGreen && HasBlue);

		/// @brief Gets the red channel.
		/// @return Red channel.
		[[nodiscard("Pure function")]]
		constexpr T& R() noexcept requires (HasRed);
		/// @brief Gets the red channel.
		/// @return Red channel.
		[[nodiscard("Pure function")]]
		constexpr const T& R() const noexcept requires (HasRed);
		/// @brief Gets the green channel.
		/// @return Green channel.
		[[nodiscard("Pure function")]]
		constexpr T& G() noexcept requires (HasGreen);
		/// @brief Gets the green channel.
		/// @return Green channel.
		[[nodiscard("Pure function")]]
		constexpr const T& G() const noexcept requires (HasGreen);
		/// @brief Gets the blue channel.
		/// @return Blue channel.
		[[nodiscard("Pure function")]]
		constexpr T& B() noexcept requires (HasBlue);
		/// @brief Gets the blue channel.
		/// @return Blue channel.
		[[nodiscard("Pure function")]]
		constexpr const T& B() const noexcept requires (HasBlue);
		/// @brief Gets the alpha channel.
		/// @return Alpha channel.
		[[nodiscard("Pure function")]]
		constexpr T& A() noexcept requires (HasAlpha);
		/// @brief Gets the alpha channel.
		/// @return Alpha channel.
		[[nodiscard("Pure function")]]
		constexpr const T& A() const noexcept requires (HasAlpha);
		/// @brief Gets the channel span.
		/// @return Channel span.
		[[nodiscard("Pure function")]]
		constexpr SpanType Span() noexcept;
		/// @brief Gets the channel span.
		/// @return Channel span.
		[[nodiscard("Pure function")]]
		constexpr ConstSpanType Span() const noexcept;
		/// @brief Gets the channel vector.
		/// @return Channel vector.
		[[nodiscard("Pure function")]]
		constexpr VectorType& Vector() noexcept;
		/// @brief Gets the channel vector.
		/// @return Channel vector.
		[[nodiscard("Pure function")]]
		constexpr const VectorType& Vector() const noexcept;

		/// @brief Calculates a grayscale value of the color.
		/// @return Grayscale value.
		[[nodiscard("Pure function")]]
		constexpr T Grayscale() const noexcept requires (HasFullColor && std::is_floating_point_v<T>);

		/// @brief Gets a minimum among the channels.
		/// @return Minimum channel.
		[[nodiscard("Pure function")]]
		constexpr T& Min() noexcept;
		/// @brief Gets a minimum among the channels.
		/// @return Minimum channel.
		[[nodiscard("Pure function")]]
		constexpr const T& Min() const noexcept;
		/// @brief Gets a maximum among the channels.
		/// @return Maximum channel.
		[[nodiscard("Pure function")]]
		constexpr T& Max() noexcept;
		/// @brief Gets a maximum among the channels.
		/// @return Maximum channel.
		[[nodiscard("Pure function")]]
		constexpr const T& Max() const noexcept;
		/// @brief Gets a minimum and maximum among the channels.
		/// @return Minimum and maximum channels.
		[[nodiscard("Pure function")]]
		constexpr std::pair<T&, T&> MinMax() noexcept;
		/// @brief Gets a minimum and maximum among the channels.
		/// @return Minimum and maximum channels.
		[[nodiscard("Pure function")]]
		constexpr std::pair<const T&, const T&> MinMax() const noexcept;

		/// @brief Converts the linear color to a gamma-corrected color.
		/// @return Gamma-corrected color.
		[[nodiscard("Pure function")]]
		Color Gamma() const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Converts the gamma-corrected color to a linear color.
		/// @return Linear color.
		[[nodiscard("Pure function")]]
		Color Linear() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the color is black.
		/// @return @a True if the color is black; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsBlack() const noexcept requires (HasColor);
		/// @brief Check if the color is almost black with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if the color is almost black; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostBlack(T tolerance = T{0.00001}) const noexcept requires (HasColor && std::is_floating_point_v<T>);
		/// @brief Checks if the color is white.
		/// @return @a True if the color is white; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsWhite() const noexcept requires (HasFullColor);
		/// @brief Check if the color is almost white with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if the color is almost white; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostWhite(T tolerance = T{0.00001}) const noexcept requires (HasFullColor && std::is_floating_point_v<T>);
		/// @brief Checks if the color is transparent.
		/// @return @a True if the color is transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsTransparent() const noexcept requires (HasAlpha);
		/// @brief Check if the color is almost transparent with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if the color is almost transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostTransparent(T tolerance = T{0.00001}) const noexcept requires (HasAlpha && std::is_floating_point_v<T>);
		/// @brief Checks if the color is opaque.
		/// @return @a True if the color is opaque; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsOpaque() const noexcept requires (HasAlpha);
		/// @brief Check if the color is almost opaque with the tolerance value.
		/// @param tolerance Tolerance. Must be positive.
		/// @return @a True if the color is almost opaque; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostOpaque(T tolerance = T{0.00001}) const noexcept requires (HasAlpha && std::is_floating_point_v<T>);

		/// @brief Checks if all the channels are finite.
		/// @return @a True if all the channels are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Creates a string representing a state of the color.
		/// @return State string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts the color to another color type.
		/// @details It uses a black color as a default and then assigns the channels from this color converting them to the target type.
		/// @tparam U Target channel type.
		/// @tparam FirstChannelU Target first channel.
		/// @tparam SecondChannelU Target second channel.
		/// @tparam ThirdChannelU Target third channel.
		/// @tparam FourthChannelU Target fourth channel.
		template<ColorChannelType U, ColorChannel FirstChannelU, ColorChannel SecondChannelU, ColorChannel ThirdChannelU, ColorChannel FourthChannelU> [[nodiscard("Pure operator")]]
		explicit constexpr operator Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>() const noexcept;

		/// @brief Converts the color to a vector.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator VectorType() const noexcept;

		/// @brief Gets a channel by the @p index.
		/// @param index Channel index. Must be in range [0, ChannelCount].
		/// @return Channel.
		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		/// @brief Gets a channel by the @p index.
		/// @param index Channel index. Must be in range [0, ChannelCount].
		/// @return Channel.
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr Color& operator =(const Color& other) noexcept = default;
		constexpr Color& operator =(Color&& other) noexcept = default;
		/// @brief Adds the @p other to @a this.
		/// @note Integer types are clamped.
		/// @param other Color to add.
		/// @return @a This.
		constexpr Color& operator +=(const Color& other) noexcept;
		/// @brief Subtracts the @p other from @a this.
		/// @note Integer types are clamped.
		/// @param other Color to subtract.
		/// @return @a This.
		constexpr Color& operator -=(const Color& other) noexcept;
		/// @brief Multiplies @a this by the @p other.
		/// @param other Color multiplier.
		/// @return @a This.
		constexpr Color& operator *=(const Color& other) noexcept requires (std::is_floating_point_v<T>);
		/// @brief Multiplier @a this by the @p multiplier.
		/// @param multiplier Color multiplier.
		/// @return @a This.
		constexpr Color& operator *=(T multiplier) noexcept requires (std::is_floating_point_v<T>);
		/// @brief Divides @a this by the @p other.
		/// @param other Color divisor.
		/// @return @a This.
		constexpr Color& operator /=(const Color& other) noexcept requires (std::is_floating_point_v<T>);
		/// @brief Divides @a this by the @p divisor.
		/// @param divisor Color divisor.
		/// @return @a This.
		constexpr Color& operator /=(T divisor) noexcept requires (std::is_floating_point_v<T>);

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Color& other) const noexcept = default;

	private:
		VectorType channels; ///< Channel values.
	};

	/// @brief Color with a red channel.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorR = Color<T, ColorChannel::Red>;
	/// @brief Color with a green channel.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorG = Color<T, ColorChannel::Green>;
	/// @brief Color with a blue channel.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorB = Color<T, ColorChannel::Blue>;
	/// @brief Color with red and green channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRG = Color<T, ColorChannel::Red, ColorChannel::Green>;
	/// @brief Color with red and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRB = Color<T, ColorChannel::Red, ColorChannel::Blue>;
	/// @brief Color with green and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorGB = Color<T, ColorChannel::Green, ColorChannel::Blue>;
	/// @brief Color with red, green and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRGB = Color<T, ColorChannel::Red, ColorChannel::Green, ColorChannel::Blue>;
	/// @brief Color with an alpha channel.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorA = Color<T, ColorChannel::Alpha>;
	/// @brief Color with red and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRA = Color<T, ColorChannel::Red, ColorChannel::Alpha>;
	/// @brief Color with green and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorGA = Color<T, ColorChannel::Green, ColorChannel::Alpha>;
	/// @brief Color with blue and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorBA = Color<T, ColorChannel::Blue, ColorChannel::Alpha>;
	/// @brief Color with red, green and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRGA = Color<T, ColorChannel::Red, ColorChannel::Green, ColorChannel::Alpha>;
	/// @brief Color with red, blue and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRBA = Color<T, ColorChannel::Red, ColorChannel::Blue, ColorChannel::Alpha>;
	/// @brief Color with green, blue and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorGBA = Color<T, ColorChannel::Green, ColorChannel::Blue, ColorChannel::Alpha>;
	/// @brief Color with red, green, blue and alpha channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorRGBA = Color<T, ColorChannel::Red, ColorChannel::Green, ColorChannel::Blue, ColorChannel::Alpha>;
	/// @brief Color with alpha and red channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorAR = Color<T, ColorChannel::Alpha, ColorChannel::Red>;
	/// @brief Color with alpha and green channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorAG = Color<T, ColorChannel::Alpha, ColorChannel::Green>;
	/// @brief Color with alpha and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorAB = Color<T, ColorChannel::Alpha, ColorChannel::Blue>;
	/// @brief Color with alpha, red and green channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorARG = Color<T, ColorChannel::Alpha, ColorChannel::Red, ColorChannel::Green>;
	/// @brief Color with alpha, red and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorARB = Color<T, ColorChannel::Alpha, ColorChannel::Red, ColorChannel::Blue>;
	/// @brief Color with alpha, green and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorAGB = Color<T, ColorChannel::Alpha, ColorChannel::Green, ColorChannel::Blue>;
	/// @brief Color with alpha, red, green and blue channels.
	/// @tparam T Channel type.
	template<ColorChannelType T>
	using ColorARGB = Color<T, ColorChannel::Alpha, ColorChannel::Red, ColorChannel::Green, ColorChannel::Blue>;

	/// @brief Converts a color channel value from one type to another.
	/// @note It follows a color conversion rules.
	/// @tparam To Target channel type.
	/// @tparam From Source channel type.
	/// @param value Source channel value.
	/// @return Target channel value.
	template<ColorChannelType To, ColorChannelType From> [[nodiscard("Pure function")]]
	constexpr To ConvertColorChannel(From value) noexcept;

	/// @brief Computes a distance between two colors.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Left color.
	/// @param rhs Right color.
	/// @return Color distance.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	T Distance(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;
	/// @brief Computes a distance between two colors.
	/// @tparam T Channel type.
	/// @tparam U Result type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Left color.
	/// @param rhs Right color.
	/// @return Color distance.
	template<std::floating_point U = double, std::integral T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	U Distance(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;
	/// @brief Computes a squared distance between two colors.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Left color.
	/// @param rhs Right color.
	/// @return Color distance.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;

	/// @brief Creates a color consisting of minimal channels of the two colors.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Left color.
	/// @param rhs Right color.
	/// @return Color of minimal channels.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Min(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;
	/// @brief Creates a color consisting of maximal channels of the two colors.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Left color.
	/// @param rhs Right color.
	/// @return Color of maximal channels.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Max(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;
	/// @brief Clamps the @p value between the @p min and @p max channel-wise.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param value Value.
	/// @param min Minimum.
	/// @param max Maximum.
	/// @return Clamped color.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Clamp(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& value, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& min, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& max) noexcept;
	/// @brief Linear interpolation between the two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two vectors if the @p time is out of range [0, 1].
	/// @note It doesn't prevent overflow or underflow.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated color.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Lerp(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& from, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& to, T time) noexcept;
	/// @brief Linear interpolation between the two vectors if the @p time is in range [0, 1].
	///        Linear extrapolation between the two vectors if the @p time is out of range [0, 1].
	/// @note It doesn't prevent overflow or underflow.
	/// @tparam U Time type.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param from Interpolation/Extrapolation start point.
	/// @param to Interpolation/Extrapolation target point.
	/// @param time Interpolation/Extrapolation time. It can be negative.
	/// @return Interpolated/Extrapolated color.
	template<std::floating_point U = double, std::integral T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure function")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Lerp(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& from, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& to, U time) noexcept;

	/// @brief Checks if the two colors are almost equal with the tolerance value.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Left color.
	/// @param rhs Right color.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if the colors are almost equal; @a false otherwise.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool AreAlmostEqual(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs, T tolerance = T{0.00001}) noexcept;

	/// @brief Sums the @p lhs and the @p rhs colors.
	/// @note Integral types are clamped.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Augend.
	/// @param rhs Addend.
	/// @return Sum.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator +(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;

	/// @brief Negates the @p color.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param color Color to negate.
	/// @return Negated color.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator -(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) noexcept;
	/// @brief Subtracts the @p rhs color from the @p lhs one.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Minuend.
	/// @param rhs Subtrahend.
	/// @return Difference.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator -(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;

	/// @brief Multiplies the @p lhs and the @p rhs colors channel-wise.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Multiplicand.
	/// @param rhs Multiplier.
	/// @return Product.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator *(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;
	/// @brief Multiplies the @p color channels by the @p multiplier.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param color Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator *(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, T multiplier) noexcept;
	/// @brief Multiplies the @p color channels by the @p multiplier.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param color Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator *(T multiplier, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) noexcept;

	/// @brief Divides the @p lhs by the @p rhs colors channel-wise.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param lhs Dividend.
	/// @param rhs Divisor.
	/// @return Quotient.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator /(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept;
	/// @brief Divides the @p color channels by the @p multiplier.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param color Dividend.
	/// @param divisor Divisor.
	/// @return Quotient.
	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel> [[nodiscard("Pure operator")]]
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator /(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, T divisor) noexcept;

	/// @brief Outputs a string representation of the @p color.
	/// @tparam T Channel type.
	/// @tparam FirstChannel First channel.
	/// @tparam SecondChannel Second channel.
	/// @tparam ThirdChannel Third channel.
	/// @tparam FourthChannel Fourth channel.
	/// @param stream Target stream.
	/// @param color Input source.
	/// @return @p stream.
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	std::ostream& operator <<(std::ostream& stream, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color);
}

/// @brief Color formatter.
/// @tparam T Channel type.
/// @tparam FirstChannel First channel.
/// @tparam SecondChannel Second channel.
/// @tparam ThirdChannel Third channel.
/// @tparam FourthChannel Fourth channel.
export template<PonyEngine::Math::ColorChannelType T, PonyEngine::Math::ColorChannel FirstChannel, PonyEngine::Math::ColorChannel SecondChannel, PonyEngine::Math::ColorChannel ThirdChannel, PonyEngine::Math::ColorChannel FourthChannel>
struct std::formatter<PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>, char>
{
	static constexpr auto parse(std::format_parse_context& context)
	{
		if (context.begin() == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}
		if (*context.begin() != '}') [[unlikely]]
		{
			throw std::format_error("Unexpected format specifier.");
		}

		return context.begin();
	}

	static auto format(const PonyEngine::Math::Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, std::format_context& context)
	{
		return std::ranges::copy(color.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel, bool Opaque = true>
	consteval Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> CreatePredefined(std::span<const std::size_t> valueIndices, bool setHalves = false) noexcept;

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	template<ColorChannel Channel>
	constexpr std::optional<std::size_t> Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::ChannelIndex() noexcept requires (Channel != ColorChannel::None)
	{
		if constexpr (Channel == FirstChannel)
		{
			return 0uz;
		}
		else if constexpr (Channel == SecondChannel)
		{
			return 1uz;
		}
		else if constexpr (Channel == ThirdChannel)
		{
			return 2uz;
		}
		else if constexpr (Channel == FourthChannel)
		{
			return 3uz;
		}
		else
		{
			return std::nullopt;
		}
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Color(const T firstChannel) noexcept requires (ChannelCount == 1) :
		channels(firstChannel)
	{
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Color(const T firstChannel, const T secondChannel) noexcept requires (ChannelCount == 2) :
		channels(firstChannel, secondChannel)
	{
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Color(const T firstChannel, const T secondChannel, const T thirdChannel) noexcept requires (ChannelCount == 3) :
		channels(firstChannel, secondChannel, thirdChannel)
	{
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Color(const T firstChannel, const T secondChannel, const T thirdChannel, const T fourthChannel) noexcept requires (ChannelCount == 4) :
		channels(firstChannel, secondChannel, thirdChannel, fourthChannel)
	{
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Color(const std::span<const T, ChannelCount> span) noexcept :
		channels(span)
	{
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Color(const VectorType& vector) noexcept :
		channels(vector)
	{
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Red() noexcept requires (HasRed)
	{
		static constexpr Color RedColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ RedIndex.value() });

		return RedColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Green() noexcept requires (HasGreen)
	{
		static constexpr Color GreenColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ GreenIndex.value() });

		return GreenColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Blue() noexcept requires (HasBlue)
	{
		static constexpr Color BlueColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ BlueIndex.value() });

		return BlueColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Black() noexcept
	{
		static constexpr Color BlackColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array<std::size_t, 0>{ });

		return BlackColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::White() noexcept requires (HasFullColor)
	{
		static constexpr Color WhiteColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ RedIndex.value(), GreenIndex.value(), BlueIndex.value() });

		return WhiteColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Clear() noexcept requires (HasAlpha)
	{
		static constexpr Color ClearColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel, false>(std::array<std::size_t, 0>{ });

		return ClearColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Gray() noexcept requires (HasFullColor)
	{
		static constexpr Color GrayColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ RedIndex.value(), GreenIndex.value(), BlueIndex.value() }, true);

		return GrayColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Yellow() noexcept requires (HasRed && HasGreen)
	{
		static constexpr Color YellowColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ RedIndex.value(), GreenIndex.value() });

		return YellowColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Magenta() noexcept requires (HasRed && HasBlue)
	{
		static constexpr Color MagentaColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ RedIndex.value(), BlueIndex.value() });

		return MagentaColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Cyan() noexcept requires (HasGreen && HasBlue)
	{
		static constexpr Color CyanColor = CreatePredefined<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(std::array{ GreenIndex.value(), BlueIndex.value() });

		return CyanColor;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::R() noexcept requires (HasRed)
	{
		static constexpr std::size_t Index = RedIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::R() const noexcept requires (HasRed)
	{
		static constexpr std::size_t Index = RedIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::G() noexcept requires (HasGreen)
	{
		static constexpr std::size_t Index = GreenIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::G() const noexcept requires (HasGreen)
	{
		static constexpr std::size_t Index = GreenIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::B() noexcept requires (HasBlue)
	{
		static constexpr std::size_t Index = BlueIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::B() const noexcept requires (HasBlue)
	{
		static constexpr std::size_t Index = BlueIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::A() noexcept requires (HasAlpha)
	{
		static constexpr std::size_t Index = AlphaIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::A() const noexcept requires (HasAlpha)
	{
		static constexpr std::size_t Index = AlphaIndex.value();

		return channels[Index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::SpanType Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Span() noexcept
	{
		return channels.Span();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::ConstSpanType Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Span() const noexcept
	{
		return channels.Span();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::VectorType& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Vector() noexcept
	{
		return channels;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::VectorType& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Vector() const noexcept
	{
		return channels;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Grayscale() const noexcept requires (HasFullColor && std::is_floating_point_v<T>)
	{
		return R() * T{0.2126} + G() * T{0.7152} + B() * T{0.0722};
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Min() noexcept
	{
		return channels.Min();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Min() const noexcept
	{
		return channels.Min();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Max() noexcept
	{
		return channels.Max();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Max() const noexcept
	{
		return channels.Max();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr std::pair<T&, T&> Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::MinMax() noexcept
	{
		return channels.MinMax();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr std::pair<const T&, const T&> Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::MinMax() const noexcept
	{
		return channels.MinMax();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsBlack() const noexcept requires (HasColor)
	{
		return *this == Black();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsAlmostBlack(const T tolerance) const noexcept requires (HasColor && std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, Black(), tolerance);
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsWhite() const noexcept requires (HasFullColor)
	{
		return *this == White();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsAlmostWhite(const T tolerance) const noexcept requires (HasFullColor && std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(*this, White(), tolerance);
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsTransparent() const noexcept requires (HasAlpha)
	{
		return A() == T{0};
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsAlmostTransparent(const T tolerance) const noexcept requires (HasAlpha && std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(A(), T{0}, tolerance);
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsOpaque() const noexcept requires (HasAlpha)
	{
		static constexpr T Value = std::is_floating_point_v<T> ? T{1} : std::numeric_limits<T>::max();

		return A() == Value;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsAlmostOpaque(const T tolerance) const noexcept requires (HasAlpha && std::is_floating_point_v<T>)
	{
		return AreAlmostEqual(A(), T{1}, tolerance);
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Gamma() const noexcept requires (std::is_floating_point_v<T>)
	{
		static constexpr auto ToGamma = [](const T channel) noexcept
		{
			const T value = channel > T{0.0031308}
				? std::pow(channel, T{1} / GammaValue) * T{1.055} - T{0.055}
				: channel * T{12.92};
			return std::clamp(value, T{0}, T{1});
		};

		Color gamma;
		if constexpr (HasRed)
		{
			gamma.R() = ToGamma(R());
		}
		if constexpr (HasGreen)
		{
			gamma.G() = ToGamma(G());
		}
		if constexpr (HasBlue)
		{
			gamma.B() = ToGamma(B());
		}
		if constexpr (HasAlpha)
		{
			gamma.A() = A(); // Alpha channel is not gamma-corrected.
		}

		return gamma;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::Linear() const noexcept requires (std::is_floating_point_v<T>)
	{
		static constexpr auto ToLinear = [](const T channel) noexcept
		{
			const T value = channel > T{0.04045}
				? std::pow((channel + T{0.055}) / T{1.055}, GammaValue)
				: channel / T{12.92};
			return std::clamp(value, T{0}, T{1});
		};

		Color linear;
		if constexpr (HasRed)
		{
			linear.R() = ToLinear(R());
		}
		if constexpr (HasGreen)
		{
			linear.G() = ToLinear(G());
		}
		if constexpr (HasBlue)
		{
			linear.B() = ToLinear(B());
		}
		if constexpr (HasAlpha)
		{
			linear.A() = A(); // Alpha channel is not gamma-corrected.
		}

		return linear;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return channels.IsFinite();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	std::string Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::ToString() const
	{
		static constexpr auto GetChannelName = [](const std::size_t index) noexcept
		{
			if (index == RedIndex)
			{
				return 'R';
			}
			if (index == GreenIndex)
			{
				return 'G';
			}
			if (index == BlueIndex)
			{
				return 'B';
			}
			if (index == AlphaIndex)
			{
				return 'A';
			}

			return 'U'; // Unknown.
		};

		std::string answer;
		for (std::size_t i = 0uz; i < ChannelCount; ++i)
		{
			if (i > 0uz)
			{
				answer += ", ";
			}
			answer += std::format("{}: {}", GetChannelName(i), channels[i]);
		}

		return answer;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	template<ColorChannelType U, ColorChannel FirstChannelU, ColorChannel SecondChannelU, ColorChannel ThirdChannelU, ColorChannel FourthChannelU>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>() const noexcept
	{
		auto answer = Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>::Black();
		if constexpr (HasRed && Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>::HasRed)
		{
			answer.R() = ConvertColorChannel<U>(R());
		}
		if constexpr (HasGreen && Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>::HasGreen)
		{
			answer.G() = ConvertColorChannel<U>(G());
		}
		if constexpr (HasBlue && Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>::HasBlue)
		{
			answer.B() = ConvertColorChannel<U>(B());
		}
		if constexpr (HasAlpha && Color<U, FirstChannelU, SecondChannelU, ThirdChannelU, FourthChannelU>::HasAlpha)
		{
			answer.A() = ConvertColorChannel<U>(A());
		}

		return answer;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator VectorType() const noexcept
	{
		return channels;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator [](const std::size_t index) noexcept
	{
		return channels[index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr const T& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator [](const std::size_t index) const noexcept
	{
		return channels[index];
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator +=(const Color& other) noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			channels += other.channels;
		}
		else
		{
			for (std::size_t i = 0uz; i < ChannelCount; ++i)
			{
				if (channels[i] > std::numeric_limits<T>::max() - other.channels[i])
				{
					channels[i] = std::numeric_limits<T>::max();
				}
				else
				{
					channels[i] += other.channels[i];
				}
			}
		}

		return *this;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator -=(const Color& other) noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			channels -= other.channels;
		}
		else
		{
			for (std::size_t i = 0; i < ChannelCount; ++i)
			{
				if (channels[i] < other.channels[i])
				{
					channels[i] = std::numeric_limits<T>::min();
				}
				else
				{
					channels[i] -= other.channels[i];
				}
			}
		}

		return *this;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator *=(const Color& other) noexcept requires (std::is_floating_point_v<T>)
	{
		channels.Multiply(other.channels);

		return *this;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator *=(const T multiplier) noexcept requires (std::is_floating_point_v<T>)
	{
		channels *= multiplier;

		return *this;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator /=(const Color& other) noexcept requires (std::is_floating_point_v<T>)
	{
		channels.Divide(other.channels);

		return *this;
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::operator /=(const T divisor) noexcept requires (std::is_floating_point_v<T>)
	{
		channels /= divisor;

		return *this;
	}

	template<ColorChannelType To, ColorChannelType From>
	constexpr To ConvertColorChannel(const From value) noexcept
	{
		if constexpr (std::is_floating_point_v<From> && std::is_integral_v<To>)
		{
			using FloatingType = std::conditional_t<(sizeof(From) < sizeof(long double) && sizeof(To) > sizeof(std::uint32_t)), long double,
				std::conditional_t<(sizeof(From) < sizeof(double) && sizeof(To) > sizeof(std::uint16_t)), double, From>>;
			return RoundToIntegral<To>(static_cast<FloatingType>(std::clamp(value, From{0}, From{1})) * static_cast<FloatingType>(std::numeric_limits<To>::max()));
		}
		else if constexpr (std::is_integral_v<From> && std::is_floating_point_v<To>)
		{
			using FloatingType = std::conditional_t<(sizeof(To) < sizeof(long double) && sizeof(From) > sizeof(std::uint32_t)), long double,
				std::conditional_t<(sizeof(To) < sizeof(double) && sizeof(From) > sizeof(std::uint16_t)), double, To>>;
			return std::clamp(static_cast<To>(static_cast<FloatingType>(value) * (FloatingType{1} / static_cast<FloatingType>(std::numeric_limits<From>::max()))), To{0}, To{1});
		}
		else if constexpr (std::is_integral_v<From> && std::is_integral_v<To> && sizeof(From) != sizeof(To))
		{
			using FloatingType = std::conditional_t<(sizeof(From) > sizeof(std::uint32_t)), long double,
				std::conditional_t<(sizeof(From) > sizeof(std::uint16_t)), double, float>>;
			return ConvertColorChannel<To>(ConvertColorChannel<FloatingType>(value));
		}
		else
		{
			return static_cast<To>(value);
		}
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	T Distance(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return Distance(lhs.Vector(), rhs.Vector());
	}

	template<std::floating_point U, std::integral T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	U Distance(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return Distance<U>(lhs.Vector(), rhs.Vector());
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr T DistanceSquared(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return DistanceSquared(lhs.Vector(), rhs.Vector());
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Min(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Min(lhs.Vector(), rhs.Vector()));
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Max(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Max(lhs.Vector(), rhs.Vector()));
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Clamp(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& value, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& min, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& max) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Clamp(value.Vector(), min.Vector(), max.Vector()));
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Lerp(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& from, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& to, const T time) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Lerp(from.Vector(), to.Vector(), time));
	}

	template<std::floating_point U, std::integral T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> Lerp(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& from, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& to, U time) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Lerp(from.Vector(), to.Vector(), time));
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr bool AreAlmostEqual(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs, const T tolerance) noexcept
	{
		return AreAlmostEqual(lhs.Vector(), rhs.Vector(), tolerance);
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator +(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(lhs.Vector() + rhs.Vector());
		}
		else
		{
			Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> answer;
			for (std::size_t i = 0; i < Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::ChannelCount; ++i)
			{
				answer[i] = lhs[i] > std::numeric_limits<T>::max() - rhs[i] ? std::numeric_limits<T>::max() : static_cast<T>(lhs[i] + rhs[i]);
			}

			return answer;
		}
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator -(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(-color.Vector());
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator -(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(lhs.Vector() - rhs.Vector());
		}
		else
		{
			Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> answer;
			for (std::size_t i = 0; i < Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::ChannelCount; ++i)
			{
				answer[i] = lhs[i] < std::numeric_limits<T>::min() + rhs[i] ? std::numeric_limits<T>::min() : static_cast<T>(lhs[i] - rhs[i]);
			}

			return answer;
		}
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator *(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Multiply(lhs.Vector(), rhs.Vector()));
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator *(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, const T multiplier) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(color.Vector() * multiplier);
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator *(const T multiplier, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator /(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& lhs, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& rhs) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Divide(lhs.Vector(), rhs.Vector()));
	}

	template<std::floating_point T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	constexpr Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> operator /(const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color, const T divisor) noexcept
	{
		return Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(color.Vector() / divisor);
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel>
	std::ostream& operator <<(std::ostream& stream, const Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>& color)
	{
		return stream << color.ToString();
	}

	template<ColorChannelType T, ColorChannel FirstChannel, ColorChannel SecondChannel, ColorChannel ThirdChannel, ColorChannel FourthChannel, bool Opaque>
	consteval Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel> CreatePredefined(const std::span<const std::size_t> valueIndices, const bool setHalves) noexcept
	{
		constexpr T max = std::is_floating_point_v<T> ? T{1} : std::numeric_limits<T>::max();
		constexpr T min = std::is_floating_point_v<T> ? T{0} : std::numeric_limits<T>::min();
		constexpr T half = std::is_floating_point_v<T> ? T(0.5) : std::numeric_limits<T>::max() / 2u;
		const T value = setHalves ? half : max;

		auto color = Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>(Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::VectorType(min));
		for (const std::size_t index : valueIndices)
		{
			color[index] = value;
		}
		if constexpr (Color<T, FirstChannel, SecondChannel, ThirdChannel, FourthChannel>::HasAlpha)
		{
			color.A() = Opaque ? max : min;
		}

		return color;
	}
}
