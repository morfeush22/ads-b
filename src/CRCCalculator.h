/*
 * CRCCalculator.h
 *
 *  Created on: 22Jun.,2017
 *      Author: morfeush22
 */

#ifndef SRC_CRCCALCULATOR_H_
#define SRC_CRCCALCULATOR_H_

#include <array>
#include <ctype.h>

#define BYTE 8
#define LOOKUP_TABLE_SIZE 256
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
