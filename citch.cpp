#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include "modules/banners.cpp"
#include "modules/fetch.h"
#include "modules/json.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define GRAY    "\033[38;5;240m"

#define operatorLeftTop "╭"
#define operatorRightTop "╮"
#define operatorTop "─"
#define operatorTopx11 "───────────"
#define operatorBottom "─"
#define operator "│"
#define operatorLeftBottom "╰"
#define operatorRightBottom "╯"
#define operatorMidLeft "├"
#define operatorMidRight "┤"

namespace fs = std::filesystem;

using json = nlohmann::json;

void printModule(const std::string& label, const std::string& icon, const std::string& value, const std::string& color) {
    std::cout << RESET operator << color << " " << icon << "  " RESET << label << " " operator << color << " " << value << "\n";
}

void printColors() {
    std::cout << RESET operatorMidLeft operatorTopx11 operatorMidRight << "\n";
    std::cout << RESET operator " 󰏘  " "colors " operator << RESET "  " RED " " YELLOW " " GREEN " " CYAN " " BLUE " " MAGENTA " " GRAY " " << "\n";
}

std::string printBanner() {
    const std::string distro = SystemInfo::getDistro();
    if (distro == "Ubuntu") return Banners::ubuntuLogo;
    if (distro == "Arch" || distro == "Arch Linux") return Banners::archLogo;
    if (distro == "Debian") return Banners::debianLogo;
    if (distro == "Fedora") return Banners::fedoraLogo;
    if (distro == "Mint") return Banners::mintLogo;
    if (distro == "Zorin") return Banners::zorinLogo;
    if (distro == "Pop!_OS" || distro == "PopOS") return Banners::poposLogo;
    if (distro == "Manjaro") return Banners::manjaroLogo;
    if (distro == "openSUSE") return Banners::opensuseLogo;
    if (distro == "Slackware") return Banners::slackwareLogo;
    if (distro == "CentOS") return Banners::centosLogo;
    if (distro == "RedHat" || distro == "Red Hat") return Banners::redhatLogo;
    if (distro == "Gentoo") return Banners::gentooLogo;
    if (distro == "EndeavourOS" || distro == "Endeavour OS") return Banners::endeavourosLogo;
    if (distro == "Artix") return Banners::artixLogo;
    return Banners::citchLogo;
}

void generateConfig() {
    std::string configDir = std::getenv("HOME") + std::string("/.config/citch");
    if (!fs::exists(configDir)) {
        fs::create_directories(configDir);
    }

    json defaultConfig = {
        {"modules", {
            {"banner", true},
            {"username", true},
            {"hostname", true},
            {"distro", true},
            {"kernel", true},
            {"uptime", true},
            {"shell", true},
            {"memory", true},
            {"packages", true},
            {"colors", true}
        }}
    };

    std::ofstream configFile(configDir + "/config.json");
    if (configFile.is_open()) {
        configFile << defaultConfig.dump(4);
        configFile.close();
        std::cout << GREEN << "Config file created successfully at ~/.config/citch/config.json\n" << RESET;
    } else {
        std::cout << RED << "Failed to create config file\n" << RESET;
    }
}

int main(int argc, char* argv[]) {
    // Check for --gen-config or -gc flag
    bool generateConfigFlag = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--gen-config" || std::string(argv[i]) == "-gc") {
            generateConfigFlag = true;
            break;
        }
    }

    if (generateConfigFlag) {
        generateConfig();
        return 0;  // Exit after generating the config
    }

    json config;
    bool configExists = false;

    try {
        std::ifstream configFile(std::getenv("HOME") + std::string("/.config/citch/config.json"));
        if (configFile.is_open()) {
            configFile >> config;
            configExists = true;
        }
    } catch (...) {}

    if (!configExists || !config.contains("modules")) {
        config = {
            {"modules", {
                {"banner", true},
                {"username", true},
                {"hostname", true},
                {"distro", true},
                {"kernel", true},
                {"uptime", true},
                {"shell", true},
                {"memory", true},
                {"packages", true},
                {"colors", true}
            }}
        };
    }

    auto [totalMem, usedMem] = SystemInfo::getMemoryUsage();
    std::string package_manager = SystemInfo::get_package_manager();

    if (config["modules"].value("banner", false))
        std::cout << BLUE << printBanner() << "\n";

    std::cout << RESET operatorLeftTop operatorTopx11 operatorRightTop << "\n";

    if (config["modules"].value("username", false)) 
        printModule("user  ", "", SystemInfo::getUsername(), YELLOW);

    if (config["modules"].value("hostname", false)) 
        printModule("hname ", "", SystemInfo::getHostname(), RED);

    if (config["modules"].value("distro", false)) 
        printModule("distro", "󰻀", SystemInfo::getDistro(), GREEN);

    if (config["modules"].value("kernel", false)) 
        printModule("kernel", "󰌢", SystemInfo::getKernelVersion(), CYAN);

    if (config["modules"].value("uptime", false)) 
        printModule("uptime", "", SystemInfo::getUptime(), BLUE);

    if (config["modules"].value("shell", false)) 
        printModule("shell ", "", SystemInfo::getShell(), MAGENTA);

    if (config["modules"].value("memory", false)) 
        printModule("mem   ", "󰍛", std::to_string(usedMem / 1024) + " MB / " + std::to_string(totalMem / 1024) + " MB", YELLOW);

    if (config["modules"].value("packages", false)) 
        printModule("pkgs  ", "󰏖", std::to_string(SystemInfo::getPackageCount(package_manager)), RED);

    if (config["modules"].value("colors", false)) 
        printColors();

    std::cout << RESET operatorLeftBottom operatorTopx11 operatorRightBottom << "\n";

    return 0;
}
