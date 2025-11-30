
#include <iostream>
#include <sys/stat.h>
#include "flint_system_api.h"

using namespace FlintAPI::IO;

FileResult FlintAPI::IO::finfo(const char *fileName, FileInfo *fileInfo) {
    struct stat st;
    if(stat(fileName, &st) == 0) {
        if(fileInfo != NULL) {
            fileInfo->readOnly = !(st.st_mode & S_IWUSR);
            fileInfo->hidden = 0;
            fileInfo->system = 0;
            fileInfo->archive = 0;
            fileInfo->directory = S_ISDIR(st.st_mode);
            fileInfo->size = (fileInfo->directory) ? 0 : st.st_size;
            fileInfo->time = st.st_mtime;

            uint16_t index = 0;
            const char *name = fileName;
            while(*fileName) {
                if(*fileName == '/' || *fileName == '\\') name = fileName + 1;
                fileName++;
            }
            while(name[index] != 0) {
                if(index < (sizeof(fileInfo->name) - 1)) {
                    fileInfo->name[index] = name[index];
                    index++;
                }
                else
                    return FILE_RESULT_ERR;
            }
            fileInfo->name[index] = 0;
        }
        return FILE_RESULT_OK;
    }
    else
        return FILE_RESULT_NO_PATH;
}

FileHandle FlintAPI::IO::fopen(const char *fileName, FileMode mode) {
    char buff[5];
    uint32_t index = 0;
    if((mode & FILE_MODE_APPEND) == FILE_MODE_APPEND)
        buff[index++] = 'a';
    else if(mode & (FILE_MODE_CREATE_ALWAYS | FILE_MODE_CREATE_NEW))
        buff[index++] = 'w';
    else
        buff[index++] = 'r';
    if(mode & FILE_MODE_CREATE_NEW)
        buff[index++] = 'x';
    if((mode & (FILE_MODE_READ | FILE_MODE_WRITE)) == (FILE_MODE_READ | FILE_MODE_WRITE))
        buff[index++] = '+';
    buff[index++] = 'b';
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

uint32_t FlintAPI::IO::fsize(FileHandle handle) {
    throw "FlintAPI::IO::fsize is not implemented in VM";
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

FileResult FlintAPI::IO::frename(const char *oldName, const char *newName) {
    throw "FlintAPI::IO::frename is not implemented in VM";
}

DirHandle FlintAPI::IO::opendir(const char *dirName) {
    throw "FlintAPI::IO::opendir is not implemented in VM";
}

FileResult FlintAPI::IO::readdir(DirHandle handle, FileInfo *fileInfo) {
    throw "FlintAPI::IO::readdir is not implemented in VM";
}

FileResult FlintAPI::IO::closedir(DirHandle handle) {
    throw "FlintAPI::IO::closedir is not implemented in VM";
}

FileResult FlintAPI::IO::mkdir(const char *path) {
    throw "FlintAPI::IO::mkdir is not implemented in VM";
}
