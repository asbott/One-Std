

bool sys_read_entire_file(Allocator a, string path, string *result);
bool sys_write_entire_file(string path, string data);

#ifdef OSTD_IMPL

bool sys_read_entire_file(Allocator a, string path, string *result) {
    File_Handle f = sys_open_file(path, FILE_OPEN_READ);
    if (!f) return false;
    
    u64 size = sys_get_file_size(f);
    assert(size > 0);
    
    *result = string_allocate(a, size);
    s64 readeded =  sys_read(f, result->data, result->count);
    
    if (readeded != (s64)size) {
        deallocate(a, result->data);
        return false;
    }
    
    return true;
}
bool sys_write_entire_file(string path, string data) {
    File_Handle f = sys_open_file(path, FILE_OPEN_WRITE | FILE_OPEN_CREATE | FILE_OPEN_RESET);
    if (!f) return false;
    
    s64 written = sys_write_string(f, data);
    
    return written == (s64)data.count;
}

#endif // OSTD_IMPL

