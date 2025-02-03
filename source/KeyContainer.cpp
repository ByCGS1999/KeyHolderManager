#include <Includes.h>
#include <SafeString.h>
#include <KeyContainer.h>
#include <DataBase.h>
#include <cryptopp/hex.h>

std::string FromHex(const std::string& hex)
{
	std::string decoded = "";
	CryptoPP::HexDecoder decoder;
	decoder.Attach(new CryptoPP::StringSink(decoded));
	decoder.Put(reinterpret_cast<const CryptoPP::byte*>(hex.data()), hex.size());
	decoder.MessageEnd();

	return decoded;
}

std::string ToHex(const std::string raw)
{
	std::string hexIV;
	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(hexIV));
	encoder.Put(reinterpret_cast<const CryptoPP::byte*>(raw.data()), raw.size());
	encoder.MessageEnd();
	return hexIV;
}

Container::Container(const std::string id, const std::string username, const std::string password)
{
	SafeString safeString = SafeString();
	this->identifier = id;
	this->username = username;
	this->password = safeString.encryptString(password);
	this->iv = safeString.GetIV();
	this->key = safeString.GetKey();
}

Container::Container(const std::string id, const std::string username, const std::string password, const std::string key, const std::string iv)
{
	this->identifier = id;
	this->username = username;
	this->password = password;
	this->key = key;
	this->iv = iv;
}

std::string Container::decryptPassword()
{
	SafeString safeString = SafeString(FromHex(this->key), FromHex(this->iv));

	return safeString.decryptString(this->password);
}

KeyContainer::KeyContainer()
{
	this->keyContainers = LoadContainers();
	if (GetGlobalIV().empty())
	{
		this->globalIV = "";
	}
	else
	{
		this->globalIV = GetGlobalIV();
	}
}

void KeyContainer::addKeyToContainer(Container& safeString)
{
	Container& container = safeString;

	container.key = EncryptionHandler.encryptString(container.key);
	container.iv = EncryptionHandler.encryptString(container.iv);

	this->keyContainers.push_back(container);
	SaveContainer(this->keyContainers.size()-1, container);
}

void KeyContainer::removeContainer(int containerIndex)
{
	try
	{
		Container& c = this->keyContainers.at(containerIndex);
		this->keyContainers.erase(this->keyContainers.begin() + containerIndex);

		DeleteContainer(containerIndex);
	}
	catch (std::exception ex)
	{
		std::cerr << "An exception has occurred: " << ex.what() << std::endl;
	}
}

std::string KeyContainer::getDecryptedPassword(const std::string identifier)
{
	for (auto& container : this->keyContainers)
	{
		if (container.identifier == identifier)
		{
			SafeString safeString = SafeString(container.key, container.iv);
			return safeString.decryptString(container.password);
		}
	}
	return "";
}

std::vector<Container> KeyContainer::GetContainers() { return this->keyContainers; }
int KeyContainer::GetContainerCount() { return this->keyContainers.size(); }

Container KeyContainer::getDecryptedContainer(int containerId)
{
	try
	{
		Container c = this->keyContainers.at(containerId);
		c.key = EncryptionHandler.decryptString(c.key);
		c.iv = EncryptionHandler.decryptString(c.iv);

		return c;
	}
	catch (std::exception exception)
	{

	}

	Container c = Container("ERROR", "DECRYPTING", "CONTAINER");
	return c;
}

void KeyContainer::Migrate(const std::string& oldPassword, const std::string& newPassword, bool& regenerateIV)
{
	if (oldPassword != globalPassword)
		return;

	std::vector<Container> decryptedContainers = std::vector<Container>();
	std::vector<Container> encryptedContainers = GetContainers();

	for (int x = 0; x < this->GetContainerCount(); x++)
	{
		decryptedContainers.push_back(getDecryptedContainer(x));
	}

	// decrypted containers

	if (regenerateIV)
		this->globalIV = "";

	this->setGlobalPassword(newPassword);
	// Do Cleanup
	this->keyContainers.clear();
	DeleteAllContainers();

	for (Container c : decryptedContainers)
	{
		addKeyToContainer(c);
	}
}

void KeyContainer::setGlobalPassword(const std::string& password)
{
	this->globalPassword = password;
	this->enteredGlobalPassword = true;
	EncryptionHandler = SafeString(password, FromHex(globalIV));

	if (globalIV == "")
		this->globalIV = EncryptionHandler.GetIV();
}

std::string KeyContainer::getGlobalIV()
{
	return EncryptionHandler.GetIV();
}
