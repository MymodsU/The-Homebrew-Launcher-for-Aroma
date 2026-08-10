#pragma once

#include <wut.h>
#include <string>
#include <vector>

// Directory storage shortcuts for scanning operations
#define SD_PREFIX          "sd:/"
#define CUSTOM_APPS_DIR    "sd:/wiiu/HBLFA/APPS"
#define AROMA_PLUGIN_DIR   "sd:/wiiu/environments/aroma/plugins"

// Structure container holding metadata configurations for found homebrew targets
struct HomebrewApp {
    std::string name;        // Clean visual screen title text
    std::string fileName;    // Raw file identifier string (e.g., "plugin.aroma")
    std::string filePath;    // Absolute path layout assignment address on SD card
    std::string author;      // Creator credit text metadata
    std::string version;     // Title release build version number
    bool isAromaPlugin;      // Format identifier logic flag (true if .aroma)
};

// --- Storage Engine Prototypes ---

/**
 * @brief Initializes and mounts the SD card partition slot into the Virtual File System space.
 * @return true if mounting operations succeed, false otherwise.
 */
bool mountSDCard();

/**
 * @brief Safely unmounts hardware storage pointers to lock blocks and prevent file corruptions.
 */
void unmountSDCard();

/**
 * @brief Sweeps an absolute directory structure path on the SD card to collect executable code formats.
 * @param directoryPath Target directory location to extract files from.
 * @return A vector list collection containing matching HomebrewApp storage blocks.
 */
std::vector<HomebrewApp> scanForHomebrew(const std::string& directoryPath);

// --- File Utility System Prototypes ---

/**
 * @brief Safely clones an application binary or plugin module across target physical paths.
 * @param source The absolute location string path of the source target file asset.
 * @param destination The absolute destination landing string location path configuration.
 * @return true if data chunks move without structural dropouts, false if a path error occurs.
 */
bool copyFile(const std::string& source, const std::string& destination);
