
# Orion Framework

**Orion Framework** is a C++ platform for building modular, dynamically loadable microservices and plugins. It empowers developers to create scalable, reusable, and high-performance applications by integrating dynamic module loading with robust communication patterns.

## Features

- **Dynamic Module Loading:** Load and unload services at runtime with ease.
- **Modular Architecture:** Isolate functionality into reusable components.
- **Standardized Interfaces:** Define and enforce clear boundaries between modules.
- **High Performance:** Leverages the speed and power of C++ for demanding applications.
- **Scalability:** Build systems that grow effortlessly as needs evolve.

---

## Getting Started

### Prerequisites

- A modern C++ compiler (C++17 or later)
- CMake 3.15 or higher
- A compatible build system (e.g., Make, Ninja, Visual Studio)

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/chevp/orion-framework.git
   cd orion-framework
   ```

2. **Build the project:**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

3. **Run the example application:**
   ```bash
   ./orion_example
   ```

---

## Usage

### Define an Interface
Define a shared interface that all modules must implement:

```cpp
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

#endif // COMMON_INTERFACE_H
```

### Create a Module
Implement the interface in a dynamically loadable library:

```cpp
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

extern "C" IService* createService() {
    return new MyService();
}
```

### Load and Use Modules
Dynamically load modules in your application:

```cpp
// main.cpp
#include "common_interface.h"
#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <vector>

int main() {
    std::vector<std::unique_ptr<IService>> services;

    void* handle = dlopen("./my_service.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading module: " << dlerror() << std::endl;
        return 1;
    }

    auto createService = reinterpret_cast<IService* (*)()>(dlsym(handle, "createService"));
    if (!createService) {
        std::cerr << "Error finding factory function: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    services.emplace_back(createService());

    for (const auto& service : services) {
        std::cout << "Service: " << service->getName() << std::endl;
        service->execute();
    }

    dlclose(handle);
    return 0;
}
```

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/your-feature-name`.
3. Commit your changes: `git commit -m 'Add your feature'`.
4. Push to the branch: `git push origin feature/your-feature-name`.
5. Submit a pull request.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
