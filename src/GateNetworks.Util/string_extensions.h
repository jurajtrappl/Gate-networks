#pragma once

#include <string>
#include <vector>

namespace gate_networks::util
{
	/// <summary>
	/// Helper methods for std::string while parsing.
	/// </summary>
	class StringExtensions
	{
	public:
		/// <summary>
		/// Indicates if the specified value is the end of the definition block.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_end(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is the commentary.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_commentary(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is the definition of a connection.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_connection_definition(const std::string& value);

		/// <summary>
		/// Indicates if the specified value has only whitespace characters.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_whitespace_only(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is the start of the network definition.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_network_definition(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is the start of the gate definition.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_gate_definition(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is the start of the inputs definition.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_inputs_definition(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is a correct name for a component.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_correct_name(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is the start of the outputs definition.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_outputs_definition(const std::string& value);

		/// <summary>
		/// Indicates if the specified value is any of tri state boolean logic value.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool is_tri_state(const std::string& value);

		/// <summary>
		/// Indicates if the specified value can be ignored, because it is an empty line
		/// or commentary or only whitespace line.
		/// </summary>
		/// <param name="value">string value to check.</param>
		static bool can_be_ignored(const std::string& value);
	};
}
