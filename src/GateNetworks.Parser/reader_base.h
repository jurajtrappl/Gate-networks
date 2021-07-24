#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace gate_networks::parser
{
	/// <summary>
	/// Defines properties and methods for readers or parsers.
	/// </summary>
	class ReaderBase
	{
	public:
		ReaderBase(std::istream& is)
			: is_(is)
			, line_("")
			, tokens_()
		{
		}

		/// <summary>
		/// Splits the content of the line_ by the space to the tokens_.
		/// </summary>
		void tokenize();
	protected:
		std::istream& is_;
		std::string line_;
		std::vector<std::string> tokens_;
	};
}