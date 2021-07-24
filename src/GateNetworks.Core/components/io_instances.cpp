#include "io_instances.h"
#include <algorithm>
#include <sstream>

using namespace std;

namespace gate_networks::core::components
{
	void IOInstances::push_back(const string& name, logic::Tri_state state)
	{
		instances_.emplace(name, state);
	}

	bool IOInstances::contains(const string& name) const
	{
		return instances_.find(name) != instances_.end();
	}

	bool IOInstances::contains_undefined() const
	{
		for (auto&& i : instances_)
		{
			if (i.second.value == nullopt)
			{
				return true;
			}
		}
		return false;
	}

	void IOInstances::all_new_unified_state(logic::Tri_state new_state)
	{
		for (auto&& s : instances_)
		{
			s.second = new_state;
		}
	}

	void IOInstances::all_new_specified_states(const vector<logic::Tri_state>& new_states)
	{
		int counter = 0;
		for (auto&& s : instances_)
		{
			s.second = new_states[counter];
			counter++;
		}
	}

	std::string IOInstances::stringify() const
	{
		std::stringstream ss;

		for (auto&& s : instances_)
		{
			ss << s.second;
			ss << " ";
		}

		//remove last space
		auto result = ss.str();
		if (result.size() > 0)
		{
			result.resize(result.size() - 1);
		}

		return result;
	}

	size_t IOInstances::size() const
	{
		return instances_.size();
	}

	logic::Tri_state IOInstances::instance_by_name(const string& name)
	{
		return instances_[name];
	}

	void IOInstances::new_state_for(const string& name, logic::Tri_state new_state)
	{
		instances_[name] = new_state;
	}

	void IOInstances::send()
	{
		for (auto&& c : connections())
		{
			c.change_state(
				c.instance_to(),
				instances_[c.instance_from()]);
		}
	}

	void IOInstances::change_state(const std::string& name, logic::Tri_state new_state)
	{
		new_state_for(name, new_state);
	}

	void IOInstances::extract_values_to(vector<logic::Tri_state>& values)
	{
		for (auto&& i : instances_) {
			values.push_back(i.second);
		}
	}
}