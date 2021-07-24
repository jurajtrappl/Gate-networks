#pragma once

#include "network_definitions.h"
#include "connection_type.h"

namespace gate_networks::parser::network
{
	/// <summary>
	/// Connection type: ga.ix->gb.oy.
	/// </summary>
	class InnerToInnerConnection : public AConnectionType
	{
	public:
		/// AConnectionType implementation.
		void configure(const network::ArrowTokens&, int);
		
		/// AConnectionType implementation.
		void connect(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::string gate_from_name_;
		std::string gate_from_output_name_;
		std::string gate_to_name_;
		std::string gate_to_input_name_;
	};

	/// <summary>
	/// Connection type: ga.ix->iy.
	/// </summary>
	class InputToInnerConnection : public AConnectionType
	{
	public:
		/// AConnectionType implementation.
		void configure(const network::ArrowTokens&, int);

		/// AConnectionType implementation.
		void connect(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::string gate_to_name_;
		std::string gate_to_instance_name_;
		std::string network_input_name_;
	};

	/// <summary>
	/// Connection type: ox->ga.oy.
	/// </summary>
	class InnerToOutputConnection : public AConnectionType
	{
	public:
		/// AConnectionType implementation.
		void configure(const ArrowTokens&, int);

		/// AConnectionType implementation.
		void connect(std::shared_ptr<core::components::GateNetwork>);
	private:
		std::string network_output_name_;
		std::string gate_from_name_;
		std::string gate_from_output_name_;
	};
}