#include "AuUI_Drawing.h"

namespace AuUI 
{
	void Draw::RenderList(Window window)
	{
		std::unique_lock<std::shared_mutex> lock(drawMutex);
		
		if (!window.pD3D || !window.pD3Ddevice || vecDrawData.empty())
			return;

		for (const auto& data : vecDrawData)
		{
			if (!data.pObject.has_value())
				continue;

			switch (data.nType) 
			{
			case EDrawType::LINE:



				break;
			}
		}


	}

	void Draw::AddLine()
	{

	}
}