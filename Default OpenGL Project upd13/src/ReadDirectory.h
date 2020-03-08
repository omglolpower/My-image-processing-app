#pragma once
#include <filesystem>
typedef std::vector<std::string> v_stringvec;

struct s_path_leaf_string
{

	std::string operator()(const std::filesystem::directory_entry& entry) const;
};
void read_directory(const std::string& name, v_stringvec& v);