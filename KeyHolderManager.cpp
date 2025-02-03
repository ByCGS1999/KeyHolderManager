#include <Includes.h>
#include <SafeString.h>
#include <KeyContainer.h>
#include "KeyHolderManager.h"
#include "ImguiImpl/imgui_impl_glfw.h"
#include "ImguiImpl/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"
#include <Themes.h>
#include <DataBase.h>
#include <PasswordGenerator.h>

GLFWwindow* window = nullptr;

bool shouldClose = true;
int selectedRow = -1;
bool dbWasCreated = false;
bool seepassword = false;
KeyContainer keyContainer;

bool initMainWindow = false;
bool initMasterKeyPopup = false;
bool initDropDatabasePopup = false;
bool initMasterKeyOverride = false;
bool initAddKeyOverride = false;
bool initPasswordGenerator = false;

bool toggleDropDatabasePopup = false;
bool toggleAddKeyPopup = false;
bool toggleMasterKeyOverridePopup = false;
bool togglePasswordGenerator = false;


std::string filterText = "";
std::string password = "";

// master override

bool mo_changeGlobalIV = false;
std::string mo_Password = "";
std::string mo_newPassword = "";
bool mo_seePassword_0 = 0;
bool mo_seePassword_1 = 0;

// add container popup

unsigned int add_flags = ImGuiInputTextFlags_Password;
bool add_isChecked = false;
std::string add_identifier;
std::string add_username;
std::string add_password;

int pg_charCount = 8;
bool pg_useUpper = true;
bool pg_useLower = true;
bool pg_useNumbers = true;
bool pg_useSymbols = true;

std::string pg_password;

void copyUsernameToClipboard(int index)
{
	try
	{
		if (selectedRow == -1)
			return;

		ImGui::SetClipboardText(keyContainer.GetContainers().at(index).username.c_str());
	}
	catch (std::exception ex)
	{

	}
}

void copyPasswordToClipboard(int index)
{
	try
	{
		if (selectedRow == -1)
			return;

		Container c = keyContainer.getDecryptedContainer(index);

		if (c.identifier == "ERROR" && c.username == "DECRYPTING" && c.decryptPassword() == "CONTAINER")
			return;

		ImGui::SetClipboardText(c.decryptPassword().c_str());
	}
	catch (std::exception ex)
	{

	}
}

void deleteRegistry(int index)
{
	keyContainer.removeContainer(index);
}

int main()
{
	glfwInit();

	const char* glsl_version = "#version 430";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	window = glfwCreateWindow(1, 1, "KeyHolderManager", NULL, NULL);

	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowPos(window, 0,0);
	glfwSetKeyCallback(window, keyboardCallback);

	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}
	glfwSwapInterval(1);

	std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;

	pg_password = GeneratePassword(pg_charCount, pg_useUpper, pg_useLower, pg_useNumbers, pg_useSymbols);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;

	dbWasCreated = InitDB();

	keyContainer = KeyContainer();

	glfwHideWindow(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		handleImguiKeyboard();

		drawGui();

		ImGui::Render();

		render();

		GLenum err;

		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL Error before rendering viewports: " << err << std::endl;
		}

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL Error after rendering viewports: " << err << std::endl;
		}

		glfwSetWindowShouldClose(window, !shouldClose);

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	CloseDB();

	glfwTerminate();
	return 0;
}

void handleImguiKeyboard()
{
	ImGuiIO& io = ImGui::GetIO();

	if (!keyContainer.enteredGlobalPassword || toggleDropDatabasePopup || toggleAddKeyPopup)
		return;

	if (ImGui::IsKeyPressed(ImGuiKey_Q, false) && io.KeyMods & ImGuiMod_Ctrl)
		shouldClose = false;
	if (ImGui::IsKeyPressed(ImGuiKey_C, false) && io.KeyMods & ImGuiMod_Ctrl)
		copyUsernameToClipboard(selectedRow);
	if (ImGui::IsKeyPressed(ImGuiKey_V, false) && io.KeyMods & ImGuiMod_Ctrl)
		copyPasswordToClipboard(selectedRow);
	if (ImGui::IsKeyPressed(ImGuiKey_Delete, false))
		deleteRegistry(selectedRow);
	if (ImGui::IsKeyPressed(ImGuiKey_I, false) && io.KeyMods & ImGuiMod_Ctrl)
		keyContainer.enteredGlobalPassword = false;
	if (ImGui::IsKeyPressed(ImGuiKey_K, false) && io.KeyMods & ImGuiMod_Ctrl && io.KeyMods & ImGuiMod_Shift)
		toggleMasterKeyOverridePopup = true;
	if (ImGui::IsKeyPressed(ImGuiKey_A, false) && io.KeyMods & ImGuiMod_Shift)
		toggleAddKeyPopup = true;
}

void InitMasterKeyPopup()
{
	if (ImGui::BeginPopupModal("Enter Master Key", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!initMasterKeyPopup)
		{
			int width, height;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			glfwGetMonitorPhysicalSize(monitor, &width, &height);

			ImVec2 v2 = {
				(float)(width / 2.0f),
				(float)(height / 2.0f)
			};
			ImGui::SetWindowPos(v2);
			initMasterKeyPopup = true;
		}

		if (dbWasCreated == true)
			ImGui::Text("Enter the master key to continue. (Entering a wrong password will give wrong passwords on demand)");
		else
			ImGui::Text("Enter a master key.");

		ImGui::Text("Master Key:"); ImGui::SameLine();
		if(seepassword)
			ImGui::InputText("###MasterKey", &password);
		else
			ImGui::InputText("###MasterKey", &password, ImGuiInputTextFlags_Password);
		ImGui::SameLine();
		ImGui::Checkbox("See Password", &seepassword);

		if (ImGui::Button("Enter"))
		{
			if (password != "")
			{
				keyContainer.setGlobalPassword(password);
				InsertGlobalIV(keyContainer.getGlobalIV());
				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Exit"))
		{
			ImGui::CloseCurrentPopup();
			shouldClose = false;
			CloseDB();
		}

		ImGui::EndPopup();
	}
}
void MasterKeyOverridePopup()
{
	if (ImGui::BeginPopupModal("Override Master Key", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!initMasterKeyOverride)
		{
			int width, height;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			glfwGetMonitorPhysicalSize(monitor, &width, &height);

			ImVec2 v2 = {
				(float)(width / 2.0f),
				(float)(height / 2.0f)
			};
			ImGui::SetWindowPos(v2);
			initMasterKeyOverride = true;
		}

		ImGui::Text("You're about to override the master key, this process is CPU intensive as");
		ImGui::Text("it will decrypt all the containers and encrypt them again with your new key");

		ImGui::Text("Key: ");
		ImGui::SameLine();
		if(mo_seePassword_0)
			ImGui::InputText("###MOv_Text", &mo_Password);
		else
			ImGui::InputText("###MOv_Text", &mo_Password, ImGuiInputTextFlags_Password);
		ImGui::SameLine();
		ImGui::Checkbox("See Password", &mo_seePassword_0);

		ImGui::Text("New Key: ");
		ImGui::SameLine();
		if (mo_seePassword_1)
			ImGui::InputText("###MOv_NewText", &mo_newPassword); 
		else
			ImGui::InputText("###MOv_NewText", &mo_newPassword, ImGuiInputTextFlags_Password);
		ImGui::SameLine();
		ImGui::Checkbox("See New Password", &mo_seePassword_1);

		ImGui::Text("Regenerate IV: ");
		ImGui::SameLine();
		ImGui::Checkbox("###MOv_RegenIV", &mo_changeGlobalIV);

		if (ImGui::Button("Continue"))
		{
			keyContainer.Migrate(mo_Password, mo_newPassword, mo_changeGlobalIV);

			if(mo_changeGlobalIV)
				UpdateGlobalIV(keyContainer.getGlobalIV());
			
			toggleMasterKeyOverridePopup = false;

			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			toggleMasterKeyOverridePopup = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}
void DropDatabasePopup()
{
	if (ImGui::BeginPopupModal("Drop Database", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!initDropDatabasePopup)
		{
			int width, height;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			glfwGetMonitorPhysicalSize(monitor, &width, &height);

			ImVec2 v2 = {
				(float)(width / 2.0f),
				(float)(height / 2.0f)
			};
			ImGui::SetWindowPos(v2);
			initDropDatabasePopup = true;
		}

		ImGui::Text("You're about to drop the database with all your saved passwords.");
		ImGui::Text("Are you sure you want to continue?");

		if (ImGui::Button("Yes"))
		{
			toggleDropDatabasePopup = false;
			CloseDB();
			shouldClose = false;
			remove("data.db");
		}
		ImGui::SameLine();
		if (ImGui::Button("No"))
		{
			toggleDropDatabasePopup = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}
void AddKeyPopup()
{
	if (ImGui::BeginPopupModal("Add Key", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!initAddKeyOverride)
		{
			int width, height;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			glfwGetMonitorPhysicalSize(monitor, &width, &height);

			ImVec2 v2 = {
				(float)(width / 2.0f),
				(float)(height / 2.0f)
			};
			ImGui::SetWindowPos(v2);
			initAddKeyOverride = true;
		}


		ImGui::Text("Identifier:");
		ImGui::SameLine();
		ImGui::InputText("###IDENTIFIER_", &add_identifier);
		ImGui::Text("Username:");
		ImGui::SameLine();
		ImGui::InputText("###USERNAME_", &add_username);
		ImGui::Text("Password:");
		ImGui::SameLine();
		ImGui::InputText("###PASSWORD_", &add_password, add_flags);
		ImGui::Text("See Password:");
		ImGui::SameLine();
		ImGui::Checkbox("###SEE_PASSWORD", &add_isChecked);

		if (add_isChecked)
			add_flags = ImGuiInputTextFlags_None;
		else
			add_flags = ImGuiInputTextFlags_Password;

		if (ImGui::Button("Yes"))
		{
			keyContainer.addKeyToContainer(Container(add_identifier, add_username, add_password));

			add_identifier = "";
			add_password = "";
			add_username = "";
			toggleAddKeyPopup = false;

			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("No"))
		{
			toggleAddKeyPopup = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}
void PasswordGeneratorPopup()
{
	if (ImGui::BeginPopupModal("Password Generator", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!initPasswordGenerator)
		{
			int width, height;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			glfwGetMonitorPhysicalSize(monitor, &width, &height);

			ImVec2 v2 = {
				(float)(width / 2.0f),
				(float)(height / 2.0f)
			};
			ImGui::SetWindowPos(v2);
			initPasswordGenerator = true;
		}

		ImGui::Text("Output Password: ");
		ImGui::SameLine();
		ImGui::InputText("", &pg_password, ImGuiInputTextFlags_ReadOnly);

		ImGui::Text("Password Length: ");
		ImGui::SameLine();
		ImGui::SliderInt("###Password Length:", &pg_charCount, 8, 64);

		ImGui::Checkbox(": Use UpperCase Letters", &pg_useUpper);
		ImGui::Checkbox(": Use LowerCase Letters", &pg_useLower);
		ImGui::Checkbox(": Use Digits", &pg_useNumbers);
		ImGui::Checkbox(": Use Special Chars", &pg_useSymbols);

		if (ImGui::Button("Regen Password"))
			pg_password = GeneratePassword(pg_charCount, pg_useUpper, pg_useLower, pg_useNumbers, pg_useSymbols);

		if (ImGui::Button("Close"))
		{
			togglePasswordGenerator = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void drawGui()
{
	ImGui::Begin("KeyHolderManager", &shouldClose, ImGuiWindowFlags_MenuBar);
	{
		if (!initMainWindow)
		{
			int width, height;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			glfwGetMonitorPhysicalSize(monitor, &width, &height);
			ImVec2 v2 = { 
				(float)(width / 2.0f), 
				(float)(height / 2.0f)
			};
			ImGui::SetWindowPos(v2);
			ImGui::SetWindowSize({ 500, 150 });
			initMainWindow = true;
		}

		if (!keyContainer.enteredGlobalPassword)
			ImGui::OpenPopup("Enter Master Key");
		if (toggleDropDatabasePopup)
			ImGui::OpenPopup("Drop Database");
		if (toggleMasterKeyOverridePopup)
			ImGui::OpenPopup("Override Master Key");
		if (toggleAddKeyPopup)
			ImGui::OpenPopup("Add Key");
		if (togglePasswordGenerator)
			ImGui::OpenPopup("Password Generator");

		if(ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Drop Database"))
				{
					toggleDropDatabasePopup = true;
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "CTRL + Q"))
				{
					shouldClose = false;
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Add Key", "Shift + A"))
					toggleAddKeyPopup = true;

				ImGui::Separator();

				if (ImGui::BeginMenu("Themes"))
				{
					if (ImGui::MenuItem("Dark Theme"))
						ImGui::StyleColorsDark();
					if (ImGui::MenuItem("Light Theme"))
						ImGui::StyleColorsLight();
					if (ImGui::MenuItem("Classic Theme"))
						ImGui::StyleColorsClassic();
					if (ImGui::MenuItem("Cinder Theme"))
						SetCinderTheme();

					ImGui::SeparatorText("ChatGPT Themes (They can be shit)");

					if (ImGui::MenuItem("Ocean Blue"))
						SetOceanBlueTheme();
					if (ImGui::MenuItem("Green Forest"))
						SetGreenForestTheme();
					if (ImGui::MenuItem("Sunset Red"))
						SetSunsetRedTheme();

					ImGui::SeparatorText("FineTuned ChatGPT Themes (Based on Cinder Theme)");

					if (ImGui::MenuItem("Dark Crimson"))
						SetDarkCrimsonTheme();
					if (ImGui::MenuItem("Neon Glow"))
						SetNeonGlowTheme();
					if (ImGui::MenuItem("Dark Red Velvet"))
						SetDarkRedVelvetTheme();
					if (ImGui::MenuItem("Ocean Breeze"))
						SetOceanBreezeTheme();

					ImGui::EndMenu();
				}

				ImGui::Separator();

				if (ImGui::BeginMenu("Set Master Key"))
				{
					if (ImGui::MenuItem("Override", "CTRL + SHIFT + K"))
					{
						toggleMasterKeyOverridePopup = true;
					}

					if (ImGui::MenuItem("Re-Input", "CTRL + I"))
					{
						keyContainer.enteredGlobalPassword = false;
					}

					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Selection"))
			{
				if (ImGui::MenuItem("Copy Username", "CTRL + C"))
					copyUsernameToClipboard(selectedRow);
				if (ImGui::MenuItem("Copy Password", "CTRL + V"))
					copyPasswordToClipboard(selectedRow);

				ImGui::Separator();

				if(ImGui::MenuItem("Delete", "Delete"))
					deleteRegistry(selectedRow);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Utility"))
			{
				if (ImGui::MenuItem("Password Generator"))
					togglePasswordGenerator = true;

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		 
		ImGui::Text("Filter By Id:");
		ImGui::SameLine();
		ImGui::InputText("###Filter", &filterText);

		if (ImGui::BeginTable("TABLE", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
		{
			ImGui::TableSetupColumn("", 0, 0.00001f);
			ImGui::TableSetupColumn("Identifier");
			ImGui::TableSetupColumn("Username");
			ImGui::TableSetupColumn("Password");
			ImGui::TableHeadersRow();

			auto containers = keyContainer.GetContainers();

			for (int i = 0; i < keyContainer.GetContainerCount(); ++i)
			{
				if (filterText != "")
				{
					if(containers[i].identifier.find(filterText) != std::string::npos)
					{
						ImGui::TableNextRow();

						// Detect click on the whole row
						if (ImGui::TableSetColumnIndex(0) && ImGui::Selectable(("##row" + std::to_string(i)).c_str(), selectedRow == i, ImGuiSelectableFlags_SpanAllColumns))
						{
							selectedRow = i;
						}

						// Display inputs in the row
						ImGui::TableSetColumnIndex(1);
						ImGui::TextUnformatted(containers[i].identifier.c_str());

						ImGui::TableSetColumnIndex(2);
						ImGui::TextUnformatted(containers[i].username.c_str());

						ImGui::TableSetColumnIndex(3);
						ImGui::TextUnformatted(containers[i].password.c_str());
					}
				}
				else
				{
					ImGui::TableNextRow();

					// Detect click on the whole row
					if (ImGui::TableSetColumnIndex(0) && ImGui::Selectable(("##row" + std::to_string(i)).c_str(), selectedRow == i, ImGuiSelectableFlags_SpanAllColumns))
					{
						selectedRow = i;
					}

					// Display inputs in the row
					ImGui::TableSetColumnIndex(1);
					ImGui::TextUnformatted(keyContainer.GetContainers()[i].identifier.c_str());

					ImGui::TableSetColumnIndex(2);
					ImGui::TextUnformatted(keyContainer.GetContainers()[i].username.c_str());

					ImGui::TableSetColumnIndex(3);
					ImGui::TextUnformatted(keyContainer.GetContainers()[i].password.c_str());
				}
			}

			ImGui::EndTable();
		}

		InitMasterKeyPopup();
		MasterKeyOverridePopup();
		DropDatabasePopup();
		AddKeyPopup();
		PasswordGeneratorPopup();
	}

	ImGui::End();
}

void render()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void keyboardCallback(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}