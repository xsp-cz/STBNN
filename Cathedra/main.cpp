#include <cmath>
#include <random>
#include <vector>
#include <iostream>

#include "clib.h"

std::vector<int> frontMale =
{ 7, 19,23,16,
  1, 18,17,4,
  13,10,22,8,
  24,21 };
std::vector<int> backMale =
{ 6, 11,
  25,26,14,12,
  9, 5, 2, 3,
  20,15 };
std::vector<int> frontFemale =
{ 46,39,52,36,
  57,49,37,28,
  33,34,54,30,
  45,41,40,43,48,42 };
std::vector<int> backFemale =
{ 58,27,51,50,32,60,
  53,29,44,31,
  38,55,59,47,
  56,35 };

void pre() { // change four "fm"-s into virtual "m"-s
	std::random_device rd; std::mt19937 gen(rd());
	for (int i = 1; i <= 2; i++) {
		std::uniform_int_distribution<> disFront(0, frontFemale.size() - 1);
		std::uniform_int_distribution<> disBack(0, backFemale.size() - 1);
		int pos1 = disFront(gen);
		frontMale.push_back(frontFemale[pos1]);
		frontFemale.erase(frontFemale.begin() + pos1);
		int pos2 = disBack(gen);
		backMale.push_back(backFemale[pos2]);
		backFemale.erase(backFemale.begin() + pos2);
	}
}

void make() {
	frontMale = clib::makeRandom(frontMale);
	backMale = clib::makeRandom(backMale);
	frontFemale = clib::makeRandom(frontFemale);
	backFemale = clib::makeRandom(backFemale);
}

void print() {
	for (int i = 1; i <= 4; i++) {
		for (int k = 1; k <= 28; k++)
			std::cout << '-';
		std::cout << std::endl;
		for (int j = 1; j <= 4; j++) {
			std::cout << "|";
			std::cout << frontMale[(i - 1) * 4 + j - 1] << " ";
			if ((int)std::log10(frontMale[(i - 1) * 4 + j - 1]) + 1 == 1)
				std::cout << " ";

			if ((int)std::log10(frontFemale[(i - 1) * 4 + j - 1]) + 1 == 1)
				std::cout << " ";
			std::cout << frontFemale[(i - 1) * 4 + j - 1];
			std::cout << "|";
		}
		std::cout << std::endl;
	}
	for (int i = 1; i <= 3; i++) {
		for (int k = 1; k <= 28; k++)
			std::cout << '-';
		std::cout << std::endl;
		for (int j = 1; j <= 4; j++) {
			std::cout << "|";
			std::cout << backMale[(i - 1) * 4 + j - 1] << " ";
			if ((int)std::log10(backMale[(i - 1) * 4 + j - 1]) + 1 == 1)
				std::cout << " ";

			if ((int)std::log10(backFemale[(i - 1) * 4 + j - 1]) + 1 == 1)
				std::cout << " ";
			std::cout << backFemale[(i - 1) * 4 + j - 1];
			std::cout << "|";
		}
		std::cout << std::endl;
	}
	for (int k = 1; k <= 28; k++)
		std::cout << '-';
	std::cout << std::endl;

	std::cout << "|";
	std::cout << backMale[12] << " ";
	if ((int)std::log10(backMale[12]) + 1 == 1)
		std::cout << " ";
	if ((int)std::log10(backFemale[12]) + 1 == 1)
		std::cout << " ";
	std::cout << backFemale[12];
	std::cout << "|";

	std::cout << "|";
	std::cout << backMale[13] << " ";
	if ((int)std::log10(backMale[13]) + 1 == 1)
		std::cout << " ";
	if ((int)std::log10(backFemale[13]) + 1 == 1)
		std::cout << " ";
	std::cout << backFemale[13];
	std::cout << "|";
	std::cout << std::endl;
}

int main() {
	pre();
	make();
	print();
	std::system("pause");
}