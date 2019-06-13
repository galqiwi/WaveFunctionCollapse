#include "headers.h"

class Pattern {
public:
	Pattern(int n = 3) {
		n_ = n;
		data = vector<vector<int>>(n, vector<int>(n, 0));
	}
	int n_;
	vector<vector<int> > data;
};

bool overlay(Pattern& p0, Pattern& p1, int x_shift = 0, int y_shift = 0) {
	int n = p0.n_;
	int x_min = max(0, x_shift);
	int x_max = n - 1 + min(0, x_shift);
	int y_min = max(0, y_shift);
	int y_max = n - 1 + min(0, y_shift);
	for (int x = x_min; x <= x_max; x++)
	for (int y = y_min; y <= y_max; y++) {
		if (p0.data[x][y] != p1.data[x - x_shift][y - y_shift])
			return false;
	}
	return true;
}

int main() {
	int image_w = 40;
	int image_h = 40;
	vector<vector<int> >image(image_w, vector<int>(image_h, 0));
	vector<Pattern> patterns;

	int n = 3;
	for (int x = 0; x <= image_w - n; x++)
	for (int y = 0; y <= image_h - n; y++) {
		patterns.push_back(Pattern(n));
		
		vector<vector<int> >& current_pattern_data = patterns.back().data;
		for (int x_ = 0; x_ < n; x_++)
		for (int y_ = 0; y_ < n; y_++)
			current_pattern_data[x_][y_] = image[x + x_][y + y_];

		for (int i = 0; i < patterns.size() - 1; i++) {
			if (overlay(patterns.back(), patterns[i]))
				patterns.erase(patterns.end());
		}
	}
}