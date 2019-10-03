#include "Qfloat.h"
#include "QINT.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

	int type = 1;

	if (argc == 4) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
		type = argv[3][0] - '0';
	}

	if (type == 2) {
		Qfloat a, b, c;
		int base1, base2;
		string line, s[4];
		while (getline(cin, line))
		{
			size_t pos = 0;
			std::string token;
			int n = 0;
			while ((pos = line.find(" ")) != std::string::npos) {
				token = line.substr(0, pos);
				s[n++] = token;
				line.erase(0, pos + 1);
			}
			s[n++] = line;
			if (n == 3) {
				base1 = stoi(s[0]);
				base2 = stoi(s[1]);
				if (base1 == 10) {
					c = Qfloat(s[2]);
				}
				else {
					c.StringBinToDec(s[2]);
				}
			}
			else {
				base1 = stoi(s[0]);
				base2 = base1;
				if (base1 == 10) {
					a = Qfloat(s[1]);
					b = Qfloat(s[3]);
				}
				else {
					a.StringBinToDec(s[1]);
					b.StringBinToDec(s[3]);
				}
				switch (s[2][0])
				{
				case '+':
					c = a + b;
					break;
				case '-':
					c = a - b;
					break;
				case '*':
					c = a * b;
					break;
				case '/':
					c = a / b;
					break;
				default:
					break;
				}
			}
			if (base2 == 10) {
				cout << c << "\n";
			}
			else {
				c.PrintBits();
			}
		}
	}
	else {
		QINT a, b, c;
		int base1, base2;
		string line, s[4];
		while (getline(cin, line))
		{
			size_t pos = 0;
			std::string token;
			int n = 0;
			while ((pos = line.find(" ")) != std::string::npos) {
				token = line.substr(0, pos);
				s[n++] = token;
				line.erase(0, pos + 1);
			}
			s[n++] = line;
			if (n == 3) {
				base1 = stoi(s[0]);

				if (base1 == 10) {
					c = s[2];
				}
				else if (base1 == 2) {
					c.ScanQIntFromBinString(s[2]);
				}
				else if (base1 == 16) {
					c.ScanQIntFromHexString(s[2]);
				}

				if (s[1][0] != '~' && s[1][0] != 'r') base2 = stoi(s[1]);
				else if (s[1][0] == '~') {
					base2 = base1;
					c = ~c;
				}
				else if (s[1][0] == 'r') {
					base2 = base1;
					if (s[1][2] == 'l') {
						c = c.rol(1);
					}
					else if (s[1][2] == 'r') {
						c = c.ror(1);
					}
				}
			}
			else {
				base1 = stoi(s[0]);
				base2 = base1;
				if (base1 == 10) {
					a = s[1];
					b = s[3];
				}
				else if (base1 == 2) {
					a.ScanQIntFromBinString(s[1]);
					b.ScanQIntFromBinString(s[3]);
				}
				else if (base1 == 16) {
					a.ScanQIntFromHexString(s[1]);
					b.ScanQIntFromHexString(s[3]);
				}
				switch (s[2][0])
				{
				case '+':
					c = a + b;
					break;
				case '-':
					c = a - b;
					break;
				case '*':
					c = a * b;
					break;
				case '/':
					c = a / b;
					break;
				case '|':
					c = a | b;
					break;
				case '&':
					c = a & b;
					break;
				case '^':
					c = a ^ b;
					break;
				case '<':
					if (s[2].length() == 2) {
						if (s[2][1] == '<') {
							c = a << b.QintToInt32();
						}
						else if (s[2][1] == '=') {
							if (a <= b)
								c = "1";
							else
								c = "0";
						}
					}
					else if (s[2].length() == 1) {
						if (a < b)
							c = "1";
						else
							c = "0";
					}
					break;
				case '>':
					if (s[2].length() == 2) {
						if (s[2][1] == '>') {
							c = a >> b.QintToInt32();
						}
						else if (s[2][1] == '=') {
							if (a >= b)
								c = "1";
							else
								c = "0";
						}
					}
					else if (s[2].length() == 1) {
						if (a > b)
							c = "1";
						else
							c = "0";
					}
					break;
				case '=':
					if (a == b)
						c = "1";
					else
						c = "0";
					break;
				default:
					break;
				}
			}
			if (base2 == 10) {
				std::cout << c.PrintQintDec() << "\n";
			}
			else if (base2 == 2) {
				std::cout << c.PrintQintBin() << "\n";
			}
			else if (base2 == 16) {
				std::cout << c.PrintQintHex() << "\n";
			}
		}
	}

	return 0;
}