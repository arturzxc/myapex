#pragma once
#include <iostream>
#include <sstream>
#include <sys/uio.h>
#include <math.h>

namespace utils
{
    const float WORLD_RATIO = 0.0254;
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
        return false; // Partial read, data might be corrupted
    }
    std::string ReadString(long address)
    {
        int size = sizeof(std::string);
        char buffer[size] = {0};
        bool success = utils::Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read String at address: " + address);
        return std::string(buffer);
    }
    short ReadShort(long address)
    {
        int size = sizeof(short);
        short buffer;
        bool success = utils::Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read short at address: " + address);
        return buffer;
    }
    void WriteShort(long address, short num)
    {
        int size = sizeof(short);
        short buffer = num;
        bool success = utils::Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write short at address: " + address);
    }
    int ReadInt(long address)
    {
        int size = sizeof(int);
        int buffer;
        bool success = utils::Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read int at address: " + address);
        return buffer;
    }
    void WriteInt(long address, int num)
    {
        int size = sizeof(int);
        int buffer = num;
        bool success = utils::Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write int at address: " + address);
    }
    float ReadFloat(long address)
    {
        int size = 4;
        float buffer;
        bool success = utils::Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read float at address: " + address);
        return buffer;
    }
    void WriteFloat(long address, float num)
    {
        int size = 4;
        float buffer = num;
        bool success = utils::Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write float at address: " + address);
    }
    long ReadLong(long address)
    {
        int size = sizeof(long);
        long buffer;
        bool success = utils::Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read long at address: " + address);
        return buffer;
    }
    void WriteLong(long address, long num)
    {
        int size = sizeof(long);
        long buffer = num;
        bool success = utils::Write(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to write long at address: " + address);
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
    long calcDistance(int x1, int y1, int z1, int x2, int y2, int z2)
    {
        long dx = (x1 - x2) * WORLD_RATIO;
        long dy = (y1 - y2) * WORLD_RATIO;
        long dz = (z1 - z2) * WORLD_RATIO;
        long distance = sqrt(pow(dx, 2) + pow(dy, 2));
        return distance;
    }
    long calcDistanceSquared(int x1, int y1, int z1, int x2, int y2, int z2)
    {
        long dx = (x1 - x2) * WORLD_RATIO;
        long dy = (y1 - y2) * WORLD_RATIO;
        long dz = (z1 - z2) * WORLD_RATIO;
        long distance = pow(dx, 2) + pow(dy, 2);
        return distance;
    }
}
