/*
   * What is this file and what does it do! 

   This file helps handle errors and log them into *.log files!
   It also shows errors directly as a message by creating a window and a text.

   * This is always on unless you turn it off * 
*/

#include <filesystem>

namespace AuUI 
{
	enum ErrorFlags
	{
		ERROR_LOG   = (1 << 1),
		ERROR_SOUND = (1 << 2),
		ERROR_CLOSE = (1 << 3),
		ERROR_NONE  = (1 << 4)
	};

	class Err 
	{
	public:
		void Show(const char* err, ErrorFlags flags)
		{
			if (!ErrOn)
				return;

			if (!(flags & ERROR_NONE)) 
			{
				if ((flags & ERROR_LOG))
				{
					// Saving & writing
				}

				if ((flags & ERROR_SOUND))
				{
					// Make error sound!
				}

				if ((flags & ERROR_CLOSE))
				{
					// Error
				}
			}


			// Create Window!
			printf(err);
		}

	private:
		void CreateFile() 
		{
			
		}

		bool ErrOn = true;
	};
}