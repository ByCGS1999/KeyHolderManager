#pragma once

class Container
{
public:
	std::string identifier;
	std::string username;
	std::string password;
	std::string key;
	std::string iv;

	Container(const std::string id, const std::string username, const std::string password);
	Container(const std::string id, const std::string username, const std::string password, const std::string key, const std::string iv);

	std::string decryptPassword();
};

class KeyContainer
{
public:
	std::string globalPassword;
	bool enteredGlobalPassword = false;

private:
	std::vector<Container> keyContainers;
	std::string globalIV;

	SafeString EncryptionHandler;

public:
	KeyContainer();

	void addKeyToContainer(Container& container);
	void removeContainer(int containerIndex);

	Container getDecryptedContainer(int containerIndex);

	std::vector<Container> GetContainers();
	int GetContainerCount();

	std::string getDecryptedPassword(const std::string identifier = "");
	void setGlobalPassword(const std::string& passwd);
	void Migrate(const std::string& oldPassword, const std::string& newPassword, bool& regenerateIV);

	std::string getGlobalIV();
};