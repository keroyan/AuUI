#pragma once
#include <vector>
#include <deque>
#include <any>
#include <shared_mutex>
#include "AuUI.h"

namespace AuUI 
{

	enum class EDrawType : int
	{
		NONE = 0,
		LINE,
	};

	struct LineObject_t
	{
		AuVec2 vecStart = {};
		AuVec2 vecEnd = {};
	
		float thickness = 0.f;
	};

	struct DrawObject_t
	{
		DrawObject_t(const EDrawType nType, std::any&& pObject) :
			nType(nType), pObject(std::move(pObject)) { }

		EDrawType nType = EDrawType::NONE;
		std::any pObject = {};
	};

	class Draw 
	{
	public:
		Draw(LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9 pD3Ddevice) :
			pD3D(pD3D), pD3Ddevice(pD3Ddevice)
		{}

		// Shall not be called from anywhere because it's already called from AuUI::Start()
		void RenderList(Window window);
		void AddLine();
		

	private:
		LPDIRECT3D9 pD3D;
		LPDIRECT3DDEVICE9 pD3Ddevice;
		std::deque<DrawObject_t> vecDrawData = {};
	    std::shared_mutex drawMutex = { };

	};
}