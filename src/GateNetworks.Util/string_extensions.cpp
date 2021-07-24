#include "string_extensions.h"
#include "container_extensions.h"

namespace gate_networks::util
{
	bool StringExtensions::is_end(const std::string& value)
	{
		return value == "end";
	}

	bool StringExtensions::is_commentary(const std::string& value)
	{
		return value[0] == ';';
	}

	bool StringExtensions::is_connection_definition(const std::string& value)
	{
		return value.find("->") != std::string::npos;
	}

	bool StringExtensions::is_whitespace_only(const std::string& value)
	{
		for (auto&& c : value)
		{
			if (!isspace(c)) return false;
		}
		return true;
	}

	bool StringExtensions::is_network_definition(const std::string& value)
	{
		return value == "network";
	}

	bool StringExtensions::is_gate_definition(const std::string& value)
	{
		return value.rfind("gate", 0) == 0;
	}

	bool StringExtensions::is_inputs_definition(const std::string& value)
	{
		return value.rfind("inputs", 0) == 0;
	}

	bool StringExtensions::is_correct_name(const std::string& value)
	{
		return !(value.find(" ") != std::string::npos || value.find("\t") != std::string::npos || value.find("\n") != std::string::npos ||
			value.find(".") != std::string::npos || value.find(";") != std::string::npos || value.find("->") != std::string::npos ||
			(value.rfind("end", 0) == 0));
	}

	bool StringExtensions::is_outputs_definition(const std::string& value)
	{
		return value.rfind("outputs", 0) == 0;
	}

	bool StringExtensions::is_tri_state(const std::string& value)
	{
		std::vector<std::string> tokens;
		ContainerExtensions<std::vector<std::string>>::split(value, tokens);
		for (auto&& t : tokens)
		{
			if (t != "1" && t != "0" && t != "?") return false;
		}
		return true;
	}

	bool StringExtensions::can_be_ignored(const std::string& value)
	{
		return value.empty() || is_commentary(value) || is_whitespace_only(value);
	}
}