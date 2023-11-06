//
// Created by Jaibeer Dugal on 30/10/2023.
//

#ifndef CPPIMAGECOMPRESSION_ARGUMENTS_HPP
#define CPPIMAGECOMPRESSION_ARGUMENTS_HPP

#include <map>
#include <string>
#include <iostream>
#include <functional>

#include "ImageBlurringAlgos/Base/ESupportedImageBlurringAlgos.hpp"

class Args
{
public:
    const std::string &getSource() const
    {
        return source;
    }

    const std::string &getDestination() const
    {
        return destination;
    }

    float getBlurFactor() const
    {
        return blurFactor;
    }

    bool getIsRunnableConfig() const
    {
        if (source.empty()) return false;
        if (destination.empty()) return false;
        if (blurFactor > 1.0f || blurFactor < 0.0) return false;

        return true;
    }

    ESupportedImageBlurringAlgos getAlgo() const
    {
        return algo;
    }

private:
    std::string source = "";
    std::string destination = "";
    float blurFactor = 0.5; // defaulting it to something if needed.
    ESupportedImageBlurringAlgos algo = ESupportedImageBlurringAlgos::NAIVE_BLUR;

private:
    // defaulting to this for now

    // Using map cause 1) it's small information 2) it's in order mostly might help me write the
    // Commands help more easily.
    // Maybe later i can use io Mannipulate to write the help easily by giving each a description.
    std::map<std::string, std::function<void(const std::string &)>> argsMap;

private:

    void InitializeArgsMap()
    {
        // EZ PZ lemon squuezy
        // The only good thing about JS style patterns.
        argsMap = {
                {"-s", [this](const std::string &val) { setSource(val); }},
                {"-d", [this](const std::string &val) { setDestination(val); }},
                {"-b", [this](const std::string &val) { setBlurFactor(val); }},
                {"-a", [this](const std::string &val) { setAlgorithm(val); }}
        };
    }

public:
    Args()
    {
        InitializeArgsMap();
    }

    Args(int argc, char *argv[])
    {
        InitializeArgsMap();
        parseArgs(argc, argv);
    }

    static void showHelp()
    {
        // we need to show tabulated help that will be easy to read.
        std::cout << "Help: " << std::endl;
        std::cout << "Usage: " << std::endl;
        std::cout << "cppImageCompression -s <source> -d <destination> -b <blurFactor> -a <algorithm>" << std::endl;
        std::cout << "Arguments: " << std::endl;
        std::cout << "-s <source> : The source image path" << std::endl;
        std::cout << "-d <destination> : The destination image path" << std::endl;
        std::cout << "-b <blurFactor> : The blur factor between 0.0 - 1.0" << std::endl;
        std::cout << "-a <algorithm> : The algorithm to use for blurring the image" << std::endl;
        std::cout << "Supported Algorithms: " << std::endl;
        std::cout << "NaiveBlur // Default" << std::endl;
        std::cout << "FastGaussianBlur" << std::endl;
        std::cout << "NaiveBlurThreaded" << std::endl;
        std::cout << "NaiveBlurPrefixSumMat" << std::endl;
    }

    void parseArgs(int argc, char *argv[])
    {
        for (int i = 1; i < argc; i += 2)
        {
            if (i + 1 < argc)
            {
                const std::string arg = argv[i];
                const std::string value = argv[i + 1];

                if(arg.compare("--help") == 0)
                {
                    showHelp();
                    break;
                }

                if (argsMap.find(arg) != argsMap.end())
                {
                    argsMap[arg](value);
                } else
                {
                    std::cerr << "Unknown argument: " << arg << std::endl;
                    showHelp();
                    break;
                }
            } else
            {
                std::cerr << "Missing value for argument: " << argv[i] << std::endl;
            }
        }
    }

    void setSource(const std::string &value)
    {
        source = value;
        std::cout << "Source set to: " << source << std::endl;
    }

    void setDestination(const std::string &value)
    {
        destination = value;
        std::cout << "Destination set to: " << destination << std::endl;
    }

    void setBlurFactor(const std::string &value)
    {
        blurFactor = std::stof(value);
        std::cout << "Blur Factor set to: " << blurFactor << std::endl;
    }

    void setAlgorithm(const std::string &str)
    {
        if (str == "NaiveBlur")
        {
            algo = ESupportedImageBlurringAlgos::NAIVE_BLUR;
        } else if (str == "FastGaussianBlur")
        {
            algo = ESupportedImageBlurringAlgos::FAST_GAUSSIAN_BLUR;
        } else if(str == "NaiveBlurThreaded")
        {
            algo = ESupportedImageBlurringAlgos::NAIVE_BLUR_THREADED;
        }
        else if(str == "NaiveBlurPrefixSumMat")
        {
            algo = ESupportedImageBlurringAlgos::NAIVE_BLUR_PREFIX_SUM_MAT;
        }
        else
        {
            std::cerr << "Unknown Algorithm: " << str << std::endl;
        }
    }
};

#endif //CPPIMAGECOMPRESSION_ARGUMENTS_HPP
