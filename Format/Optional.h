#ifndef __OPTIONAL__
#define __OPTIONAL__
/******************************************************************************
*                                 STL Headers                                 *
******************************************************************************/
#include <memory>
template <typename Ty>
class Optional
{
public:
	Optional():m_data(nullptr){ };

	Optional(Ty data):m_data(std::make_shared<Ty>(data)){ };
	Optional(const Optional& that):m_data(that.m_data) { };
	Optional& operator=(const Optional& that)
	{
		m_data = that.m_data;
		return *this;
	}
	Optional& operator = (Ty data)
	{
		m_data = std::make_shared<Ty>(data);
		return *this;
	}
	void release()
	{
		m_data = nullptr;
	}
	bool exist()
	{
		return m_data != nullptr;
	}
	operator Ty()
	{
		if (m_data == nullptr)
		{
			return Ty();
		}
		return *m_data;
	}
private:
	std::shared_ptr<Ty> m_data;
};
template <typename Ty>
Ty& Cast(Optional<Ty>& obj)
{
	return static_cast<Ty>(obj);
}
#endif