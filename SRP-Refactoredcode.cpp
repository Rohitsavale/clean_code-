#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Handles environmental monitoring
class EnvironmentMonitor {
public:
    void updateTemperature(float temperature) {
        if (temperature > 35.0) {
            cout << "ALERT: High temperature detected (Environment)" << endl;
        }
    }

    void checkNoData(int code) {
        if (code == 0x00) {
            cout << "ALERT: No data from machine (Environment)" << endl;
        }
    }
};

// Handles machine-specific monitoring
class MachineMonitor {
public:
    void updateDimensionVariation(float variation) {
        if (variation > 0.05) {
            cout << "ALERT: Part-dimension variation too high (Machine)" << endl;
        }
    }

    void updateContinuousOperation(int minutes) {
        if (minutes > 360) {
            cout << "ALERT: Continuous operation exceeded 6 hours (Machine)" << endl;
        }
    }
};

// Handles diagnostic code interpretation
class DiagnosticChecker {
public:
    void checkSelfTestCode(int code) {
        switch (code) {
            case 0xFF:
                cout << "Self-test OK" << endl;
                break;
            case 0x01:
                cout << "ALERT: Controller board failure (Machine)" << endl;
                break;
            case 0x02:
                cout << "ALERT: Configuration data corrupted (Machine)" << endl;
                break;
            default:
                if (code != 0x00) {
                    cout << "ALERT: Unknown self-test code (Machine)" << endl;
                }
        }
    }
};

// Coordinates all monitoring components
class CNCMachineMonitor {
private:
    EnvironmentMonitor envMonitor;
    MachineMonitor machineMonitor;
    DiagnosticChecker diagChecker;

public:
    void process(float temp, float variation, int minutes, int selfTestCode) {
        envMonitor.updateTemperature(temp);
        machineMonitor.updateDimensionVariation(variation);
        machineMonitor.updateContinuousOperation(minutes);
        envMonitor.checkNoData(selfTestCode);
        diagChecker.checkSelfTestCode(selfTestCode);
    }
};

int main() {
    CNCMachineMonitor monitor;
    ifstream infile("cnc_data.txt");

    if (!infile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    float temp, variation;
    int minutes, selfTest;

    while (infile >> temp >> variation >> minutes >> hex >> selfTest) {
        monitor.process(temp, variation, minutes, selfTest);
        cout << "---" << endl;
    }

    infile.close();
    return 0;
}
