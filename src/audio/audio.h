#pragma once

#define handle(x) if (FAILED(x)) return x;

struct audio
{
	IXAudio2* instance = nullptr;
	IXAudio2MasteringVoice* voice = nullptr;
};

HRESULT init_audio(audio* _audio)
{
	HRESULT handle_result;
	handle(handle_result = CoInitializeEx(nullptr, COINIT_MULTITHREADED));
	handle(handle_result = XAudio2Create(&_audio->instance));
	handle(handle_result = _audio->instance->CreateMasteringVoice(&_audio->voice));
}