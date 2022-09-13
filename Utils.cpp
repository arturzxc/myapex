#pragma once
#include <iostream>
#include <sstream>
#include <sys/uio.h>

namespace utils
{
    void PrintTypeSizes()
    {
        std::cout << "char size: " << sizeof(char) << "\n";     // 1
        std::cout << "int size: " << sizeof(int) << "\n";       // 4
        std::cout << "float size: " << sizeof(float) << "\n";   // 4
        std::cout << "long size: " << sizeof(long) << "\n";     // 4
        std::cout << "double size: " << sizeof(double) << "\n"; // 8
    }

    pid_t GetPID()
    {
        char buf[512];
        FILE *cmd_pipe = popen("pidof -s R5Apex.exe", "r");
        fgets(buf, 512, cmd_pipe);
        pid_t pid = strtoul(buf, NULL, 10);
        pclose(cmd_pipe);
        if (pid == 0)
            throw std::invalid_argument("game not found");
        return pid;
    }

    bool Read(long address, void *pBuff, size_t size)
    {
        if (size == 0)
            return false;
        void *pAddress = (void *)address;
        pid_t pid = GetPID();
        struct iovec iovLocalAddressSpace[1]{0};
        struct iovec iovRemoteAddressSpace[1]{0};
        iovLocalAddressSpace[0].iov_base = pBuff;     // Store data in this buffer
        iovLocalAddressSpace[0].iov_len = size;       // which has this size.
        iovRemoteAddressSpace[0].iov_base = pAddress; // The data comes from here
        iovRemoteAddressSpace[0].iov_len = size;      // and has this size.
        ssize_t sSize = process_vm_readv(
            pid,                   // Remote process id
            iovLocalAddressSpace,  // Local iovec array
            1,                     // Size of the local iovec array
            iovRemoteAddressSpace, // Remote iovec array
            1,                     // Size of the remote iovec array
            0);                    // Flags, unused
        if (sSize == (ssize_t)size)
            return true;
        else if (sSize == 0)
            return false;
        return false; // Partial read, data might be corrupted
    }

    std::string ReadString(long address)
    {
        int size = sizeof(std::string);
        char buffer[size] = {0};
        bool memReadSuccess = utils::Read(address, &buffer, size);
        if (!memReadSuccess)
            throw new std::invalid_argument("Failed to read String at address: " + address);
        return std::string(buffer);
    }

    short ReadShort(long address)
    {
        int size = sizeof(short);
        short buffer;
        bool memReadSuccess = utils::Read(address, &buffer, size);
        if (!memReadSuccess)
            throw new std::invalid_argument("Failed to read short at address: " + address);
        return buffer;
    }

    int ReadInt(long address)
    {
        int size = sizeof(int);
        int buffer;
        bool memReadSuccess = utils::Read(address, &buffer, size);
        if (!memReadSuccess)
            throw new std::invalid_argument("Failed to read int at address: " + address);
        return buffer;
    }

    long ReadFloat(long address)
    {
        int size = sizeof(float);
        float buffer;
        bool memReadSuccess = utils::Read(address, &buffer, size);
        if (!memReadSuccess)
            throw new std::invalid_argument("Failed to read float at address: " + address);
        return buffer;
    }

    long ReadLong(long address)
    {
        int size = sizeof(long);
        long buffer;
        bool memReadSuccess = utils::Read(address, &buffer, size);
        if (!memReadSuccess)
            throw new std::invalid_argument("Failed to read long at address: " + address);
        return buffer;
    }

    void PrintPointer(std::string name, long pointerLong)
    {
        std::string str;
        std::cout << name << ": 0x" << std::hex << pointerLong << "\n";
    }

    std::string convertPointerToHexString(long pointer)
    {
        std::stringstream stream;
        stream << "0x" << std::hex << pointer;
        std::string result(stream.str());
        return result;
    }

    template <typename T>
    std::string convertNumberToString(const T a_value)
    {
        std::ostringstream out;
        out.precision(6);
        out << std::fixed << a_value;
        return out.str();
    }
}
