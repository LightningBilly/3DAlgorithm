# 在MSVC中，添加数据文件

macro(add_source_files ret ext)

	foreach(_dir ${ARGN})
		# get files of dir
		file (GLOB _files "${_dir}/${ext}")
		# remove file
		foreach(_file ${_files}) 
			get_filename_component(_filename ${_file} NAME)
			if(_filename MATCHES "^[.]")
				list(REMOVE_ITEM _files ${_file})
			endif()
		endforeach()
		message("files : ${_files}")
		list (APPEND ${ret} ${_files})

	endforeach()

endmacro()