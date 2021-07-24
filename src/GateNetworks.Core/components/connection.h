#pragma once

#include "../logic/tri_state.h"

#include <memory>
#include <string>
#include <vector>

namespace gate_networks::core::components
{
	class AConnectible;
	typedef std::shared_ptr<AConnectible> Connectible_shared_ptr;

	/// <summary>
	/// Represents an edge between two instances.
	/// Three types:
	///     ga.ix->gb.oy
	///     ga.ix->iy
	///     ox->ga.oy
	/// </summary>
	class Connection
	{
	public:
		Connection(
			const std::string& instance_from,
			Connectible_shared_ptr to,
			const std::string& instance_to)
			: to_(to)
			, instance_from_(instance_from)
			, instance_to_(instance_to)
		{
		}

		/// <summary>
		/// Modifies the state of the given.
		/// </summary>
		/// <param name="">name of the instance to change.</param>
		/// <param name="">new value for the instance.</param>
		void change_state(const std::string& instance_name, logic::Tri_state new_state) const;

		/// <returns>name of the instance at the beginning of the connection.</returns>
		const std::string& instance_from() const;

		/// <returns>name of the instance at the end of the connection.</returns>
		const std::string& instance_to() const;
	private:
		std::string instance_from_;
		std::string instance_to_;
		Connectible_shared_ptr to_;
	};

	/// <summary>
	/// Base class for each instance that can be connected.
	/// </summary>
	class AConnectible 
	{
	public:
		AConnectible() : connections_()
		{
		}

		/// <summary>
		/// Adds a new connection.
		/// </summary>
		/// <param name="c">new connection</param>
		void add_connection(Connection c);

		/// <summary>
		/// Modifies the state of the instance with the given name to the given state.
		/// </summary>
		/// <param name="instance_name">name of the instance which state is about to change.</param>
		/// <param name="new_state">new value for state of the instance.</param>
		virtual void change_state(const std::string& instance_name, logic::Tri_state new_state) = 0;

		/// <summary>
		/// Gets the list of connections.
		/// </summary>
		const std::vector<Connection>& connections();

		/// <summary>
		/// Propagates the state of the input of the connection to the output.
		/// </summary>
		virtual void send() = 0;
	private:
		std::vector<Connection> connections_;
	};
}
