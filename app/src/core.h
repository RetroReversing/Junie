#pragma once

#include "configuration.h"

#include "libretro.h"

typedef struct JUN_Core JUN_Core;

typedef struct JUN_CoreCallbacks JUN_CoreCallbacks;

typedef enum {
	JUN_CORE_NONE,
	JUN_CORE_GENESIS,
	JUN_CORE_MELONDS,
	JUN_CORE_MGBA,
	JUN_CORE_QUICKNES,
	JUN_CORE_SNES9X,
} JUN_CoreType;

struct JUN_CoreCallbacks
{
	retro_environment_t environment;
	retro_video_refresh_t video_refresh;
	retro_audio_sample_t audio_sample;
	retro_audio_sample_batch_t audio_sample_batch;
	retro_input_poll_t input_poll;
	retro_input_state_t input_state;
};

JUN_Core *JUN_CoreInitialize(JUN_CoreType type, const char *game_path, const char *state_path, const char *sram_path, const char *rtc_path, const char *cheats_path);
JUN_Configuration *JUN_CoreGetConfiguration(JUN_Core *this);
void JUN_CoreSetCallbacks(JUN_Core *this, JUN_CoreCallbacks *callbacks);
bool JUN_CoreHasStarted(JUN_Core *this);
double JUN_CoreGetSampleRate(JUN_Core *this);
double JUN_CoreGetFramesPerSecond(JUN_Core *this);
bool JUN_CoreStartGame(JUN_Core *this);
void JUN_CoreRun(JUN_Core *this);
void JUN_CoreSaveMemories(JUN_Core *this);
void JUN_CoreRestoreMemories(JUN_Core *this);
void JUN_CoreSetCheats(JUN_Core *this);
void JUN_CoreResetCheats(JUN_Core *this);
void JUN_CoreSaveState(JUN_Core *this);
void JUN_CoreRestoreState(JUN_Core *this);
void JUN_CoreDestroy(JUN_Core **this);
