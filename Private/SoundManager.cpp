#pragma once
#include "stdafx.h"

#define INITIAL_VECTOR_SIZE   100
#define INCREASE_VECTOR_SIZE  20

#define DOPPLER_SCALE         1.0
#define DISTANCE_FACTOR       1.0
#define ROLLOFF_SCALE         0.5

SoundManager* SoundManager::ms_Singleton = 0;

void SoundInstance::Clear(void)
{
	fileName.clear();
	//streamPtr.setNull();
	//fileArchive = NULL;
	fmodSound = NULL;
	soundType = SOUND_TYPE_INVALID;
}

void ChannelInstance::Clear(void)
{
	sceneNode = NULL;
	prevPosition = D3DXVECTOR3(0, 0, 0);
}



SoundManager::SoundManager()
{
	system = NULL;
	prevListenerPosition = D3DXVECTOR3(0, 0, 0);
	soundInstanceVector = new SoundInstanceVector;

	// Initialized to zero, but pre-incremented in GetNextSoundInstanceIndex(), so vector starts at one.
	nextSoundInstanceIndex = 0;

	// Start off with INITIAL_VECTOR_SIZE soundInstanceVectors.  It can grow from here.
	soundInstanceVector->resize(INITIAL_VECTOR_SIZE);
	for (int vectorIndex = 0; vectorIndex < INITIAL_VECTOR_SIZE; vectorIndex++)
	{
		soundInstanceVector->at(vectorIndex) = new SoundInstance;
		soundInstanceVector->at(vectorIndex)->Clear();
	}

	for (int channelIndex = 0; channelIndex < MAX_SOUND_CHANNELS; channelIndex++)
		channelArray[channelIndex].Clear();
}

SoundManager::~SoundManager()
{
	for (int vectorIndex = 0; vectorIndex < (int)soundInstanceVector->capacity(); vectorIndex++)
	{
		soundInstanceVector->at(vectorIndex)->fileName.clear();
		//      soundInstanceVector->at(vectorIndex)->streamPtr->close();
		delete soundInstanceVector->at(vectorIndex);
	}
	delete soundInstanceVector;
	if (system)
		system->release();
}

void SoundManager::Initialize(void)
{
	FMOD_RESULT result;

	// Create the main system object.
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
		return;
	result = system->init(MAX_SOUND_CHANNELS, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
		return;
	system->set3DSettings(DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);

	result = system->setFileSystem(&fmodFileOpenCallback, &fmodFileCloseCallback, &fmodFileReadCallback, &fmodFileSeekCallback, 2048);
	if (result != FMOD_OK)
		return;
}

SoundManager* SoundManager::getSingletonPtr(void)
{
	return ms_Singleton;
}

SoundManager& SoundManager::getSingleton(void)
{
	return (*ms_Singleton);
}

void SoundManager::FrameStarted(CObject *listenerNode, float timeElapsed)
{
	int            channelIndex;
	FMOD::Channel *nextChannel;
	FMOD_VECTOR    listenerPosition;
	FMOD_VECTOR    listenerForward;
	FMOD_VECTOR    listenerUp;
	FMOD_VECTOR    listenerVelocity;
	D3DXVECTOR3  vectorVelocity;
	D3DXVECTOR3  vectorForward;
	D3DXVECTOR3  vectorUp;

	if (timeElapsed > 0)
		vectorVelocity = (listenerNode->GetPos() - prevListenerPosition) / timeElapsed;
	else
		vectorVelocity = D3DXVECTOR3(0, 0, 0);

	//vectorForward = listenerNode->m_vForward;

	//vectorUp = listenerNode->m_vUp;

	listenerPosition.x = listenerNode->GetPos().x;
	listenerPosition.y = listenerNode->GetPos().y;
	listenerPosition.z = listenerNode->GetPos().z;

	listenerForward.x = vectorForward.x;
	listenerForward.y = vectorForward.y;
	listenerForward.z = vectorForward.z;

	listenerUp.x = vectorUp.x;
	listenerUp.y = vectorUp.y;
	listenerUp.z = vectorUp.z;

	listenerVelocity.x = vectorVelocity.x;
	listenerVelocity.y = vectorVelocity.y;
	listenerVelocity.z = vectorVelocity.z;

	// update 'ears'
	system->set3DListenerAttributes(0, &listenerPosition, &listenerVelocity, &listenerForward, &listenerUp);
	system->update();

	char buf[255];
	sprintf_s(buf, "%f,%f,%f\n", listenerPosition.x, listenerPosition.y, listenerPosition.z);
	OutputDebugStringA(buf);
	prevListenerPosition = listenerNode->GetPos();

	for (channelIndex = 0; channelIndex < MAX_SOUND_CHANNELS; channelIndex++)
	{
		if (channelArray[channelIndex].sceneNode != NULL)
		{
			system->getChannel(channelIndex, &nextChannel);
			if (timeElapsed > 0)
				vectorVelocity = (channelArray[channelIndex].sceneNode->GetPos() - channelArray[channelIndex].prevPosition) / timeElapsed;
			else
				vectorVelocity = D3DXVECTOR3(0, 0, 0);

			listenerPosition.x = channelArray[channelIndex].sceneNode->GetPos().x;
			listenerPosition.y = channelArray[channelIndex].sceneNode->GetPos().y;
			listenerPosition.z = channelArray[channelIndex].sceneNode->GetPos().z;

			listenerVelocity.x = vectorVelocity.x;
			listenerVelocity.y = vectorVelocity.y;
			listenerVelocity.z = vectorVelocity.z;

			nextChannel->set3DAttributes(&listenerPosition, &listenerVelocity);
			channelArray[channelIndex].prevPosition = channelArray[channelIndex].sceneNode->GetPos();
		}
	}
}

int SoundManager::CreateStream(string &fileName)
{
	return CreateSound(fileName, SOUND_TYPE_2D_SOUND);
}

int SoundManager::CreateSound(string &fileName)
{
	return CreateSound(fileName, SOUND_TYPE_3D_SOUND);
}

int SoundManager::CreateLoopedSound(string &fileName)
{
	return CreateSound(fileName, SOUND_TYPE_3D_SOUND_LOOPED);
}

int SoundManager::CreateLoopedStream(string &fileName)
{
	return CreateSound(fileName, SOUND_TYPE_2D_SOUND_LOOPED);
}

// fileName is actually a pointer to a SoundInstance, passed in from CreateSound().
FMOD_RESULT SoundManager::fmodFileOpenCallback(const char *fileName, int unicode, unsigned int *filesize, void **handle, void **userdata)
{
	SoundInstance *soundInstance;

	soundInstance =(SoundInstance*) fileName;

	*userdata = NULL;
	
	fopen_s(&soundInstance->file, soundInstance->fileName.c_str(), "rb"); //read a file into the memory
	fseek(soundInstance->file, 0, SEEK_END);
	*filesize = ftell(soundInstance->file);

	fseek(soundInstance->file, 0, SEEK_SET);
	*handle = (void *)soundInstance;
	return FMOD_OK;
}

FMOD_RESULT SoundManager::fmodFileCloseCallback(void *handle, void *userdata)
{
	SoundInstance *soundInstance;

	soundInstance = (SoundInstance *)handle;
	fclose(soundInstance->file);
	return FMOD_OK;
}

FMOD_RESULT SoundManager::fmodFileReadCallback(void *handle, void *buffer, unsigned int sizeBytes, unsigned int *bytesRead, void *userData)
{
	SoundInstance *soundInstance;

	soundInstance = (SoundInstance *)handle;
	/**bytesRead = (unsigned int)soundInstance->streamPtr->read(buffer, (size_t)sizeBytes);
	if (*bytesRead == 0)
		return FMOD_ERR_FILE_EOF;*/
	size_t haveRead = fread(buffer, 1, sizeBytes,(FILE*)soundInstance->file);
	*bytesRead = (unsigned int)haveRead;
	return FMOD_OK;
}

FMOD_RESULT SoundManager::fmodFileSeekCallback(void *handle, unsigned int pos, void *userdata)
{
	SoundInstance *soundInstance;

	soundInstance = (SoundInstance *)handle;
	fseek((FILE*)soundInstance->file, pos, SEEK_SET);
	return FMOD_OK;
}

int SoundManager::CreateSound(string &fileName, SOUND_TYPE soundType)
{
	//Archive *      fileArchive;
	FMOD_RESULT    result;
	FMOD::Sound *  sound;
	string         fullPathName;
	SoundInstance *newSoundInstance;

	/*int soundIndex;
	soundIndex = FindSound(fileName, soundType);
	if (soundIndex != INVALID_SOUND_INDEX)
		return soundIndex;*/

		/*fullPathName = fileName;
		FileLocator * fileLocator = (FileLocator *)ResourceGroupManager::getSingletonPtr();
		fileArchive = fileLocator->Find(fullPathName);
		if (!fileArchive)
		{
			Ogre::LogManager::getSingleton().logMessage("SoundManager::CreateSound could not find sound '" + fileName + "'");
			return INVALID_SOUND_INDEX;
		}*/

	IncrementNextSoundInstanceIndex();
	newSoundInstance = soundInstanceVector->at(nextSoundInstanceIndex);
	newSoundInstance->fileName = fileName;
	//newSoundInstance->fileArchive = fileArchive;
	newSoundInstance->soundType = soundType;

	switch (soundType)
	{
	case SOUND_TYPE_3D_SOUND:
	{
		result = system->createSound((const char *)newSoundInstance, FMOD_3D | FMOD_HARDWARE, 0, &sound);
		break;
	}

	case SOUND_TYPE_3D_SOUND_LOOPED:
	{
		result = system->createSound((const char *)newSoundInstance, FMOD_LOOP_NORMAL | FMOD_3D | FMOD_HARDWARE, 0, &sound);
		break;
	}

	case SOUND_TYPE_2D_SOUND:
	{
		result = system->createStream((const char *)newSoundInstance, FMOD_DEFAULT, 0, &sound);
		break;
	}

	case SOUND_TYPE_2D_SOUND_LOOPED:
	{
		result = system->createStream((const char *)newSoundInstance, FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &sound);
		break;
	}

	default:
	{
		return INVALID_SOUND_INDEX;
	}
	}

	if (result != FMOD_OK)
	{
		return INVALID_SOUND_INDEX;
	}

	newSoundInstance->fmodSound = sound;
	return nextSoundInstanceIndex;
}

void SoundManager::IncrementNextSoundInstanceIndex(void)
{
	int oldVectorCapacity;

	oldVectorCapacity = (int)soundInstanceVector->capacity();
	nextSoundInstanceIndex += 1;
	if (nextSoundInstanceIndex < oldVectorCapacity)
		return;

	int vectorIndex;
	SoundInstanceVector *newSoundInstanceVector;

	// Create a new, larger SoundInstanceVector
	newSoundInstanceVector = new SoundInstanceVector;
	newSoundInstanceVector->resize(oldVectorCapacity + INCREASE_VECTOR_SIZE);

	// Copy values from old vector to new
	for (vectorIndex = 0; vectorIndex < oldVectorCapacity; vectorIndex++)
		newSoundInstanceVector->at(vectorIndex) = soundInstanceVector->at(vectorIndex);

	int newVectorCapacity;

	newVectorCapacity = (int)newSoundInstanceVector->capacity();
	// Clear out the rest of the new vector
	while (vectorIndex < newVectorCapacity)
	{
		newSoundInstanceVector->at(vectorIndex) = new SoundInstance;
		newSoundInstanceVector->at(vectorIndex)->Clear();
		vectorIndex++;
	}

	// Clear out the old vector and point to the new one.
	soundInstanceVector->clear();
	delete(soundInstanceVector);
	soundInstanceVector = newSoundInstanceVector;
	//delete newSoundInstanceVector;
}

void SoundManager::PlaySound(int soundIndex, CObject *soundNode, int *channelIndex)
{
	int            channelIndexTemp;
	FMOD_RESULT    result;
	FMOD_VECTOR    initialPosition;
	FMOD::Channel *channel;
	SoundInstance *soundInstance;

	if (soundIndex == INVALID_SOUND_INDEX)
		return;

	if (channelIndex)
		channelIndexTemp = *channelIndex;
	else
		channelIndexTemp = INVALID_SOUND_CHANNEL;

	// If the channelIndex already has a sound assigned to it, test if it's the same sceneNode.
	if ((channelIndexTemp != INVALID_SOUND_CHANNEL) && (channelArray[channelIndexTemp].sceneNode != NULL))
	{
		result = system->getChannel(channelIndexTemp, &channel);
		if (result == FMOD_OK)
		{
			bool isPlaying;

			result = channel->isPlaying(&isPlaying);
			if ((result == FMOD_OK) && (isPlaying == true) && (channelArray[channelIndexTemp].sceneNode == soundNode))
				return;  // Already playing this sound attached to this node.
		}
	}

	soundInstance = soundInstanceVector->at(soundIndex);
	// Start the sound paused
	result = system->playSound(FMOD_CHANNEL_FREE, soundInstance->fmodSound, true, &channel);
	if (result != FMOD_OK)
	{
		if (channelIndex)
			*channelIndex = INVALID_SOUND_CHANNEL;
		return;
	}

	channel->getIndex(&channelIndexTemp);
	channelArray[channelIndexTemp].sceneNode = soundNode;

	if (soundNode)
	{
		channelArray[channelIndexTemp].prevPosition = soundNode->GetPos();

		initialPosition.x = soundNode->GetPos().x;
		initialPosition.y = soundNode->GetPos().y;
		initialPosition.z = soundNode->GetPos().z;
		channel->set3DAttributes(&initialPosition, NULL);
	}

	result = channel->setVolume(1.0);
	// This is where the sound really starts.
	result = channel->setPaused(false);

	if (channelIndex)
		*channelIndex = channelIndexTemp;
}

SoundInstance *SoundManager::GetSoundInstance(int soundIndex)
{
	return soundInstanceVector->at(soundIndex);
}

FMOD::Channel *SoundManager::GetSoundChannel(int channelIndex)
{
	if (channelIndex == INVALID_SOUND_CHANNEL)
		return NULL;

	FMOD::Channel *soundChannel;

	system->getChannel(channelIndex, &soundChannel);
	return soundChannel;
}

void SoundManager::Set3DMinMaxDistance(int channelIndex, float minDistance, float maxDistance)
{
	FMOD_RESULT    result;
	FMOD::Channel *channel;

	if (channelIndex == INVALID_SOUND_CHANNEL)
		return;

	result = system->getChannel(channelIndex, &channel);
	if (result == FMOD_OK)
		channel->set3DMinMaxDistance(minDistance, maxDistance);
}

void SoundManager::StopAllSounds(void)
{
	int            channelIndex;
	FMOD_RESULT    result;
	FMOD::Channel *nextChannel;

	for (channelIndex = 0; channelIndex < MAX_SOUND_CHANNELS; channelIndex++)
	{
		result = system->getChannel(channelIndex, &nextChannel);
		if ((result == FMOD_OK) && (nextChannel != NULL))
			nextChannel->stop();
		channelArray[channelIndex].Clear();
	}
}

void SoundManager::StopSound(int *channelIndex)
{
	if (*channelIndex == INVALID_SOUND_CHANNEL)
		return;

	FMOD::Channel *soundChannel;

	system->getChannel(*channelIndex, &soundChannel);
	soundChannel->stop();

	channelArray[*channelIndex].Clear();
	*channelIndex = INVALID_SOUND_CHANNEL;
}

int SoundManager::FindSound(string &fileName, SOUND_TYPE soundType)
{
	int            vectorIndex;
	int            vectorCapacity;
	SoundInstance *nextSoundInstance;

	vectorCapacity = (int)soundInstanceVector->capacity();
	for (vectorIndex = 0; vectorIndex < vectorCapacity; vectorIndex++)
	{
		nextSoundInstance = soundInstanceVector->at(vectorIndex);
		if ((soundType == nextSoundInstance->soundType) && (fileName == nextSoundInstance->fileName))
			//      if ((soundType == nextSoundInstance->soundType) && (fileName == nextSoundInstance->fileArchive->getName()))
			return vectorIndex;
	}

	return INVALID_SOUND_INDEX;
}

float SoundManager::GetSoundLength(int soundIndex)
{
	if (soundIndex == INVALID_SOUND_INDEX)
		return 0.0;

	unsigned int   soundLength;   // length in milliseconds
	FMOD_RESULT    result;
	SoundInstance *soundInstance;

	soundInstance = soundInstanceVector->at(soundIndex);
	if (soundInstance)
	{
		result = soundInstance->fmodSound->getLength(&soundLength, FMOD_TIMEUNIT_MS);
		if (result != FMOD_OK)
		{
			return 0.0;
		}
	}
	else
	{
		return 0.0;
	}

	return (float)soundLength / 1000.0f;
}