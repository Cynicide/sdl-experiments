#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

class ConfigManager
{
public:
    //Static accessor
    static ConfigManager* get();


private:
    //Static instance
    static ConfigManager sConfigManager;


    //Private constructor
    ConfigManager();

    // PrivateDestructor
    ~ConfigManager(){};

};
#endif