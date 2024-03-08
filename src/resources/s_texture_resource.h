#include "resource.h"
#include "texture.h"


class STextureResource : public UResource<Texture2D> {
    public:
        Texture2D* AddResource(const char* image_url, std::string name, bool bIs_alpha = false);
        Texture2D GetResource(std::string name) override;
        void DeleteResource(std::string res_name) override;
        void ClearAllResources() override;
        Texture2D GenerateTextureDataFromUrl(const char* image_url, bool bIs_alpha = false);
};