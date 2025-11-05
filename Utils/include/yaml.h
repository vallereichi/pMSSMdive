#pragma once

#include <optional>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <yaml-cpp/yaml.h>



// struct to handle input paramters from input.yaml file with sequence or fixed value
struct inputPar 
{
    std::optional<double> fixed_value;                          // fixed value input parameter
    std::optional<std::pair<double, double>> range;             // range input (min, max)

    static inputPar fromYaml(const YAML::Node& node)
    {
        inputPar par;
        if (node.IsScalar())
        {
            // load fixed value from yaml
            par.fixed_value = node.as<double>();
        }
        else if (node.IsSequence() && node.size() == 2)
        {
            // load range from yaml
            par.range = std::make_pair(node[0].as<double>(), node[1].as<double>());
        }
        else
        {
            throw std::runtime_error("Invalid input parameter format. must be either a fixed value or a range [min, max]");
        }
        return par;
    }

    void print(const std::string& name) const
    {
        if (fixed_value)
        {
            std::cout << "  " << name << ": " << *fixed_value << "\n";
        }
        else if (range)
        {
            std::cout << "  " << name << ": [" << range->first << ", " << range->second << "]\n";
        }
    }
};






// load yaml file from the given file path and return a YAML::Node
YAML::Node loadYamlFile(const std::string& file_path);

// create a edfault yaml configuration
YAML::Node createDefaultConfig();

// read the scan configuration from the yaml file and print it to the screen
void readYamlConfig(YAML::Node& config, const YAML::Node& input_config);

// print the yaml configuration to the screen
void printYamlConfig(const YAML::Node& config);

// save the yaml configuration to the scans output directory
void dumpYamlConfig(const YAML::Node& config);

