#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <chrono>

constexpr char ALL_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

constexpr unsigned char ALL_CHARS_LENGTH = 26;
constexpr unsigned char NUMERIC_CHARS_LENGTH = 10;

constexpr int KEY_LENGTH = 18;

int GenerateRandom(const int nSeed)
{
	std::random_device d{};
	std::mt19937 r(d());
	const int nRand = r();
	nRand + (__COUNTER__ + (__TIME__[1]));
	return nRand;
}

std::string GenerateKey()
{
	std::string szRes;
	szRes.reserve(KEY_LENGTH);
	for (int i = 0; i < KEY_LENGTH; i++)
	{
		szRes.push_back(ALL_CHARS[std::clamp<int>((GenerateRandom(i) * 1000) % ALL_CHARS_LENGTH,
			0, ALL_CHARS_LENGTH)]);
	}

	if (szRes.length() >= KEY_LENGTH)
	{
		szRes[5] = '-';
		szRes[11] = '-';
	}

	return szRes;
}

enum Format_e
{
	FORMAT_PLAIN = 0,
	FORMAT_CSV = 1,
	FORMAT_COUNT,
};

const char* g_szFileExtension[] = { ".txt", ".csv" };

#define WRITE_FORMAT_PLAIN() while (nAmount > 0)\
	{\
		File << GenerateKey() << "\n";\
		nAmount--;\
	}

#define WRITE_FORMAT_CSV() while (nAmount > 0)\
	{\
		File << GenerateKey() << ",\n";\
		nAmount--;\
	}

int main()
{
	printf_s("Select an output format: \n");
	printf_s("PLAIN: 0\n");
	printf_s("CSV: 1\n");

	std::string szFormatInput = "";
	std::cin >> szFormatInput;

	printf_s("\n");

	const int nFormat = std::atoi(szFormatInput.c_str());
	if (nFormat >= FORMAT_COUNT)
	{
		printf_s("Invalid format: %i", nFormat);
		return 0;
	}

	printf_s("Amount of keys to generate: ");
	std::string szInput = "";
	std::cin >> szInput;

	int nAmount = std::atoi(szInput.c_str());

	std::ofstream File(std::string("keys_generated") + g_szFileExtension[nFormat]);

	switch (nFormat)
	{
	case FORMAT_PLAIN: WRITE_FORMAT_PLAIN(); break;
	case FORMAT_CSV: WRITE_FORMAT_CSV(); break;
	default:
		printf_s("ERROR: Can't start writing due to invalid format\n");
		break;
	}

	printf_s("Done!\n");
	system("pause");

	return 0;
}