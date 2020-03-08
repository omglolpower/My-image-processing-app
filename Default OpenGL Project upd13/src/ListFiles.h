#pragma once
#include <filesystem>
#include <iostream>
struct path_leaf_string
{
	std::string operator()(const std::filesystem::directory_entry& entry) const;
};

void read_directory(const std::string& name, stringvec& v);