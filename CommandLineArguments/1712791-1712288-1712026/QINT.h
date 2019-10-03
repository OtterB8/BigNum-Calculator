#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <sstream>

using namespace std;

class QINT
{
private:
	int32_t m_qint[4];

public:
	// -----------------------------SCAN FROM STRING-----------------------------
	// Checking its negative
	bool checkNegative(string s);

	// Checking input string is number
	bool checkFormat(string& s);

	// Scanning
	void ScanBit(bool bits[]);
	void ScanQInt(bool bits[]);
	void ScanQIntFromBinString(string input); // Nhap tu chuoi nhi phan
	void ScanQIntFromHexString(string input); // Nhap tu chuoi thap luc phan
	void ScanQInt();

	// -----------------------------------Print-----------------------------------
	// Cong hai so thap phan kieu chuoi
	string AddStringNumber(string a, string b);

	// Nhan hai so thap phan kieu chuoi trong do co 1 so chi co 1 chu so
	string MultipleStringNumber(string a, string b);

	// In so thap phan kieu chuoi
	string PrintQintDec();

	// In so thap luc phan kieu chuoi
	string PrintQintHex();

	// In so nhi phan kieu chuoi
	string PrintQintBin();

	// -----------------------------------PARSE-----------------------------------
	// MAYBE ERROR
	void DecToBin(bool bits[128]) const;
	// Chuyen nhi phan sang thap phan (kieu QINT)
	QINT & BinToDec(bool *bits);

	// Chuyen nhi phan sng thap luc phan
	string BinToHex(bool bits[]);

	// Chuyen thap phan sang thap luc phan
	string DecToHex();

	// Chuyen ve bu 2
	QINT Bu2();

	// Chuyen dang bu 2 sang duong
	QINT Bu2ToDuong();

	// Chuyen tu QINT sang INT32_T (Neu khong du 32 bits thi tu dong thanh 0)
	int32_t QintToInt32();
public:
	QINT operator+(const QINT& q);
	QINT operator-(const QINT& q);
	QINT operator*(const QINT& M);
	QINT operator/(const QINT& M);

	QINT operator~() const;
	QINT operator&(const QINT& q);
	QINT operator|(const QINT& q);
	QINT operator^(const QINT& q);

	QINT operator<<(int x);
	QINT operator>>(int x);
	QINT rol(int x);
	QINT ror(int x);

	bool operator>(const QINT& q);
	bool operator<(const QINT& q);
	bool operator==(const QINT& q);
	bool operator<=(const QINT& q);
	bool operator>=(const QINT& q);
	QINT & operator=(const string& input);

public:
	QINT();
	~QINT();
};

