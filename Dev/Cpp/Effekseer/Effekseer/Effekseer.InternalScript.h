
#ifndef __EFFEKSEER_INTERNAL_SCRIPT_H__
#define __EFFEKSEER_INTERNAL_SCRIPT_H__

#include <array>
#include <stdint.h>
#include <vector>

namespace Effekseer
{

class InternalScript
{
	enum class OperatorType : int32_t
	{
		Constant = 0,
		Add = 1,
		Sub = 2,
		Mul = 3,
		Div = 4,
	};



private:
	std::vector<float> registers;
	std::vector<uint8_t> operators;
	int32_t version_ = 0;
	int32_t operatorCount_ = 0;
	int32_t outputRegister_ = 0;
	bool isValid_ = false;

public:
	InternalScript();
	virtual ~InternalScript();
	bool Load(uint8_t* data, int size);
	float Execute(const std::array<float, 4>& externals);
};

} // namespace Effekseer

#endif
