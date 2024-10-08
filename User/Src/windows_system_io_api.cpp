
#include <iostream>
#include "flint_system_api.h"

FlintFileResult FlintAPI::IO::finfo(const char *fileName, uint32_t *size, int64_t *time) {
    throw "FlintAPI::IO::finfo is not implemented in VM";
}

void *FlintAPI::IO::fopen(const char *fileName, FlintFileMode mode) {
    char buff[6];
    uint32_t index = 0;
    if(mode & (FLINT_FILE_CREATE_ALWAYS | FLINT_FILE_CREATE_NEW)) {
        buff[index++] = 'w';
        if(mode & FLINT_FILE_CREATE_NEW)
            buff[index++] = 'x';
    }
    else
        buff[index++] = 'r';
    buff[index++] = 'b';
    if((mode & (FLINT_FILE_READ | FLINT_FILE_WRITE)) == (FLINT_FILE_READ | FLINT_FILE_WRITE))
        buff[index++] = '+';
    buff[index] = 0;

    return ::fopen(fileName, buff);
}

FlintFileResult FlintAPI::IO::fread(void *handle, void *buff, uint32_t btr, uint32_t *br) {
    uint32_t temp = ::fread(buff, 1, btr, (FILE *)handle);
    *br = temp;
    if(temp != btr)
        return FILE_RESULT_ERR;
    return FILE_RESULT_OK;
}

FlintFileResult FlintAPI::IO::fwrite(void *handle, void *buff, uint32_t btw, uint32_t *bw) {
    uint32_t temp = ::fwrite(buff , 1, btw, (FILE *)handle);
    *bw = temp;
    if(temp != btw)
        return FILE_RESULT_ERR;
    return FILE_RESULT_OK;
}

uint32_t FlintAPI::IO::fsize(void *handle) {
    uint32_t temp = ::ftell((FILE *)handle);
    if(::fseek((FILE *)handle, 0, SEEK_END) != 0)
        throw "error while getting file size";
    uint32_t length = ::ftell((FILE *)handle);
    if(::fseek((FILE *)handle, temp, SEEK_SET) != 0)
        throw "error while getting file size";
    return length;
}

uint32_t FlintAPI::IO::ftell(void *handle) {
    return ::ftell((FILE *)handle);
}

FlintFileResult FlintAPI::IO::fseek(void *handle, uint32_t offset) {
    return ::fseek((FILE *)handle, offset, SEEK_SET) != 0 ? FILE_RESULT_ERR : FILE_RESULT_OK;
}

FlintFileResult FlintAPI::IO::fclose(void *handle) {
    if(handle != 0)
        if(::fclose((FILE *)handle) != 0)
            return FILE_RESULT_ERR;
    return FILE_RESULT_OK;
}

FlintFileResult FlintAPI::IO::fremove(const char *fileName) {
    throw "FlintAPI::IO::fremove is not implemented in VM";
}

void *FlintAPI::IO::opendir(const char *dirName) {
    throw "FlintAPI::Directory::open is not implemented in VM";
}

FlintFileResult FlintAPI::IO::readdir(void *handle, uint8_t *attribute, char *nameBuff, uint32_t buffSize, uint32_t *size, int64_t *time) {
    throw "FlintAPI::Directory::read is not implemented in VM";
}

FlintFileResult FlintAPI::IO::closedir(void *handle) {
    throw "FlintAPI::Directory::close is not implemented in VM";
}

FlintFileResult FlintAPI::IO::mkdir(const char *path) {
    throw "FlintAPI::Directory::create is not implemented in VM";
}
