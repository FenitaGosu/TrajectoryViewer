#pragma once

#include <vector>

#include "Color.h"

namespace GraphicsViewers {

class ColorGradientGenertor
{
public:
	static std::vector<std::vector<Color>> GenerateColorDistribution(const std::vector<std::vector<double>>& values);
};

}
