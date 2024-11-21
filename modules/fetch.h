#ifndef FETCH_H
#define FETCH_H

#include <string>
#include <fstream>
#include <sstream>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include <filesystem>
#include <cstdlib>

class SystemInfo {
public:
    static std::string getUsername() {
        struct passwd* pw = getpwuid(getuid());
        return pw ? pw->pw_name : "unknown";
    }

    static std::string getHostname() {
        char hostname[256];
        gethostname(hostname, sizeof(hostname));
        return std::string(hostname);
    }

    static std::string getDistro() {
        std::ifstream file("/etc/os-release");
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("PRETTY_NAME=") == 0) {
                return line.substr(13, line.size() - 14); // Remove quotes
            }
        }
        return "unknown";
    }

    static std::string getKernelVersion() {
        struct utsname buffer;
        if (uname(&buffer) == 0) {
            return buffer.release;
        }
        return "unknown";
    }

    static std::string getUptime() {
        std::ifstream file("/proc/uptime");
        double uptime;
        if (file >> uptime) {
            int hours = static_cast<int>(uptime) / 3600;
            int minutes = (static_cast<int>(uptime) % 3600) / 60;
            std::ostringstream oss;
            oss << hours << "h " << minutes << "m";
            return oss.str();
        }
        return "unknown";
    }

    static std::string getShell() {
        const char* shell = getenv("SHELL");
        return shell ? std::string(shell) : "unknown";
    }

    static std::string get_package_manager() {
        if (std::system("which pacman > /dev/null 2>&1") == 0) return "pacman";
        if (std::system("which apt > /dev/null 2>&1") == 0) return "apt";
        if (std::system("which dnf > /dev/null 2>&1") == 0) return "dnf";
        if (std::system("which zypper > /dev/null 2>&1") == 0) return "zypper";
        return "unknown";
    }

    static int getPackageCount(const std::string& package_manager) {
        std::string command;
        if (package_manager == "pacman") {
            command = "pacman -Q | wc -l";
        } else if (package_manager == "apt") {
            command = "dpkg-query -f '.\\n' -W | wc -l";
        } else if (package_manager == "dnf") {
            command = "dnf list installed | wc -l";
        } else if (package_manager == "zypper") {
            command = "zypper se --installed-only | wc -l";
        } else {
            return -1;
        }

        FILE* fp = popen(command.c_str(), "r");
        if (fp == nullptr) {
            return -1;
        }
        
        char buffer[128];
        fgets(buffer, sizeof(buffer), fp);
        fclose(fp);
        return std::stoi(buffer);
    }

    static std::pair<int, int> getMemoryUsage() {
        std::ifstream file("/proc/meminfo");
        std::string line;
        int totalMem = 0, freeMem = 0;
        while (std::getline(file, line)) {
            if (line.find("MemTotal:") == 0) {
                std::istringstream iss(line);
                std::string key;
                iss >> key >> totalMem;
            }
            if (line.find("MemAvailable:") == 0) {
                std::istringstream iss(line);
                std::string key;
                iss >> key >> freeMem;
                break;
            }
        }
        return {totalMem, totalMem - freeMem}; // Return total and used memory in KB
    }
};

#endif // FETCH_H
