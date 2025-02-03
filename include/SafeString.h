#pragma once

struct SafeString
{
private:
	std::string key;
	std::string iv;

public:
	SafeString();
	SafeString(const std::string key, const std::string iv);

	void GenerateRandomKeyAndIV();
	void GenerateRandomKey();
	void GenerateRandomIV();
	std::string encryptString(const std::string rawData);
	std::string decryptString(const std::string password);

	void SetKey(const std::string key);

	std::string GetKey() const;
	std::string GetIV() const;
};