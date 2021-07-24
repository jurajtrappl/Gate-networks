#include "simple_gate_prototype_factory.h"

using namespace std;

namespace gate_networks::parser::gate
{
	bool SimpleGatePrototypeFactory::contains(const std::string& name)
	{
		return prototypes_.find(name) != prototypes_.end();
	}

	void SimpleGatePrototypeFactory::register_prototype(Simple_gate_unique_ptr new_prototype)
	{
		if (prototypes_.find(new_prototype->name()) != prototypes_.end())
		{
			return;
		}
		prototypes_.emplace(new_prototype->name(), move(new_prototype));
	}

	Simple_gate_unique_ptr SimpleGatePrototypeFactory::create(const string& name)
	{
		auto cloned = prototypes_[name]->clone();
		return move(cloned);
	}
}