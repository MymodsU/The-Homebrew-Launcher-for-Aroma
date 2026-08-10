#include "controller.h"

MenuController::MenuController() : m_lastError(VPAD_READ_SUCCESS) {
    // Clear out base state data block arrays on construction
    m_currentStatus = {};
}

MenuController::~MenuController() {}

VPADReadError MenuController::UpdateInputChannels() {
    // Read input straight from the GamePad controller registers
    VPADRead(VPAD_CHAN_0, &m_currentStatus, 1, &m_lastError);
    return m_lastError;
}

bool MenuController::IsButtonClicked(uint32_t buttonBitmask) {
    if (m_lastError != VPAD_READ_SUCCESS) return false;
    
    // Evaluate if the input register contains the clicked button bitflag during this evaluation loop pass
    return (m_currentStatus.trigger & buttonBitmask) != 0;
}
