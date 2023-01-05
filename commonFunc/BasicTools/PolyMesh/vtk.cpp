#include "VTK/vtk.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace acamcad {
	void VTK::clear_lines() {
		lines.clear();
	}

	void VTK::add_line(MPoint3& a, MPoint3& b) {
		lines.push_back(a);
		lines.push_back(b);
	}

	void VTK::show_lines() {
		printf("show_lines\n");
		if (lines.empty())return;
		for (auto p : lines) {
			std::cout << p << "\n";
		}
	}

	void VTK::write_lines(std::string _filename) {
		if (lines.empty())return;
		std::fstream ifile(_filename.c_str(), std::ios_base::out);
		for (auto p : lines) {
			ifile << p <<"\n";
		}
		ifile.close();
	}
	void VTK::read_lines(std::string _filename) {
		std::fstream ifile(_filename.c_str(), std::ios_base::in);
		clear_lines();
		while (ifile && !ifile.eof()) {
			MPoint3 a;
			for (int i = 0; i < 3; ++i) {
				ifile >> a[i];
			}
			lines.push_back(a);
		}
		// std::cout << lines.size() << std::endl;
		if (lines.size() & 1) {
			lines.pop_back();
		}
		// std::cout << lines.size() << std::endl;
		ifile.close();
	}
}//namespaec acamcad