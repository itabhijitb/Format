#ifndef __KWARG__
#define __KWARG__
#include <string>
#include <memory>
#include <map>
#include "Types.h"
class kwarg
{
public:
    
    kwarg(std::tstring name): m_name(name) {}
    kwarg(const tchar *name): m_name(name) {}
    struct kwarg_proxy_base
    {
        virtual ~kwarg_proxy_base() = 0;
    };
    template <typename Ty>
    struct kwarg_proxy: kwarg_proxy_base
    {
        kwarg_proxy(const Ty& value):m_value(value){}
        const Ty& m_value ;
    };
    template <typename Ty>
    kwarg& operator=(const Ty& rhs)
    {
        m_value = std::make_shared<kwarg_proxy_base>(
            new kwarg_proxy<Ty>(rhs))
    }
    kwarg& operator=(const kwarg& rhs)
    {
        m_value = rhs.m_value;
    }
    std::tstring name() const
    {
        return m_name;
    }
    template<typename Ty>
    operator const Ty&() const {
        if (!m_value) return Ty();
        return dynamic_cast<const kwarg_proxy<Ty> &>(*m_value).m_value;
    }

    template <typename Ty>
    operator Ty*() const {
        if (!m_value) return nullptr;
        return &dynamic_cast<const kwarg_proxy<Ty> &>(*m_value).m_value;
    }

    template <typename Ty>
    operator Ty() const {
        if (!m_value) return Ty();
        return dynamic_cast<const kwarg_proxy<Ty> &>(*m_value).m_value;
    }
    template <typename Ty>
    Ty value_type(){return Ty()};
private:
    std::tstring m_name;
    std::shared_ptr<kwarg_proxy_base> m_value;
};
#endif