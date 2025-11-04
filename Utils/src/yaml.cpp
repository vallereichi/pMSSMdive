#include "yaml.h"



YAML::Node loadYamlFile(const std::string& file_path)
{
    try 
    {
        YAML::Node config = YAML::LoadFile("yaml-files/test.yaml");
        if (!config) 
        {
            throw std::runtime_error("Failed to load YAML file");
        }
        std::cout << "YAML config loaded successfully!\n";
        return config;
    } 
    catch (const YAML::BadFile& e) 
    {
        std::cerr << "Could not open YAML file: " << e.what() << std::endl;
    }
    catch (const YAML::ParserException& e) 
    {
        std::cerr << "YAML syntax error: " << e.what() << std::endl;
    }
    return YAML::Node(); // return empty node on exception
}



void readYamlConfig(const YAML::Node& config)
{
    // --- Access Options from yaml file ---
    auto options = config["Options"];
    std::string sampling_method = options["Sampling"]["method"].as<std::string>();
    int n_models = options["Sampling"]["n_models"].as<int>();
    std::string output_path = options["Output"]["path"].as<std::string>();

    std::cout << "YAML Options:" << "\n";
    std::cout << "  Sampling method: " << sampling_method << "\n";
    std::cout << "  n_models:        " << n_models << "\n";
    std::cout << "  output path:     " << output_path << "\n";


    // --- Acces Standard Model parameters from yaml file ---
    auto standard_model = config["Parameters"]["StandardModel"];
    double m_h = standard_model["m_h"].as<double>();
    double m_t = standard_model["m_t"].as<double>();
    double alpha_s = standard_model["alpha_s"].as<double>();

    std::cout << "Standard Model Parameters:" << "\n";
    std::cout << "  m_h:      " << m_h << "\n";
    std::cout << "  m_t:      " << m_t << "\n";
    std::cout << "  alpha_s:  " << alpha_s << "\n";


    // --- Access pMSSM parameters from yaml file ---
    auto pmssm_input = config["Parameters"]["pMSSM"];
    std::map<std::string, inputPar> pmssm_parameters;
    for (const auto& it : pmssm_input)
    {
        std::string name = it.first.as<std::string>();
        inputPar par = inputPar::fromYaml(it.second);
        pmssm_parameters[name] = par;
    }
    std::cout << "pMSSM Parameters:" << "\n";
    for (const auto& [name, par] : pmssm_parameters)
    {
        par.print(name);
    }
}