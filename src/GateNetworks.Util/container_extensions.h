#pragma once

#include <set>
#include <vector>
#include <string>
#include <stdexcept>

namespace gate_networks::util
{
	/// <summary>
	/// Additional methods that work with containers.
	/// </summary>
	/// <typeparam name="Container">type of container</typeparam>
	template <typename Container>
	class ContainerExtensions
	{
	public:
		/// <summary>
		/// Counts unique elements in the specified container.
		/// </summary>
		/// <param name="container">collection of elements.</param>
		/// <returns>numbers of distinct elements.</returns>
		static int64_t count_distinct(const Container& container)
		{
			throw std::invalid_argument("Invalid container type argument");
		}
				
		/// <summary>
		/// Divides the specified string by the specified delimiter to the given container.
		/// </summary>
		/// <param name="to_split">string to divide.</param>
		/// <param name="container">stores the result of splitting.</param>
		/// <param name="delimiter">string used to divide the original string.</param>
		static void split(const std::string& to_split, Container& container, const std::string& delimiter = " ")
		{
			throw std::invalid_argument("Invalid container type argument");
		}
	private:
		/// <summary>
		/// Implementation of count_distinct method.
		/// </summary>
		static int64_t private_count_distinct(const Container& container)
		{
			return std::set(container.begin(), container.end()).size();
		}

		/// <summary>
		/// Implementation of split method.
		/// </summary>
		static void private_split(const std::string& to_split, Container& container, const std::string& delimiter = " ")
		{
			std::size_t current, previous = 0;
			current = to_split.find_first_of(delimiter);
			while (current != std::string::npos) {
				container.push_back(to_split.substr(previous, current - previous));
				previous = current + 1;
				current = to_split.find_first_of(delimiter, previous);
			}
			container.push_back(to_split.substr(previous, current - previous));
		}
	};

	/// <summary>
	/// Specialized count_distinct method for vector of strings.
	/// </summary>
	template<>
	static int64_t ContainerExtensions<std::vector<std::string>>::count_distinct(const std::vector<std::string>& container)
	{
		return private_count_distinct(container);
	}

	/// <summary>
	/// Specialized split method for vector of strings.
	/// </summary>
	template<>
	static void ContainerExtensions<std::vector<std::string>>::split(
		const std::string& to_split,
		std::vector<std::string>& container,
		const std::string& delimiter)
	{
		return private_split(to_split, container, delimiter);
	}
}