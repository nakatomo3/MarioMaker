#include "Text.h"
#include "LogWriter.h"
#include "GameObject.h"

void Text::Draw() {

	layer = UI;
	if (_tcslen(c) == 0) {
		SetText("NewText");
	}
	Vector3 firstPos = position;

	bool existDrawChar = true;
	unsigned int charIndex = 0;
	unsigned int charCount = 0;
	while (existDrawChar == true) {

		TCHAR* readChar = c + charIndex;
#if _UNICODE
		// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
		code = (UINT)*c;
#else
		// マルチバイト文字の場合、
		// 1バイト文字のコードは1バイト目のUINT変換、
		// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
		if (IsDBCSLeadByte(*readChar)) {
			charIndex += 2;
		} else {
			charIndex++;
		}
#endif

		if (charIndex > strlen(c)) {
			existDrawChar = false;
			position = firstPos;
			return;
		}

		if (readChar[0] == (TCHAR)_T('\n')) {
			position = Vector3(firstPos.GetX(), position.GetY() + fontY[charCount] * scale, 0);
			charCount++;
			continue;
		}

		Vertex vertex[4];

		vertex[0].position = D3DXVECTOR3(position.GetX() + gameObject->GetPosition().GetX(), position.GetY() + gameObject->GetPosition().GetY(), 0.0f);
		vertex[0].normal = D3DXVECTOR3(0, 0, 0);
		vertex[0].diffuse = color;
		vertex[0].texUV = D3DXVECTOR2(0, 0);

		vertex[1].position = D3DXVECTOR3(position.GetX() + gameObject->GetPosition().GetX() + fontX[charCount] * scale, position.GetY() + gameObject->GetPosition().GetY(), 0.0f);
		vertex[1].normal = D3DXVECTOR3(0, 0, 0);
		vertex[1].diffuse = color;
		vertex[1].texUV = D3DXVECTOR2(1, 0);

		vertex[2].position = D3DXVECTOR3(position.GetX() + gameObject->GetPosition().GetX(), position.GetY() + gameObject->GetPosition().GetY() + fontY[charCount] * scale, 0.0f);
		vertex[2].normal = D3DXVECTOR3(0, 0, 0);
		vertex[2].diffuse = color;
		vertex[2].texUV = D3DXVECTOR2(0, 1);

		vertex[3].position = D3DXVECTOR3(position.GetX() + gameObject->GetPosition().GetX() + fontX[charCount] * scale, position.GetY() + gameObject->GetPosition().GetY() + fontY[charCount] * scale, 0.0f);
		vertex[3].normal = D3DXVECTOR3(0, 0, 0);
		vertex[3].diffuse = color;
		vertex[3].texUV = D3DXVECTOR2(1, 1);

		position += Vector3(fontX[charCount] * scale, 0);

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

		RendererManager::SetWorldViewProjection2D();

		//頂点バッファ設定
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		//テクスチャ設定
		ID3D11ShaderResourceView* texture = textures[charCount];
		RendererManager::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		//プリミティブトポロジ設定
		RendererManager::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//ポリゴン描画
		RendererManager::GetDeviceContext()->Draw(4, 0);

		wasChange = false;

		if (vertexBuffer != NULL) {				
			vertexBuffer->Release();
		}
		charCount++;
	}
}

void Text::CreateTexture() {
	for (unsigned int i = 0; i < textures.size(); i++) {
		if (textures[i] != nullptr) {
			textures[i]->Release();
		}
	}
	
	textures.clear();
	fontX.clear();
	fontY.clear();

	bool existDrawChar = true;
	unsigned int charCount = 0;
	while (existDrawChar == true) {

		// フォントの生成
		LOGFONT lf = { fontSize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("ＭＳ ゴシック") };
		HFONT hFont;
		if (!(hFont = CreateFontIndirect(&lf))) {
			LogWriter::Log("フォントを正常に作成できませんでした");
			return;
		}

		// デバイスコンテキスト取得
		// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
		HDC hdc = GetDC(NULL);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		// 文字コード取得
		UINT code = 0;
		TCHAR* readChar = c + charCount;
#if _UNICODE
		// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
		code = (UINT)*c;
#else
		// マルチバイト文字の場合、
		// 1バイト文字のコードは1バイト目のUINT変換、
		// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
		if (IsDBCSLeadByte(*readChar)) {
			code = (BYTE)readChar[0] << 8 | (BYTE)readChar[1];
			charCount += 2;
		} else {
			code = readChar[0];
			charCount++;
		}
#endif
		if (charCount > strlen(c)) {
			existDrawChar = false;
			return;
		}

		// フォントビットマップ取得
		TEXTMETRIC TM;
		GetTextMetrics(hdc, &TM);
		GLYPHMETRICS GM;
		CONST MAT2 Mat = { {0,1}, {0,0}, {0,0}, {0,1} };
		DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
		BYTE* ptr = new BYTE[size];
		GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

		// デバイスコンテキストとフォントハンドルの開放
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		ReleaseDC(NULL, hdc);

		//--------------------------------
		// 書き込み可能テクスチャ作成
		//--------------------------------

		// CPUで書き込みができるテクスチャを作成します。
		// 自前でテクスチャに色をつけたい場合に使えます。

		// テクスチャ作成
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.Width = GM.gmCellIncX;
		desc.Height = TM.tmHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)タイプ
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DYNAMIC;			// 動的（書き込みするための必須条件）
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// シェーダリソースとして使う
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUからアクセスして書き込みOK

		if (readChar[0] == (TCHAR)_T('\n')) {
			ID3D11ShaderResourceView* texture = NULL;
			textures.emplace_back(texture);
			fontX.emplace_back(desc.Width);
			fontY.emplace_back(desc.Height);
			continue;
		}

		ID3D11Texture2D** ppTexture = 0;

		RendererManager::GetDevice()->CreateTexture2D(&desc, 0, ppTexture);

		fontX.emplace_back(desc.Width);
		fontY.emplace_back(desc.Height);

		/*wh->x = (float)desc.Width;
		wh->y = (float)desc.Height;*/

		// テクスチャに書き込み
		// テクスチャをマップ（＝ロック）すると、
		// メモリにアクセスするための情報がD3D10_MAPPED_TEXTURE2Dに格納されます。
		D3D11_MAPPED_SUBRESOURCE mapped;
		ID3D11Texture2D* fontTexture = 0;
		RendererManager::GetDevice()->CreateTexture2D(&desc, NULL, &fontTexture);
		RendererManager::GetDeviceContext()->Map(
			fontTexture,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&mapped);

		BYTE* pBits = (BYTE*)mapped.pData;

		// フォント情報の書き込み
		// iOfs_x, iOfs_y : 書き出し位置(左上)
		// iBmp_w, iBmp_h : フォントビットマップの幅高
		// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
		int iOfs_x = GM.gmptGlyphOrigin.x;
		int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
		int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
		int iBmp_h = GM.gmBlackBoxY;
		int Level = 17;
		int x, y;
		DWORD Alpha, Color;
		memset(pBits, 0, mapped.RowPitch * TM.tmHeight);
		for (y = iOfs_y; y < iOfs_y + iBmp_h; y++)
			for (x = iOfs_x; x < iOfs_x + iBmp_w; x++) {
				Alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
				Color = 0x00ffffff | (Alpha << 24);
				memcpy((BYTE*)pBits + mapped.RowPitch * y + 4 * x, &Color, sizeof(DWORD));
			}

		RendererManager::GetDeviceContext()->Unmap(fontTexture, 0);

		delete[] ptr;

		// ShaderResourceViewの情報を作成する
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;

		ID3D11ShaderResourceView* texture = NULL;

		RendererManager::GetDevice()->CreateShaderResourceView(fontTexture, &srvDesc, &texture);
		textures.emplace_back(texture);
		fontTexture->Release();

		// シェーダ用にサンプラを作成する
		D3D11_SAMPLER_DESC samDesc;
		ZeroMemory(&samDesc, sizeof(samDesc));
		samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samDesc.MaxAnisotropy = 1;
		samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samDesc.MaxLOD = D3D11_FLOAT32_MAX;

		RendererManager::GetDevice()->CreateSamplerState(&samDesc, RendererManager::GetSampler());
	}
}

void Text::SetPosition(Vector3 newPos) {
	position = newPos;
}

Vector3 Text::GetPosition() {
	return position;
}

void Text::SetColor(D3DXVECTOR4 newColor) {
	color = newColor;
}

D3DXVECTOR4 Text::GetColor() {
	return color;
}

void Text::SetText(TCHAR * newText) {
	if (c != newText) {
		c = newText;
		CreateTexture();
		LogWriter::Log("Set:%x", c);
	}
}

void Text::SetText(const char * newText) {
	if (c != (TCHAR*)newText) {
		SetText((TCHAR*)newText);
	}
}

void Text::SetText(string newText) {
	if (c != (TCHAR*)(newText.c_str())) {
		SetText((TCHAR*)(newText.c_str()));
	}
}

TCHAR * Text::GetText() {
	return c;
}

void Text::SetFontSize(int _size) {
	fontSize = _size;
	CreateTexture();
}

int Text::GetFontSize() {
	return fontSize;
}

void Text::SetScale(float _scale) {
	scale = _scale;
}

float Text::GetScale() {
	return scale;
}

void Text::OnDestroy() {
	if (vertexBuffer != nullptr) {
		vertexBuffer->Release();
	}
	for (unsigned int i = 0; i < textures.size(); i++) {
		if (textures[i] != nullptr) {
			textures[i]->Release();
		}
	}
}
