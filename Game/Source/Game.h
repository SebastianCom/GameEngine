#pragma once

#include "Framework.h"

class Enemy;
class Player;
class PlayerController;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void Init();
    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    void WaterToggles();
    void ResetScene(const char* name);
    void SwitchScene();
    void ChangeWindowSize();
    virtual void Draw() override;


    // Getters.
    fw::Mesh* GetMesh(std::string name) { return m_Meshes[name]; }
    fw::ShaderProgram* GetShader(std::string name) { return m_Shaders[name]; }
    fw::Texture* GetTexture(std::string name) { return m_Textures[name]; }
    fw::SpriteSheet* GetSpriteSheet(std::string name) { return m_SpriteSheets[name]; }
    fw::Material* GetMaterial(std::string name) { return m_Materials[name]; }

protected:
    fw::FWCore& m_FWCore;
    fw::ImGuiManager* m_pImGuiManager = nullptr;

    bool WFrameToggle;

    GLenum CurrentprimType;

    fw::vec2 m_GridSize;
    fw::vec2 m_OldGridSize;

    fw::vec3 m_WorldSize;
    fw::vec3 m_OldWorldSize;

    std::map<std::string, fw::Mesh*> m_Meshes;
    std::map<std::string, fw::ShaderProgram*> m_Shaders;
    std::map<std::string, fw::Texture*> m_Textures;
    std::map<std::string, fw::SpriteSheet*> m_SpriteSheets;
    std::map<std::string, fw::Material*> m_Materials;
    std::map<std::string, fw::Scene*>  m_Scenes;

    fw::Scene* m_pCurrentScene = nullptr;

};
