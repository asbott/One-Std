


string path_get_filename(string path);
string path_strip_one_extension(string path);
string path_strip_all_extensions(string path);

#ifdef OSTD_IMPL

string path_get_filename(string path) {
	for (s64 i = (s64)(path.count-1); i >= 0; i -= 1) {
		if (path.data[i] == '\\' || path.data[i] == '/') {
			return string_slice(path, (u64)i+1, path.count-(u64)i-1);
		}
    }
    return path;
}

string path_strip_one_extension(string path) {
	for (s64 i = (s64)(path.count-1); i >= 0; i -= 1) {
		if (path.data[i] == '\\' || path.data[i] == '/') {
			return path;
		}
		if (path.data[i] == '.') {
			return string_slice(path, 0, (u64)i);
		}
    }
    return path;
}

string path_strip_all_extensions(string path) {
	s64 lowest_index = -1;
	for (s64 i = (s64)(path.count-1); i >= 0; i -= 1) {
		if (path.data[i] == '\\' || path.data[i] == '/') {
			break;
		}
		if (path.data[i] == '.') {
			if (lowest_index == -1 || i < lowest_index) {
				lowest_index = i;
			}
		}
    }
    if (lowest_index == -1) return path;
    
	return string_slice(path, 0, (u64)lowest_index);
}

#endif // OSTD_IMPL
