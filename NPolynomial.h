#pragma once
#include <iostream>
#include <algorithm>
#include <valarray>

namespace our
{
	template <typename T>
	class NPolynomial;

	template <typename T>
	std::ostream& operator<<(std::ostream& ostream, const our::NPolynomial<T>& npolynomial);

	template <typename T>
	std::istream& operator>>(std::istream& istream, our::NPolynomial<T>& npolynomial);

	template <typename T>
	std::fstream& operator<<(std::fstream& fstream, const our::NPolynomial<T>& npolynomial);

	template <typename T>
	std::fstream& operator>>(std::fstream& fstream, our::NPolynomial<T>& npolynomial);

	template <typename PT, typename NT>
	NPolynomial<PT> operator+ (const NT& number, const our::NPolynomial<PT>& npolynomial);
}

template <typename T>
class our::NPolynomial
{
public:
	NPolynomial();
	~NPolynomial();
	NPolynomial(const NPolynomial& npolynomial);
	explicit NPolynomial(NPolynomial&& npolynomial); // noexcept;
	explicit NPolynomial(const size_t degree);
	explicit NPolynomial(const size_t degree, const T& number);
	explicit NPolynomial(const T& number);
//	explicit NPolynomial(const size_t degree, const T npolynomial[]);
	//	NPolynomial(size_t degree, T&,...);
//	initializer_list NPolynomial();

	
	template <typename T>
	friend std::ostream& our::operator<<<>(std::ostream& ostream,
		const our::NPolynomial<T>& npolynomial);

	std::ostream& printMonomial(std::ostream& ostream, const size_t degree) const;

	template <typename T>
	friend std::istream& our::operator>><>(std::istream& istream,
		our::NPolynomial<T>& npolynomial);

	template <typename T>
	friend std::fstream& our::operator<<<>(std::fstream& fstream,
		const our::NPolynomial<T>& npolynomial);

	template <typename T>
	friend std::fstream& our::operator>><>(std::fstream& fstream,
		our::NPolynomial<T>& npolynomial);

	NPolynomial<T>& operator= (const our::NPolynomial<T>& npolynomial);
	NPolynomial<T>& operator= (our::NPolynomial<T>&& npolynomial); // noexcept;
	NPolynomial<T> operator+ (const our::NPolynomial<T>& npolynomial) const;
	NPolynomial<T> operator+ (const T& number) const;
	NPolynomial<T>& operator+= (const our::NPolynomial<T>& npolynomial);
	NPolynomial<T>& operator+= (const T& number);
	NPolynomial<T> operator- (const our::NPolynomial<T>& npolynomial) const;
	NPolynomial<T>& operator-= (const our::NPolynomial<T>& npolynomial);
	NPolynomial<T> operator- () const;
	NPolynomial<T> operator* (const our::NPolynomial<T>& npolynomial) const;
	NPolynomial<T>& operator*= (const our::NPolynomial<T>& npolynomial);
	NPolynomial<T> operator/ (const our::NPolynomial<T>& npolynomial) const;
	NPolynomial<T>& operator/= (const our::NPolynomial<T>& npolynomial);
	NPolynomial<T> operator% (const our::NPolynomial<T>& npolynomial) const;
	NPolynomial<T>& operator%= (const our::NPolynomial<T>& npolynomial);

	bool operator== (const our::NPolynomial<T>& npolynomial) const;
	bool operator!= (const our::NPolynomial<T>& npolynomial) const;
	operator void* () const;
	bool operator! () const;

	const T& operator[] (const size_t index) const;
	T& operator[] (const size_t index);
	NPolynomial<T>& operator() (const size_t index, const T& coefficient);

	NPolynomial<T> operator() (const size_t lowDegree, const size_t highDegree,
			const size_t step);

//	NPolynomial<T> operator[] (const char* slice);

	T operator() (const T& argument) const;

	NPolynomial<T> devide(const our::NPolynomial<T>& devisor,
										our::NPolynomial<T>& remainder) const;

	NPolynomial<T> multiplyByMonomial(const size_t degree, const T& coefficient) const;

	size_t deg() const;
	void checkEmpty() const;
	size_t length() const;



private:
	void reduceLength();
	void length(const size_t length) const;

	std::valarray<T> *coefficients_; // valarray
	bool isInitialized = false;
	// class NMonomial<T>
};

template <typename T>
inline our::NPolynomial<T>::NPolynomial()
{
	coefficients_ = new std::valarray<T>(0);
}

template <typename T>
inline our::NPolynomial<T>::NPolynomial(size_t degree)
{
	coefficients_ = new std::valarray<T>(degree + 1);
}

template <typename T>
inline our::NPolynomial<T>::NPolynomial(const size_t degree, const T& number)
{
	coefficients_ = new std::valarray<T>(number, degree + 1);
	isInitialized = true;
}

template <typename T>
our::NPolynomial<T>::NPolynomial(const our::NPolynomial<T>& npolynomial)
{
	npolynomial.checkEmpty();
	coefficients_ = new std::valarray<T>(npolynomial.length());
	*coefficients_ = *npolynomial.coefficients_;
	isInitialized = true;
}

template <typename T>
our::NPolynomial<T>::NPolynomial(our::NPolynomial<T>&& npolynomial) // noexcept
{
	npolynomial.checkEmpty();
	coefficients_ = npolynomial.coefficients_;
	npolynomial.coefficients_ = nullptr;
	isInitialized = true;
}

template <typename T>
inline our::NPolynomial<T>::~NPolynomial()
{
	delete coefficients_;
}

template <typename T>
our::NPolynomial<T>& our::NPolynomial<T>::operator= (const our::NPolynomial<T>& npolynomial)
{
	npolynomial.checkEmpty();
	length(npolynomial.length());
	*coefficients_ = *npolynomial.coefficients_;
	isInitialized = true;
	return *this;
}

template <typename T>
our::NPolynomial<T>& our::NPolynomial<T>::operator= (our::NPolynomial<T>&& npolynomial) // noexcept
{
	npolynomial.checkEmpty();
	coefficients_ = npolynomial.coefficients_;
	npolynomial.coefficients_ = nullptr;
	isInitialized = true;
	return *this;
}

template <typename T>
std::ostream& our::operator<<(std::ostream& ostream, const our::NPolynomial<T>& npolynomial)
{
	// color manipulutors via ansi color
	npolynomial.checkEmpty();
	npolynomial.printMonomial(ostream, npolynomial.deg());
		
	if (npolynomial.deg() == 0)
		return ostream;

	ostream << ' ' << std::showpos;

	for (size_t ii = npolynomial.deg(); ii > 0; ii--)
	{
		npolynomial.printMonomial(ostream, ii - 1);

		if (ii != 1) ostream << ' ';
	}

	ostream << std::noshowpos;
	return ostream;
}

template <typename T>
std::istream& our::operator>>(std::istream& istream, our::NPolynomial<T>& npolynomial)
{
	size_t degree;
	istream >> degree;
	npolynomial.length(degree + 1);

	for (size_t ii = degree + 1; ii > 0; ii--)
		istream >> npolynomial[ii - 1];

	npolynomial.isInitialized = true;
	npolynomial.reduceLength();
	return istream;
}

template <typename T>
std::fstream& our::operator<<(std::fstream& fstream, const our::NPolynomial<T>& npolynomial)
{
	npolynomial.checkEmpty();
	fstream << npolynomial.deg();

	for (T ii : *npolynomial.coefficients_)
		fstream << ' ' << ii;

	fstream << std::endl;
	return fstream;
}

template <typename T>
std::fstream& our::operator>>(std::fstream& fstream, our::NPolynomial<T>& npolynomial)
{
	size_t degree;
	fstream >> degree;
	npolynomial.length(degree + 1);

	for (size_t ii = 0; ii < npolynomial.length(); ii++)
		fstream >> npolynomial[ii];

	npolynomial.isInitialized = true;
	return fstream;
}

template <typename T>
our::NPolynomial<T> our::NPolynomial<T>::operator- () const
{
	checkEmpty();
	NPolynomial<T> result(deg());
	*result.coefficients_ = -*coefficients_;
	result.isInitialized = true;
	return result;
}

template <typename T>
our::NPolynomial<T> our::NPolynomial<T>::operator+
							(const our::NPolynomial<T>& npolynomial) const
{
	checkEmpty();
	npolynomial.checkEmpty();
	const size_t resultDegree = std::max(deg(), npolynomial.deg());
	NPolynomial<T> result(resultDegree);
	
	const size_t minDegree = std::min(deg(), npolynomial.deg());

	for (size_t ii = 0; ii <= minDegree; ii++)
		result[ii] = (*this)[ii] + npolynomial[ii];

	const our::NPolynomial<T> &highestDgreeNpolynomial
							= (deg() > npolynomial.deg()) ? *this : npolynomial;

	for (size_t ii = minDegree + 1; ii <= resultDegree; ii++)
				result[ii] = highestDgreeNpolynomial[ii];

	result.isInitialized = true;
	result.reduceLength();
	return result;
}

template <typename T>
our::NPolynomial<T> our::NPolynomial<T>::multiplyByMonomial(const size_t degree,
						const T& coefficient) const
{
	checkEmpty();
	NPolynomial<T> result(deg() + degree);

	for (size_t ii = 0; ii <= deg(); ii++)
		result[ii + degree] = (*this)[ii] * coefficient;

	result.isInitialized = true;
	result.reduceLength();
	return result;
}

template <typename T>
our::NPolynomial<T> our::NPolynomial<T>::operator* (const our::NPolynomial<T>& npolynomial) const
{
	checkEmpty();
	npolynomial.checkEmpty();
	NPolynomial<T> result( deg() + npolynomial.deg(), 0 );

	for (size_t ii = 0; ii <= npolynomial.deg(); ii++)
		result += multiplyByMonomial(ii, npolynomial[ii]);

	result.reduceLength();
	return result;
}

template <typename T>
inline size_t our::NPolynomial<T>::length() const
{
	return coefficients_->size();
}

template <typename T>
inline void our::NPolynomial<T>::length(const size_t length) const
{
	coefficients_->resize(length);
}

template <typename T>
inline void our::NPolynomial<T>::checkEmpty() const
{
	if (!isInitialized)
		throw "Многочлен не инициализирован!\n";
}

template <typename T>
inline size_t our::NPolynomial<T>::deg() const
{
	checkEmpty();
	return length() - 1;
}

template <typename T>
std::ostream& our::NPolynomial<T>::printMonomial(std::ostream& ostream,
						const size_t degree) const
{
	checkEmpty();

	if ( (*this)[degree] != 0)
	{
		if (degree == 0)
			ostream << (*this)[degree];
		else if (degree == 1)
			ostream << (*this)[degree] << " * x";
		else ostream << (*this)[degree] << " * x^{ " << degree << " }";
	}

	return ostream;
}

template<typename T>
inline our::NPolynomial<T>& our::NPolynomial<T>::operator+=
										(const our::NPolynomial<T>& npolynomial)
{
	*this = *this + npolynomial;
	return *this;
}

template <typename T>
inline our::NPolynomial<T>& our::NPolynomial<T>::operator*=
										(const our::NPolynomial<T>& npolynomial)
{
	*this = *this * npolynomial;
	return *this;
}

template <typename T>
inline our::NPolynomial<T> our::NPolynomial<T>::operator-
								(const our::NPolynomial<T>& npolynomial) const
{
	return *this + (-npolynomial);
}

template<typename T>
inline our::NPolynomial<T>& our::NPolynomial<T>::operator-=
												(const our::NPolynomial<T>& npolynomial)
{
	*this = *this - npolynomial;
	return *this;
}

template<typename T>
T our::NPolynomial<T>::operator() (const T& argument) const
{
	T result = (*this)[deg()];

	for (size_t ii = deg(); ii > 0; ii--)
		result = (*this)[ii - 1] + argument * result;

	return result;
}

template<typename T>
our::NPolynomial<T> our::NPolynomial<T>::devide(const our::NPolynomial<T>& devisor,
											our::NPolynomial<T>& remainder) const
{
	devisor.checkEmpty();

	if (devisor)
		throw "Devision by 0!\n";

	checkEmpty();

	size_t qoutinentCoefficientIndex = deg() - devisor.deg();
	our::NPolynomial<T> qoutinent(qoutinentCoefficientIndex), difference = *this;
	T monomialCoefficient;
	size_t monomialDegree;

	while (difference.deg() >= devisor.deg())
	{
		monomialCoefficient = qoutinent[qoutinentCoefficientIndex--] =
			difference[difference.deg()]
							/ devisor[devisor.deg()];

		monomialDegree = difference.deg() - devisor.deg();

		our::NPolynomial<T> subtrahendPolynonomial(devisor.deg() + monomialDegree);

		subtrahendPolynonomial = devisor.multiplyByMonomial(monomialDegree,
																	monomialCoefficient);

		difference -= subtrahendPolynonomial;
	}

	remainder = difference;
	remainder.isInitialized = qoutinent.isInitialized = true;
	remainder.reduceLength();
	return qoutinent;
}

template <typename T>
inline bool our::NPolynomial<T>::operator==(const our::NPolynomial<T>& npolynomial) const
{
	checkEmpty();
	npolynomial.checkEmpty();
	return *coefficients_ == *npolynomial.coefficients_;
}

template <typename T>
inline bool our::NPolynomial<T>::operator!=(const our::NPolynomial<T>& npolynomial) const
{
	checkEmpty();
	npolynomial.checkEmpty();
	return *coefficients_ != *npolynomial.coefficients_;
}

template <typename T>
void our::NPolynomial<T>::reduceLength()
{
	checkEmpty();
	size_t actualDegree = 0;

	for (size_t ii = deg(); ii > 0; ii--)
		if ((*this)[ii] != 0)
			actualDegree++;

		if (deg() != actualDegree)
		{
			std::valarray<T> *newCoefficients = new std::valarray<T>(actualDegree + 1);
			*newCoefficients = (*coefficients_)[std::slice(0, actualDegree + 1, 1)];
			delete coefficients_;
			coefficients_ = newCoefficients;
		}
}

template <typename T>
our::NPolynomial<T>::operator void* () const
{
	checkEmpty();

	if (deg() == 0 && (*this)[0] == 0)
		return reinterpret_cast<void*>(true);
	else
		return reinterpret_cast<void*>(false);
}

template <typename T>
inline bool our::NPolynomial<T>::operator! () const
{
	return !reinterpret_cast<bool>(static_cast<void*>(*this));
}

template <typename T>
inline const T& our::NPolynomial<T>::operator[] (const size_t index) const
{
#ifdef _DEBUG
	checkEmpty();

	if (index >= length())
		throw "Error: index out of range!";
#endif

	return (*coefficients_)[index];
}

template <typename T>
inline T& our::NPolynomial<T>::operator[] (const size_t index)
{
#ifdef _DEBUG
	if (index >= length())
		throw "Error: index out of range!";
#endif

	return (*coefficients_)[index];
}
