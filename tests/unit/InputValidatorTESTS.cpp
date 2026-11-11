#include "GameConfig.h"
#include "InputValidator.h"
#include <boost/static_string/static_string.hpp>
#include <gtest/gtest.h>

TEST(InputValidatorTESTS, IsValidNumericInputAcceptsBoundaries)
{
    EXPECT_TRUE(InputValidator::IsValidNumericInput(1, 1, 5));
    EXPECT_TRUE(InputValidator::IsValidNumericInput(5, 1, 5));
    EXPECT_TRUE(InputValidator::IsValidNumericInput(3, 1, 5));
}

TEST(InputValidatorTESTS, IsValidNumericInputRejectsOutOfRange)
{
    EXPECT_FALSE(InputValidator::IsValidNumericInput(0, 1, 5));
    EXPECT_FALSE(InputValidator::IsValidNumericInput(6, 1, 5));
    EXPECT_FALSE(InputValidator::IsValidNumericInput(-1, 1, 5));
}

TEST(InputValidatorTESTS, IsValidFileNameRejectsEmpty)
{
    EXPECT_FALSE(InputValidator::IsValidFileName(""));
}

TEST(InputValidatorTESTS, IsValidFileNameRejectsTooLongNames)
{
    constexpr auto SIZE = GameConfig::MAX_FILENAME_LENGTH + 1U;
    const auto longName = boost::static_string<SIZE>(SIZE, 'a');
    EXPECT_FALSE(InputValidator::IsValidFileName(longName));
}

TEST(InputValidatorTESTS, IsValidFileNameAcceptsAlphanumericAndSeparators)
{
    EXPECT_TRUE(InputValidator::IsValidFileName("save_1"));
    EXPECT_TRUE(InputValidator::IsValidFileName("my-save-2"));
    EXPECT_TRUE(InputValidator::IsValidFileName("ABC123"));
}

TEST(InputValidatorTESTS, IsValidFileNameRejectsPathTraversal)
{
    EXPECT_FALSE(InputValidator::IsValidFileName("../etc/passwd"));
    EXPECT_FALSE(InputValidator::IsValidFileName("..\\bad"));
    EXPECT_FALSE(InputValidator::IsValidFileName("a/b"));
    EXPECT_FALSE(InputValidator::IsValidFileName("."));
    EXPECT_FALSE(InputValidator::IsValidFileName(".."));
}

TEST(InputValidatorTESTS, IsValidFileNameRejectsSpacesAndSpecialChars)
{
    EXPECT_FALSE(InputValidator::IsValidFileName("my save"));
    EXPECT_FALSE(InputValidator::IsValidFileName("save!"));
    EXPECT_FALSE(InputValidator::IsValidFileName("save*"));
    EXPECT_FALSE(InputValidator::IsValidFileName("save\\"));
}
