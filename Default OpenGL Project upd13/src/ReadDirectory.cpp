#include "ReadDirectory.h"

std::string s_path_leaf_string::operator()(const std::filesystem::directory_entry& entry) const
{
	return entry.path().string();
}

void read_directory(const std::string& name, v_stringvec& v)
{
	std::filesystem::path p(name);
	std::filesystem::directory_iterator start(p);
	std::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(v), s_path_leaf_string());
}