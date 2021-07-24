#include "functions.h"
#include "container_extensions.h"

using namespace std;

namespace gate_networks::core::components
{
	void Functions::add(const vector<logic::Tri_state>& input_values, const vector<logic::Tri_state>& output_values)
	{
		functions_.emplace(input_values, output_values);
	}

	bool Functions::contains(const vector<logic::Tri_state>& values)
	{
		return functions_.find(values) != functions_.end();
	}

	const std::vector<logic::Tri_state>& Functions::get(const vector<logic::Tri_state>& values)
	{
		return functions_[values];
	}
}