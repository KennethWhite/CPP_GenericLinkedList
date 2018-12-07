#include "BigInteger.h"

//Kenneth White
//CSCD305 Spring, 2018

using namespace std;

BigInteger::BigInteger() {
	positive = true;
	digits.push_back(0);
	size = 1;
}


BigInteger::BigInteger(string number)
{
	positive = true;
	uint32_t index = 0;
	if (number[0] == '-') {
		positive = false;
		index++;
	}
	for (; index < number.length(); index++) {
		digits.push_back(number[index] - '0');
	}
	size = (positive) ? number.length() : number.length() - 1;
}

BigInteger::BigInteger(const BigInteger& other) {
	positive = other.isPositive();
	digits = other.getDigits();
	size = other.getSize();
}

BigInteger::~BigInteger()
{
}

istream& operator >> (istream& in, BigInteger& number) {
	string line;
	in >> line;
	number = BigInteger(line);
	return in;
}
ostream& operator << (ostream& out, const BigInteger& number) {
	if (!number.isPositive())
		out << '-';
	for (int n : number.getDigits()) {
		out << n;
	}
	return out;
}

BigInteger operator + (BigInteger& lhs, BigInteger& rhs) {
	BigInteger ret;
	BigInteger plhs, prhs;
	plhs = BigInteger(lhs);
	prhs = BigInteger(rhs);
	if (lhs.isPositive() != rhs.isPositive()) {// N + P / P + N == P - (-N)
		plhs = (lhs.isPositive()) ? BigInteger(lhs) : BigInteger(rhs);
		prhs = (lhs.isPositive()) ? BigInteger(rhs) : BigInteger(lhs);
		prhs.setPostive(true); 
		ret= plhs - prhs;
		return ret;
	}
	if (!lhs.isPositive() && !rhs.isPositive()) { // n + n == -(p + p)
		plhs.setPostive(true);
		prhs.setPostive(true);
		ret = plhs + prhs;
		ret.setPostive(false);
		return ret;
	}
	int diff = abs(lhs.getSize() - rhs.getSize());
	int size = (lhs.getSize() >= rhs.getSize()) ? lhs.getSize() : rhs.getSize();
	vector<int> shorterDigits = (lhs.getSize() >= rhs.getSize()) ? rhs.getDigits() : lhs.getDigits();
	vector<int> longerDigits = (lhs.getSize() >= rhs.getSize()) ? lhs.getDigits() : rhs.getDigits();

	vector<int>::iterator it = shorterDigits.begin();
	shorterDigits.insert(it, diff, 0); 

	vector<int> retDigits = ret.getDigits();
	retDigits.clear();
	int carry = 0, sum = 0;

	for (int index = size - 1; index >= 0; index--) {
		it = retDigits.begin();
		sum = shorterDigits.at(index) + longerDigits.at(index) + carry;
		carry = 0;
		if (sum > 9) {
			carry = sum / 10;
			sum = sum % 10;
		}
		retDigits.insert(it, sum);
	}
	if (carry > 0) {
		it = retDigits.begin();
		retDigits.insert(it, carry);
	}
	ret.setDigits(retDigits);
	return ret;
}

BigInteger operator - (BigInteger& lhs, BigInteger& rhs) {
	
	BigInteger ret;
	BigInteger plhs, prhs;
	plhs = BigInteger(lhs);
	prhs = BigInteger(rhs);
	if (!lhs.isPositive() && rhs.isPositive()) {// N - p == -(p + p)
		plhs.setPostive(true);
		ret = plhs + prhs;
		ret.setPostive(false);
		return ret;
	}
	if(lhs.isPositive() && !rhs.isPositive()){ // p - n == p + p
		prhs.setPostive(true);
		ret = plhs + prhs;
		return ret;
	}
	if (!lhs.isPositive() && !rhs.isPositive()) { // N - N == -(p - p)
		prhs.setPostive(true);
		plhs.setPostive(true);
		ret = plhs - prhs;
		bool sign = (ret.isPositive()) ? false : true;
		if (prhs == plhs) {
			sign = true;
		}
		ret.setPostive(sign);
		return ret;
	}
	
	
	bool flip = false;
	if (prhs > plhs) {
		flip = true;
		plhs = BigInteger(rhs);
		prhs = BigInteger(lhs);
	}

	int size = (plhs.getSize() >= prhs.getSize()) ? plhs.getSize() : prhs.getSize();
	vector<int> lhsDigits = plhs.getDigits();
	vector<int> rhsDigits = prhs.getDigits();

	vector<int>::iterator it;
	if (prhs.getSize() < plhs.getSize()) {
		it = rhsDigits.begin();
		int diff = abs(plhs.getSize() - prhs.getSize());
		rhsDigits.insert(it, diff, 0);
	}

	vector<int> retDigits = ret.getDigits();
	retDigits.clear();
	int carry = 0, difference = 0;

	for (int index = size - 1; index >= 0; index--) {
		it = retDigits.begin();
		difference = lhsDigits.at(index) - rhsDigits.at(index) + carry;
		carry = 0;
		if (difference < 0) {
			carry = -1;
			difference = difference+10;
		}
		retDigits.insert(it, difference);
	}

	BigInteger::removeLeadingZeros(retDigits);

	ret.setDigits(retDigits);
	if (flip) {
		ret.setPostive(false);
	}
	
	return ret;

 }

void BigInteger::removeLeadingZeros(vector<int> &retDigits) {
	while (!retDigits.empty() && retDigits.at(0) == 0) {
		if (retDigits.size()==1) {
			return;
		}
		retDigits.erase(retDigits.begin());
	}
}

BigInteger operator * (BigInteger& lhs, BigInteger& rhs) {
	BigInteger ret;
	BigInteger plhs, prhs;
	plhs = BigInteger(lhs);
	prhs = BigInteger(rhs);
	bool sign = !(plhs.isPositive() ^ prhs.isPositive());
	int size = (plhs.getSize() >= prhs.getSize()) ? plhs.getSize() : prhs.getSize();
	vector<int> lhsDigits = plhs.getDigits();
	vector<int> rhsDigits = prhs.getDigits();
	vector<int> retDigits = ret.getDigits();
	int carry = 0, product = 0;

	retDigits.clear();
	vector<int>::iterator it;
	vector<vector<int>> productsToSum;
	int numZeroes = 0;

	for (int index = plhs.getSize() - 1; index >= 0; index--) {
		for (int i = 0; i < numZeroes; i++) {
			retDigits.push_back(0);
		}
		for (int rhsIndex = prhs.getSize() - 1; rhsIndex >= 0; rhsIndex--) {
			it = retDigits.begin();
			product = lhsDigits.at(index) * rhsDigits.at(rhsIndex) + carry;
			carry = 0;
			if (product > 9) {
				carry = product/10;
				product = product % 10;
			}
			retDigits.insert(it, product);
		}
		if(carry > 0){
			it = retDigits.begin();
			retDigits.insert(it, carry);
		}
		productsToSum.push_back(retDigits);
		retDigits.clear();
		numZeroes++;
	}
	retDigits = BigInteger::sumVectors(productsToSum);
	ret.setDigits(retDigits);
	ret.setPostive(sign);
	return ret;
}

vector<int> BigInteger::sumVectors(vector<vector<int>> products) {
	if (products.size()== 1) {
		return products[0];
	}
	BigInteger lhs, rhs, sum;
	while (products.size() > 1) {
		lhs.setDigits(products[0]);
		rhs.setDigits(products[1]);
		products[0] = (lhs + rhs).getDigits();
		products.erase(products.begin() + 1);
	}
	return products[0];
}

 bool operator != (BigInteger& lhs, BigInteger& rhs) {
	 return !(lhs == rhs);
 }
 
 bool operator < (BigInteger& lhs, BigInteger& rhs) {
	 if (lhs.isPositive() < rhs.isPositive()) {
		 return true;
	 }
	 if (lhs.isPositive() > rhs.isPositive()) {
		 return false;
	 }
	 if (!lhs.isPositive() && !rhs.isPositive()) {
		 BigInteger temp, temp1;
		 temp = BigInteger(lhs);
		 temp1 = BigInteger(rhs);
		 temp.setPostive(true);
		 temp1.setPostive(true);
		 return temp > temp1;
	 }
	 if (lhs.getSize() < rhs.getSize()) {
		 return true;
	 }
	 if (rhs.getSize() < lhs.getSize()) {
		 return false;
	 }
	 vector<int> ldigs = lhs.getDigits();
	 vector<int> rdigs = rhs.getDigits();
	 int max = lhs.getSize(), tleft, tright;
	 for (int index = 0; index < max ; index++) {
		 tleft = ldigs.at(index);
		 tright = rdigs.at(index);
		 if (tleft < tright) {
			 return true;
		 }
		 if (tleft > tright) {
			 return false;
		 }
		 if (index == max-1 && tright == tleft) {
			 return false;
		 }
	 }
	 return true;
 }

 bool operator > (BigInteger& lhs, BigInteger& rhs) {
	 if (lhs.isPositive() > rhs.isPositive()) {
		 return true;
	 }
	 if (lhs.isPositive() < rhs.isPositive()) {
		 return false;
	 }
	 if (!lhs.isPositive() && !rhs.isPositive()) {
		 BigInteger temp, temp1;
		 temp = BigInteger(lhs);
		 temp1 = BigInteger(rhs);
		 temp.setPostive(true);
		 temp1.setPostive(true);
		 return temp < temp1;
	 }
	 if (lhs.getSize() > rhs.getSize()) {
		 return true;
	 }
	 if (rhs.getSize() > lhs.getSize()) {
		 return false;
	 }
	 vector<int> ldigs = lhs.getDigits();
	 vector<int> rdigs = rhs.getDigits();
	 int max = lhs.getSize(), tleft, tright;
	 for (int index = 0; index < max; index++) {
		 tleft = ldigs.at(index);
		 tright = rdigs.at(index);
		 if (tleft > tright) {
			 return true;
		 }
		 if (tleft < tright) {
			 return false;
		 }
		 if (index == max - 1 && tright == tleft) {
			 return false;
		 }
	 }
	 return true;
 }

 bool operator >= (BigInteger& lhs, BigInteger& rhs) {
	 return (lhs > rhs || lhs == rhs);
 }
 bool operator <= (BigInteger& lhs, BigInteger& rhs) {
	 return (lhs < rhs || lhs == rhs);
 }

 BigInteger operator += (BigInteger& lhs, BigInteger& rhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2.setDigits(rhs.getDigits());
	 temp2.setPostive(rhs.isPositive());
	 res = temp + temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return lhs;
 }

 BigInteger operator -= (BigInteger& lhs, BigInteger& rhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2.setDigits(rhs.getDigits());
	 temp2.setPostive(rhs.isPositive());
	 res = temp - temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return lhs;
 }
 BigInteger operator *= (BigInteger& lhs, BigInteger& rhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2.setDigits(rhs.getDigits());
	 temp2.setPostive(rhs.isPositive());
	 res = temp * temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return lhs;
 }

 BigInteger operator -- (BigInteger& lhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2 = BigInteger("1");
	 res = temp - temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return lhs;
 }
 BigInteger operator -- (BigInteger& lhs, int rhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2 = BigInteger("1");
	 res = temp - temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return lhs;
 }
 BigInteger operator ++ (BigInteger& lhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2 = BigInteger("1");
	 res = temp + temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return lhs;
 }
 BigInteger operator ++ (BigInteger& lhs, int rhs) {
	 BigInteger temp, temp2, res;
	 temp.setDigits(lhs.getDigits());
	 temp.setPostive(lhs.isPositive());
	 temp2 = BigInteger("1");
	 res = temp + temp2;
	 lhs.setDigits(res.getDigits());
	 lhs.setPostive(res.isPositive());
	 return temp;
 }

 bool operator == (const BigInteger& lhs, const BigInteger& rhs) {
	 if (lhs.getSize() != rhs.getSize()) {
		 return false;
	 }
	 if (lhs.isPositive() != rhs.isPositive()) {
		 return false;
	 }

	 vector<int> ldigs = lhs.getDigits();
	 vector<int> rdigs = rhs.getDigits();
	 int max = lhs.getSize(), tleft, tright;

	 for (int index = 0; index < max; index++) {
		 tleft = ldigs.at(index);
		 tright = rdigs.at(index);
		 if (!(tleft == tright)) {
			 return false;
		 }
	 }
	 return true;
 }