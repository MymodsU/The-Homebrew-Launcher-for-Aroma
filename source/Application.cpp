#include "Application.h"
#include "common/common.h"
#include "gui/gui.h"
#include <vpad/input.h>
#include <proc_ui/procui.h>
#include <whb/gfx.h>
#include <coreinit/shutdown.h>

Application::Application() 
    : m_currentState(AppState::Loading), m_selectedIndex(0), m_activePage(0), m_isSystemRunning(true) {}

Application::~Application() {}

void Application::Initialize() {
    WHBGfxInit();
    
    if (mountSDCard()) {
        m_scannedApps = scanForHomebrew(CUSTOM_APPS_DIR);
    }
    
    m_currentState = AppState::MainMenu;
}

void Application::ProcessInputs() {
    VPADStatus vpad;
    VPADReadError err;
    VPADRead(VPAD_CHAN_0, &vpad, 1, &err);

    if (err != VPAD_READ_SUCCESS) return;

    if (vpad.hold & VPAD_BUTTON_HOME) {
        m_currentState = AppState::Exiting;
        return;
    }

    if (m_currentState == AppState::MainMenu && !m_scannedApps.empty()) {
        if (vpad.trigger & VPAD_BUTTON_RIGHT) {
            if (m_selectedIndex + 1 < (int)m_scannedApps.size()) m_selectedIndex++;
        }
        if (vpad.trigger & VPAD_BUTTON_LEFT) {
            if (m_selectedIndex - 1 >= 0) m_selectedIndex--;
        }
        if (vpad.trigger & VPAD_BUTTON_DOWN) {
            if (m_selectedIndex + 3 < (int)m_scannedApps.size()) m_selectedIndex += 3;
        }
        if (vpad.trigger & VPAD_BUTTON_UP) {
            if (m_selectedIndex - 3 >= 0) m_selectedIndex -= 3;
        }

        if (vpad.trigger & VPAD_BUTTON_A) {
            m_currentState = AppState::Launching;
        }
    }
}

void Application::UpdateState() {
    // Dynamically calculate grid pages matching classic HBL rows (3 Cols x 2 Rows)
    m_activePage = m_selectedIndex / 6;

    if (m_currentState == AppState::Launching) {
        HomebrewApp chosen = m_scannedApps[m_selectedIndex];
        if (chosen.isAromaPlugin) {
            std::string destination = std::string(AROMA_PLUGIN_DIR) + "/" + chosen.fileName;
            if (copyFile(chosen.filePath, destination)) {
                OSShutdown(OS_SHUTDOWN_TYPE_REBOOT);
            }
        }
        m_currentState = AppState::MainMenu; // Fallback if execution fails
    }

    if (m_currentState == AppState::Exiting) {
        m_isSystemRunning = false;
    }
}

void Application::RenderScene() {
    if (m_currentState == AppState::MainMenu) {
        renderClassicHBLViewport(m_scannedApps, m_selectedIndex, m_activePage);
    }
}

void Application::Run() {
    Initialize();

    while (m_isSystemRunning && ProcUIInRunningLoop()) {
        ProcessInputs();
        UpdateState();
        RenderScene();
    }

    Shutdown();
}

void Application::Shutdown() {
    WHBGfxShutdown();
}
