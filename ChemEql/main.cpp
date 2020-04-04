#include <iostream>
#include <string>
#include <cstring>
#include <map>

int gcd(int x, int y) {
	return x % y == 0 ? y : gcd(y, x % y);
}

int lcm(int x, int y) {
	return x * y / gcd(x, y);
}

class frac {
public:
	int a, b;
	frac(int _a = 0, int _b = 1) {
		a = _a;
		b = _b;
		reduce();
	}

	frac abs() {
		int p = a > 0 ? a : -a;
		int q = b > 0 ? b : -b;
		return frac(p, q);
	}

	frac operator=(int x) {
		a = x;
		b = 1;
		return *this;
	}
	frac operator=(const frac x) {
		a = x.a;
		b = x.b;
		reduce();
		return *this;
	}
	frac operator+(const frac x) {
		return frac(a * x.b + x.a * b, b * x.b);
	}
	frac operator-(const frac x) {
		return frac(a * x.b - x.a * b, b * x.b);
	}
	frac operator*(const frac x) {
		return frac(a * x.a, b * x.b);
	}
	frac operator/(const frac x) {
		return frac(a * x.b, b * x.a);
	}
	bool operator<(const frac x) {
		return a * x.b < b * x.a;
	}
	bool operator>(const frac x) {
		return a * x.b > b * x.a;
	}
	bool operator==(const frac x) {
		return a * x.b == b * x.a;
	}

private:
	void reduce() {
		int n = gcd(a, b);
		a /= n;
		b /= n;
		if (b < 0)
			a = -a, b = -b;
		return;
	}
};

std::string eql;
int messNum = 0;
int atomNum = 0;
std::map<std::string, int> atomMap;
frac matrix[1005][1005];
char messName[1005][1005];
frac _ans[1005];
int ans[1005];

int getnum(int& f) {
	int x = 0;
	while (f < eql.length() && eql[f] >= '0' && eql[f] <= '9') {
		x = x * 10 + (int)eql[f] - (int)'0';
		f++;
	}
	if (x > 0) return x;
	else       return 1;
}

std::string getstr(int& i) {
	std::string ans;
	ans += eql[i++];
	while (i < eql.length() && eql[i] >= 'a' && eql[i] <= 'z')
		ans += eql[i++];
	return ans;
}

void counter(int left, int right) {
	messNum++;
	for (int i = 0; i <= right - left && eql[left + i] != '#'; i++)
		messName[messNum][i] = eql[left + i];
}

void scan(int left, int right, int w) {
	if (left == right) return;
	int _left = left, _right = right;
	while (_left < right - 1 && eql[_left] != '(') _left++;
	while (_right > left && eql[_right] != ')') _right--;
	if (eql[_left] == '(') {
		scan(left, _left, w);
		int f = _right + 1;
		scan(_left + 1, _right, getnum(f) * w);
		scan(f, right, w);
		return;
	}
	for (int i = left; i < right;) {
		std::string str = getstr(i);
		if (atomMap.count(str) == 0)
			atomMap[str] = ++atomNum;
		matrix[atomMap[str]][messNum] = matrix[atomMap[str]][messNum] + frac(w * getnum(i), 1);
	}
}

bool Solve() {
	int K = atomNum, N = messNum - 1;
	for (int i = 1; i <= K; i++) matrix[i][messNum] = matrix[i][messNum] * frac(-1, 1);
	for (int n = 1; n <= N; n++) {
		frac maxf = frac(-1, 1); int maxi = n;
		for (int i = n; i <= K; i++) {
			if (matrix[i][n].abs() > maxf)
				maxf = matrix[i][n], maxi = i;
		}
		if (maxf == frac(0, 1)) return false;
		if (maxi != n) {
			for (int j = 1; j <= N + 1; j++)
				std::swap(matrix[n][j], matrix[maxi][j]);
		}
		frac tmp = matrix[n][n];
		for (int j = 1; j <= N + 1; j++) matrix[n][j] = matrix[n][j] / tmp;
		for (int i = 1; i <= K; i++) {
			if (i == n) continue;
			frac _tmp = matrix[i][n];
			for (int j = 1; j <= N + 1; j++)
				matrix[i][j] = matrix[i][j] - _tmp * matrix[n][j];
		}
	}
	return true;
}

int main() {
	std::cin >> eql;
	int w = 1, len = eql.length();
	eql += '#';
	for (int i = 0; i < len; i++) {
		int j = i;
		while (eql[j] != '+' && eql[j] != '=' && eql[j] != '#')
			j++;
		counter(i, j);
		scan(i, j, w);
		i = j;
		if (eql[j] == '=') w = -1;
	}
	if (Solve()) {
		for (int i = 1; i <= messNum - 1; i++)
			_ans[i] = matrix[i][messNum];
		_ans[messNum] = frac(1, 1);
		int Lcm = lcm(_ans[1].b, _ans[2].b);
		for (int i = 3; i <= messNum; i++) Lcm = lcm(Lcm, _ans[i].b);
		for (int i = 1; i <= messNum; i++) ans[i] = _ans[i].a * Lcm / _ans[i].b;
		for (int i = 1; i <= messNum; i++) {
			if (ans[i] > 1) std::cout << ans[i];
			for (int j = 0; j < std::strlen(messName[i]); j++)
				std::cout << messName[i][j];
		}
	}
	else std::cout << "Failed to solve";
	/*for (int i = 1; i <= atomNum; i++) {
		for (int j = 1; j <= messNum; j++) {
			std::cout << matrix[i][j].a << "/" << matrix[i][j].b << " ";
		}
		std::cout << std::endl;
	}*/
	return 0;
}