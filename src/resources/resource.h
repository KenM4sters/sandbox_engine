#pragma once
#include "../utils/includes.h"
// Base resource class to hold a map of resources, either texture or shaders, and provide

// functionality to access an modify them
template <typename T>
class UResource {
    public:
        virtual T AddResource(T& res) = 0
        virtual T GetResource(std::string name) = 0;
        virtual void DeleteResource(std::string res_name) = 0;

        virtual std::unordered_map<std::string, T> GetAllResources() { return res_; }
        virtual void ClearAllResources();
        
    protected:
        std::unordered_map<std::string, T> res_;

};