#include "framework.h"

struct TMVector3
{
	float x;
	float y;
	float z;
};

struct RDTLVERTEX
{
	TMVector3 position;
	float rhw;
	unsigned int diffuse;
	float tu;
	float tv;
};

void RenderRectProgress(float fProgress, LPDIRECT3DDEVICE9 renderDevice)
{
	if (fProgress < 1.0f)
	{
		//fProgress = 1.0f - fProgress; // todo: inverte o processo, funciona do jeito que tem que ser, criando o retangulo preenchido e desfazendo ele
		// porem esta no sentido anti horario, isso tem que ser feito no sentido horario

		renderDevice->SetFVF(324);

		float iX = 50.0f;
		float iY = 50.0f;

		float iCX = 100.0f;
		float iCY = 100.0f;

		DWORD dwColor = 0xFF000000 | 0xFF1493;

		float fSX = (float)(iCX / 2.0f) + iX;
		float fSY = (float)(iCY / 2.0f) + iY;
		float fWidth = iCX / 2.0f;
		float fHeight = iCY / 2.0f;

		RDTLVERTEX vertex[10];

		std::fill(std::begin(vertex), std::end(vertex), RDTLVERTEX{ .diffuse = dwColor });

		vertex[0].position = { fSX, fSY };
		vertex[1].position = { fSX, fSY - fHeight };
		vertex[2].position = { fSX + fWidth, fSY - fHeight };
		vertex[3].position = { fSX + fWidth, fSY };
		vertex[4].position = { fSX + fWidth, fSY + fHeight };
		vertex[5].position = { fSX, fSY + fHeight };
		vertex[6].position = { fSX - fWidth, fSY + fHeight };
		vertex[7].position = { fSX - fWidth, fSY };
		vertex[8].position = { fSX - fWidth, fSY - fHeight };

		if (fProgress <= 0.125f)
		{
			vertex[2].position = { fSX + fWidth * (fProgress / 0.125f), fSY - fHeight };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 1u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 0.25f)
		{
			vertex[3].position = { fSX + fWidth, fSY - fHeight + fHeight * ((fProgress - 0.125f) / 0.125f) };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 0.375f)
		{
			vertex[4].position = { fSX + fWidth, fSY + fHeight * ((fProgress - 0.25f) / 0.125f) };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 3u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 0.5f)
		{
			vertex[5].position = { fSX + fWidth - fWidth * ((fProgress - 0.375f) / 0.125f), fSY + fHeight };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 4u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 0.625f)
		{
			vertex[6].position = { fSX - fWidth * ((fProgress - 0.5f) / 0.125f), fSY + fHeight };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 5u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 0.75f)
		{
			vertex[7].position = { fSX - fWidth, fSY + fHeight - fHeight * ((fProgress - 0.625f) / 0.125f) };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 6u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 0.875f)
		{
			vertex[8].position = { fSX - fWidth, fSY - fHeight * ((fProgress - 0.75f) / 0.125f) };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 7u, vertex, sizeof(RDTLVERTEX));
		}
		else if (fProgress <= 1.0f)
		{
			vertex[9].position = { fSX - fWidth + fWidth * ((fProgress - 0.875f) / 0.125f), fSY - fHeight };
			renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 8u, vertex, sizeof(RDTLVERTEX));
		}
	}
}

void update()
{
	static auto startTime = timeGetTime();

	int totalTime = 2;

	unsigned int dwSub = timeGetTime() - startTime;

	float fProgress = (float)dwSub / ((float)totalTime * 1000.0f);
	if (fProgress > 1.0f)
	{
		fProgress = 0.0f;
		startTime = timeGetTime();
	}

	RenderRectProgress(fProgress, d3ddev);
}