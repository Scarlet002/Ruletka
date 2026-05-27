#pragma once
#include "IGameState.h"
#include "Serializer.h"
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <cassert>
#include <string>
#include <stdexcept>

class SerializationManager
{
private:
	std::unordered_map<uint8_t, std::shared_ptr<Serializer>> serializations;
	std::mutex mtx;
	std::shared_ptr<Serializer> serialization;
public:
	SerializationManager() = default;

	SerializationManager(const SerializationManager&) = delete;
	SerializationManager& operator=(const SerializationManager&) = delete;

	SerializationManager(SerializationManager&&) = delete;
	SerializationManager& operator=(SerializationManager&&) = delete;

	void SetSerializer(uint8_t serializationType)
	{
		std::lock_guard<std::mutex> lock(mtx);
		assert(serializations.contains(serializationType));
		if (serializations.contains(serializationType))
		{
			serialization = serializations.at(serializationType);
		}
		else throw std::runtime_error("Brak wybranej serializacji!");
	}

	void Serialize(const std::shared_ptr<IGameState> gs,
		const std::string& fileName)
	{
		std::lock_guard<std::mutex> lock(mtx);
		assert(serialization);
		if (!serialization) throw std::runtime_error("Nie ustawiono serializacji!");
		serialization->Serialize(gs, fileName);
	}

	void Deserialize(std::shared_ptr<IGameState> gs,
		const std::string& fileName)
	{
		std::lock_guard<std::mutex> lock(mtx);
		assert(serialization);
		if (!serialization) throw std::runtime_error("Nie ustawiono serializacji!");
		serialization->Deserialize(gs, fileName);
	}

	void AddSerializer(uint8_t serializationType, std::shared_ptr<Serializer> serializer)
	{
		std::lock_guard<std::mutex> lock(mtx);
		assert(!serializations.contains(serializationType));
		if (!serializations.contains(serializationType))
		{
			serializations[serializationType] = std::move(serializer);
			if (!serialization) serialization = serializations[serializationType];
		}
		else throw std::runtime_error("Proba zdublowania serializacji!");
	}

	[[nodiscard]] std::string GetSerializationLog()
	{
		std::lock_guard<std::mutex> lock(mtx);
		assert(serialization);
		if (!serialization) throw std::runtime_error("Nie ustawiono serializacji!");
		return serialization->GetSerializationLog();
	}
};