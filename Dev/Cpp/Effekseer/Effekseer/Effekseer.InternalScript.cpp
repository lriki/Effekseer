#include "Effekseer.InternalScript.h"

namespace Effekseer
{

bool InternalScript::IsValidOperator(int value) const
{
	if (0 <= value && value <= 4)
		return true;
	if (11 <= value && value <= 12)
		return true;

	return false;
}

InternalScript::InternalScript() {}

InternalScript ::~InternalScript() {}
bool InternalScript::Load(uint8_t* data, int size)
{
	if (size < 16)
		return false;

	int32_t registerCount = 0;

	memcpy(&version_, data + sizeof(int) * 0, sizeof(int));
	memcpy(&registerCount, data + sizeof(int) * 1, sizeof(int));
	memcpy(&operatorCount_, data + sizeof(int) * 2, sizeof(int));
	memcpy(&outputRegister_, data + sizeof(int) * 3, sizeof(int));

	if (registerCount < 0)
		return false;

	registers.resize(registerCount);

	if ((outputRegister_ < 0 || outputRegister_ >= registers.size()) && outputRegister_ != (0xfff + 0) && outputRegister_ != (0xfff + 1) &&
		outputRegister_ != (0xfff + 2) && outputRegister_ != (0xfff + 3))
	{
		return false;
	}

	operators.resize(size - 16);
	memcpy(operators.data(), data + sizeof(int) * 4, size - 16);

	// check operators
	int offset = 0;
	for (int i = 0; i < operatorCount_; i++)
	{
		// type
		OperatorType type;
		if (offset + 4 > operators.size())
			return false;

		memcpy(&type, operators.data() + offset, sizeof(OperatorType));
		offset += sizeof(int);

		if (!IsValidOperator((int)type))
			return false;

		// input
		if (offset + 4 > operators.size())
			return false;

		int32_t inputCount = 0;
		memcpy(&inputCount, operators.data() + offset, sizeof(int));
		offset += sizeof(int);

		for (int j = 0; j < inputCount; j++)
		{
			if (offset + 4 > operators.size())
				return false;
			int index = 0;
			memcpy(&index, operators.data() + offset, sizeof(int));
			offset += sizeof(int);

			if ((index < 0 || index >= registers.size()) && index != (0xfff + 0) && index != (0xfff + 1) && index != (0xfff + 2) &&
				index != (0xfff + 3))
			{
				return false;
			}
		}

		// output
		if (offset + 4 > operators.size())
			return false;

		int32_t outputCount = 0;
		memcpy(&outputCount, operators.data() + offset, sizeof(int));
		offset += sizeof(int);

		for (int j = 0; j < outputCount; j++)
		{
			if (offset + 4 > operators.size())
				return false;
			int index = 0;
			memcpy(&index, operators.data() + offset, sizeof(int));
			offset += sizeof(int);

			if ((index < 0 || index >= registers.size()))
			{
				return false;
			}
		}

		// attribute
		if (offset + 4 > operators.size())
			return false;

		int32_t attributeCount = 0;
		memcpy(&attributeCount, operators.data() + offset, sizeof(int));
		offset += sizeof(int);

		for (int j = 0; j < attributeCount; j++)
		{
			if (offset + 4 > operators.size())
				return false;
			int index = 0;
			memcpy(&index, operators.data() + offset, sizeof(int));
			offset += sizeof(int);
		}
	}

	if (offset != operators.size())
		return false;

	isValid_ = true;

	return true;
}

float InternalScript::Execute(const std::array<float, 4>& externals)
{
	if (!isValid_)
		return 0.0f;

	int offset = 0;
	for (int i = 0; i < operatorCount_; i++)
	{
		// type
		OperatorType type;
		memcpy(&type, operators.data() + offset, sizeof(OperatorType));
		offset += sizeof(int);

		int32_t inputCount = 0;
		memcpy(&inputCount, operators.data() + offset, sizeof(int));
		offset += sizeof(int);

		std::array<float, 4> tempInputs;

		for (int j = 0; j < inputCount; j++)
		{
			int index = 0;
			memcpy(&index, operators.data() + offset, sizeof(int));
			offset += sizeof(int);

			if (index < registers.size())
			{
				tempInputs[j] = registers[index];
			}
			else
			{
				tempInputs[j] = externals[index - 0xfff];
			}
		}

		int32_t outputCount = 0;
		memcpy(&outputCount, operators.data() + offset, sizeof(int));
		offset += sizeof(int);

		int outputIndex = -1;

		for (int j = 0; j < outputCount; j++)
		{
			int index = 0;
			memcpy(&index, operators.data() + offset, sizeof(int));
			offset += sizeof(int);

			if (type == OperatorType::Add)
				registers[index] = tempInputs[0] + tempInputs[1];
			else if (type == OperatorType::Sub)
				registers[index] = tempInputs[0] - tempInputs[1];
			else if (type == OperatorType::Mul)
				registers[index] = tempInputs[0] * tempInputs[1];
			else if (type == OperatorType::Div)
				registers[index] = tempInputs[0] / tempInputs[1];
			else if (type == OperatorType::UnaryAdd)
				registers[index] = tempInputs[0];
			else if (type == OperatorType::UnarySub)
				registers[index] = - tempInputs[0];
			else if (type == OperatorType::Constant)
				outputIndex = index;
		}

		int32_t attributeCount = 0;
		memcpy(&attributeCount, operators.data() + offset, sizeof(int));
		offset += sizeof(int);

		for (int j = 0; j < attributeCount; j++)
		{
			float att = 0;
			memcpy(&att, operators.data() + offset, sizeof(int));
			offset += sizeof(int);

			if (type == OperatorType::Constant)
				registers[outputIndex] = att;
		}
	}

	return registers[outputRegister_];
}

} // namespace Effekseer