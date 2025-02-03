#include <string>
#include "PasswordGenerator.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <vector>

const std::string UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
const std::string DIGITS = "0123456789";
const std::string SPECIAL = "!@#$%^&*()-_=+[]{}|;:,.<>?/";

std::string GeneratePassword(int length, bool upper, bool lower, bool digits, bool special)
{
    if (length < 8) // Ensure a minimum length for strength
    {
        throw std::invalid_argument("Password length must be at least 8 characters!");
        return "";
    }

    // Build the allowed character pool based on user selection
    std::string allowedChars;
    std::vector<char> password(length);
    CryptoPP::AutoSeededRandomPool prng;

    if (upper) allowedChars += UPPERCASE;
    if (lower) allowedChars += LOWERCASE;
    if (digits) allowedChars += DIGITS;
    if (special) allowedChars += SPECIAL;

    if (allowedChars.empty())
    {
        throw std::invalid_argument("At least one character type must be enabled!");
        return "";
    }

    // Ensure at least one character from each selected category
    int index = 0;
    if (upper)
        password[index++] = UPPERCASE[prng.GenerateByte() % UPPERCASE.length()];
    if (lower)
        password[index++] = LOWERCASE[prng.GenerateByte() % LOWERCASE.length()];
    if (digits)
        password[index++] = DIGITS[prng.GenerateByte() % DIGITS.length()];
    if (special)
        password[index++] = SPECIAL[prng.GenerateByte() % SPECIAL.length()];

    // Fill the rest of the password randomly
    for (; index < length; index++)
    {
        password[index] = allowedChars[prng.GenerateByte() % allowedChars.length()];
    }

    // Shuffle password to remove predictable patterns
    for (int i = 0; i < length; i++)
    {
        int swapIndex = prng.GenerateByte() % length;
        std::swap(password[i], password[swapIndex]);
    }

    return std::string(password.begin(), password.end());
}