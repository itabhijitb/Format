#ifndef __TOKEN__
#define __TOKEN__
/******************************************************************************
*                                 STL Headers                                 *
******************************************************************************/
#include <string>
#include <locale> 
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <bitset>
/******************************************************************************
*                             Application Headers                             *
******************************************************************************/
#include "Optional.h"
#include "Identifier.h"
#include "Types.h"

class GenericToken
{
public:
private:
	enum class STATE {GOOD, FAIL}  m_state;
protected:
	GenericToken();
	GenericToken(std::tstring szToken);
	std::tstring Center(std::tstring& text);
	std::tstringstream& Justify(std::tstringstream& out, bool bRight = false);
protected:
	std::tstring m_id;
	Optional<tchar> m_fill;
	Optional<Align> m_align;
	Optional<Sign> m_sign;

	Optional<size_t> m_width;
	Optional<size_t> m_precission;
	Type m_type;
	Optional<tchar> m_hash;
	bool m_bCenter;
};
template <typename Ty>
class Token: public GenericToken
{
public:
	Token() {};
	Token(std::tstring szToken) {};
	virtual Token& operator=(const Token&) {};

};
template <>
class Token<std::tstring>: public GenericToken
{

public:
	Token(std::tstring szToken);
	std::tstring operator()(const std::tstring& data);
};
template <>
class Token<long double>: public GenericToken
{
protected:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	std::tstring operator()(long double data);
private:
	long double m_data;
	bool m_bPct;
};
template <>
class Token<double>: public Token<long double>
{
protected:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(double data);
private:
	long double m_data;
	bool m_bPct;
};
template <>
class Token<float>: public Token<double>
{
protected:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(float data);
private:
	long double m_data;
	bool m_bPct;
};

template <>
class Token<uintmax_t>: public Token<float>
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	std::tstring operator()(uintmax_t data);
private:
	uintmax_t m_data;
	Optional<std::tstring> m_text;


};

template <>
class Token<intmax_t> : public Token<uintmax_t>
{
protected:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(intmax_t data);
private:
	intmax_t m_data;
	Optional<std::tstring> m_text;


};

template <>
class Token<int32_t> : public Token<intmax_t>
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(int32_t data);
private:
	int8_t m_data;
	Optional<std::tstring> m_text;


};

template <>
class Token<int16_t> : public Token<int32_t>
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(int16_t data);
private:
	int8_t m_data;
	Optional<std::tstring> m_text;


};

template <>
class Token<int8_t> : public Token<int16_t>
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(int8_t data);
private:
	int8_t m_data;
	Optional<std::tstring> m_text;


};
//template <>
//class Token<int64_t>: GenericToken
//{
//private:
//	std::tstringstream& Type(std::tstringstream& out);
//public:
//	Token(std::tstring szToken);
//	std::tstring operator()(int32_t data);
//private:
//	int8_t m_data;
//	Optional<std::tstring> m_text;
//
//
//};
//template <>
//class Token<int8_t>: GenericToken
//{
//private:
//	std::tstringstream& Type(std::tstringstream& out);
//public:
//	Token(std::tstring szToken);
//	std::tstring operator()(uint8_t data);
//private:
//	int8_t m_data;
//	Optional<std::tstring> m_text;
//
//
//};
//template <>
//class Token<int16_t>: GenericToken
//{
//private:
//	std::tstringstream& Type(std::tstringstream& out);
//public:
//	Token(std::tstring szToken);
//	std::tstring operator()(uint16_t data);
//private:
//	int8_t m_data;
//	Optional<std::tstring> m_text;
//
//
//};
//template <>
//class Token<int32_t>: GenericToken
//{
//private:
//	std::tstringstream& Type(std::tstringstream& out);
//public:
//	Token(std::tstring szToken);
//	std::tstring operator()(uint32_t data);
//private:
//	int8_t m_data;
//	Optional<std::tstring> m_text;
//
//
//};
//template <>
//class Token<int64_t>: GenericToken
//{
//private:
//	std::tstringstream& Type(std::tstringstream& out);
//public:
//	Token(std::tstring szToken);
//	std::tstring operator()(uint32_t data);
//private:
//	int8_t m_data;
//	Optional<std::tstring> m_text;
//
//
//};
template <>
class Token<char *>: GenericToken
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(tchar * data);
private:
	int8_t m_data;
	Optional<std::tstring> m_text;


};
template <>
class Token<char>: GenericToken
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(char data);
private:
	int8_t m_data;
	Optional<std::tstring> m_text;


};
template <>
class Token<wchar_t >: GenericToken
{
private:
	std::tstringstream& Type(std::tstringstream& out);
public:
	Token(std::tstring szToken);
	//std::tstring operator()(wchar_t  data);
private:
	int8_t m_data;
	Optional<std::tstring> m_text;


};
#endif
