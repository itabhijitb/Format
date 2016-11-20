#include "Identifier.h"

bool Sign::IsSignChar(wchar_t symbol) 
{
	switch(symbol)
	{
	case L'+':case L'-':case L' ':
		return true;
	default:
		return false;
	}
}
Sign::Sign(): m_sign('-'), m_state(STATE::GOOD) { };
Sign::Sign(wchar_t sign)
{
	if (Sign::IsSignChar(sign))
	{
		m_sign = sign;
		m_state = STATE::GOOD;
	}
	else
	{
		m_state = STATE::FAIL;
		m_sign = L'\0';
	}
}
bool Sign::Good()
{
	return m_state == STATE::GOOD;
}
Sign::operator wchar_t()
{
	return m_sign;
}

bool Align::IsAlignChar(wchar_t symbol) 
{
	switch(symbol)
	{
	case L'<':case L'^':case L'>':case L'=':
		return true;
	default:
		return false;
	}
}
Align::Align(): m_align('<'), m_state(STATE::GOOD)	{ }
Align::Align(wchar_t align)
{
	if (Align::IsAlignChar(align))
	{
		m_align = align;
		m_state = STATE::GOOD;
	}
	else
	{
		m_state = STATE::FAIL;
		m_align = L'\0';
	}
}
bool Align::Good()
{
	return m_state == STATE::GOOD;
}
Align::operator wchar_t()
{
	return m_align;
}


bool Type::IsTypeChar(wchar_t symbol) 
{
	switch(symbol)
	{
	case L'b' : case L'c' : case L'd' : case L'e' : case L'E' : 
	case L'f' : case L'F' : case L'g' : case L'G' : case L'n' : 
	case L'o' : case L's' : case L'x' : case L'X' : case L'%' :
		return true;
	default:
		return false;
	}
}
Type::Type(): m_type('s'), m_state(STATE::GOOD) { };
Type::Type(wchar_t type)
{
	if (Type::IsTypeChar(type))
	{
		m_type = type;
		m_state = STATE::GOOD;
	}
	else
	{
		m_state = STATE::FAIL;
		m_type = L's';
	}
}
bool Type::Good()
{
	return m_state == STATE::GOOD;
}
Type::operator wchar_t()
{
	return m_type;
}
