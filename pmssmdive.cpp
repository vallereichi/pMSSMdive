#include <iostream>
#include <optional>
#include <yaml-cpp/yaml.h>

#include "yaml.h"







int main() 
{
    std::cout << "pMSSMdive module initialized." << std::endl;

    // load yaml configuration file
    YAML::Node config = loadYamlFile("yaml-files/test.yaml");
    // read scan configuration and print it to the screen 
    readYamlConfig(config);

    return 0;
}