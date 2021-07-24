#pragma once

#include <stdexcept>
#include <string>

namespace gate_networks::parser
{
	/// <summary>
	/// Describes an exception that occurs when parsing input file.
	/// </summary>
	class InputFileException : public std::exception
	{
	public:
		InputFileException(
			int current_line,
			const std::string& error_type)
			: current_line_number_(current_line)
			, message_(format_error_message(current_line, error_type))
		{
		}

		virtual const char* what() const override
		{ 
			return message_.c_str();
		}
	private:
		int current_line_number_;
		std::string message_;

		std::string format_error_message(int current_line_number, const std::string& error_type);
	};

	/// <summary>
	/// An error in connection definition.
	/// </summary>
	class BindingRuleException : public InputFileException
	{
	public:
		BindingRuleException(int current_line_number)
			: InputFileException(current_line_number, "Binding rule")
		{
		}
	};

	/// <summary>
	/// An error that occurs when the same name of some gate network components was defined.
	/// </summary>
	class DuplicateException : public InputFileException
	{
	public:
		DuplicateException(int current_line_number)
			: InputFileException(current_line_number, "Duplicate")
		{
		}
	};

	/// <summary>
	/// An error that occurs when an important word is missing in the definition.
	/// </summary>
	class MissingKeywordException : public InputFileException
	{
	public:
		MissingKeywordException(int current_line_number)
			: InputFileException(current_line_number, "Missing keyword")
		{
		}
	};

	/// <summary>
	/// An error that occurs e. g. when incorrect name was supplied, reference to non-existent IO and so on.
	/// </summary>
	class SyntaxException : public InputFileException
	{
	public:
		SyntaxException(int current_line_number)
			: InputFileException(current_line_number, "Syntax")
		{
		}
	};
}