#include "connection.h"

using namespace std;

namespace gate_networks::core::components {
	const string& Connection::instance_from() const {
		return instance_from_;
	}

	const string& Connection::instance_to() const {
		return instance_to_;
	}

	void AConnectible::add_connection(Connection c) {
		connections_.push_back(c);
	}

	const vector<Connection>& AConnectible::connections() {
		return connections_;
	}

	void Connection::change_state(const string& instance_name, logic::Tri_state new_state) const {
		to_->change_state(instance_name, new_state);
	}
}