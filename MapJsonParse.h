#pragma once
#include "Structs.h"
#include <iostream>
#include <fstream>
//#include <vector>
#include <string>
static class MapJsonParse
{
public:

    static MapData LoadMapFromJsonFile(const std::string& filepath);
};

