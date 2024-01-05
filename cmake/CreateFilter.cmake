# 在MSVC中，根据目录结构filter

macro(create_filter_by_dir src_dir)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	foreach(file ${ARGN})
		# get dir of file
		get_filename_component(PARENT_DIR "${file}" DIRECTORY)
		# remove dir
		string(REPLACE ${src_dir} "" GROUP "${PARENT_DIR}")
		# USE WINDOWS SLASHES
		string(REPLACE "/" "\\" GROUP "${GROUP}")

		source_group("${GROUP}" FILES "${file}")

	endforeach()

endmacro()