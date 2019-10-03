#include "QINT.h"



QINT::QINT()
{
	for (int i = 0; i < 4; i++)
	{
		m_qint[i] = 0;
	}
}


QINT::~QINT()
{
}

// -----------------------------SCAN FROM STRING-----------------------------
	// Checking its negative
bool QINT::checkNegative(string s)
{
	return s[0] == '-';
}

// Checking input string is number
bool QINT::checkFormat(string& s)
{
	string tmp = "0";

	for (size_t i = checkNegative(s); i <= s.length(); i++)
	{
		if (i < s.length() && '0' <= s[i] && s[i] <= '9')
			tmp += s[i];
		else
		{
			s = tmp;
			return 0;
		}
	}

	return 1;
}

// Scanning
void QINT::ScanBit(bool bits[])
{
	string input, tmp_input;
	cin >> input;
	tmp_input = input;

	checkFormat(input);

	//bool bits[128] = { 0 };
	int index = 0;
	do
	{
		int tmp = 0;
		string rs = "";

		for (rsize_t i = 0; i < input.length(); i++)
		{
			tmp += input[i] - '0';

			if (i == 0 && tmp < 2 && i < input.length() - 1)
			{
				tmp = 10 * tmp + input[i + 1] - '0';
				i++;
			}

			rs += tmp / 2 + '0';
			tmp %= 2;
			tmp *= 10;
		}

		input = rs;
		bits[index++] = (tmp / 10) % 2;
	} while (input != "0" && index < 128);

	ScanQInt(bits);

	if (checkNegative(tmp_input)) *this = this->Bu2();

	if (input != "0")
	{
		if (!checkNegative(tmp_input))
		{
			m_qint[3] = -1;
			m_qint[2] = -1;
			m_qint[1] = -1;
			m_qint[0] = INT32_MAX;
		}
		else
		{
			m_qint[3] = 0;
			m_qint[2] = 0;
			m_qint[1] = 0;
			m_qint[0] = INT32_MIN;
		}
	}
}
void QINT::ScanQInt(bool bits[])
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 32; j++)
		{
			m_qint[i] = (bits[96 - i * 32 + j] << j) | m_qint[i];
		}
	}
}
void QINT::ScanQIntFromBinString(string input)
{
	bool bits[128] = { 0 };

	for (int i = input.length() - 1, j = 0; i >= 0 && j < 128; i--, j++)
	{
		bits[j] = input[i] - '0';
	}

	for (int i = 0; i < 4; i++)
	{
		m_qint[i] = 0;
	}
	BinToDec(bits);
}
void QINT::ScanQIntFromHexString(string input)
{
	string table[] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" },
		result;

	for (int i = 0; i < input.length(); i++)
	{
		string tmp;
		switch (input[i])
		{
		case '0': tmp = table[0]; break;
		case '1': tmp = table[1]; break;
		case '2': tmp = table[2]; break;
		case '3': tmp = table[3]; break;
		case '4': tmp = table[4]; break;
		case '5': tmp = table[5]; break;
		case '6': tmp = table[6]; break;
		case '7': tmp = table[7]; break;
		case '8': tmp = table[8]; break;
		case '9': tmp = table[9]; break;
		case 'A': tmp = table[10]; break;
		case 'B': tmp = table[11]; break;
		case 'C': tmp = table[12]; break;
		case 'D': tmp = table[13]; break;
		case 'E': tmp = table[14]; break;
		case 'F': tmp = table[15]; break;
		default: break;
		}
		result += tmp;
	}
	this->ScanQIntFromBinString(result);
}
void QINT::ScanQInt()
{
	bool bits[128] = { 0 };

	ScanBit(bits);

	/*for (int i = 0; i < 128; i++)
	{
	cout << bits[127 - i] << "";
	}
	cout << endl;
	for (size_t i = 0; i < 4; i++)
	{
		cout << m_qint[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 31; j >= 0; j--)
		{
			int tmp = (m_qint[i] >> (j)) & 1;
			cout << tmp;
		}
	}*/
}

// -----------------------------------Print-----------------------------------
// Cong hai so thap phan kieu chuoi
string QINT::AddStringNumber(string a, string b)
{
	string result = "",
		tmp_0 = "";
	int length = a.length() - b.length();

	// Can bang do dai cho 2 chuoi bang cach them chuoi gom cac chu so 0 vao chuoi nho hon
	for (int i = 0; i < abs(length); i++)
	{
		tmp_0 += "0";
	}
	if (length > 0) b = tmp_0 + b;
	else if (length < 0) a = tmp_0 + a;

	// Thuc hien cong hai chuoi thap phan
	int nho = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int a_0 = a[i] - '0',
			b_0 = b[i] - '0',
			c = a_0 + b_0 + nho;

		nho = c / 10;
		result += c % 10 + '0';
	}

	if (nho) result += nho + '0';
	reverse(result.begin(), result.end());

	return result;
}

// Nhan hai so thap phan kieu chuoi trong do co 1 so chi co 1 chu so
string QINT::MultipleStringNumber(string a, string b)
{
	string result = "", // Chua ket qua
		tmp_str; // Luu so co nhieu chu so
	int tmp_num; // Luu so co 1 chu so
	if (a.length() == 1)
	{
		tmp_str = b;
		tmp_num = a[0] - '0';
	}
	else if (b.length() == 1)
	{
		tmp_str = a;
		tmp_num = b[0] - '0';
	}
	else return result;

	int nho = 0; // Bien nho
	for (int i = tmp_str.length() - 1; i >= 0; i--)
	{
		int t_0 = (tmp_str[i] - '0') * tmp_num + nho; // Nhan tung so
		nho = t_0 / 10; // Tinh nho
		result += (t_0 % 10) + '0';
	}

	if (nho) result += nho + '0'; // Neu con nho thi them vao


	// Xoa cac so 0 du o dau
	while (result.length() > 1 && result[result.length() - 1] == '0')
	{
		result.pop_back();
	}

	// Dao chuoi
	reverse(result.begin(), result.end());

	return result;
}

// In so thap phan kieu chuoi
string QINT::PrintQintDec()
{
	bool bits[128],
		sign = 0;
	string result = "0",
		tmp = "1";

	DecToBin(bits);

	// Kiem tra am
	if (bits[127] == 1)
	{
		Bu2ToDuong().DecToBin(bits);
		sign = 1;
	}

	for (int i = 0; i < 128; i++)
	{
		if (bits[i])
		{
			result = AddStringNumber(result, tmp);
		}

		tmp = MultipleStringNumber(tmp, "2");
	}

	// Them dau tru neu la so am
	if (sign == 1) result = "-" + result;

	return result;
}

// In so thap luc phan kieu chuoi
string QINT::PrintQintHex()
{
	return DecToHex();
}

// In so nhi phan kieu chuoi
string QINT::PrintQintBin()
{
	bool bits[128];
	string result = "";
	DecToBin(bits);

	for (int i = 0; i < 128; i++)
	{
		result += bits[i] + '0';
	}

	for (int i = 127; i > 0; i--)
	{
		if (result[i] == '0') result.pop_back();
		else break;
	}

	reverse(result.begin(), result.end());

	return result;
}

// -----------------------------------PARSE-----------------------------------
// MAYBE ERROR
void QINT::DecToBin(bool bits[128]) const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			bits[i * 32 + j] = (m_qint[3 - i] >> j) & 1;
		}
	}
}

// Chuyen nhi phan sang thap phan (kieu QINT)
QINT & QINT::BinToDec(bool *bits)
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 32; j++)
		{
			m_qint[i] = (bits[96 - i * 32 + j] << j) | m_qint[i];
		}
	}
	return *this;
}

// Chuyen nhi phan sng thap luc phan
string QINT::BinToHex(bool bits[])
{
	string result = "";
	string table[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };

	int tmp = 0;

	for (int i = 3; i < 128; i += 4)
	{
		for (int j = 0; j < 4; j++)
		{
			if (bits[i - j]) tmp++;
			if (j < 3) tmp = tmp << 1;
		}

		result += table[tmp];
		tmp = 0;
	}

	while (result.length() != 1 && result[result.length() - 1] == '0')
	{
		result.pop_back();
	}

	reverse(result.begin(), result.end());
	return result;
}

// Chuyen thap phan sang thap luc phan
string QINT::DecToHex()
{
	bool bits[128];
	this->DecToBin(bits);

	return this->BinToHex(bits);
}

// Chuyen ve bu 2
QINT QINT::Bu2()
{
	QINT tmp;
	QINT t;
	t.m_qint[3]++;
	tmp = (~(*this) + t);
	return tmp;
}

// Chuyen dang bu 2 sang duong
QINT QINT::Bu2ToDuong()
{
	QINT tmp;
	QINT t;
	t.m_qint[3]++;
	tmp = (~(*this - t));
	return tmp;
}

// Chuyen tu QINT sang INT32_T (Neu khong du 32 bits thi tu dong thanh 0)
int32_t QINT::QintToInt32()
{
	if (m_qint[0] == 0 && m_qint[1] == 0 && m_qint[2] == 0)
		return m_qint[3];
	else
		return 0;
}

QINT QINT::operator+(const QINT& q)
{
	bool bits[3][128];
	int nho = 0;

	q.DecToBin(bits[0]);
	this->DecToBin(bits[1]);

	for (int i = 0; i < 128; i++)
	{
		bits[2][i] = (bits[0][i] + bits[1][i] + nho) % 2;
		nho = (bits[0][i] + bits[1][i] + nho) / 2;
	}

	QINT tmp;
	return tmp.BinToDec(bits[2]);
}
QINT QINT::operator-(const QINT& q)
{
	QINT t;
	t.m_qint[3]++;
	return *this + (~q + t);
}
QINT QINT::operator*(const QINT& M)
{
	QINT A, Q = *this;
	bool Q_1 = 0;
	int step = 0;

	while (step < 128)
	{
		bool Q_0 = Q.m_qint[3] & 1;

		if (Q_0 > Q_1) A = A - M;
		else if (Q_0 < Q_1) A = A + M;

		bool A_0 = A.m_qint[3] & 1;

		Q_1 = Q_0;
		Q = Q >> 1;
		if (A_0) Q.m_qint[0] = (A_0 << 31) | Q.m_qint[0];
		else Q.m_qint[0] = (INT32_MAX)& Q.m_qint[0];
		A = A >> 1;

		step++;
	}

	return Q;
}
QINT QINT::operator/(const QINT& M)
{
	QINT A,
		Q = *this,
		M1 = M,
		tmp_0; // Dai dien cho so 0
	int step = 0,
		sign = 0; // Xet dau

	// Kiem tra cung dau : sign = 0, 2 cung dau va sign = 1 khac dau
	if (((M1.m_qint[0] >> 31) & 1))
	{
		M1 = M1.Bu2ToDuong();
		sign++;
	}
	if (((Q.m_qint[0] >> 31) & 1))
	{
		Q = Q.Bu2ToDuong();
		sign++;
	}

	while (step < 128)
	{
		int32_t Q_32 = (Q.m_qint[0] >> 31) & 1; // Lay bit cuoi cung cua Q

		// Step 1: Shilf left A, Q
		Q = Q << 1;
		A = A << 1;
		if (Q_32) A.m_qint[3] = (Q_32 | A.m_qint[3]); // Thay doi bit dau tien cua A thanh bit cuoi cung cua Q
		else A.m_qint[3] = (-2) & A.m_qint[3];


		// Step 2
		A = A - M1;

		if (A < tmp_0)
		{
			Q.m_qint[3] = ((int32_t)(-2)) & Q.m_qint[3]; // Gan Q_0 = 0
			A = A + M1;
		}
		else
		{
			Q.m_qint[3] = 1 | Q.m_qint[3]; // Gan Q_0 = 1
		}

		// Step 3
		step++;
	}

	if (sign == 1) Q = Q.Bu2();
	return Q;
}

QINT QINT::operator~() const
{
	QINT tmp = *this;
	for (int i = 0; i < 4; i++)
	{
		tmp.m_qint[i] = ~tmp.m_qint[i];
	}
	return tmp;
}
QINT QINT::operator&(const QINT& q)
{
	QINT tmp;
	bool bits[3][128];
	q.DecToBin(bits[0]);
	this->DecToBin(bits[1]);

	for (int i = 0; i < 128; i++)
	{
		bits[2][i] = bits[0][i] & bits[1][i];
	}

	return tmp.BinToDec(bits[2]);
}
QINT QINT::operator|(const QINT& q)
{
	QINT tmp;
	bool bits[3][128];
	q.DecToBin(bits[0]);
	this->DecToBin(bits[1]);

	for (int i = 0; i < 128; i++)
	{
		bits[2][i] = bits[0][i] | bits[1][i];
	}

	return tmp.BinToDec(bits[2]);
}
QINT QINT::operator^(const QINT& q)
{
	QINT tmp;
	bool bits[3][128];
	q.DecToBin(bits[0]);
	this->DecToBin(bits[1]);

	for (int i = 0; i < 128; i++)
	{
		bits[2][i] = bits[0][i] ^ bits[1][i];
	}

	return tmp.BinToDec(bits[2]);
}

QINT QINT::operator<<(int x)
{
	bool bits[128];
	this->DecToBin(bits);

	for (int i = 127 - x; i >= 0; i--)
	{
		bits[i + x] = bits[i];
	}

	for (int i = 0; i < x; i++)
	{
		bits[i] = 0;
	}

	QINT tmp;
	return tmp.BinToDec(bits);
}
QINT QINT::operator>>(int x)
{
	bool bits[128];
	this->DecToBin(bits);

	for (int i = x; i < 128; i++)
	{
		bits[i - x] = bits[i];
	}

	for (int i = 127 - x; i < 128; i++)
	{
		bits[i] = bits[127];
	}

	QINT tmp;
	return tmp.BinToDec(bits);
}
QINT QINT::rol(int x)
{
	//return ((*this << x) | (*this >> (128 - x)));
	QINT tmp;
	bool bits[128];
	int tmp_bits;

	this->DecToBin(bits);
	tmp_bits = bits[127];

	for (int i = 126; i >= 0; i--)
	{
		bits[i + 1] = bits[i];
	}
	bits[0] = tmp_bits;

	tmp.BinToDec(bits);
	return tmp;
}
QINT QINT::ror(int x)
{
	//return ((*this >> x) | (*this << (128 - x)));
	QINT tmp;
	bool bits[128];
	int tmp_bits;

	this->DecToBin(bits);
	tmp_bits = bits[0];

	for (int i = 0; i < 127; i++)
	{
		bits[i] = bits[i + 1];
	}
	bits[127] = tmp_bits;

	tmp.BinToDec(bits);
	return tmp;
}

bool QINT::operator>(const QINT& q)
{
	bool bits[2][128],
		check = 1;

	this->DecToBin(bits[0]);
	q.DecToBin(bits[1]);

	// So sanh hai so khac dau
	if (bits[0][127] > bits[1][127])	  return !check;
	else if (bits[0][127] < bits[1][127]) return  check;

	// So sanh hai so cung dau
	for (int i = 126; i >= 0; i--)
	{
		if (bits[0][i] > bits[1][i])	  return  check;
		else if (bits[0][i] < bits[1][i]) return !check;
	}

	return !check;
}
bool QINT::operator<(const QINT& q)
{
	bool bits[2][128],
		check = 0;

	this->DecToBin(bits[0]);
	q.DecToBin(bits[1]);

	// So sanh hai so khac dau
	if (bits[0][127] > bits[1][127])	  return !check;
	else if (bits[0][127] < bits[1][127]) return  check;

	// So sanh hai so cung dau
	for (int i = 126; i >= 0; i--)
	{
		if (bits[0][i] > bits[1][i])	  return  check;
		else if (bits[0][i] < bits[1][i]) return !check;
	}

	return check;
}
bool QINT::operator==(const QINT& q)
{
	bool bits[2][128],
		check = 1;

	this->DecToBin(bits[0]);
	q.DecToBin(bits[1]);

	for (int i = 127; i >= 0; i--)
	{
		if (bits[0][i] != bits[1][i])
			return !check;
	}

	return check;
}
bool QINT::operator<=(const QINT& q)
{
	return !(*this > q);
}
bool QINT::operator>=(const QINT& q)
{
	return !(*this < q);
}
QINT & QINT::operator=(const string& input)
{
	// Xoa du lieu cu
	for (int i = 0; i < 4; i++)
	{
		m_qint[i] = 0;
	}

	bool bits[128] = { 0 };
	string tmp_input = input;

	checkFormat(tmp_input); // Dua ve dinh dang hop le

	int index = 0;
	do
	{
		int tmp = 0;
		string rs = "";

		for (rsize_t i = 0; i < tmp_input.length(); i++)
		{
			tmp += tmp_input[i] - '0'; // Dua kieu string ve int

			if (i == 0 && tmp < 2 && i < tmp_input.length() - 1)
			{
				tmp = 10 * tmp + tmp_input[i + 1] - '0';
				i++;
			}

			rs += tmp / 2 + '0';
			tmp %= 2;
			tmp *= 10;
		}

		tmp_input = rs;
		bits[index++] = (tmp / 10) % 2;
	} while (tmp_input != "0");

	ScanQInt(bits);

	if (checkNegative(input))
	{
		*this = this->Bu2();
	}

	if (tmp_input != "0")
	{
		if (!checkNegative(input))
		{
			m_qint[3] = INT32_MAX;
			m_qint[2] = INT32_MAX;
			m_qint[1] = INT32_MAX;
			m_qint[0] = INT32_MAX;
		}
		else
		{
			m_qint[3] = 0;
			m_qint[2] = 0;
			m_qint[1] = 0;
			m_qint[0] = INT32_MIN;
		}
	}

	return *this;
}
