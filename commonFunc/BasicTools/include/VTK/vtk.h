#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <assert.h>
#include "../Math/MPoint3.h"

namespace acamcad
{
	class VTK
	{
	public:
		std::vector<MPoint3> lines;
		void clear_lines();
		void add_line(MPoint3 &a, MPoint3 &b);
		void write_lines(std::string file);
		void show_lines();
		void read_lines(std::string file);
	};

	inline std::ostream& operator<<(std::ostream& os, VTK& vtk)
	{
		for (int i = 0; i < vtk.lines.size(); ++i) {
			os << vtk.lines[i] << "-->" << vtk.lines[i+1] <<std::endl;
		}
		return os;
	}

}

