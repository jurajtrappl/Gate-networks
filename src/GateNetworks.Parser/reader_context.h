#pragma once

#include "components/gate_network.h"
#include "reader_base.h"
#include "gate/simple_gate_prototype_factory.h"

namespace gate_networks::parser
{
	/// <summary>
	/// Main reading loop handler working with the input file.
	/// </summary>
	class ReaderContext : public ReaderBase
	{
	public:
		ReaderContext(
			std::shared_ptr<core::components::GateNetwork> gate_network,
			std::istream& is)
			: ReaderBase(is)
			, current_line_number_(0)
			, gate_network_(gate_network)
			, networks_count_(0)
			, prototypes_(new gate::SimpleGatePrototypeFactory())
		{
		}

		~ReaderContext()
		{
			delete prototypes_;
		}

		/// <summary>
		/// Main reading loop processing the input file.
		/// </summary>
		void read();
	private:
		/// <summary>
		/// Contains prototypes of parsed gates.
		/// </summary>
		gate::SimpleGatePrototypeFactory* prototypes_;

		/// <summary>
		/// Total number of parsed gate networks.
		/// </summary>
		int networks_count_;

		/// <summary>
		/// Resulting gate network if correctly defined.
		/// </summary>
		std::shared_ptr<core::components::GateNetwork> gate_network_;

		/// <summary>
		/// Current line number in the input file.
		/// </summary>
		int current_line_number_;

		/// <returns>indicator if the minimum number of gates is present.</returns>
		int enough_gate_prototypes() const;

		/// <returns>indicator if the minimum number of gate network is present.</returns>
		bool enough_networks_parsed() const;

		/// <summary>
		/// Counts newly parsed gate network.
		/// </summary>
		void increment_networks_count();
	};
}
