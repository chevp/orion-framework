// my_service.cpp
#include "common_interface.h"
#include <iostream>

class MyService : public IService {
public:
    std::string getName() const override {
        return "MyService";
    }

    void execute() override {
        std::cout << "Executing MyService!" << std::endl;
    }
};

// Exportiere die Factory-Funktion
extern "C" IService* createService() {
    return new MyService();
}
