#pragma once

#include <wut.h>
#include <vector>
#include "launcher.h"

enum class AppState {
    Loading,
    MainMenu,
    Launching,
    Exiting
};

class Application {
public:
    Application();
    ~Application();

    // Core lifecycle functions
    void Initialize();
    void Run();
    void Shutdown();

private:
    void ProcessInputs();
    void UpdateState();
    void RenderScene();

    AppState m_currentState;
    std::vector<HomebrewApp> m_scannedApps;
    int m_selectedIndex;
    int m_activePage;
    bool m_isSystemRunning;
};
