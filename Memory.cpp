#pragma once
#include <iostream>
#include <sstream>
#include <sys/uio.h>
#include <math.h>
#include <errno.h>

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

    std::string ReadString(long address)
    {
        int size = sizeof(std::string);
        char buffer[size] = {0};
        bool success = Read(address, &buffer, size);
        if (!success)
            throw new std::invalid_argument("Failed to read String at address: " + address);
        return std::string(buffer);
    }

    template <typename T>
    T ReadMemory(long address)
    {
        T buffer = T();
        
        // Prepare the iovec structures
        struct iovec local_iov = {&buffer, sizeof(T)};
        struct iovec remote_iov = {reinterpret_cast<void *>(address), sizeof(T)};

        // Get the process ID of the current process
        pid_t pid = GetPID();

        // Read the memory using process_vm_readv
        ssize_t bytes_read = process_vm_readv(pid, &local_iov, 1, &remote_iov, 1, 0);
        if (bytes_read != sizeof(T))
        {
            // Error occurred while reading the memory
            if (bytes_read == -1)
            {
                // Get the error code from errno and log it
                int error_code = errno;
                printf("ERROR: ReadMemory failed. MemoryAddress: %ld ErrorCode:%d", address, error_code);
            }
        }
        return buffer;
    }

    template <typename T>
    bool WriteMemory(long address, const T &value)
    {
        // Prepare the iovec structures
        struct iovec local_iov = {const_cast<T *>(&value), sizeof(T)};
        struct iovec remote_iov = {reinterpret_cast<void *>(address), sizeof(T)};

        // Get the process ID of the current process
        pid_t pid = GetPID();

        // Write the memory using process_vm_writev
        ssize_t bytes_written = process_vm_writev(pid, &local_iov, 1, &remote_iov, 1, 0);
        if (bytes_written != sizeof(T))
        {
            // Error occurred while writing the memory
            if (bytes_written == -1)
            {
                // Get the error code from errno and log it
                int error_code = errno;
                printf("ERROR: WriteMemory failed. MemoryAddress: %ld ErrorCode:%d", address, error_code);
            }
            return false;
        }
        return true;
    }

}