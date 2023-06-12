#include "pch.h"

template <typename T>
void JTEEngine::JTEUtilities::print(T value) {
	std::cout << value;
}

template <typename T>
void JTEEngine::JTEUtilities::println(T value) {
	std::cout << value << '\n';
}

template <typename T>
std::string JTEEngine::JTEUtilities::string(T value) {
	return std::to_string(value);
}
