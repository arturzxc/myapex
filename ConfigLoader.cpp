#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Utils.cpp"

class ConfigLoader
{
private:
    const std::string m_fileName = "myapex.ini";
    std::vector<std::string> *lines = new std::vector<std::string>;
    long m_lastTimeFileEdited = 0;

    // features
    bool m_featureAimbotOn = false;
    bool m_featureNoRecoilOn = false;
    bool m_featureSenseOn = false;

    // aimbot
    int m_aimbotSmoothing = 999999;
    int m_aimbotActivationFOV = 0;
    int m_aimbotTrigger = 0x0000;

    // norecoil
    double m_norecoilPitchStrength = 0;
    double m_norecoilYawStrength = 0;

    void loadFileIntoVector()
    {
        lines->clear();
        std::string str;
        std::ifstream myFile(m_fileName);
        while (getline(myFile, str))
        {
            utils::trim(str);
            if (str.empty())
                continue;
            if (str.rfind("#", 0) == 0)
                continue;
            lines->push_back(str);
        }
        myFile.close();
    }

    void parseLines()
    {
        for (int i = 0; i < lines->size(); i++)
        {
            std::vector<std::string> lineParts = utils::split(lines->at(i));

            // line key
            std::string lineKey(lineParts.at(0));
            utils::trim(lineKey);
            if (lineKey.empty())
                throw "Cannot parse the config";

            // line value
            std::string lineValue(lineParts.at(1));
            utils::trim(lineValue);
            if (lineValue.empty())
                throw "Cannot parse the config";

            // features
            m_featureAimbotOn = (lineKey.compare("FEATURE_AIMBOT_ON") != 0) ? m_featureAimbotOn : utils::toBool(lineValue);
            m_featureNoRecoilOn = (lineKey.compare("FEATURE_NORECOIL_ON") != 0) ? m_featureNoRecoilOn : utils::toBool(lineValue);
            m_featureSenseOn = (lineKey.compare("FEATURE_SENSE_ON") != 0) ? m_featureSenseOn : utils::toBool(lineValue);
            // aimbot
            m_aimbotTrigger = (lineKey.compare("AIMBOT_TRIGGER") != 0) ? m_aimbotTrigger : stoi(lineValue, 0, 16);
            m_aimbotSmoothing = (lineKey.compare("AIMBOT_SMOOTHING") != 0) ? m_aimbotSmoothing : stoi(lineValue);
            m_aimbotActivationFOV = (lineKey.compare("AIMBOT_ACTIVATION_FOV") != 0) ? m_aimbotActivationFOV : stoi(lineValue);
            // norecoil
            m_norecoilPitchStrength = (lineKey.compare("NORECOIL_PITCH_STRENGTH") != 0) ? m_norecoilPitchStrength : stod(lineValue);
            m_norecoilYawStrength = (lineKey.compare("NORECOIL_YAW_STRENGTH") != 0) ? m_norecoilYawStrength : stod(lineValue);
        }
    }

    void print()
    {
        printf("=== SETTINGS LOADED ===\n");

        printf("FEATURE_AIMBOT_ON \t\t%s\n", m_featureAimbotOn ? "true" : "false");
        printf("FEATURE_NORECOIL_ON \t\t%s\n", m_featureNoRecoilOn ? "true" : "false");
        printf("FEATURE_SENSE_ON \t\t%s\n", m_featureSenseOn ? "true" : "false");

        printf("AIMBOT_TRIGGER \t\t\t%d\n", m_aimbotTrigger);
        printf("AIMBOT_SMOOTHING \t\t%d\n", m_aimbotSmoothing);
        printf("AIMBOT_ACTIVATION_FOV \t\t%d\n", m_aimbotActivationFOV);

        printf("NORECOIL_PITCH_STRENGTH \t%.6f\n", m_norecoilPitchStrength);
        printf("NORECOIL_YAW_STRENGTH \t\t%.6f\n", m_norecoilYawStrength);
    }

public:
    ConfigLoader()
    {
        loadFileIntoVector();
        parseLines();
        print();
    }

    // features
    bool isAimbotOn()
    {
        return m_featureAimbotOn;
    }
    bool isNorecoilOn()
    {
        return m_featureNoRecoilOn;
    }
    bool isSenseOn()
    {
        return m_featureSenseOn;
    }

    // aimbot
    int getAimbotTrigger()
    {
        return m_aimbotTrigger;
    }
    int getAimbotSmoothing()
    {
        return m_aimbotSmoothing;
    }
    int getAimbotActivationFOV()
    {
        return m_aimbotActivationFOV;
    }

    // norecoil
    double getNorecoilPitchStrength()
    {
        return m_norecoilPitchStrength;
    }
    double getNorecoilYawStrength()
    {
        return m_norecoilYawStrength;
    }
};