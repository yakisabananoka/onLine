#pragma once
#include <string>

namespace SceneArgsStruct
{
	struct BaseArgs
	{
		//型統一用
		BaseArgs(bool sBgmFlg = true) :stopBGMFlg(sBgmFlg) {};
		bool stopBGMFlg;
	};

	struct TitleArgs:
		public BaseArgs
	{
		//なし
	};

	struct OptionArgs :
		public BaseArgs
	{
		//なし
	};

	struct TutorialCheckArgs :
		public BaseArgs
	{
		//なし
	};

	struct SelectArgs :
		public BaseArgs
	{
		//なし
	};

	struct GameArgs:
		public BaseArgs
	{
		GameArgs(std::string mapFilePath, bool sBgmFlg = false, bool menuFlg = true) :
			BaseArgs(sBgmFlg), mapfilePath_(mapFilePath), menuFlg_(menuFlg) {};
		std::string mapfilePath_;
		bool menuFlg_;
	};

	struct ResultArgs:
		public BaseArgs
	{
		ResultArgs(double cntTime, double totalLineDist) :
			cntTime_(cntTime), totalLineDist_(totalLineDist) {};
		double cntTime_;
		double totalLineDist_;
	};

	namespace Transition
	{
		struct TransitionArgs:
			public BaseArgs
		{
			TransitionArgs(bool sBgmFlg = false) :BaseArgs(sBgmFlg) {};
		};

		struct CrossOverArgs :
			public TransitionArgs
		{
		};

		struct FadeIOArgs :
			public TransitionArgs
		{
		};

		struct FadeMArgs :
			public TransitionArgs
		{
			FadeMArgs(std::string imagePath) :fadeImagePath(imagePath) {};
			std::string fadeImagePath;
		};

		struct SquareArgs :
			public TransitionArgs
		{
		};

		struct FillLineArgs :
			public TransitionArgs
		{
		};
	}

	namespace Temporary
	{
		struct TemporaryArgs:
			public BaseArgs
		{
			TemporaryArgs(bool sBgmFlg = false) :BaseArgs(sBgmFlg) {};
		};

		struct PlayMenuArgs :
			public TemporaryArgs
		{
		};

		struct HowToPlayArgs :
			public TemporaryArgs
		{
		};

		struct OptionMenuArgs :
			public TemporaryArgs
		{
		};
	}

}
