#ifndef __QFLOAT_H__
#define __QFLOAT_H__
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
//#include "StringQfloat.h"

using namespace std;

class Qfloat
{
public:
	static const int len = 128;
	static const int exponentLen = 15;
	static const int significandLen = 112;
	static const int bias = (1 << (exponentLen - 1)) - 1;
	static const int accuracy = 37;
private:
	uint32_t* a;
private:
	int GetDecimalPoint(string &s) const;
	int IntegerPartToBinary(string s, bool bit[], int len, int &e, int &precision);
	int FractionalPartToBinary(string s, bool bit[], int len, int &e, int &precision);
	int Rounding(bool bit[]);
	void SaveSign(int sign) const;
	void SaveExponent(int e) const;
	void SaveSignificand(bool significandBits[]);
	void StringToQfloat(string s);
	string SignificandValue() const;
	int ExponentValue() const;
	int GetSign() const;
	int GetIntegerPart() const;
	void Mul2(string& s) const;
	void Div2(string& s) const;
	void DelLeadingZero(string& s) const;
	int RemoveTailWithRound(string &s, int &e) const;
	void SignificandToBit(bool bit[]) const;
	void ShiftSignificandRight(int x, int &integerPart) const;
	void ShiftSignificandLeft(int x, int &integerPart) const;
	bool IsSignificandEqualZero(int integerPart) const;
	void AddPositiveSignificands(Qfloat x, int intX, Qfloat y, int intY, Qfloat &z, int &intZ) const;
	void SubPositiveSignificands(Qfloat x, int intX, Qfloat y, int intY, Qfloat &z, int &intZ) const;
	void AddSignedSignificands(Qfloat x, int intX, Qfloat y, int intY, Qfloat &z, int &intZ) const;
	int LeftmostBit(bool bit[], int n) const;
	void MulSigificands(Qfloat x, Qfloat y, bool bit[], int n) const;
	int CmpBit(bool bitX[], int lenX, bool bitY[], int lenY) const;
	int SubtractBit(bool bitX[], int lenX, bool bitY[], int lenY, bool bitZ[], int lenZ) const;
public:
	Qfloat();
	Qfloat(const Qfloat &other);
	Qfloat(const string &s);
	~Qfloat();
	void SetBit(int index, int bit) const;
	int GetBit(int index) const;
	friend istream& operator >> (istream& is, Qfloat& f);
	void PrintBits();
	string ToStringDec() const;
	friend ostream& operator << (ostream& os, const Qfloat& f);
	Qfloat BinToDec(bool *bit);
	void StringBinToDec(string s);
	bool *DecToBin(Qfloat x);
	//Qfloat operator >> (const int &x);
	bool IsZero() const;
	bool IsNaN() const;
	bool IsSubnormal() const;
	Qfloat &operator = (const Qfloat &other);
	Qfloat operator + (const Qfloat &other);
	Qfloat operator - (const Qfloat &other);
	Qfloat operator * (const Qfloat &other);
	Qfloat operator / (const Qfloat &other);
public:
	static Qfloat Zero;
	static Qfloat Infinity;
	static Qfloat NaN;
	static class _init {
	public:
		_init() {
			for (int i = 0; i < Zero.len; ++i) {
				Zero.SetBit(i, 0);
			}
			Infinity = Zero;
			for (int i = Infinity.significandLen; i < Infinity.significandLen + Infinity.exponentLen; ++i) {
				Infinity.SetBit(i, 1);
			}
			NaN = Infinity;
			NaN.SetBit(0, 1);
		}
	} _initializer;
};


#endif // __QFLOAT_H__
