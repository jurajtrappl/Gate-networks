#pragma once

#include <stdexcept>
#include <string>

namespace gate_networks::core
{
	/// <summary>
	/// Describes an exception that occurs when executing a command.
	/// </summary>
	class CommandException : public std::exception
	{
	public:
		CommandException(const std::string& err) : message_(err)
		{
		}

		virtual const char* what() const override
		{
			return message_.c_str();
		}
	private:
		std::string message_;
	};
}