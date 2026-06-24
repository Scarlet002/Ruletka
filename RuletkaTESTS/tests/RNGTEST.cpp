#include "pch.h"
#include "RNG.h"

TEST(RNG, GenerateRandomNumberInRange)
{
	int min = 1;
	int max = 10;
	int randomNumber = RNG::GetRN(min, max);
	EXPECT_GE(randomNumber, min);
	EXPECT_LE(randomNumber, max);
}