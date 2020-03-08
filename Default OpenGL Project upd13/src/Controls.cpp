#include "Controls.h"

bool pressObj(GLFWwindow*& window, double& cursor_x, double & cursor_y, int& ww, int& hh, cRect &r2, int& LMB)
{
	
		if (LMB==1)
		{

			if (
				static_cast<float>(cursor_x) / static_cast<float>(ww / 2) - 1.0f < r2.x[0] &&
				-(static_cast<float>(cursor_y) / static_cast<float>(hh / 2) - 1.0f) < r2.y[0] &&
				static_cast<float>(cursor_x) / static_cast<float>(ww / 2) - 1.0f > r2.x[1] &&
				-(static_cast<float>(cursor_y) / static_cast<float>(hh / 2) - 1.0f) > r2.y[2]
				)
			{
				
				
				if (r2.exists)
				{
					std::cout << "PRESSED " << r2.name << std::endl;

					return true;
				}
				

			}
		}
		return false;
}
bool pressNotObj(GLFWwindow*& window, double& cursor_x, double& cursor_y, int& ww, int& hh, cRect& r2, int& LMB)
{

	if (LMB == 1)
	{

		if (!(
			static_cast<float>(cursor_x) / static_cast<float>(ww / 2) - 1.0f < r2.x[0] &&
			-(static_cast<float>(cursor_y) / static_cast<float>(hh / 2) - 1.0f) < r2.y[0] &&
			static_cast<float>(cursor_x) / static_cast<float>(ww / 2) - 1.0f > r2.x[1] &&
			-(static_cast<float>(cursor_y) / static_cast<float>(hh / 2) - 1.0f) > r2.y[2]
			))
		{


			std::cout << "PRESSED OUT OF " << r2.name << std::endl;
			return true;

		}
	}
	return false;
}
