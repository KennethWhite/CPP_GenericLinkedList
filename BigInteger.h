#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

/*
Kenneth White
CSCD 305 8:00 Spring 18
Assignment 2 - Operator overload, dynamic memory allocation, robust class design

Shortcomings:
	None that I know of

Compilation details :
	Compile using g++ *.cpp

	I used Microsoft Visual C++ compiler via Visual Studio 2017
	I also used g++ version 7.2.0 via MinGW64

Operators implemented:
	 >>
	 <<
	 =
	 <
	 >
	 ==
	 !=
	 >=
	 <=
	 +
	 +=
	 ++
	 -
	 -=
	 --
	 *
	 *=

*/



class BigInteger
{
private:
	std::vector<int> digits;
	bool positive;
	int size;
	
	//helpers
	static void removeLeadingZeros(std::vector<int> &retDigits);
	static std::vector<int> sumVectors(std::vector<std::vector<int>> products);

public:
	//CTORs
	BigInteger();
	BigInteger(std::string number);
	BigInteger(const BigInteger& other);
	~BigInteger();

	//Accessors
	bool isPositive() const { return positive; }
	std::vector<int> getDigits() const { return digits; }
	int getSize() const { return size; }
	
	//Mutators
	void setPostive(bool pos) { positive = pos; }
	void setDigits(std::vector<int> newDigits) { digits = newDigits; size = newDigits.size(); }

	//Operators
	friend BigInteger operator+ (BigInteger& lhs, BigInteger& rhs);
	friend BigInteger operator- (BigInteger& lhs, BigInteger& rhs);
	friend BigInteger operator* (BigInteger& lhs, BigInteger& rhs);
	
	friend bool operator != (BigInteger& lhs, BigInteger& rhs);
	friend bool operator < (BigInteger& lhs, BigInteger& rhs);
	friend bool operator > (BigInteger& lhs, BigInteger& rhs);
	friend bool operator >= (BigInteger& lhs, BigInteger& rhs);
	friend bool operator <= (BigInteger& lhs, BigInteger& rhs);
	friend BigInteger operator += (BigInteger& lhs, BigInteger& rhs);
	friend BigInteger operator -= (BigInteger& lhs, BigInteger& rhs);
	friend BigInteger operator *= (BigInteger& lhs, BigInteger& rhs);
	friend BigInteger operator -- (BigInteger& lhs);
	friend BigInteger operator -- (BigInteger& lhs, int rhs);
	friend BigInteger operator ++ (BigInteger& lhs);
	friend BigInteger operator ++ (BigInteger& lhs, int rhs);
};

std::ostream& operator<< (std::ostream& out, const BigInteger& number);
std::istream& operator>> (std::istream& in, BigInteger& number);
bool operator == (const BigInteger& lhs, const BigInteger& rhs);