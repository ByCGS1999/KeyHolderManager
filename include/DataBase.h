#pragma once

bool InitDB();
void CloseDB();

bool SaveContainer(const int index, const Container& container);
Container LoadContainer(const std::string& containerId);

int GetContainerId(const Container& container);
void DeleteContainer(int ContainerId);
void DeleteAllContainers();

std::vector<Container> LoadContainers();
std::string GetGlobalIV();
void InsertGlobalIV(const std::string& IV);
void UpdateGlobalIV(const std::string& IV);