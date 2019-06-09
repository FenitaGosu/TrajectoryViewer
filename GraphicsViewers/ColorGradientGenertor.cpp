#include <algorithm>
#include <limits>

#include "ColorGradientGenertor.h"

using namespace GraphicsViewers;

namespace
{
	int Muffle(size_t color)
	{
		return static_cast<int>(color * 3 / 4 + 64);
	}
}

std::vector<std::vector<Color>> ColorGradientGenertor::GenerateColorDistribution(const std::vector<std::vector<double>>& values)
{
	std::vector<std::vector<Color>> colors;

	double minU = std::numeric_limits<double>::max();
	double maxU = std::numeric_limits<double>::min();

	double stepUBig, stepUSmall;

	for (const auto& row : values)
	{
		const auto minMaxOnRow = std::minmax_element(row.cbegin(), row.cend());

		minU = std::min(*minMaxOnRow.first, minU);
		maxU = std::max(*minMaxOnRow.second, maxU);
	}

	stepUBig = (maxU - minU) / 4.0;
	stepUSmall = stepUBig / 255.0;

	colors.reserve(values.size());

	for (size_t i = 0, szi = values.size(); i < szi; ++i)
	{
		std::vector<Color> rowColors;
		rowColors.reserve(values[i].size());

		for (size_t j = 0, szj = values[i].size(); j < szj; ++j)
		{
			size_t rColor = 0, gColor = 0, bColor = 0;
			if (values[i][j] > minU + stepUBig * 3.0)
			{
				rColor = 255;
				gColor = 255 - static_cast<size_t>((values[i][j] - (minU + stepUBig * 3.0)) / stepUSmall);
				bColor = 0;
			}
			else if (values[i][j] > minU + stepUBig * 2.0)
				{
					rColor = static_cast<size_t>((values[i][j] - (minU + stepUBig * 2.0)) / stepUSmall);
					gColor = 255;
					bColor = 0;
				}
				else if (values[i][j] > minU + stepUBig)
					{
						size_t tmp = static_cast<size_t>((values[i][j] - (minU + stepUBig)) / stepUSmall);
						rColor = 0;
						gColor = tmp;
						bColor = 255 - tmp;
					}
					else
					{
						size_t tmp = 76 - static_cast<size_t>((values[i][j] - minU) / (stepUSmall * (255.0 / 76.0)));
						rColor = tmp;
						gColor = 0;
						bColor = 255 - tmp;
					}

			rowColors.emplace_back(Muffle(rColor), Muffle(gColor), Muffle(bColor));
		}

		colors.push_back(std::move(rowColors));
	}

	return colors;
}
