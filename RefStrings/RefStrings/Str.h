#include "_str.h"


class Str {
	_str* m_pStr;
public:
	Str() { m_pStr = new _str; }		//���� �� �����, �� �������
	Str(const char* p) {		// ����� ������
		m_pStr = new _str(p);
	}
	Str(const Str& s)
	{
		m_pStr = s.m_pStr; 	// ��������� �� ��� �� ������
		m_pStr->AddRef(); 	// ��������, ��� ���������
	}
	Str& operator = (const Str& s) {
		if (this != &s) {
			s.m_pStr->AddRef();
			m_pStr->Release();
			m_pStr = s.m_pStr;
		}
		return *this;
	}
	///��������� +=, []
	Str& operator += (const Str& s) {
		int length = len() + s.len();
		if (s.len() != 0) {		// ���������� ������ �� �������!
			_str* pstrTmp = new _str; 	// ����� ������
			delete[] pstrTmp->m_pszData;

			pstrTmp->m_pszData = new char[length + 1];
			strcpy_s(pstrTmp->m_pszData, length + 1, m_pStr->m_pszData);
			strcat_s(pstrTmp->m_pszData, length + 1, s.m_pStr->m_pszData);

			m_pStr->Release();
			m_pStr = pstrTmp;
		}
		return *this;
	}
	~Str() {
		m_pStr->Release(); 	// �� ���������� ������!
	}				// ��������� ������� ������!

	int len() const {
		return strlen(m_pStr->m_pszData);
	}
	operator const char* () const {
		return m_pStr->m_pszData;
	}
	char& operator[](int i) {
		if (i < 0 || i >= strlen(m_pStr->m_pszData)) {
			throw std::out_of_range("Index out of range");
		}

		if (m_pStr->m_nCount > 1) {
			_str* newString = new _str(m_pStr->m_pszData);
			m_pStr->Release();
			m_pStr = newString;
		}

		return m_pStr->m_pszData[i];
	}
};

