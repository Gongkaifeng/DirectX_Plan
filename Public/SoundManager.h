#pragma once

#define MAX_SOUND_CHANNELS       200

#define INVALID_SOUND_INDEX      0
#define INVALID_SOUND_CHANNEL    -1

typedef enum
{
	SOUND_TYPE_INVALID = 0,
	SOUND_TYPE_3D_SOUND,
	SOUND_TYPE_3D_SOUND_LOOPED,
	SOUND_TYPE_2D_SOUND,
	SOUND_TYPE_2D_SOUND_LOOPED,
} SOUND_TYPE;

class SoundInstance
{
public:
	void           Clear(void);
	string         fileName;
	FILE *		   file;

	SOUND_TYPE     soundType;
	FMOD::Sound *  fmodSound;
};
class ChannelInstance
{
public:
	void              Clear(void);
	CObject*		  sceneNode;
	D3DXVECTOR3     prevPosition;
};
class SoundManager
{
	static SoundManager* ms_Singleton;
public:
	static SoundManager* GetSoundManagerInstancePtr()
	{
		if (!ms_Singleton)
			ms_Singleton = new SoundManager;
		return ms_Singleton;
	}
	SoundManager();
	virtual             ~SoundManager();
	void                 Initialize(void);
	void                 StopAllSounds(void);
	void                 FrameStarted(CObject *listenerNode, float timeElapsed);

	int                  CreateSound(string &fileName);         // single-shot 3D sound.  returns soundIndex
	int                  CreateStream(string &fileName);        // single-shot 2D stream.  returns soundIndex
	int                  CreateLoopedSound(string &fileName);   // looping 3D sound.  returns soundIndex
	int                  CreateLoopedStream(string &fileName);  // looping 2D stream.  returns soundIndex

	int                  CreateSound(string &fileName, SOUND_TYPE soundType);

	void                 PlaySound(int soundIndex, CObject *soundNode, int *channelIndex);
	void                 StopSound(int *channelIndex);
	int                  FindSound(string &fileName, SOUND_TYPE soundType);    // returns soundIndex;

	void                 Set3DMinMaxDistance(int channelIndex, float minDistance, float maxDistance);

	float                GetSoundLength(int soundIndex);        // returns seconds
	SoundInstance       *GetSoundInstance(int soundIndex);
	FMOD::Channel       *GetSoundChannel(int channelIndex);

	static SoundManager& getSingleton(void);
	static SoundManager* getSingletonPtr(void);

private:
	typedef std::vector<SoundInstance *>   SoundInstanceVector;
	typedef SoundInstanceVector::iterator  SoundInstanceVectorItr;

	int                  nextSoundInstanceIndex;
	FMOD::System *       system;
	D3DXVECTOR3        prevListenerPosition;
	SoundInstanceVector *soundInstanceVector;
	ChannelInstance      channelArray[MAX_SOUND_CHANNELS];

	void                 IncrementNextSoundInstanceIndex(void);

	static FMOD_RESULT F_CALLBACK  fmodFileOpenCallback(const char *fileName, int unicode, unsigned int *filesize, void **handle, void **userdata);
	static FMOD_RESULT F_CALLBACK  fmodFileCloseCallback(void *handle, void *userdata);
	static FMOD_RESULT F_CALLBACK  fmodFileReadCallback(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);
	static FMOD_RESULT F_CALLBACK  fmodFileSeekCallback(void *handle, unsigned int pos, void *userdata);
};