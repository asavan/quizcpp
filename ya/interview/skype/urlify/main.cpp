#include <string>
#include <cassert>

/*
�������� �����, ������� ������� ��� ������� � ������ �� "%20" inplace.
�� ���� �������� ������ � ������������������ ��� ���������� ���������
(�������������, ��� resize �� �������� �������� �� ����� ������������ ������).

void urlify(std::string& s);

std::string s0 = "my url";
s0.reserve(20);
urlify(s0);
assert(s0 == "my%20url");
*/


void urlify(std::string& s) {
    size_t spaceCount = 0;
    for (char c : s) {
        if (c == ' ') {
            ++spaceCount;
        }
    }
    size_t last = s.size();
    size_t currIndex = s.size() + spaceCount * 2;
    s.resize(currIndex);
    while (spaceCount > 0) {
        char c = s[--last];
        if (c != ' ') {
            s[--currIndex] = c;
        }
        else {
            s[--currIndex] = '0';
            s[--currIndex] = '2';
            s[--currIndex] = '%';
            --spaceCount;
        }
    }
}


int main()
{
    std::string s0 = "my url";
    s0.reserve(20);
    urlify(s0);
    assert(s0 == "my%20url");
    return 0;
}
