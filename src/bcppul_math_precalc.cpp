//src/bcppul_math_precalc.cpp
#include "bcppul/bcppul_math_precalc.h"

namespace bcppul {
	Precalculation::Precalculation()
	{

	}
	Precalculation::~Precalculation()
	{
		delete[] sinuses;
		sinuses = nullptr;
	}

	void Precalculation::precalculateSinuses(unsigned long long amount){
		this->amount = amount;
		if (sinuses != nullptr) {
			delete sinuses;
		}
		sinuses = new float[amount];
		step = HALF_PI / amount;
		for (size_t i = 0; i < amount; ++i){
			sinuses[i] = std::sinf(step * i);
		}
	}

	float Precalculation::getSin(float angle) {
		if (sinuses == nullptr) {
			return std::sin(angle);
		}
		angle = std::fmod(angle, TAU);
		if (angle < 0) {
			angle += TAU;
		}

		float result;

		if (angle < HALF_PI) {
			result = sinuses[static_cast<long long>(angle * amount / HALF_PI)];
		}
		else if (angle < PI) {
			result = sinuses[static_cast<long long>((PI - angle) * amount / HALF_PI)];
		}
		else if (angle < ONE_AND_HALF_PI) {
			result = -sinuses[static_cast<long long>((angle - PI) * amount / HALF_PI)];
		}
		else {
			result = -sinuses[static_cast<long long>((TAU - angle) * amount / HALF_PI)];
		}

		return result;
	}

	inline float Precalculation::getCos(float angle)
	{
		return getSin(angle + HALF_PI);
	}

	inline float Precalculation::getTan(float angle)
	{
		return getSin(angle) / getCos(angle);
	}
	inline float Precalculation::getCot(float angle)
	{
		return 1 / precalculation.getTan(angle);
	}

	inline float sin(float angle) {
		return precalculation.getSin(angle);
	}
	inline float cos(float angle) {
		return precalculation.getCos(angle);
	}
	inline float tan(float angle) {
		return precalculation.getTan(angle);
	}
	inline float cot(float angle) {
		return 1 / precalculation.getTan(angle);
	}


} // namespace bcppul