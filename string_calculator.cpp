// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl;

unsigned int digit_to_decimal(char digit) {
	unsigned int int_digit = 0;
	if (digit >= 48 && digit <= 57) {
		int_digit = digit - 48;
	} else {
		throw std::invalid_argument("");
	}
	
    return int_digit;
}

char decimal_to_digit(unsigned int decimal) {
	char char_decimal = '0';
    if (decimal <= 9) {
		char_decimal = char_decimal + decimal;
	} else {
		throw std::invalid_argument("");
	}
    return char_decimal;
}

my_string trim_leading_zeros(const my_string& num) {
	
	my_string num1(num);
	
	if (num1.at(0) == '0') {
		unsigned int i = 0;
		while (num1[i] == '0') {
			if (i == num1.size() - 1) {
				break;
			}
			i++;
		}
		
		num1.erase(0, i);
	} else if (num1.at(0) == '-') {
		unsigned int i = 1;
		while (num1[i] == '0') {
			if (i == num1.size() - 1) {
				break;
			}
			i++;
		}
		
		num1.erase(1, i - 1);
		
		if (num1 == "-0") {
			num1.erase(0, 1);
		}
	}
    return num1;
}

my_string add(const my_string& lhs, const my_string& rhs) {
	my_string final_num = "0";
	int carry_bit = 0;
	char dig_sum = '0';
	bool negativeTotal = false;
	bool firstVal = false;
	
	my_string LHS(lhs);
	my_string RHS(rhs);
	
	if (rhs == "0") {
		final_num = lhs;
		return final_num;
	}
	if (lhs == "0") {
		final_num = rhs;
		return final_num;
	}
	
	if (LHS.at(0) == '-' && RHS.at(0) == '-') {
		
		LHS.erase(0,1);
		RHS.erase(0,1);
		
		LHS = trim_leading_zeros(LHS);
		RHS = trim_leading_zeros(RHS);
		
		LHS = '0' + LHS;
		RHS = '0' + RHS;
		
		if (RHS.size() > LHS.size()) {
			while (RHS.size() > LHS.size()) {
				LHS = '0' + LHS;
			}
		} else if (LHS.size() > RHS.size()) {
			while (LHS.size() > RHS.size()) {
				RHS = '0' + RHS;
			}
		}
		
		for (size_t i = 0; i < LHS.size(); i++) {
			dig_sum = carry_bit + (LHS.at(LHS.size() - 1 - i) + RHS.at(LHS.size() - 1 - i) - 48);
			if (dig_sum > '9') {
				carry_bit = 1;
				dig_sum = dig_sum - 10;
				
				if (final_num.size() == 1 && firstVal == false) {
					final_num[0] = dig_sum;
					firstVal = true;
				} else {
					final_num = dig_sum + final_num;
				}
			} else {
				carry_bit = 0;
				
				if (final_num.size() == 1 && firstVal == false) {
					final_num[0] = dig_sum;
					firstVal = true;
				} else {
					final_num = dig_sum + final_num;
				}
				
			}
		}
		
		final_num = trim_leading_zeros(final_num);
		final_num = '-' + final_num;
		
	} else if (LHS.at(0) != '-' && RHS.at(0) != '-') {
		LHS = trim_leading_zeros(LHS);
		RHS = trim_leading_zeros(RHS);
		
		LHS = '0' + LHS;
		RHS = '0' + RHS;
		
		if (RHS.size() > LHS.size()) {
			while (RHS.size() > LHS.size()) {
				LHS = '0' + LHS;
			}
		} else if (LHS.size() > RHS.size()) {
			while (LHS.size() > RHS.size()) {
				RHS = '0' + RHS;
			}
		}
		
		for (size_t i = 0; i < LHS.size(); i++) {
			dig_sum = carry_bit + (LHS.at(LHS.size() - 1 - i) + RHS.at(LHS.size() - 1 - i) - 48);
			if (dig_sum > '9') {
				carry_bit = 1;
				dig_sum = dig_sum - 10;
				
				if (final_num.size() == 1 && firstVal == false) {
					final_num[0] = dig_sum;
					firstVal = true;
				} else {
					final_num = dig_sum + final_num;
				}
			} else {
				carry_bit = 0;
				
				if (final_num.size() == 1 && firstVal == false) {
					final_num[0] = dig_sum;
					firstVal = true;
				} else {
					final_num = dig_sum + final_num;
				}
				
			}
		}
		
		final_num = trim_leading_zeros(final_num);
		
	}
	
	
	
	
	else if (LHS.at(0) == '-' && RHS.at(0) != '-') {
		
		LHS = LHS.erase(0, 1);
		LHS = trim_leading_zeros(LHS);
		RHS = trim_leading_zeros(RHS);
		
		LHS = '0' + LHS;
		RHS = '0' + RHS;
		
		if (RHS.size() > LHS.size()) {
			while (RHS.size() > LHS.size()) {
				LHS = '0' + LHS;
			}
			
			for (size_t i = 0; i < LHS.size(); i++) {
				dig_sum = carry_bit + (RHS.at(LHS.size() - 1 - i) - LHS.at(LHS.size() - 1 - i) + 48);
				if (dig_sum < '0') {
					carry_bit = -1;
					dig_sum = dig_sum + 10;
					
					if (final_num.size() == 1 && firstVal == false) {
						final_num[0] = dig_sum;
						firstVal = true;
					} else {
						final_num = dig_sum + final_num;
					}

				} else {
					carry_bit = 0;
					
					if (final_num.size() == 1 && firstVal == false) {
						final_num[0] = dig_sum;
						firstVal = true;
					} else {
						final_num = dig_sum + final_num;
					}
					
				}
			}
		} else if (LHS.size() > RHS.size()) {
			while (LHS.size() > RHS.size()) {
				RHS = '0' + RHS;
			}
				
			negativeTotal = true;
			
			for (size_t i = 0; i < LHS.size(); i++) {
				dig_sum = carry_bit + (LHS.at(LHS.size() - 1 - i) - RHS.at(LHS.size() - 1 - i) + 48);
				if (dig_sum < '0') {
					carry_bit = -1;
					dig_sum = dig_sum + 10;
					
					if (final_num.size() == 1 && firstVal == false) {
						final_num[0] = dig_sum;
						firstVal = true;
					} else {
						final_num = dig_sum + final_num;
					}
					
				} else {
					carry_bit = 0;
					
					if (final_num.size() == 1 && firstVal == false) {
						final_num[0] = dig_sum;
						firstVal = true;
					} else {
						final_num = dig_sum + final_num;
					}
					
				}
			}
		} else {
			
			for (size_t i = 0; i < LHS.size(); i++) {
				if (RHS[i] > LHS[i]) {
					negativeTotal = false;
					break;
				}
				if (LHS[i] > RHS[i]) {
					negativeTotal = true;
					break;
				}
			}
			if (RHS == LHS) {
				final_num = "0";
				return final_num;
			}
			
			if (negativeTotal) {
				for (size_t i = 0; i < LHS.size(); i++) {
					dig_sum = carry_bit + (LHS.at(LHS.size() - 1 - i) - RHS.at(LHS.size() - 1 - i) + 48);
					if (dig_sum < '0') {
						carry_bit = -1;
						dig_sum = dig_sum + 10;
					
						if (final_num.size() == 1 && firstVal == false) {
							final_num[0] = dig_sum;
							firstVal = true;
						} else {
							final_num = dig_sum + final_num;
						}
						
					} else {
						carry_bit = 0;
					
						if (final_num.size() == 1 && firstVal == false) {
							final_num[0] = dig_sum;
							firstVal = true;
						} else {
							final_num = dig_sum + final_num;
						}
						
					}
				}
			} else {
				for (size_t i = 0; i < LHS.size(); i++) {
					dig_sum = carry_bit + (RHS.at(LHS.size() - 1 - i) - LHS.at(LHS.size() - 1 - i) + 48);
					if (dig_sum < '0') {
						carry_bit = -1;
						dig_sum = dig_sum + 10;
					
						if (final_num.size() == 1 && firstVal == false) {
							final_num[0] = dig_sum;
							firstVal = true;
						} else {
							final_num = dig_sum + final_num;
						}
						
					} else {
						carry_bit = 0;
					
						if (final_num.size() == 1 && firstVal == false) {
							final_num[0] = dig_sum;
							firstVal = true;
						} else {
							final_num = dig_sum + final_num;
						}
						
					}
				}
			}
		}
	} else if (LHS.at(0) != '-' && RHS.at(0) == '-') {
		return add(RHS, LHS);
	}
	
	
	
	final_num = trim_leading_zeros(final_num);
	if (negativeTotal == true) {
		final_num = '-' + final_num;
	}
    return final_num;
}

my_string subtract(const my_string& lhs, const my_string& rhs) {
	my_string RHS(rhs);
	my_string LHS(lhs);
	
	if (rhs == lhs) {
		return ("0");
	}
	
	if (RHS.at(0) == '-') {
		RHS.erase(0, 1);
	} else {
		RHS = '-' + RHS;
	}
    
    return add(LHS, RHS);
}

my_string multiply(const my_string& lhs, const my_string& rhs) {
	my_string lhs1(lhs);
	my_string rhs1(rhs);
	
	bool negativeTotal = false;
	my_string final_num = "0";
	
	if (rhs1.at(0) == '-' && lhs1.at(0) != '-') {
		negativeTotal = true;
		rhs1 = rhs1.erase(0,1);
	}
	if (rhs1.at(0) != '-' && lhs1.at(0) == '-') {
		negativeTotal = true;
		lhs1 = lhs1.erase(0,1);
	}
	if (rhs1.at(0) == '-' && lhs1.at(0) == '-') {
		lhs1 = lhs1.erase(0,1);
		rhs1 = rhs1.erase(0,1);
	}
	
	my_string orig_lhs = lhs1;
	lhs1 = '0' + lhs1;
	int carry_bit = 0;
	int currLHS = 0;
	int currRHS = 0;
	int k = 0;
	my_string addnum;
	my_string origaddnum = addnum;
	
	for (size_t i = 0; i < rhs1.size(); ++i) {
		currRHS = digit_to_decimal(rhs1[rhs1.size() - 1 - i]);
		for (size_t j = 0; j < lhs1.size() ; ++j) {
			currLHS = digit_to_decimal(lhs1[lhs1.size() - 1 - j]);
			
			currLHS *= currRHS;
			currLHS += carry_bit;
			
			addnum = decimal_to_digit(currLHS % 10) + addnum;
			
			if (currLHS < 10) {
				carry_bit = 0;
			} else {
				carry_bit = currLHS / 10;
			}
		}
		
		for (int l = 0; l < k; ++l) {
			addnum = addnum + '0';
		}
		++k;
		
		final_num = add(addnum, final_num);
		addnum = origaddnum;
	}
	
	lhs1 = orig_lhs;
	
	final_num = trim_leading_zeros(final_num);
	if (negativeTotal) {
		final_num = '-' + final_num;
	}
	
    return final_num;
}