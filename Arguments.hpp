//
// Created by Jaibeer Dugal on 30/10/2023.
//

#ifndef CPPIMAGECOMPRESSION_ARGUMENTS_HPP
#define CPPIMAGECOMPRESSION_ARGUMENTS_HPP

#include <map>
#include <string>
#include <iostream>
#include <functional>

class Args {
private:
public:
    const std::string &getSource() const {
        return source;
    }

    const std::string &getDestination() const {
        return destination;
    }

    float getBlurFactor() const {
        return blurFactor;
    }

    bool getIsRunnableConfig() const {
        if(source.empty()) return false;
        if(destination.empty()) return false;
        if(blurFactor>1.0f || blurFactor<0.0) return false;

        return true;
    }

private:
    // Variables
    std::string source = "";
    std::string destination = "";
    float blurFactor = 0.5; // defaulting it to something if needed.

    // Argument map
    std::map<std::string, std::function<void(const std::string&)>> argsMap;

private:
    // private functions
    void InitializeArgsMap()
    {
        argsMap["-s"] = [this](const std::string& val){ setSource(val);};
        argsMap["-d"] = [this](const std::string& val){ setDestination(val);};
        argsMap["-b"] = [this](const std::string& val){ setBlurFactor(val);};
    }

public:
    Args()
    {
        InitializeArgsMap();
    }

    Args(int argc , char* argv[] )
    {
        InitializeArgsMap();
        parseArgs(argc,argv);

    }
    void parseArgs(int argc , char* argv[])
    {
        for (int i = 1; i < argc; i += 2)
        {
            if (i + 1 < argc)
            {
                const std::string arg = argv[i];
                const std::string value = argv[i + 1];

                if (argsMap.find(arg) != argsMap.end())
                {
                    argsMap[arg](value);
                }
                else
                {
                    std::cerr << "Unknown argument: " << arg << std::endl;
                }
            }
            else
            {
                std::cerr << "Missing value for argument: " << argv[i] << std::endl;
            }
        }
    }

    void setSource(const std::string& value)
    {
        source = value;
        std::cout << "Source set to: " << source << std::endl;
    }

    void setDestination(const std::string& value)
    {
        destination = value;
        std::cout << "Destination set to: " << destination << std::endl;
    }

    void setBlurFactor(const std::string& value)
    {
        blurFactor = std::stof(value);
        std::cout << "Blur Factor set to: " << blurFactor << std::endl;
    }
};

#endif //CPPIMAGECOMPRESSION_ARGUMENTS_HPP
