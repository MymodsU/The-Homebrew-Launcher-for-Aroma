#pragma once

#include <wut.h>
#include <vpad/input.h>

/**
 * @brief Simple input abstraction layer mirroring the original launcher's control loop structure.
 */
class MenuController {
public:
    MenuController();
    ~MenuController();

    /**
     * @brief Queries hardware interfaces to snap active button trigger states.
     * @return The error status or success line configuration.
     */
    VPADReadError UpdateInputChannels();

    /**
     * @brief Inspects active states to determine if a target D-Pad mapping parameter matches.
     * @param buttonBitmask Target button flag constraint (e.g., VPAD_BUTTON_LEFT).
     * @return true if the matching direction button was actively clicked down this frame.
     */
    bool IsButtonClicked(uint32_t buttonBitmask);

private:
    VPADStatus m_currentStatus;
    VPADReadError m_lastError;
};
