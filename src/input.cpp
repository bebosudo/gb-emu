/*
 * See pages 35 to 37 of the documentation (docs/GB.pdf)
 * See https://gbdev.io/pandocs/Joypad_Input.html
 */

#include "../include/input.h"

namespace gameboy
{
    Input::Input(Memory *memory)
        : m_memory(memory)
    {}

    void Input::setButton(JoypadButton button, bool pressed)
    {
        // Remember that the joypad state is inverted (0 = pressed, 1 = not pressed)
        if (pressed)
            m_currentJoypadState = m_memory->m_joypadState & ~(static_cast<uint8_t>(button));
        else
            m_currentJoypadState = m_memory->m_joypadState | static_cast<uint8_t>(button);
    }

    void Input::sendInterrupt(Memory *memory)
    {
        if (m_currentJoypadState != 0)
        {
            // Set the interrupt
            uint8_t interruptFlag = memory->read(INTERRUPT_FLAG_ADDRESS);
            interruptFlag |= 0x10;
            memory->write(INTERRUPT_FLAG_ADDRESS, interruptFlag);

            // Store the joypad state that triggered the interrupt
            memory->joypadState = m_currentJoypadState;
            // Reset the joypad state
            m_currentJoypadState = 0;
        }
    }
} // namespace gameboy
