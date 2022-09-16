/**
 * @file gb.h
 * @brief This file contains the declaration of the GB class.
 *        It includes all the other classes and is responsible for the emulator to run.
 */

#pragma once

#include "cpu.h" // CPU
#include "input.h" // Input
#include "memory.h" // Memory
#include "platform.h" // Platform
#include "ppu.h" // PPU
#include "timer.h" // Timer

namespace gameboy
{
    /**
     * @brief The GB class is responsible for the emulator to run.
     */
    class GB
    {
    public:
        /**
         * @brief Create and initialize the emulator
         *
         * @param rom The path to the rom file
         * @param scale The scale of the window
         */
        GB(const std::string &rom, const int scale);

        /**
         * @brief Run the emulator
         * @details Do the steps of the CPU, PPU, Timer and Input
         */
        void run();

    private:
        Platform m_platform;
        Memory m_memory;

        constexpr static int FPS = 60;
        constexpr static int FRAMERATE = 1000 / FPS;

        /**
         * @brief Update the screen and handle the inputs
         * @details If the PPU is rendering, update the screen and handle the inputs
         *
         * @param lastCycleTime The last time the screen was updated
         * @return True if the user wants to quit, false otherwise
         */
        bool updatePlatform(uint64_t &lastCycleTime, PPU &ppu, Input &input);
    };
} // namespace gameboy
