/*
 * CRCCalculator.h
 *
 *  Created on: 22Jun.,2017
 *      Author: morfeush22
 */

#ifndef SRC_CRCCALCULATOR_H_
#define SRC_CRCCALCULATOR_H_

#include <algorithm>
#include <array>
#include <ctype.h>
#include <vector>

#define BYTE 8
#define LOOKUP_TABLE_SIZE 256
#define REG_FINAL UINT32_MAX
#define REG_INIT UINT32_MAX
#define TOP_BIT_MASK 0x1


template<typename T>
class CRCCalculator {
public:
	CRCCalculator(T poly);
	virtual ~CRCCalculator();
	T poly() const {
		return poly_;
	}
	std::array<T, LOOKUP_TABLE_SIZE> lookup_table() const {
		return lookup_table_;
	}
	T CalculateCRC(const std::vector<uint8_t> &msg);

private:
	void CalculateLookupTable();

	T poly_;
	std::array<T, LOOKUP_TABLE_SIZE> lookup_table_;
};

template<typename T>
CRCCalculator<T>::CRCCalculator(T poly): poly_(poly) {
	CalculateLookupTable();
}

template<typename T>
CRCCalculator<T>::~CRCCalculator() {
}

template<typename T>
T CRCCalculator<T>::CalculateCRC(const std::vector<uint8_t> &msg) {
	T reg = REG_INIT;
	std::for_each(msg.begin(), msg.end(), [&reg, this](const uint8_t &byte) {
		reg = (reg >> BYTE) ^ lookup_table_[static_cast<uint8_t>(reg) ^ byte];
	});
	return reg ^ REG_FINAL;
}

template<typename T>
void CRCCalculator<T>::CalculateLookupTable() {
	for (int i = 0; i < LOOKUP_TABLE_SIZE; ++i) {
		T reg = static_cast<T>(i);
		for (int j = 0; j < BYTE; ++j) {
			if ((reg & TOP_BIT_MASK) == 1)
				reg = (reg >> 1) ^ poly_;
			else
				reg >>= 1;
		}
		lookup_table_[i] = reg;
	}
}

#endif /* SRC_CRCCALCULATOR_H_ */
