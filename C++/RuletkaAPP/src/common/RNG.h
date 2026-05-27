#pragma once
#include <random>
#include <cstdint>
#include <type_traits>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <cassert>

class RNG
{
private:
	using ushort = unsigned short;
	[[nodiscard]] static std::mt19937& GetEngine()
	{
		static std::mt19937 engine(std::random_device{}());
		return engine;
	}
public:
	RNG() = delete;

	template<typename T>
	requires std::is_integral_v<T>&& std::is_unsigned_v<T>
	[[nodiscard]] static T GetRN(T lowerBand, T upperBand)
	{
		static std::mt19937& engine = GetEngine();
		assert(lowerBand <= upperBand);
		if (lowerBand == upperBand) return lowerBand;
		if (lowerBand > upperBand) throw std::invalid_argument("LowerBand > UpperBand!");
		using Promoted = std::conditional_t<sizeof(T) <= 2, ushort, T>;
		return static_cast<T>(
			std::uniform_int_distribution<Promoted>(
				static_cast<Promoted>(lowerBand),
				static_cast<Promoted>(upperBand)
			)(engine));	
	}
};