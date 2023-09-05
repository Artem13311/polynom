#pragma once
#include <iostream>

#if !defined(MAKE_DIAG_INFO)
#define MAKE_DIAG_INFO __FILE__ << " : " << __FUNCTION__ << " : " << __LINE__
#else
#error MAKE_DIAG_INFO already difined!
#endif // MAKE_DIAG_INFO


namespace our
{
	class CoupledStream;
	extern CoupledStream cio;
}

class our::CoupledStream
{
public:
	CoupledStream(std::istream& ist = std::cin, std::ostream& ost = std::cout);

	template <class T> CoupledStream& operator>> (T& data);
	template <class T> CoupledStream& operator<< (const T& data);
private:
	std::istream& istream_;
	std::ostream& ostream_;
};


inline our::CoupledStream::CoupledStream(std::istream& ist, std::ostream& ost)
	: istream_{ ist }, ostream_{ ost } {}

template <class T> our::CoupledStream& our::CoupledStream::operator>> (T& data)
{
	istream_ >> data;
	return *this;
}

template <class T> our::CoupledStream& our::CoupledStream::operator<< (const T& data)
{
	ostream_ << data;
	return *this;
}
