/******************************************************************************
*                             Application Headers                             *
******************************************************************************/
#include "Token.h"
GenericToken::GenericToken(std::tstring szToken):m_bCenter(false)
{
	auto fmt_it = szToken.crbegin();
	std::locale loc;
	std::tstring szValue;
	// If String is Empty, return with Empty Hands
	if (fmt_it == szToken.crend()) return; 
	// A suffix character if its a valid Type Character should
	// always be a Type Character
	if (Type::IsTypeChar(*fmt_it )) 
	{
		m_type = szToken.back();
	}
	//Check the previous Character, and return if None present
	if (std::next(fmt_it) == szToken.crend()) return; 
	szValue = _T("");
	for(int count = 1; 
	fmt_it != szToken.crend() && std::isdigit(*fmt_it, loc);
		fmt_it++, count *= 10)
	{
		szValue = *fmt_it + szValue;
	}
	// Did you parse some valid numbers?
	if (szValue != _T(""))
	{
		// No more character to Parse. 
		if (fmt_it == szToken.crend() || *fmt_it != L'.')
		{
			// Its guranteed that the parsed character is width
			// But also check the prefix
			// A Zero Indicates, a pad character
			if (szValue[0] == L'0')
			{
				m_fill = L'0';
			}
			m_width = std::stoi(szValue);
			if (fmt_it == szToken.crend()) return; 
		}
		else
		{
			// As a dot precedes the number, the parsed
			// number should be the precission
			m_precission = std::stoi(szValue);
			//Check and Skip the previous Character, 
			// and return if None present
			if (++fmt_it == szToken.crend()) return; 

		}
	}
	if (*fmt_it == L'#')
	{
		m_hash = *fmt_it;
	}
	// Check and Skip the previous Character, 
	// and return if None present

	if (++fmt_it == szToken.crend()) return; 
	if (Sign::IsSignChar(*fmt_it))
	{
		m_sign = *fmt_it;
	}
	//Check the previous Character, and return if None present
	if (++fmt_it == szToken.crend()) return; 
	if (Align::IsAlignChar(*fmt_it))
	{
		m_align = *fmt_it;
		if (++fmt_it == szToken.crend()) return; 
		// The Align Character may be preceded by a fill Character
		m_fill = *fmt_it;
	}		
}
std::tstring GenericToken::Center(std::tstring& text)
{
	size_t pad = (text.size() - static_cast<int>(m_width)) / 2;
	if (pad < 0) pad = 0;
	text = std::tstring(m_width, m_fill) + text;
	text += std::tstring(m_width - pad, m_fill) ;
	return text;
}
std::tstringstream& GenericToken::Justify(std::tstringstream& out, bool bRight)
{
	switch(static_cast<Align>(m_align))
	{

	case L'<':
		out<<std::left;break;				
	case L'=':
		out<<std::internal;break;
	case L'^':
		m_bCenter = true; out<<std::left; break;
	case L'>':
		out<<std::right;break;
	default:
		if (bRight)
		{
			out<<std::right;
		}
		else
		{
			out<<std::left;	
		}
		break;
	}
	return out;
}

Token<std::tstring>::Token(std::tstring szToken):GenericToken(szToken) {};
std::tstring Token<std::tstring>::operator()(const std::tstring& data)
{
	std::tstringstream  out;
	if (m_fill.exist())	
	{
		out<<std::setfill(static_cast<wchar_t>(m_fill));
	}
	if (m_align.exist())
	{
		Justify(out);
	}
	if (m_width.exist())
	{
		out<<std::setw(static_cast<int>(m_width)); 
	}
	if (m_precission.exist())
	{
		if (static_cast<size_t>(m_precission) < data.size())
		{
			data.substr(0, m_precission);
		}
	}
	out<<data;
	std::tstring text = out.str();
	if (m_bCenter)
	{
		Center(text);
	}
	return text;
}

std::tstringstream& Token<long double>::Type(std::tstringstream& out)
{
	switch(static_cast<wchar_t>(m_type))
	{
	case L'E':
		out<<std::uppercase;
	case L'e':
		out<<std::scientific;	break;
	case L'%':
		m_bPct = true;
		m_data *= 100;
	case L'F':
		out<<std::uppercase;
	case L'f':
		out<<std::fixed;	break;
	case L'G':
		out<<std::uppercase;
	case L'n':
		out.imbue(std::locale(""));
	case L'g':
		{
			size_t p = static_cast<int>(m_precission);
			if (!p) p = 1;
			std::tstringstream wsDress;
			wsDress<<std::setprecision(p);
			wsDress<< std::scientific;
			wsDress<<m_data;
			size_t pos = wsDress.str().find_last_of(_T("+-"));
			if (pos == wsDress.str().npos)
			{
				// Unhandled Exception
			}
			intmax_t exp = std::stoll(wsDress.str().substr(pos));
			if (-4 <= exp && exp < p + 1)
			{
				out<<std::setprecision(p - exp);
				out<<std::fixed;
			}
			else
			{
				out<<std::setprecision(p);
				out<<std::scientific;
			}
		}
	default:
		out << std::setprecision(1);
		out << std::fixed;
		out << std::setw(m_width);
		break;
	}
	return out;
}
Token<long double>::Token(std::tstring szToken):GenericToken(szToken),m_bPct(false) {};
std::tstring Token<long double>::operator()(long double data)
{
	m_data = data;
	std::tstringstream  out;
	if (m_fill)	
	{
		out<<std::setfill(static_cast<wchar_t>(m_fill));  
	}
	if (m_align.exist())
	{
		Justify(out);
	}
	if (m_sign.exist() && Cast(m_sign) != L'-')	
	{
		if(Cast(m_sign) == '+')
		{
			out<<std::showpos;
		}
		else
		{
			// Not Implemented
		}
	}
	if (m_width)
	{
		out<<std::setw(static_cast<int>(m_width)); 
	}
	if (m_precission)
	{
		out<<std::setprecision(static_cast<int>(m_precission)); 
	}
	else
	{
		out<<std::setprecision(6);
	}
	if (m_type)
	{
		Type(out);
	}
	out<<m_data;
	std::tstring text = out.str();
	if (m_bPct)	text += L'%';
	if (m_bCenter)
	{
		Center(text);
	}
	return text;
}

std::tstringstream& Token<intmax_t>::Type(std::tstringstream& out)
{
	switch(static_cast<wchar_t>(m_type))
	{
	case L'b':
		{
			//intmax_t data = std::stoll(text);
			size_t bitness = sizeof(intmax_t); 
			intmax_t mask = 0XFF << (bitness - 8);
			for(;bitness > 1  && !(m_data & mask); 
				bitness -= 8, (mask = 0XFF << (bitness - 8)));
				std::bitset<sizeof(intmax_t)> bData;
			std::string temp = std::bitset<sizeof(intmax_t)>(m_data).to_string();
			m_text = std::tstring(temp.begin(), temp.end());
			break;
		}
	case L'o':
		out<<std::setbase(8); break;
	case L'X':
		out<<std::uppercase;
	case L'x':
		out<<std::setbase(16); break;
	case L'c':
		m_text = std::to_tstring(m_data);
	case L'n':
		out.imbue(std::locale(""));
	case L'd':
	default:
		out<<std::setbase(10); break;

	}
	return out;
}

Token<double>::Token(std::tstring szToken) :Token<long double>(szToken) {};
Token<float>::Token(std::tstring szToken) :Token<double>(szToken) {};

Token<uintmax_t>::Token(std::tstring szToken):Token<float>(szToken) {};
std::tstring Token<uintmax_t>::operator()(uintmax_t data)
{
	m_data = data;
	std::tstringstream  out;

	bool bUpper = false;
	if (m_fill)	
	{
		out<<std::setfill(static_cast<wchar_t>(m_fill));  
	}
	if (m_align.exist())
	{
		Justify(out, true);
	}
	if (m_sign.exist() && Cast(m_sign) != '-')	
	{
		if(Cast(m_sign) == '+')
		{
			out<<std::showpos;
		}
		else
		{
			// Not Implemented
		}
	}
	if (m_hash) 
	{
		out<<std::showbase; 
	}
	if (m_width)
	{
		out<<std::setw(static_cast<int>(m_width)); 
	}
	if (m_type)
	{

	}
	if (m_text.exist())
	{
		out << Cast(m_text);
	}
	else
	{
		out << m_data;
	}
	m_text = out.str();

	if (m_bCenter)
	{
		Center(static_cast<std::tstring>(m_text));
	}
	return m_text;

}
Token<intmax_t>::Token(std::tstring szToken) :Token<uintmax_t>(szToken) {};
Token<int32_t>::Token(std::tstring szToken) :Token<intmax_t>(szToken) {};
Token<int16_t>::Token(std::tstring szToken) :Token<int32_t>(szToken) {};
Token<int8_t>::Token(std::tstring szToken) :Token<int16_t>(szToken) {};
Token<char *>::Token(std::tstring szToken) :GenericToken(szToken) {};
Token<char>::Token(std::tstring szToken) :GenericToken(szToken) {};
Token<wchar_t>::Token(std::tstring szToken) :GenericToken(szToken) {};