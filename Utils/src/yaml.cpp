#include "yaml.h"


YAML::Node createDefaultConfig()
{
    YAML::Node default_config;
    YAML::Node default_options = default_config["Options"];
    YAML::Node default_parameters = default_config["Parameters"];

    // --- Set default options ---
    default_options["sampling"]["method"] = "random";
    default_options["sampling"]["n_models"] = 100;
    default_options["output"]["path"] = "./";

    // --- Set default Standard Model parameters ---
    YAML::Node standard_model = default_parameters["StandardModel"];
    standard_model["m_h"] = 125.18;
    standard_model["m_t"] = 172.76;
    standard_model["alpha_s"] = 0.1181;
    standard_model["m_Z"] = 91.1876;
    standard_model["G_F"] = 1.1663787e-5;


    // --- Set default pMSSM parameters ---
    // All pMSSM parameters must be specified in the input.yaml file.
    // Here I set them to zero as placeholders and for model declaration porpuses
    YAML::Node pmssm = default_parameters["pMSSM"];
    pmssm["tanb"] = 0;
    pmssm["mu"] = 0;
    pmssm["m_A"] = 0;
    pmssm["M1"] = 0;
    pmssm["M2"] = 0;
    pmssm["M3"] = 0;
    pmssm["A_t"] = 0;
    pmssm["A_b"] = 0;
    pmssm["A_tau"] = 0;
    pmssm["m_f"] = 0;

    return default_config;
}


void printYamlConfig(const YAML::Node& config)
{
    std::cout << "SCAN CONFIGURATION:\n";
    std::cout << config << "\n";
}













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


// helper function to get all valid keys from the default config
void getValidKeys(const YAML::Node& node, std::set<std::string>& valid_keys)
    {   
        for (const auto& it : node)
        {
            const std::string key = it.first.as<std::string>();
            const YAML::Node value = it.second;

            valid_keys.insert(key);
            if (value.IsMap())
            {
                getValidKeys(node[key], valid_keys);
            }

        }
    }


void readYamlConfig(YAML::Node& default_config, const YAML::Node& input_config)
{
    for (const auto& it : input_config)
    {

        std::set<std::string> valid_keys;
        getValidKeys(default_config, valid_keys);
        


        const std::string key = it.first.as<std::string>();
        const YAML::Node value = it.second;

        // check for invalid input options
        if (!valid_keys.count(key))
        {
            throw std::runtime_error("Invalid input option: " + key);
            return;
        }

        // check for missing pMSSM parameters
        // users are required to provide ALL pMSSM parameters in the input.yaml file
        if (key == "pMSSM")
        {
            for (const auto& par : default_config["Parameters"]["pMSSM"])
            {
                const std::string pssm_key = par.first.as<std::string>();
                if (!value[pssm_key])
                {
                    throw std::runtime_error("Missing pMSSM parameter: " + pssm_key);
                    return;
                }
            }
        }



        if (value.IsMap())
        {
            // recursive call for nested maps
            YAML::Node next_target = default_config[key];
            readYamlConfig(next_target, value);
        }
        else
        {
            // update default config
            default_config[key] = value;
        }
    }


    // // --- Access pMSSM parameters from yaml file ---
    // auto pmssm_input = default_config["Parameters"]["pMSSM"];
    // std::map<std::string, inputPar> pmssm_parameters;
    // for (const auto& it : pmssm_input)
    // {
    //     std::string name = it.first.as<std::string>();
    //     inputPar par = inputPar::fromYaml(it.second);
    //     pmssm_parameters[name] = par;
    // }
    // std::cout << "pMSSM Parameters:" << "\n";
    // for (const auto& [name, par] : pmssm_parameters)
    // {
    //     par.print(name);
    // }
}


void dumpYamlConfig(const YAML::Node& config)
{

    std::string output_dir = config["Options"]["output"]["path"].as<std::string>();
    std::string output_path = output_dir + "/config.yaml";

    // create output directory if it doesn't exist
    std::filesystem::create_directories(output_dir);

    std::ofstream fout(output_path);

    if (!fout.is_open())
    {
        throw std::runtime_error("Could not open file for writing: " + output_path);
    }

    fout << config;
    fout.close();
}