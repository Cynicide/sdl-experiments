#include <ConfigManager.h>

ConfigManager ConfigManager::sConfigManager;

ConfigManager::ConfigManager() {

}

ConfigManager* ConfigManager::get()
{
    //Get static instance
    return &sConfigManager;
}