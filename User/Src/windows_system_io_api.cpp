
#include <iostream>
#include "flint_system_api.h"

FileResult FlintAPI::IO::finfo(const char *fileName, uint32_t *size, int64_t *time) {
    throw "FlintAPI::IO::finfo is not implemented in VM";
}

FileHandle FlintAPI::IO::fopen(const char *fileName, FileMode mode) {
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

    return (FileHandle)::fopen(fileName, buff);
}

FileResult FlintAPI::IO::fread(FileHandle handle, void *buff, uint32_t btr, uint32_t *br) {
    uint32_t temp = ::fread(buff, 1, btr, (FILE *)handle);
    *br = temp;
    if(temp != btr)
        return FILE_RESULT_ERR;
    return FILE_RESULT_OK;
}

FileResult FlintAPI::IO::fwrite(FileHandle handle, void *buff, uint32_t btw, uint32_t *bw) {
    uint32_t temp = ::fwrite(buff , 1, btw, (FILE *)handle);
    *bw = temp;
    if(temp != btw)
        return FILE_RESULT_ERR;
    return FILE_RESULT_OK;
}

uint32_t FlintAPI::IO::ftell(FileHandle handle) {
    return ::ftell((FILE *)handle);
}

FileResult FlintAPI::IO::fseek(FileHandle handle, uint32_t offset) {
    return ::fseek((FILE *)handle, offset, SEEK_SET) != 0 ? FILE_RESULT_ERR : FILE_RESULT_OK;
}

FileResult FlintAPI::IO::fclose(FileHandle handle) {
    if(handle != 0)
        if(::fclose((FILE *)handle) != 0)
            return FILE_RESULT_ERR;
    return FILE_RESULT_OK;
}

FileResult FlintAPI::IO::fremove(const char *fileName) {
    throw "FlintAPI::IO::fremove is not implemented in VM";
}

DirHandle FlintAPI::IO::opendir(const char *dirName) {
    throw "FlintAPI::Directory::open is not implemented in VM";
}

FileResult FlintAPI::IO::readdir(DirHandle handle, uint8_t *attribute, char *nameBuff, uint32_t buffSize, uint32_t *size, int64_t *time) {
    throw "FlintAPI::Directory::read is not implemented in VM";
}

FileResult FlintAPI::IO::closedir(DirHandle handle) {
    throw "FlintAPI::Directory::close is not implemented in VM";
}

FileResult FlintAPI::IO::mkdir(const char *path) {
    throw "FlintAPI::Directory::create is not implemented in VM";
}
