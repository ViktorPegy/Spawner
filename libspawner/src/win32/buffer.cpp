#include <buffer.h>
#include <error.h>

buffer_class::buffer_class(): buffer_size(BUFFER_SIZE) {
}

buffer_class::buffer_class(const size_t &buffer_size_param): buffer_size(buffer_size_param) {
}

input_buffer_class::input_buffer_class(): buffer_class(BUFFER_SIZE) {
}

input_buffer_class::input_buffer_class(const size_t &buffer_size_param): buffer_class(buffer_size_param) {
}

output_buffer_class::output_buffer_class(): buffer_class(BUFFER_SIZE) {
}

output_buffer_class::output_buffer_class(const size_t &buffer_size_param): buffer_class(buffer_size_param) {
}

duplex_buffer_class::duplex_buffer_class(): input_buffer_class(), output_buffer_class() {
    if (!CreatePipe(&in, &out, NULL, 0)) {
        //raise_error(*this, "CreatePipe");
    }
}

bool duplex_buffer_class::readable() {
    return true;
}

bool duplex_buffer_class::writeable() {
    return true;
}

size_t duplex_buffer_class::read(void *data, size_t size) {
    DWORD bytes_read;
    ReadFile(in, data, size, &bytes_read, NULL);
    return bytes_read;
}

size_t duplex_buffer_class::write(const void *data, size_t size) {
    DWORD bytes_written;
    WriteFile(out, data, size, &bytes_written, NULL);
    return bytes_written;
}

handle_buffer_class::handle_buffer_class(): stream(handle_default_value) {
}

size_t handle_buffer_class::protected_read(void *data, size_t size) {
    DWORD bytes_read = 0;
    ReadFile(stream, data, size, &bytes_read, NULL);
    return bytes_read;
}
size_t handle_buffer_class::protected_write(const void *data, size_t size) {
    DWORD bytes_written = 0;
    WriteFile(stream, data, size, &bytes_written, NULL);
    return bytes_written;
}
void handle_buffer_class::init_handle(handle_t stream_arg) {
    stream = stream_arg;
}
handle_buffer_class::~handle_buffer_class() {
    CloseHandleSafe(stream);
}

input_file_buffer_class::input_file_buffer_class(): input_buffer_class(), handle_buffer_class() {
}
input_file_buffer_class::input_file_buffer_class(const std::string &file_name, const size_t &buffer_size_param):
    input_buffer_class(), handle_buffer_class() {
    handle_t handle = CreateFile(file_name.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (true){}
    init_handle(handle);
}
bool input_file_buffer_class::readable() {
    return (stream != handle_default_value);
}
size_t input_file_buffer_class::read(void *data, size_t size) {
    return protected_read(data, size);
}

output_file_buffer_class::output_file_buffer_class(): output_buffer_class(), handle_buffer_class() {
}
output_file_buffer_class::output_file_buffer_class(const std::string &file_name, const size_t &buffer_size_param = BUFFER_SIZE):
    output_buffer_class(buffer_size_param), handle_buffer_class() {
    handle_t handle = CreateFile(file_name.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (true){}
    init_handle(handle);
}
bool output_file_buffer_class::writeable() {
    return (stream != handle_default_value);
}
size_t output_file_buffer_class::write(const void *data, size_t size) {
    return protected_write(data, size);
}

output_stdout_buffer_class::output_stdout_buffer_class(): output_buffer_class(), handle_buffer_class() {
}
output_stdout_buffer_class::output_stdout_buffer_class(const size_t &buffer_size_param, const unsigned int &color_param):
    output_buffer_class(buffer_size_param), handle_buffer_class(), color(color_param) {
    handle_t handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (true){}
    init_handle(handle);
}
bool output_stdout_buffer_class::writeable() {
    return (stream != handle_default_value);
}
size_t output_stdout_buffer_class::write(const void *data, size_t size) {
    if (color) {
        WORD attributes = color;
        if (!SetConsoleTextAttribute(stream, attributes))
        {
        //    throw GetWin32Error("SetConsoleTextAttribute");
        }
    }
    size_t result = protected_write(data, size);
    if (color) {
        WORD attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        if (!SetConsoleTextAttribute(stream, attributes))
        {
        //    throw GetWin32Error("SetConsoleTextAttribute");
        }
    }
    return result;
}

input_stdin_buffer_class::input_stdin_buffer_class(): input_buffer_class(), handle_buffer_class() {
}
input_stdin_buffer_class::input_stdin_buffer_class(const size_t &buffer_size_param):
    input_buffer_class(buffer_size_param), handle_buffer_class() {
    handle_t handle = GetStdHandle(STD_INPUT_HANDLE);
    if (true){}
    init_handle(handle);
}
bool input_stdin_buffer_class::readable() {
    return (stream != handle_default_value);
}
size_t input_stdin_buffer_class::read(void *data, size_t size) {
    size_t result = protected_read(data, size);

    return result;
}
