#pragma once
#include <iostream>
#include <sstream>
#include <sys/uio.h>
#include <math.h>

namespace mem
{
    pid_t m_pid = 0;

    pid_t GetPID()
    {
        if (m_pid > 0)
            return m_pid;
        char buf[512];
        FILE *cmd_pipe = popen("pidof -s R5Apex.exe", "r");
        fgets(buf, 512, cmd_pipe);
        pid_t pid = strtoul(buf, NULL, 10);
        pclose(cmd_pipe);
        m_pid = pid;
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
        return false;
    }
    bool Write(long address, void *pBuff, size_t size)
    {
        if (size == 0)
            return false;
        void *pAddress = (void *)address;
        pid_t pid = GetPID();
        struct iovec iovLocalAddressSpace[1]{0};
        struct iovec iovRemoteAddressSpace[1]{0};
        iovLocalAddressSpace[0].iov_base = pBuff;     // Store data in this buffer
        iovLocalAddressSpace[0].iov_len = size;       // which has this size.
        iovRemoteAddressSpace[0].iov_base = pAddress; // The data will be writted here
        iovRemoteAddressSpace[0].iov_len = size;      // and has this size.
        ssize_t sSize = process_vm_writev(
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
        return false;
    }
    std::string ReadString(long address)
    {
        int size = sizeof(std::string);
        char buffer[size] = {0};
        bool success = Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read String at address: " + address);
        return std::string(buffer);
    }
    short ReadShort(long address)
    {
        int size = sizeof(short);
        short buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read short at address: " + address);
        return buffer;
    }
    void WriteShort(long address, short num)
    {
        int size = sizeof(short);
        short buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write short at address: " + address);
    }
    int ReadInt(long address)
    {
        int size = sizeof(int);
        int buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read int at address: " + address);
        return buffer;
    }
    void WriteInt(long address, int num)
    {
        int size = sizeof(int);
        int buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write int at address: " + address);
    }
    float ReadFloat(long address)
    {
        int size = sizeof(float);
        float buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read float at address: " + address);
        return buffer;
    }
    void WriteFloat(long address, float num)
    {
        int size = sizeof(float);
        float buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write float at address: " + address);
    }
    long ReadLong(long address)
    {
        int size = sizeof(long);
        long buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read long at address: " + address);
        return buffer;
    }
    void WriteLong(long address, long num)
    {
        int size = sizeof(long);
        long buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write long at address: " + address);
    }
    std::string convertPointerToHexString(long pointer)
    {
        std::stringstream stream;
        stream << "0x" << std::hex << pointer;
        std::string result(stream.str());
        return result;
    }
}