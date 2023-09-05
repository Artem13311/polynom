#include <iostream>
#include <iomanip>
#include <fstream>
#include "CStream.h"
#include "NPolynomial.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << std::endl << std::setw(3);

	try {
		our::NPolynomial<double> npolynomial;
		std::cout << "npolynomial = " << npolynomial << std::endl;
		our::cio << "Введите степень и коэффиценты npolynomial: " >> npolynomial;

		std::cout << "Вы ввели npolynomial = " << npolynomial << " степени "
			<< npolynomial.deg() << std::endl;

		std::fstream file("npolynomial.txt",
			std::fstream::in | std::fstream::out | std::fstream::app);

		file >> npolynomial;

		std::cout << "Считан из файла npolynomial = " << npolynomial << " степени "
			<< npolynomial.deg() << std::endl;


		our::NPolynomial<double> npolynomial1(npolynomial);
		file >> npolynomial1;

		std::cout << "Считан из файла npolynomial1 = " << npolynomial1 << " степени "
			<< npolynomial1.deg() << std::endl;

		std::cout << "Копия npolynomial: " << npolynomial1 << std::endl;
		our::NPolynomial<double> npolynomial2 = -npolynomial1;
		std::cout << "npolynomial2 = -npolynomial1: " << npolynomial2 << std::endl;

		our::cio << "Введите степень и коэффиценты npolynomial1: " >> npolynomial1;

		std::cout << npolynomial << " +\n" << npolynomial1 << " =\n"
			<< npolynomial + npolynomial1 << std::endl;

		size_t degree;
		double coefficient;
		our::cio << "Введите степень и коэффицент одночлена: " >> degree >> coefficient;

		std::cout << npolynomial << " *\n" << coefficient << " * x^{ " << degree << " } =\n"
			<< npolynomial.multiplyByMonomial(degree, coefficient);

		std::cout << "\n\n" << npolynomial << " *\n" << npolynomial1 << " =\n"
			<< npolynomial * npolynomial1 << std::endl;

		our::NPolynomial<double> remainder;

		std::cout << "\n\n" << npolynomial << " = \n" << npolynomial1 << " *\n"
			<< npolynomial.devide(npolynomial1, remainder) << " +\n"
			<< remainder << std::endl;

		double argument;

		our::cio << "Введите аргумент: " >> argument << "npolynomial1("
			<< argument << ") = ";
		
		std::cout << npolynomial1(argument) << '\n';

	}
	catch (const char* message)
	{
		std::cerr << message;
		system("pause");
		return 255;
	}

	system("pause");
	return 0;
}
