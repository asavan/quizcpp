#include <iostream>

int main()
{
	std::string S, J;
	std::cin >> J;
	std::cin >> S;
	int juls[26] = {};
	for (auto c : J) {
		juls[c - 'a'] = 1;
	}
	int res = 0;
	for (auto c : S) {
		res += juls[c - 'a'];
	}
	std::cout << res;
	return 0;
}
