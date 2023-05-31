#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <chrono>

#include "XoshiroCpp.h"

constexpr char ALL_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

constexpr unsigned char ALL_CHARS_LENGTH = 26;
constexpr unsigned char NUMERIC_CHARS_LENGTH = 10;

int GenerateRandom(const int nSeed)
{
	XoshiroCpp::Xoshiro256PlusPlus rng(nSeed);
	std::uniform_int_distribution<int> dist(0, strlen(ALL_CHARS));

	return dist(rng);
}

std::chrono::steady_clock g_Clock;

int AddRTTimeRandomization(const int nRand)
{
	return nRand + (g_Clock.now().time_since_epoch().count() + (__TIME__[1]));
}

std::string GenerateKey()
{
	std::string szRes = "";
	for (int i = 0; i < 18; i++)
		szRes.push_back(ALL_CHARS[AddRTTimeRandomization(GenerateRandom(i) * 1000) % ALL_CHARS_LENGTH]);

	if (szRes.length() >= 18)
	{
		szRes[5] = '-';
		szRes[11] = '-';
	}

	return szRes;
}

int main()
{
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