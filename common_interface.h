// common_interface.h
#ifndef COMMON_INTERFACE_H
#define COMMON_INTERFACE_H

#include <string>

class IService {
public:
    virtual ~IService() = default;
    virtual std::string getName() const = 0;
    virtual void execute() = 0;
};

// Factory-Funktion, die von Modulen bereitgestellt werden muss
typedef IService* (*CreateServiceFunc)();

#endif // COMMON_INTERFACE_H
