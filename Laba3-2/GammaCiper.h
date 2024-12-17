#pragma once
#include <locale>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <codecvt>
class GammaCipher
{
	private:
		int key;
	public:
		GammaCipher() = delete;
		GammaCipher(int key);
		std::wstring encrypt(const std::wstring& text);
		std::wstring decrypt(const std::wstring& encrypted_text);
		std::wstring getValidKey(const std::wstring & s);
		std::wstring getValidOpenText(const std::wstring & s);
		std::wstring getValidCipherText(const std::wstring & s);
};

class cipher_error: public std::invalid_argument {
public:
	explicit cipher_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};
