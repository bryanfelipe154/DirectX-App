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
	if (fProgress > 0.0f)
	{
		renderDevice->SetFVF(324);

		float iX = 50.0f;
		float iY = 50.0f;

		float iCX = 100.0f;
		float iCY = 100.0f;

		float fSX = (float)(iCX / 2.0f) + iX;
		float fSY = (float)(iCY / 2.0f) + iY;
		float fWidth = iCX / 2.0f;
		float fHeight = iCY / 2.0f;

		DWORD dwColor = 0xFF000000 | 0xFF1493;

		std::vector<RDTLVERTEX> vertex =
		{
			{ { fSX, fSY }, 0.0f, dwColor },
			{ { fSX, fSY - fHeight }, 0.0f, dwColor },
			{ { fSX + fWidth, fSY - fHeight }, 0.0f, dwColor },
			{ { fSX + fWidth, fSY }, 0.0f, dwColor },
			{ { fSX + fWidth, fSY + fHeight }, 0.0f, dwColor },
			{ { fSX, fSY + fHeight }, 0.0f, dwColor },
			{ { fSX - fWidth, fSY + fHeight }, 0.0f, dwColor },
			{ { fSX - fWidth, fSY }, 0.0f, dwColor },
			{ { fSX - fWidth, fSY - fHeight }, 0.0f, dwColor },
			{ { fSX, fSY - fHeight }, 0.0f, dwColor }
		};

		std::map<float, TMVector3> mapProgress =
		{
			{ 0.125f, { fSX + fWidth * (fProgress / 0.125f), fSY - fHeight} },
			{ 0.25f, { fSX + fWidth, fSY - fHeight + fHeight * ((fProgress - 0.125f) / 0.125f) } },
			{ 0.375f, { fSX + fWidth, fSY + fHeight * ((fProgress - 0.25f) / 0.125f) } },
			{ 0.5f, { fSX + fWidth - fWidth * ((fProgress - 0.375f) / 0.125f), fSY + fHeight} },//
			{ 0.625f, { fSX - fWidth * ((fProgress - 0.5f) / 0.125f), fSY + fHeight } },
			{ 0.75f, { fSX - fWidth, fSY + fHeight - fHeight * ((fProgress - 0.625f) / 0.125f) } },
			{ 0.875f, { fSX - fWidth, fSY - fHeight * ((fProgress - 0.75f) / 0.125f) } },
			{ 1.0f, { fSX - fWidth + fWidth * ((fProgress - 0.875f) / 0.125f), fSY - fHeight } }
		};

		//fProgress = 1.0f - fProgress; // quando faço isso, o progresso ele fica no sentido anti-horário e faz o que eu quero, 
		//que é iniciar preenchido e se desfazer durante o tempo, eu preciso fazer isso mas no sentido horario, no sentido horario
		//ele inicia vazio e vai se preenchendo

		for (const auto&& [i, it] : std::ranges::enumerate_view(mapProgress))
		{
			if (fProgress <= it.first)
			{
				vertex[i + 2].position = it.second;
				renderDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, i + 1, vertex.data(), sizeof(RDTLVERTEX));
				break;
			}
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
