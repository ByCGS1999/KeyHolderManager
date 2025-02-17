#include <Includes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/randpool.h>
#include <cryptopp/osrng.h>
#include <SafeString.h>
#include <KeyContainer.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/secblock.h>
#include <iostream>

using namespace CryptoPP;
using namespace std;

const short KEYLENGTH = AES::DEFAULT_KEYLENGTH; // KeyLength


std::string deriveKeyFromPassword(const std::string& password, const std::string& salt, size_t keyLength = 16)
{
	CryptoPP::SecByteBlock key(keyLength);
	CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf2;

	pbkdf2.DeriveKey(
		key, key.size(), 0,
		reinterpret_cast<const CryptoPP::byte*>(password.data()), password.size(),
		reinterpret_cast<const CryptoPP::byte*>(salt.data()), salt.size(),
		10000 // Iteration count (higher = more secure, but slower)
	);

	// Convert key to hex
	std::string hexKey;
	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(hexKey));
	encoder.Put(key, key.size());
	encoder.MessageEnd();

	return hexKey;
}

std::string hexToRawKey(const std::string& hexKey)
{
	std::string rawKey;
	CryptoPP::HexDecoder decoder;
	decoder.Attach(new CryptoPP::StringSink(rawKey));
	decoder.Put(reinterpret_cast<const CryptoPP::byte*>(hexKey.data()), hexKey.size());
	decoder.MessageEnd();

	return rawKey;
}


std::string HashKey(const std::string& key, const size_t max_size = KEYLENGTH)
{
	std::string hashed;
	CryptoPP::SHA256 hash;
	StringSource ss(key, true, new HashFilter(hash, new StringSink(hashed)));
	return hashed.substr(0, max_size);
}

void SafeString::GenerateRandomKeyAndIV()
{
	GenerateRandomIV();
	GenerateRandomKey();
}

void SafeString::GenerateRandomKey()
{
	CryptoPP::AutoSeededRandomPool prng;

	// Generate a 16-byte AES key (128-bit key for AES-128)
	this->key.resize(KEYLENGTH);
	prng.GenerateBlock(reinterpret_cast<CryptoPP::byte*>(&key[0]), KEYLENGTH);
}


void SafeString::GenerateRandomIV()
{
	CryptoPP::AutoSeededRandomPool prng;

	// Generate a 16-byte IV for AES (CBC mode requires a 16-byte IV)
	iv.resize(AES::BLOCKSIZE);
	prng.GenerateBlock(reinterpret_cast<CryptoPP::byte*>(&iv[0]), AES::BLOCKSIZE);
}

std::string SafeString::encryptString(const std::string& rawData)
{
	std::string ciphered = "";

	try
	{
		CBC_Mode<AES>::Encryption cbcEncryption(
			reinterpret_cast<const CryptoPP::byte*>(this->key.data()),
			KEYLENGTH,
			reinterpret_cast<const CryptoPP::byte*>(this->iv.data())
		);

		StringSource ss(rawData, true,
			new StreamTransformationFilter(
				cbcEncryption,
				new StringSink(
					ciphered
				)
			)
		);

		// Convert to hex
		std::string hexCipherText;
		StringSource ss2(ciphered,
			true,
			new HexEncoder(
				new StringSink(hexCipherText)
			)
		);

		ciphered = hexCipherText;
	}
	catch (const std::exception& e) {
		std::cerr << "Encryption failed: " << e.what() << std::endl;
	}

	return ciphered;
}


std::string SafeString::decryptString(const std::string& cipherHex)
{
	std::string recovered;

	try
	{
		std::string cipherRaw;
		StringSource ss(cipherHex, true,
			new HexDecoder(new StringSink(cipherRaw))
		);

		CBC_Mode<AES>::Decryption cbcDecryption(
			reinterpret_cast<const CryptoPP::byte*>(this->key.data()),
			KEYLENGTH,
			reinterpret_cast<const CryptoPP::byte*>(this->iv.data())
		);

		StringSource ss2(cipherRaw, true,
			new StreamTransformationFilter(
				cbcDecryption,
				new StringSink(recovered),
				StreamTransformationFilter::PKCS_PADDING
			)
		);
	}
	catch (const std::exception& e) {
		std::cerr << "Decryption failed: " << e.what() << std::endl;
	}

	return recovered;
}



SafeString::SafeString()
{
	this->GenerateRandomKeyAndIV();
}

std::string PadKeyToSize(const std::string& key, size_t size = KEYLENGTH)
{
	std::string paddedKey = key;
	while (paddedKey.size() < size)
	{
		paddedKey += "0";
	}
	paddedKey.resize(size);
	return paddedKey;
}

std::string PadBlockToSize(const std::string& key, size_t size = AES::BLOCKSIZE)
{
	std::string paddedKey = key;
	while (paddedKey.size() < size)
	{
		paddedKey += "0";
	}
	paddedKey.resize(size);
	return paddedKey;
}

SafeString::SafeString(const std::string key, const std::string iv)
{
	if (key.empty()) 
	{
		GenerateRandomKey();
	}
	else
	{
		this->key = PadKeyToSize(key, KEYLENGTH);
	}

	if (iv.empty())
	{
		GenerateRandomIV();
	}
	else
	{
		this->iv = iv;
	}
}

std::string SafeString::GetKey() const
{
	std::string hexKey;
	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(hexKey));
	encoder.Put(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size());
	encoder.MessageEnd();
	return hexKey;
}

std::string SafeString::GetIV() const
{
	std::string hexIV;
	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(hexIV));
	encoder.Put(reinterpret_cast<const CryptoPP::byte*>(iv.data()), iv.size());
	encoder.MessageEnd();
	return hexIV;
}