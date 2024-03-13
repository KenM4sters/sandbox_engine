#pragma once
#include "../utils/includes.h"
// Base resource class to hold a map of resources, either texture or shaders, and provide
template <typename T>
class UResource {
    public:
        virtual T* GetResource(std::string name) = 0;
        virtual void DeleteResource(std::string res_name) = 0;

        virtual std::unordered_map<std::string, T*> GetAllResources() { return res_; }
        virtual void ClearAllResources() = 0;
    
        std::unordered_map<std::string, T*> res_;
        unsigned int type_;
        int num;
};