#pragma once

#include <random>
#include <vector>
#include <algorithm>

namespace clib {

	struct flag {
		int obj;
		double num;
		bool operator<(const flag& other) {
			return num < other.num;
		}
	};

	std::vector<int> makeRandom(std::vector<int> data) {
		std::vector<flag> offset;
		std::random_device rd;
		std::mt19937 gen(rd());
		for (int i = 0; i < data.size(); i++) {
			flag f;
			f.obj = data[i];
			f.num = std::generate_canonical<double, 10>(gen);
			offset.push_back(f);
		}
		std::sort(offset.begin(), offset.end());

		std::vector<int> ans;
		for (int i = 0; i < data.size(); i++) {
			ans.push_back(offset[i].obj);
		}
		return ans;
	}

}