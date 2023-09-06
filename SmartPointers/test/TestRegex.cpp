
#include <SmartPointers/Regex.h>
#include <gtest/gtest.h>

#include <algorithm>
namespace smartPointers
{
TEST(ValidateEmailTest, ValidEmail)
{
    std::string email = "example@example.com";
    EXPECT_TRUE(validateEmail(email));
}

TEST(ValidateEmailTest, InvalidEmail)
{
    std::string email = "example@.com";
    EXPECT_FALSE(validateEmail(email));
}

TEST(ValidateEmailTest, NoAtSymbol)
{
    std::string email = "example.com";
    EXPECT_FALSE(validateEmail(email));
}

TEST(ValidateEmailTest, NoDomainExtension)
{
    std::string email = "example@example";
    EXPECT_FALSE(validateEmail(email));
}

TEST(RemoveWhitespaceTest, BasicTest)
{
    std::string text = "  This is a test  with     white spaces   ";
    std::string expected = "Thisisatestwithwhitespaces";
    std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(RemoveWhitespaceTest, NewlineTest)
{
    std::string text = "This\nis\na\ntest\nwith\nnewline\ncharacters\n";
    std::string expected = "Thisisatestwithnewlinecharacters";
    std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(RemoveWhitespaceTest, EmptyStringTest)
{
    std::string text = "";
    std::string expected = "";
    std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(RemoveWhitespaceTest, OnlySpacesTest)
{
    std::string text = "    ";
    std::string expected = "";
    std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(ExtractDomainTest, ValidEmailSimple)
{
    std::string email = "johndoe@example.com";
    std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "example.com");
}
TEST(ExtractDomainTest, ValidEmail)
{
    std::string email = "John Doe johndoe@example.com";
    std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "example.com");
}

TEST(ExtractDomainTest, NoDomain)
{
    std::string email = "John Doe @johndoe";
    std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "");
}

TEST(ExtractDomainTest, InvalidEmail)
{
    std::string email = "John@ Doe";
    std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "");
}

}  // namespace smartPointers
