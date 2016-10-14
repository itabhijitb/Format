#ifndef __IDENTIFIER__
#define __IDENTIFIER__
class Sign
{
public:
	static bool IsSignChar(wchar_t symbol) ;
	Sign();
	Sign(wchar_t sign);
	bool Good();
	operator wchar_t();
private:
	wchar_t m_sign;
	enum class STATE {GOOD, FAIL}  m_state;
};
class Align
{
public:
	static bool IsAlignChar(wchar_t symbol) ;
	Align();
	Align(wchar_t align);
	bool Good();
	operator wchar_t();
private:
	wchar_t m_align;
	enum class STATE {GOOD, FAIL}  m_state;
};
class Type
{
public:
	static bool IsTypeChar(wchar_t symbol) ;
	Type();
	Type(wchar_t type);
	bool Good();
	operator wchar_t();
private:
	wchar_t m_type;
	enum class STATE {GOOD, FAIL}  m_state;
};
#endif