#pragma once

#include "components/gate_network.h"
#include <fstream>
#include <memory>
#include <string>

namespace gate_networks::application
{
	/// <summary>
	/// Input file processor.
	/// </summary>
	class InputParser
	{
	public:
		InputParser(std::ifstream& is) : is_(is)
		{
		}

		/// <summary>
		/// Parses the content of input file to the specified gate network.
		/// </summary>
		/// <param name=""></param>
		void parse_network(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::istream& is_;
	};
}