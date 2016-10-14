struct DATATYPE
    {

        enum class BOOLTYPE {BOOL};
        enum class CHARTYPE {SIGNED_CHAR, UNSIGNED_CHAR, CHAR, WCHAR_T, CHAR16_T, CHAR32_T};
        enum class INTTYPE {SHORT_INT,UNSIGNED_SHORT_INT,INT,UNSIGNED_INT,LONG_INT,UNSIGNED_LONG_INT,LONG_LONG_INT,UNSIGNED_LONG_LONG_INT};
        enum class FLOATTYPE {FLOAT, DOUBLE, LONG_DOUBLE};
        enum class STRTYPE {CHARPTR, WCHARPTR, WSTRING, STRING};
    };
struct BOOLTYPE: DATATYPE {};



struct FLOATTYPE: DATATYPE {};
struct LONG_DOUBLE: FLOATTYPE {};
struct DOUBLE: LONG_DOUBLE {};
struct FLOAT : DOUBLE {};

struct INTTYPE : FLOAT {};
struct UNSIGNED_LONG_LONG_INT: INTTYPE 
{
    unsigned long long int operator()(long long int data){return data;};
    unsigned long long int operator()(unsigned long int data){return data;};
    unsigned long long int operator()(long int data){return data;};
    unsigned long long int operator()(unsigned int data){return data;};
    unsigned long long int operator()(int data){return data;};
    unsigned long long int operator()(unsigned short int data){return data;};
    unsigned long long int operator()(short int data){return data;};
};
struct LONG_LONG_INT: UNSIGNED_LONG_LONG_INT 
{
    long long int operator()(unsigned long int data){return data;};
    long long int operator()(long int data){return data;};
    long long int operator()(unsigned int data){return data;};
    long long int operator()(int data){return data;};
    long long int operator()(unsigned short int data){return data;};
    long long int operator()(short int data){return data;};
};
struct UNSIGNED_LONG_INT: LONG_LONG_INT 
{
    unsigned long int operator()(long int data){return data;};
    unsigned long int operator()(unsigned int data){return data;};
    unsigned long int operator()(int data){return data;};
    unsigned long int operator()(unsigned short int data){return data;};
    unsigned long int operator()(short int data){return data;};
};
struct LONG_INT : UNSIGNED_LONG_INT {};
struct UNSIGNED_INT: LONG_INT {};
struct INT: UNSIGNED_INT {};
struct UNSIGNED_SHORT_INT: INT {};
struct SHORT_INT: UNSIGNED_SHORT_INT {};

struct CHARTYPE: INTTYPE {};
struct UNSIGNED_CHAR: CHARTYPE {};
struct SIGNED_CHAR: UNSIGNED_CHAR {};
struct CHAR: SIGNED_CHAR {};
struct WCHAR_T: CHARTYPE {};
struct CHAR16_T: CHARTYPE {};
struct CHAR32_T: CHARTYPE {};


struct STRTYPE: DATATYPE {};
struct WSTRING: STRTYPE {};
struct STRING: WSTRING {};
struct WCHARPTR: WSTRING {};
struct CHARPTR : STRING {};







