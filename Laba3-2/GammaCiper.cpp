#include "GammaCiper.h"
#include <locale>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <codecvt>
using namespace std;
GammaCipher::GammaCipher(int key)
	: key(key)
{
}
	std::wstring GammaCipher::encrypt(const std::wstring& text)
{
	std::wstring new_text = getValidOpenText(text);
	int rows;
	if (key < 1){throw cipher_error(std::string("Неправильный ключ: "));
}
	if(new_text.length() % key != 0) {
		rows = new_text.length() / key + 1;
	} else {
		rows = new_text.length() / key;
	}
	wchar_t Gamma[rows][key];
	int index = 0; 
	for(int i = 0; i < rows; i++) { 
		for(int j = 0; j < key; j++) { 
			if(index < new_text.length()) {
				Gamma[i][j] = new_text[index];
				index++;
			} else {
				Gamma[i][j] = L' ';
			}
		}
	}
	std::wstring encrypted_text;
	for(int i = key - 1; i >= 0; i--) {
		for(int j = 0; j < rows; j++) {
			encrypted_text += Gamma[j][i];
		}
	}
	return encrypted_text;
}
std::wstring GammaCipher::decrypt(const std::wstring& encrypted_text)
{
	std::wstring new_encrypted_text = getValidCipherText(encrypted_text);
	int rows;
	if (key < 1){throw cipher_error(std::string("Неправильный ключ: "));}
	if(new_encrypted_text.length() % key != 0) {
		rows = new_encrypted_text.length() / key + 1;
	} else {
		rows = new_encrypted_text.length() / key;
	}
	wchar_t Gamma[rows][key];
	int index = 0;
	for(int i = key - 1; i >= 0; i--) {
		for(int j = 0; j < rows; ++j) {
			if(index < new_encrypted_text.length()) {
				Gamma[j][i] = new_encrypted_text[index];
				index++;
			} else {
				Gamma[i][j] = L' ';
			}
		}
	}
	wstring decrypted_text;
	index = 0;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < key; j++) {
			decrypted_text += Gamma[i][j];
		}
	}
	return decrypted_text;
}

inline std::wstring GammaCipher::getValidKey(const std::wstring& s)
{
    if(s.empty())
        throw cipher_error("Empty key");
    std::wstring tmp(s);
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; 
	std::string m = converter.to_bytes(tmp);
    for(auto& c : tmp) {
        if(!iswalpha(c))
            throw cipher_error(std::string("Неправильный ключ: ") + m);
        if(iswlower(c))
            c = towupper(c);
    }
    return tmp;
}

inline std::wstring GammaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; 
    std::string m = converter.to_bytes(tmp);
    for(auto c : s) {
        if(iswalpha(c)) {
            if(iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if(tmp.empty())
        throw cipher_error("Пустой открытый текст");
    return tmp;
}

inline std::wstring GammaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");

    std::wstring tmp(s);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; 
    std::string m = converter.to_bytes(tmp);
    for (auto& c : tmp) {
        if (!iswupper(c)) {
            std::string error_msg = "Invalid cipher text: ";
            error_msg += m;
            throw cipher_error(error_msg);
        }
    }

    return tmp;
}