#include "Format.h"
/*
	Examples of Invalid Tokens

	"{", "}","{{}"

	Examples of Valid Tokens
	"{{}}", "{{", "{{{}}}", "{}"

	================
	Parsing Logic
	================
	--------------------------------
	|Guidelines                     |
	|-------------------------------|
	|>        : Advance Pointer     |
	|<--->    : Token Found         |
	|S        : Start Pointer       |
	|E        : End Pointer         |
	--------------------------------

Token Found?                                             AAA{{B}}ZZ{{X{XX}X}}CCC{DDD}{EEE}TTTT"
                                                         ^  ^  ^   ^  ^  ^^^    ^   ^^   ^^  ^
            start = 0                                    |  |  |   |  |  |||    |   ||   ||  |
            end = fmt.find_first_of(_T("{}"), start + 1))   S  E  |   |  |  |||    |   ||   ||  |
                                                               |   |  |  |||    |   ||   ||  |
               fmt[end] == L'{'                                |   |  |  |||    |   ||   ||  |
            && fmt[end + 1] == L'{'?                           |   |  |  |||    |   ||   ||  |
             fmt.find_first_of(_T("{}"), start + 1))           >>>E   |  |  |||    |   ||   ||  |
                                                                   |  |  |||    |   ||   ||  |
               fmt[end] == L'}'                                    |  |  |||    |   ||   ||  |
            && fmt[end + 1] == L'}'?                               |  |  |||    |   ||   ||  |
             fmt.find_first_of(_T("{}"), start + 1))              >>>>E  |  |||    |   ||   ||  |
                                                                      |  |||    |   ||   ||  |
               fmt[end] == L'{'                                       |  |||    |   ||   ||  |
            && fmt[end + 1] == L'{'?                               >>>E  |||    |   ||   ||  |
                                                                      |  |||    |   ||   ||  |
               fmt[start] != L'{'                                     |  |||    |   ||   ||  |
            && fmt[end - 1] != '}'?                                   |  |||    |   ||   ||  |
TEXT         token = fmt.substr(start, start - end)      <...........>|  |||    |   ||   ||  |
                                                                      |  |||    |   ||   ||  |
            start = end                                               S  |||    |   ||   ||  |
            end = fmt.find_first_of(_T("{}"), start + 1))                   E||    |   ||   ||  |
                                                                         |||    |   ||   ||  |
               fmt[start] == L'{'                                        |||    |   ||   ||  |
             && fmt[end] == '}' ?                                        |||    |   ||   ||  |
RF          token = fmt.substr(start, start - end + 1)                <..>||    |   ||   ||  |
                                                                          ||    |   ||   ||  |
                                                                          ||    |   ||   ||  |
            start = end + 1                                              >S|    |   ||   ||  |
            end = fmt.find_first_of(_T("{}"), start + 1))                    |E    |   ||   ||  |
                                                                          |     |   ||   ||  |
               fmt[end] == L'}'                                           |     |   ||   ||  |
            && fmt[end + 1] == L'}'?                                      |     |   ||   ||  |
             fmt.find_first_of(_T("{}"), start + 1))                         |>>>>>E   E|   ||  |
                                                                          |     |   ||   ||  |
               fmt[start] != L'{'                                         |     |   ||   ||  |
            && fmt[end - 1] != '}'?                                       |     |   ||   ||  |
TEXT         token = fmt.substr(start, start - end)                       <----->   >|   ||  |
                                                                                |   ||   ||  |
            start = end                                                         S   ||   ||  |
            end = fmt.find_first_of(_T("{}"), start + 1))                          |   E|   ||  |
                                                                                |   ||   ||  |
               fmt[start] == L'{'                                               |   ||   ||  |
             && fmt[end] == '}'?                                                |   ||   ||  |
RF          token = fmt.substr(start, start - end + 1)                          <--->|   ||  |
                                                                                    ||   ||  |
            start = end + 1                                                         >S   ||  |
            end = fmt.find_first_of(_T("{}"), start + 1))                               |   EE  E
                                                                                     |   ||  |
               fmt[start] == L'{'                                                    |   ||  |
             && fmt[end] == '}'?                                                     |   ||  |
RF          token = fmt.substr(start, start - end + 1)                               <--->|  |
                                                                                          |  |
            start = end + 1                                                               S  S
            end = fmt.find_first_of(_T("{}"), start + 1))                                    |  |<npos>
                                                                                          |  |
            fmt[start] != L'{'?                                                           |  |
TEXT        fmt.substr(start)                                                             <-->

	*/


// Tokenize a format String based on braces
std::vector<std::tstring> Format::Tokenize(const std::tstring& fmt)
{
	std::vector<std::tstring> tokens;
	for(size_t start = 0,
		end   = fmt.find_first_of(_T("{}"), start + 1);
		end != fmt.npos;
	start = end,
		end   = fmt.find_first_of(_T("{}"), start + 1))
	{
		while(end != fmt.npos)
		{
			if(fmt[end] == L'{')
			{
				// Escaped Opening brace - {{?
				if (end + 1 < fmt.size() && fmt[end + 1] == L'{')
				{
					// Skip the current and next character 
					// and advance to the next brace
					end = fmt.find_first_of(_T("{}"), end + 2);
				}
				else break;
			}
			else if(fmt[end] == L'}')
			{
				// Escaped Closing brace - }}?
				if (end + 1 < fmt.size() && fmt[end + 1] == L'}')
				{
					end = fmt.find_first_of(_T("{}"), end + 2);
				}
				else break;
			}
			else break;
		}

		if (end != fmt.npos)
		{
			//Found Valid replacement_field - {....}
			if (fmt[start] == L'{' && fmt[end] == '}')
			{
				tokens.push_back(fmt.substr(start, end -start + 1));
				end += 1;
			}
			//Found Valid Text Token - 
			else if(fmt[start] != L'{' && fmt[end - 1] != '}')
			{
				tokens.push_back(fmt.substr(start, end - start));
			}
			else if(fmt[start] == L'{')
			{
				//Single '{' encountered in format string **ERROR**
			}
			else
			{
				//Single '}' encountered in format string **ERROR**
			}
		}
		else 
		{
			if(fmt[start] != L'{')
			{
				tokens.push_back(fmt.substr(start));
			}
			else
			{
				//Single '{' encountered in format string **ERROR**
			}
		}
	}
	return tokens;
}
bool Format::is_number(std::tstring s)
{
	return !s.empty() && ( s.find_first_not_of(_T("0123456789")) == std::tstring::npos);
}
std::pair<std::tstring, std::shared_ptr<std::tstring>>  
	Format::ParseReplacementField(std::tstring token)
{
	token = token.substr(1, token.size() - 2);
	auto sep = token.find(L':');		
	if (sep == 0 || token.size() == 0)
	{
		// {:}, {}
		if (m_autoFieldCount == -1)
		{
			// {1:} {}
			//cannot switch from manual field specification to automatic field numbering **Error**
		}
		if (sep == 0)
		{
			token = token.size() > 1 ? token.substr(1):_T("");
		}
		return std::make_pair(std::to_tstring(m_autoFieldCount++), 
			std::make_shared<std::tstring>(token));
	}
	else
	{

		std::tstring id = _T(""), format = _T("");
		if (sep == token.npos || token.size() > sep)
		{
			// {10} {ABC} {10:} {ABC:}
			id = token;
			format = _T("");
		}
		else
		{

			// {10:020} {ABC:020s}
			id = token.substr(0, sep);
			format = token.substr(sep + 1);
		}
		if (is_number(id) && m_autoFieldCount > 0)
		{
			//  {} {1:]
			//cannot switch from automatic field numbering to manual field specification **Error**
		}
		m_autoFieldCount = -1;
		return std::make_pair(id, std::make_shared<std::tstring>(format));

	}

}

Format::Format(std::tstring fmt):m_autoFieldCount(0)
{
    size_t id = 0;
    if (fmt.size() == 0)
    {
        return;
    }
    for(auto token:  Tokenize(fmt))
    {
        if (token.size() > 0 && token[0] == L'{')
        {
            auto id_format = ParseReplacementField(token);
            m_tokens.insert(id_format);
            m_result.push_back(id_format.second);
        }
        else
        {
            m_result.push_back(std::make_shared<std::tstring>(token));
        }
    }
}



std::tstring Format::str()
{
    std::tstring result = _T("");
    for(auto token: m_result)
    {
        result += *token;
    }
    return result;
}

std::tstring Format::GenID(size_t id)
{
    return _T(":") + std::to_tstring(id);
}