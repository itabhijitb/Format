#ifndef __FORMAT__
#define __FORMAT__
/******************************************************************************
*                                 STL Headers                                 *
******************************************************************************/
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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
	std::tstring ReplaceField(size_t index, const Ty& value)
	{
        //std::tstring key;
        if (std::is_same<Ty, kwarg>::value)
        {
			//auto key = value;
   //         if (m_tokens.count(key) == 0)
   //         {
   //             // tuple index out of range **Error**
   //         }
			//(Token<Ty>)(*m_tokens[key]) = value;
   //         m_tokens.erase(key);
        }
        else
        {
			return Token<Ty>{ *m_tokens [std::to_tstring(index) ]}(value);
        }
		
	}
    template <>
	std::tstring ReplaceField<kwarg>(size_t index, const kwarg& value)
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
	std::tstring operator()(const Ty& last)
	{
		return ReplaceField(m_argsCount, last);
	}
	template <typename First, typename... Rest>
	std::tstring operator()(const First& first, const Rest&... rest)
	{
		std::size_t args_size = sizeof...(Rest);
		m_argsCount = std::max(m_argsCount, args_size - 1);
        return ReplaceField(m_argsCount - args_size, first) + (*this)(rest...);
	}
	std::tstring str();
private:
	std::tstring m_original;
	std::vector<std::shared_ptr<std::tstring>> m_result;
	std::map<std::tstring, std::shared_ptr<std::tstring>> m_tokens;
	std::size_t m_autoFieldCount;
	std::size_t m_argsCount = 0;
	enum class STATE {GOOD, FAIL}  m_state;
};
#endif