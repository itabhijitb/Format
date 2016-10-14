#ifndef __FORMAT__
#define __FORMAT__
/******************************************************************************
*                                 STL Headers                                 *
******************************************************************************/
#include <string>
#include <vector>
#include <map>

/******************************************************************************
*                             Application Headers                             *
******************************************************************************/
#include "Optional.h"
#include "Identifier.h"
#include "Token.h"
#include "Types.h"
#include "kwarg.h"
class Format
{
private:
	std::tstring GenID(size_t id);

	// Tokenize a format String based on braces
	std::vector<std::tstring> Tokenize(const std::tstring& fmt);
	bool is_number(std::tstring s);
	std::pair<std::tstring, std::shared_ptr<std::tstring>>  
	ParseReplacementField(std::tstring token);
    template <typename Ty>
	void ReplaceField(const Ty& value)
	{
        std::tstring key;
        if (std::is_same(Ty, kwarg)::value)
        {
            key = value.m_name;
            if (m_tokens.find(key) == 0)
            {
                // tuple index out of range **Error**
            }
            (Token<Ty>)(*m_tokens[key]) = value.m_value;
            m_tokens.erase(key);
        }
        else
        {
            key = m_tokens.cbegin();
            (Token<Ty>)(*m_tokens[key]) = value;
            m_tokens.erase(key);
        }
		
	}
    template <>
    void ReplaceField<kwarg>(const kwarg& value)
    {
        auto key = value.name();
        if (m_tokens.find(key) == m_tokens.cend())
            {
                // tuple index out of range **Error**
            }
         (Token<decltype(value)>)(*m_tokens[key]) = value;
         m_tokens.erase(key);

    }
public:

	Format(std::tstring fmt);

	template <typename Ty>
	Format& operator()(const Ty& last)
	{
		ReplaceField(last);
		
		return *this;
	}
	template <typename First, typename... Rest>
	Format& operator()(const First& first, const Rest&... rest)
	{
        
        ReplaceField(first);
		return *this;
	}
	std::tstring str();
private:
	std::tstring m_original;
	std::vector<std::shared_ptr<std::tstring>> m_result;
	std::map<std::tstring, std::shared_ptr<std::tstring>> m_tokens;
	intmax_t m_autoFieldCount;
	enum class STATE {GOOD, FAIL}  m_state;
};
#endif