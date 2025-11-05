#include <iostream>
#include <optional>
#include <yaml-cpp/yaml.h>

#include "yaml.h"







int main() 
{
    std::cout << "pMSSMdive module initialized." << std::endl;

    // load yaml configuration file
    YAML::Node input_config = loadYamlFile("yaml-files/test.yaml");
    
    // read scan configuration and print it to the screen 
    YAML::Node config = createDefaultConfig();
    readYamlConfig(config, input_config);
    printYamlConfig(config);


    // save the configuration to disk
    dumpYamlConfig(config);


    return 0;
}