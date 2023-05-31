#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <Windows.h>

constexpr char ALL_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

constexpr unsigned char ALL_CHARS_LENGTH = 26;
constexpr unsigned char NUMERIC_CHARS_LENGTH = 10;

std::chrono::steady_clock g_Clock;

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
	std::string szRes = "";
	for (int i = 0; i < 18; i++)
	{
		szRes.push_back(ALL_CHARS[std::clamp<int>((GenerateRandom(i) * 1000) % ALL_CHARS_LENGTH,
			0, ALL_CHARS_LENGTH)]);
	}

	if (szRes.length() >= 18)
	{
		szRes[5] = '-';
		szRes[11] = '-';
	}

	return szRes;
}

int main()
{
	// FIXME: We need to sleep here because the random number generation fucks up if g_Clock.now()
	// isn't high enough

	printf_s("Amount of keys to generate: ");
	std::string szInput = "";
	std::cin >> szInput;

	int nAmount = std::atoi(szInput.c_str());

	g_Clock.now();

	std::ofstream File("keys_generated.txt");

	while (nAmount > 0)
	{
		File << GenerateKey() << "\n";

		nAmount--;
	}

	printf_s("Done!\n");
	system("pause");

	return 0;
}