# KeyHolderManager

KeyHolderManager is a Password Manager application written in C++, using CryptoPP, GLFW3, SQLITE3 and ImGUI.
Its a fast, safe, easy to setup, password manager.

## With a simplistic ImGUI ui for its user interface.
![image](https://github.com/user-attachments/assets/3b5e5cf5-1506-4c60-879b-e5606c0cc037).

## It comes with a built in safe customizable password generator (64 chars max).
<br>

![image](https://github.com/user-attachments/assets/a1bd07b3-5ff6-402a-bb5f-63e4fe87eb96)

## And has multiple built-in themes.
<br>

![image](https://github.com/user-attachments/assets/d0b6b14d-8c71-4f94-9ba1-47b7e3979cb1)
![image](https://github.com/user-attachments/assets/b30c3a36-c36f-42dd-9261-8e1078cd7245)

## Has shortcuts for easier accesibility.
- CTRL + C to copy username.
- CTRL + V to copy password.
- SHIFT + A to Add a new Key.
- Delete to remove the selected entry from the list.
- CTRL + Q to Quit.

It also allows you to filter through all your credentials using the 'identifier' column.

## Tested Platforms
- Windows

## Untested Platforms
- Linux
- MacOS

Theoricly, it should work natively in both Linux and Mac as it doesn't use any Windows-only dependency.

## Dependencies.

- CMake
- VCPKG (GLFW3, GLAD, CryptoPP, SQLITE3)
- C++20
- A Brain (semi functional should be enough)

- Change VCPKG root route to make it link libraries and compile, can change it on CMakePresets.json.
