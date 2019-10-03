#include "Qfloat.h"

Qfloat Qfloat::Zero;
Qfloat Qfloat::Infinity;
Qfloat Qfloat::NaN;
Qfloat::_init Qfloat::_initializer;

//Hàm khởi tạo mặc định
Qfloat::Qfloat()
{
	a = new uint32_t[len / 32];
}

Qfloat::Qfloat(const Qfloat& other) {
	a = new uint32_t[len / 32];
	for (int i = 0; i < len / 32; ++i) {
		a[i] = other.a[i];
	}
}

Qfloat::Qfloat(const string &s) {
	a = new uint32_t[len / 32];
	StringToQfloat(s);
}

//Hàm hủy
Qfloat::~Qfloat()
{
	delete[] a;
}

//Chuyển phần nguyên không dấu hệ 10 sang hệ 2 được lưu trong bool* với độ dài len bit, độ chính xác được lưu vào precision.
//Trả về vị trí bit trái nhất khác 0 nếu có, ngược lại trả về -1.
int Qfloat::IntegerPartToBinary(string s, bool bit[], int len, int &e, int &precision) {
	for (int i = 0; i < len; ++i) {
		bit[i] = 0;
	}
	int i = 0, k = len - 1;
	while (i < s.size() && k >= 0) {
		if (s[i] == '0') {
			++i;
			continue;
		}
		int j = i, r = 0;
		while (j < s.size()) {
			char c = s[j];
			s[j] = '0' + (r * 10 + c - '0') / 2;
			r = (r * 10 + c - '0') % 2;
			j++;
		}
		bit[k--] = r;
		++precision;
	}
	if (i < s.size() && k < 0) {
		bit[0] = 1;
	}
	return k + 1;
}

//Chuyển phần thập phân hệ 10 sang hệ 2 được lưu trong bool* với độ dài len bit.
//Trả về vị trí bit trái nhất khác 0 nếu có, ngược lại trả về -1.
int Qfloat::FractionalPartToBinary(string s, bool bit[], int len, int &e, int &precision) {
	for (int i = 0; i < len; ++i) {
		bit[i] = 0;
	}
	int i = s.size() - 1, k = 0;
	while (i >= 0 && k < len) {
		if (s[i] == '0') {
			--i;
			continue;
		}
		int j = i, r = 0;
		while (j >= 0) {
			char c = s[j];
			s[j] = '0' + (r + (c - '0') * 2) % 10;
			r = (r + (c - '0') * 2) / 10;
			--j;
		}
		bit[k++] = r;
		++precision;
		/*if (precision > significandLen + 5) {
			break;
		}*/
	}
	int l = len;
	for (int i = 0; i < len; ++i) {
		if (bit[i] == 1) {
			l = i;
			break;
		}
	}
	return l;
}

//Chuyển bit ở vị trí index thành giá trị bit
void Qfloat::SetBit(int index, int bit) const {
	index = len - index - 1;
	int i = index / 32, j = 32 - index % 32 - 1;
	a[i] = (a[i] & ~(1U << j)) | (bit << j);
}

//Lấy giá trị bit ở vị trí index
int Qfloat::GetBit(int index) const {
	index = len - index - 1;
	int i = index / 32, j = 32 - index % 32 - 1;
	return ((a[i] >> j) & 1U);
}

//Lưu dấu cho Qfloat
void Qfloat::SaveSign(int sign) const {
	SetBit(len - 1, sign);
}

//Lấy dấu của Qfloat
int Qfloat::GetSign() const {
	return GetBit(len - 1);
}

//Lấy giá trị phần nguyên của Qfloat
int Qfloat::GetIntegerPart() const {
	if (IsSubnormal()) {
		return 0;
	}
	return 1;
}

//Lưu phần mũ cho Qfloat
void Qfloat::SaveExponent(int e) const {
	e += bias;
	for (int i = 0; i < exponentLen; ++i) {
		int bit = (e >> i) & 1U;
		SetBit(significandLen + i, bit);
	}
}

//Lưu phần định trị cho Qfloat
void Qfloat::SaveSignificand(bool significandBits[]) {
	for (int i = 0; i < significandLen; ++i) {
		SetBit(significandLen - i - 1, significandBits[i]);
	}
}

//Trả về vị trí của dấu chấm thập phân
int Qfloat::GetDecimalPoint(string& s) const {
	int decimal_point = -1;
	int i;
	for (i = 0; i < s.size(); i++) {
		if (s[i] == '.' && decimal_point == -1) {
			decimal_point = i;
		}
		else if (s[i] < '0' || '9' < s[i])
		{
			break;
		}
	}
	s.erase(i, s.size() - i);
	if (decimal_point == -1) {
		decimal_point = s.size();
		s = s + ".0";
	}
	//cout << s << '\n';
	return decimal_point;
}

//Làm tròn round to nearest-even trong hệ nhị phân
int Qfloat::Rounding(bool bit[]) {
	int g = bit[significandLen + 1], r = bit[significandLen + 2], s = bit[significandLen + 3];
	if (g == 1) {
		if (!(r == 0 && s == 0 && bit[significandLen] == 0)) {
			int t = 1;
			for (int i = significandLen; i >= 0 && t > 0; --i) {
				int c = bit[i] + t;
				bit[i] = c % 2;
				t = c / 2;
			}
			return t;
		}
	}
	return 0;
}

//Chuyển số thập phân dưới dạng string sang dạng Qfloat
void Qfloat::StringToQfloat(string s) {
	int sign = 0;
	if (s[0] == '-') {
		sign = 1;
		s.erase(0, 1);
	}
	SaveSign(sign);

	int decimal_point = GetDecimalPoint(s);

	int n = (1 << (exponentLen - 1));
	int e = 0, precision = 0;
	bool* bit = new bool[3 * n];
	int l = IntegerPartToBinary(s.substr(0, decimal_point), bit, n, e, precision);
	/*for (int i = 0; i < n; ++i) {
		cout << bit[i];
	}
	cout << "\n";*/
	e = n - l - 1;
	if (l == 0) { //Trường hợp = infinity
		*this = Infinity;
		SaveSign(sign);
		delete[] bit;
		return;
	}
	if (e < 0) {
		l = 3 * n;
	}
	//cout << s.substr(decimal_point + 1, s.size() - decimal_point - 1) << "\n";
	l = min(l, n + FractionalPartToBinary(s.substr(decimal_point + 1, s.size() - decimal_point - 1), bit + n, n + 2 * significandLen, e, precision));
	/*for (int i = n; i < 3 * n; ++i) {
		cout << bit[i];
	}
	cout << "\n";*/
	if (e < 0) { //Phần nguyên = 0
		e = n - (l + 1);
	}
	//cout << e << "\n";
	bit[n - e - 2] = Rounding(bit + (n - e - 1));
	if (bit[0] == 1) { //Trường hợp = infinity
		*this = Infinity;
		SaveSign(sign);
		delete[] bit;
		return;
	}
	SaveExponent(e);
	if (e < 1 - bias) { //subnormal
		SaveExponent(-bias);
		e = 1 - bias;
	}
	bool* significandBits = new bool[significandLen];
	for (int i = n - e; i < n - e + significandLen; ++i) {
		significandBits[i - (n - e)] = bit[i];
		//cout << significandBits[i - (n - e)];
	}
	//cout << "\n";
	SaveSignificand(significandBits);
	delete[] bit;
	delete[] significandBits;
}

//Overloading toán tử >>
istream& operator >> (istream& is, Qfloat& f) {
	string s;
	is >> s;

	f.StringToQfloat(s);

	return is;
}

//In ra giá trị các bit được lưu trong bộ nhớ
void Qfloat::PrintBits() {
	for (int i = len - 1; i >= 0; --i) {
		cout << GetBit(i);
		if ((i == 127) || (i == 112)) {
			//cout << " ";
		}
	}
	cout << "\n";
}

//Tính giá trị của phần trị
string Qfloat::SignificandValue() const {
	string val, s; //val chứa kết quả, s chứa giá trị của các lũy thừa 2 ở mỗi bước
	for (int i = significandLen - 1; i >= 0; --i) {
		int j = 0, r = 0;
		while (j < s.size()) {
			int t = (r * 10 + (s[j] - '0'));
			s[j] = '0' + t / 2;
			r = t % 2;
			++j;
		}
		if (s == "") {
			r = 1;
		}
		//cout << i << "\n";
		if (r > 0) {
			s.push_back('0' + (r * 10) / 2);
		}
		//cout << s << "\n";
		if (GetBit(i) == 0) {
			continue;
		}
		r = 0;
		for (j = val.size() - 1; j >= 0; --j) {
			int t = (val[j] - '0') + (s[j] - '0') + r;
			val[j] = '0' + t % 10;
			r = t / 10;
		}
		if (val.size() < s.size()) {
			val += s.substr(val.size(), s.size() - val.size());
		}
	}
	if (val.size() > 0) {
		val = '.' + val;
	}
	val = (IsSubnormal() ? '0' : '1') + val;
	return val;
}

//Tính giá trị của phần mũ
int Qfloat::ExponentValue() const {
	if (IsSubnormal()) {
		return 1 - bias;
	}
	int val = 0, p = 1;
	for (int i = significandLen; i < significandLen + exponentLen; ++i) {
		val += GetBit(i) * p;
		p *= 2;
	}
	val -= bias;
	return val;
}

//Nhân một số được lưu trong string cho 2
void Qfloat::Mul2(string& s) const {
	int i = s.size() - 1, r = 0;
	while (i >= 0) {
		if (s[i] == '.') {
			--i;
			continue;
		}
		int t = (s[i] - '0') * 2 + r;
		s[i] = '0' + t % 10;
		r = t / 10;
		--i;
	}
	if (r > 0) {
		s.insert(s.begin(), '0' + r % 10);
	}
}

//Chia một số được lưu trong string cho 2
void Qfloat::Div2(string& s) const {
	int i = 0, r = 0;
	while (i < s.size()) {
		if (s[i] == '.') {
			++i;
			continue;
		}
		int t = r * 10 + (s[i] - '0');
		s[i] = '0' + t / 2;
		r = t % 2;
		++i;
	}
	if (r > 0) {
		s.push_back('0' + (r * 10) / 2);
	}
}

//Xóa các chữ số 0 ở đầu string
void Qfloat::DelLeadingZero(string& s) const {
	int i = 0;
	while (i < s.size() - 1 && s[i] == '0') {
		++i;
	}
	s.erase(0, i);
}

//Bỏ một chữ số ở cuối string và làm tròn trong hệ thập phân
int Qfloat::RemoveTailWithRound(string &val, int &e10) const {
	int r;
	if (val.back() == '.') {
		val[val.size() - 1] = val[val.size() - 2];
		val[val.size() - 2] = '.';
		++e10;
	}
	r = val.back() - '0' >= 5 ? 1 : 0;
	val.pop_back();
	int i = val.size() - 1;
	while (i >= 0 && r > 0) {
		if (val[i] == '.') {
			--i;
			continue;
		}
		int t = (val[i] - '0') + r;
		val[i] = '0' + t % 10;
		r = t / 10;
		--i;
	}
	if (r > 0) {
		val.insert(val.begin(), '0' + r % 10);
	}
	return 0;
}

//Chuyển số Qfloat sang dạng thập phân lưu trong string
string Qfloat::ToStringDec() const {
	string val = SignificandValue();
	if (val.size() > accuracy) {
		val.erase(accuracy, val.size() - accuracy);
	}

	int decimal_point = GetDecimalPoint(val);

	int e = ExponentValue(), e10 = 0;
	//if (e + bias == 0) { //Phần mũ = 0...0
	//	val[0] = '0';
	//	e = 1 - bias;
	//}
	//if (e + bias == (1 << exponentLen) - 1) { //Phần mũ = 1...1

	//}
	while (e) {
		if (e > 0) {
			Mul2(val);
			while (val.size() > accuracy) {
				RemoveTailWithRound(val, e10);
			}
			--e;
		}
		else {
			Div2(val);
			DelLeadingZero(val);
			if (val[0] == '.') {
				int i = 0;
				do
				{
					val[i] = val[i + 1];
					val[i + 1] = '.';
					--e10;
					++i;
				} while (i < val.size() - 1 && val[i - 1] == '0' && ('0' <= val[i + 1] && val[i + 1] <= '9'));
			}
			DelLeadingZero(val);
			if (val[0] == '.') {
				val[0] = '0';
				e10 = 0;
				break;
			}
			while (val.size() > accuracy) {
				RemoveTailWithRound(val, e10);
			}
			++e;
		}
	}

	decimal_point = GetDecimalPoint(val);
	while (e10 > 0 && decimal_point > 1) {
		val[decimal_point] = val[decimal_point - 1];
		val[--decimal_point] = '.';
		++e10;
	}
	if (e10 < 0 && e10 > -accuracy / 2/*val.size() - (decimal_point - 1 + e10) <= accuracy*/) {
		while (e10 < 0) {
			val[decimal_point] = val[decimal_point - 1];
			val[--decimal_point] = '.';
			if (decimal_point == 0) {
				val = '0' + val;
				RemoveTailWithRound(val, e10);
				++decimal_point;
			}
			++e10;
		}
	}
	while (val.size() > 34) RemoveTailWithRound(val, e10);
	while (val.back() == '0') {
		val.pop_back();
	}
	if (val.back() == '.') val.pop_back();

	stringstream writer;
	if (GetSign() == 1) {
		writer << "-";
	}
	writer << val;
	if (e10) {
		writer << "e";
		if (e10 > 0) writer << "+";
		writer << e10;
	}

	return writer.str();
}

//Overloading toán tử <<
ostream& operator << (ostream& os, const Qfloat& f) {
	//string s = f.SignificandValue();
	//os << f.SignificandValue() << 'e' << f.ExponentValue() << "\n";
	if (f.IsNaN()) {
		os << "NaN";
		return os;
	}
	if (f.IsZero()) {
		f.SaveSign(0);
	}
	os << f.ToStringDec();
	return os;
}

//Chuyển đổi số Qfloat nhị phân sang thập phân
Qfloat Qfloat::BinToDec(bool *bit) {
	Qfloat f;
	for (int i = 0; i < len; ++i) {
		f.SetBit(len - i - 1, bit[i]);
	}
	return f;
}

//Chuyển đổi string nhị phân 128 bit IEEE sang Qfloat
void Qfloat::StringBinToDec(string s) {
	while (s.size() < len) s.push_back('0');
	for (int i = 0; i < len; ++i) {
		SetBit(len - i - 1, s[i] - '0');
	}
}

//Chuyển đổi số Qfloat thập phân sang nhị phân
bool *Qfloat::DecToBin(Qfloat x) {
	bool *bit = new bool[len];
	for (int i = 0; i < len; ++i) {
		bit[i] = GetBit(len - i - 1);
	}
	return bit;
}

//Toán tử gán =
Qfloat &Qfloat::operator = (const Qfloat &other) {
	delete[] a;
	a = new uint32_t[len / 32];
	for (int i = 0; i < len / 32; ++i) {
		a[i] = other.a[i];
	}
	return *this;
}

//Kiểm tra có phải số 0 không
bool Qfloat::IsZero() const {
	for (int i = 0; i < significandLen + exponentLen; ++i) {
		if (GetBit(i) == 1) {
			return false;
		}
	}
	return true;
}

//Kiểm tra có phải NaN không
bool Qfloat::IsNaN() const {
	if (ExponentValue() != bias + 1) {
		return false;
	}
	for (int i = 0; i < significandLen; ++i) {
		if (GetBit(i) == 1) {
			return true;
		}
	}
	return false;
}

//Kiểm tra có phải số không chuẩn không
bool Qfloat::IsSubnormal() const {
	for (int i = significandLen; i < significandLen + exponentLen; ++i) {
		if (GetBit(i) == 1) {
			return false;
		}
	}
	return true;
}

//Lưu phần trị vào bool*
void Qfloat::SignificandToBit(bool bit[]) const {
	//bool *bit = new bool[significandLen + 1];
	for (int i = 0; i < significandLen; ++i) {
		bit[significandLen - i] = GetBit(i);
	}
	bit[0] = IsSubnormal() ? 0 : 1;
	//return bit;
}

//Dịch các bit phần trị sang phải
void Qfloat::ShiftSignificandRight(int x, int &integerPart) const {
	if (x <= 0) return;
	int i;
	for (i = 0; i + x < significandLen; ++i) {
		SetBit(i, GetBit(i + x));
	}
	i = significandLen - x;
	if (i >= 0) {
		SetBit(i, integerPart);
		++i;
	}
	for (i = max(0, i); i < significandLen; ++i) {
		SetBit(i, 0);
	}
	if (x > 0) {
		integerPart = 0;
	}
	int e = min(ExponentValue() + x, bias + 1);
	SaveExponent(e);
}


//Dịch các bit phần trị sang trái
void Qfloat::ShiftSignificandLeft(int x, int &integerPart) const {
	if (x <= 0) return;
	int i;
	i = significandLen - x;
	if (i >= 0) {
		integerPart = GetBit(i);
	}
	else {
		integerPart = 0;
	}
	for (i = significandLen - 1; i - x >= 0; --i) {
		SetBit(i, GetBit(i - x));
	}
	for (i = min(significandLen - 1, x - 1); i >= 0; --i) {
		SetBit(i, 0);
	}
	int e = ExponentValue() - x;
	SaveExponent(e);
}

//Kiểm tra tất cả các bit có bằng 0 hay không
bool Qfloat::IsSignificandEqualZero(int integerPart) const {
	for (int i = 0; i < significandLen; ++i) {
		if (GetBit(i) == 1) {
			return false;
		}
	}
	return integerPart == 0;
}

//Cộng 2 phần trị dương X, Y lưu vào Z
void Qfloat::AddPositiveSignificands(Qfloat x, int intX, Qfloat y, int intY, Qfloat &z, int &intZ) const {
	z.SaveSign(0);
	z.SaveExponent(x.ExponentValue());
	int r = 0;
	for (int i = 0; i < significandLen; ++i) {
		int t = x.GetBit(i) + y.GetBit(i) + r;
		z.SetBit(i, t % 2);
		r = t / 2;
	}
	intZ = intX + intY + r;
	if (intZ > 1) {
		int t = intZ % 2;
		z.ShiftSignificandRight(1, t);
		intZ /= 2;
	}
}

//Trừ 2 phần trị dương X, Y lưu vào Z
void Qfloat::SubPositiveSignificands(Qfloat x, int intX, Qfloat y, int intY, Qfloat &z, int &intZ) const {
	if (intX < intY) {
		SubPositiveSignificands(y, intY, x, intX, z, intZ);
		z.SaveSign(1);
		return;
	}
	z.SaveSign(0);
	z.SaveExponent(x.ExponentValue());
	int r = 0;
	for (int i = 0; i < significandLen; ++i) {
		int t = x.GetBit(i) - y.GetBit(i) - r;
		r = 0;
		if (t < 0) {
			t += 2;
			r = 1;
		}
		z.SetBit(i, t % 2);
	}
	if (intX - intY - r < 0) {
		SubPositiveSignificands(y, intY, x, intX, z, intZ);
		z.SaveSign(1);
		return;
	}
	intZ = intX - intY - r;
}

//Cộng 2 phần trị có dấu X, Y lưu vào Z
void Qfloat::AddSignedSignificands(Qfloat x, int intX, Qfloat y, int intY, Qfloat &z, int &intZ) const {
	if (x.GetSign() == 1) {
		if (y.GetSign() == 1) { // (-) + (-) = -((+) + (+))
			//x.SaveSign(0); y.SaveSign(0);
			AddPositiveSignificands(x, intX, y, intY, z, intZ);
			z.SaveSign(1);
		}
		else {					// (-) + (+) = (+) - (+)
			SubPositiveSignificands(y, intY, x, intX, z, intZ);
		}
	}
	else {
		if (y.GetSign() == 0) { // (+) + (+) = (+) + (+)
			AddPositiveSignificands(x, intX, y, intY, z, intZ);
		}
		else {					// (+) + (-) = (+) - (+)
			SubPositiveSignificands(x, intX, y, intY, z, intZ);
		}
	}
}

//Toán tử +
Qfloat Qfloat::operator+(const Qfloat &other) {
	if (this->IsZero()) {
		return other;
	}
	if (other.IsZero()) {
		return *this;
	}

	int eX = this->ExponentValue(), eY = other.ExponentValue(), integerPartY;
	//bool *significandX = new bool[significandLen + 1], *significandY = new bool[significandLen + 1];
	Qfloat x = *this, y = other;
	integerPartY = y.GetIntegerPart();
	if (eX < eY) {
		return (y + x);
	}
	//significandX = this->SignificandToBit();
	//significandY = other.SignificandToBit();

	y.ShiftSignificandRight(eX - eY, integerPartY);
	//significandY = 0?
	if (y.IsSignificandEqualZero(integerPartY)) {
		return x;
	}

	Qfloat z;
	int integerPartZ;
	AddSignedSignificands(x, x.GetIntegerPart(), y, integerPartY, z, integerPartZ);

	if (z.IsSignificandEqualZero(integerPartZ)) {
		return Zero;
	}
	if (z.ExponentValue() == bias + 1) {
		return Infinity;
	}

	while (integerPartZ == 0) {
		z.ShiftSignificandLeft(1, integerPartZ);
	}

	return z;
}

//Toán tử -
Qfloat Qfloat::operator - (const Qfloat &other) {
	Qfloat f = other;
	f.SaveSign(1 - other.GetSign());
	return (*this + f);
}

//Tìm vị trí bit đầu tiên khác 0 từ trái sang trong bool bit[] nếu không có trả về n
int Qfloat::LeftmostBit(bool bit[], int n) const {
	for (int i = 0; i < n; ++i) {
		if (bit[i]) {
			return i;
		}
	}
	return n;
}

//Nhân 2 phần trị và lưu vào bool bit[]
void Qfloat::MulSigificands(Qfloat x, Qfloat y, bool bit[], int n) const {
	for (int i = 0; i <= significandLen; ++i) {
		if ((i == significandLen && y.GetIntegerPart() == 0) || (i < significandLen && y.GetBit(i) == 0)) {
			continue;
		}
		int j = n - 1 - i, r = 0, k, t;
		for (k = 0; k < significandLen; ++k) {
			t = x.GetBit(k) + bit[j - k] + r;
			bit[j - k] = t % 2;
			r = t / 2;
		}
		t = x.GetIntegerPart() + bit[j - k] + r;
		bit[j - k] = t % 2;
		r = t / 2;
		++k;
		while (r > 0) {
			t = bit[j - k] + r;
			bit[j - k] = t % 2;
			r = t / 2;
			++k;
		}
	}
}

//Toán tử *
Qfloat Qfloat::operator * (const Qfloat &other) {
	if (this->IsZero() || other.IsZero()) {
		return Zero;
	}

	Qfloat z;
	int e = this->ExponentValue() + other.ExponentValue();
	if (e > bias) { // Overflow
		z = Infinity;
		z.SaveSign((this->GetSign() + other.GetSign()) % 2);
		return z;
	}


	z.SaveSign((this->GetSign() + other.GetSign()) % 2);

	//Multiply significands
	int n = (significandLen + 1) * 2 + 1;
	bool *bit = new bool[n];
	for (int i = 0; i < n; ++i) bit[i] = 0;
	MulSigificands(*this, other, bit, n);
	int decimal_point = n - 2 * significandLen - 1;
	int s = decimal_point - bit[decimal_point - 1];
	bit[s - 1] = Rounding(bit + (s));
	int leftmostBit = LeftmostBit(bit, n);
	e += decimal_point - leftmostBit;
	if (e > bias) { // Overflow
		z = Infinity;
		z.SaveSign((this->GetSign() + other.GetSign()) % 2);
		delete[] bit;
		return z;
	}
	if (e < 1 - bias - significandLen) { // Underflow
		z = Zero;
		z.SaveSign((this->GetSign() + other.GetSign()) % 2);
		delete[] bit;
		return z;
	}
	if (e < 1 - bias) { // Subnormal
		z.SaveExponent(-bias);
		z.SaveSignificand(bit + leftmostBit + 1 - (1 - bias - e));
	}
	else {
		z.SaveExponent(e);
		z.SaveSignificand(bit + leftmostBit + 1);
	}

	/*this->PrintBits();
	Qfloat(other).PrintBits();
	z.PrintBits();*/

	delete[] bit;

	return (z);
}

//So sánh giá trị 2 dãy bit
int Qfloat::CmpBit(bool bitX[], int lenX, bool bitY[], int lenY) const {
	if (lenX < lenY) return -1;
	if (lenX > lenY) return 1;
	for (int i = 0; i < lenX; ++i) {
		if (bitX[i] < bitY[i]) return -1;
		if (bitX[i] > bitY[i]) return 1;
	}
	return 0;
}

//Dãy bit X trừ dãy bit Y lưu vào dãy bit Z, các dãy bit có độ dài len.
//Trả về 1 nếu X < Y ngược lại trả về 0
int Qfloat::SubtractBit(bool bitX[], int lenX, bool bitY[], int lenY, bool bitZ[], int lenZ) const {
	/*for (int i = 0; i < lenX; ++i) cout << bitX[i]; cout << "\n";
	for (int i = 0; i < lenX - lenY; ++i) cout << 0;
	for (int i = 0; i < lenY; ++i) cout << bitY[i]; cout << "\n";*/
	int r = 0, t;
	for (int i = 0; i < min(lenX, lenY); ++i) {
		t = bitX[lenX - i - 1] - bitY[lenY - i - 1] - r;
		r = 0;
		if (t < 0) {
			t += 2;
			r = 1;
		}
		bitZ[lenZ - i - 1] = t;
	}
	for (int i = min(lenX, lenY); i < max(lenX, lenY); ++i) {
		if (lenZ - i - 1 < 0) break;
		if (lenX - i - 1 < 0) t = 0;
		else t = bitX[lenX - i - 1];
		if (lenY - i - 1 < 0) t -= 0;
		else t -= bitY[lenY - i - 1];
		t -= r;
		r = 0;
		if (t < 0) {
			t += 2;
			r = 1;
		}
		bitZ[lenZ - i - 1] = t;
	}
	/*for (int i = 0; i < lenX; ++i) cout << bitZ[i]; cout << "\n";
	cout << "---\n";*/
	return r;
}

//Toán tử /
Qfloat Qfloat::operator/(const Qfloat &other) {
	if (this->IsZero()) {
		return Zero;
	}
	if (other.IsZero()) {
		return NaN;
	}

	int e = this->ExponentValue() - other.ExponentValue(), l, lenX = 0, lenY = 0;
	bool *significandX = new bool[2 * bias + significandLen + 1],
		*significandY = new bool[significandLen + 1],
		*significandZ = new bool[2 * bias + significandLen + 1];

	this->SignificandToBit(significandZ);
	l = LeftmostBit(significandZ, significandLen + 1);
	for (int i = l; i <= significandLen; ++i) significandX[lenX++] = significandZ[i];

	other.SignificandToBit(significandZ);
	l = LeftmostBit(significandZ, significandLen + 1);
	for (int i = l; i <= significandLen; ++i) significandY[lenY++] = significandZ[i];

	//Divide significands
	//Decimal point after significandZ[lenX - 1]
	l = -1;
	int lX = 0;
	for (int i = 0; ; ++i) {
		if (l >= 0 && e + lenX - l - 1 > bias) { //Overflow
			Qfloat z = Infinity;
			z.SaveSign((this->GetSign() + other.GetSign()) % 2);
			delete[] significandX;
			delete[] significandY;
			delete[] significandZ;
			return z;
		}
		if (l == -1 && e + lenX - i - 1 < 1 - bias - significandLen) { //Underflow
			Qfloat z = Zero;
			delete[] significandX;
			delete[] significandY;
			delete[] significandZ;
			return z;
		}
		if (l >= 0 && i - l > significandLen) break;
		if (i >= lenX) significandX[i] = 0;
		// chia
		if (CmpBit(significandX + lX, i - lX + 1, significandY, lenY) < 0) {
			significandZ[i] = 0;
			continue;
		}
		significandZ[i] = 1;
		SubtractBit(significandX + lX, i - lX + 1, significandY, lenY, significandX + lX, i - lX + 1);
		if (l == -1 && significandZ[i] == 1) {
			l = i;
		}
		while (lX <= i && significandX[lX] == 0) ++lX;
	}

	Qfloat z;
	z.SaveSign((this->GetSign() + other.GetSign()) % 2);
	if (e + lenX - l - 1 < 1 - bias) { //Subnormal
		z.SaveExponent(-bias);
		z.SaveSignificand(significandZ + (lenX + 1 + e - (1 - bias)));
	}
	else {
		z.SaveExponent(e + lenX - l - 1);
		z.SaveSignificand(significandZ + l + 1);
	}

	/*this->PrintBits();
	Qfloat(other).PrintBits();
	z.PrintBits();*/

	delete[] significandX;
	delete[] significandY;
	delete[] significandZ;

	return z;
}
