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
		// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
		code = (UINT)*c;
#else
		// �}���`�o�C�g�����̏ꍇ�A
		// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
		// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
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

		//���_�o�b�t�@�ݒ�
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		//�e�N�X�`���ݒ�
		ID3D11ShaderResourceView* texture = textures[charCount];
		RendererManager::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		//�v���~�e�B�u�g�|���W�ݒ�
		RendererManager::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//�|���S���`��
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

		// �t�H���g�̐���
		LOGFONT lf = { fontSize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("�l�r �S�V�b�N") };
		HFONT hFont;
		if (!(hFont = CreateFontIndirect(&lf))) {
			LogWriter::Log("�t�H���g�𐳏�ɍ쐬�ł��܂���ł���");
			return;
		}

		// �f�o�C�X�R���e�L�X�g�擾
		// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
		HDC hdc = GetDC(NULL);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		// �����R�[�h�擾
		UINT code = 0;
		TCHAR* readChar = c + charCount;
#if _UNICODE
		// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
		code = (UINT)*c;
#else
		// �}���`�o�C�g�����̏ꍇ�A
		// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
		// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
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

		// �t�H���g�r�b�g�}�b�v�擾
		TEXTMETRIC TM;
		GetTextMetrics(hdc, &TM);
		GLYPHMETRICS GM;
		CONST MAT2 Mat = { {0,1}, {0,0}, {0,0}, {0,1} };
		DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
		BYTE* ptr = new BYTE[size];
		GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

		// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		ReleaseDC(NULL, hdc);

		//--------------------------------
		// �������݉\�e�N�X�`���쐬
		//--------------------------------

		// CPU�ŏ������݂��ł���e�N�X�`�����쐬���܂��B
		// ���O�Ńe�N�X�`���ɐF���������ꍇ�Ɏg���܂��B

		// �e�N�X�`���쐬
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.Width = GM.gmCellIncX;
		desc.Height = TM.tmHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)�^�C�v
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DYNAMIC;			// ���I�i�������݂��邽�߂̕K�{�����j
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// �V�F�[�_���\�[�X�Ƃ��Ďg��
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU����A�N�Z�X���ď�������OK

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

		// �e�N�X�`���ɏ�������
		// �e�N�X�`�����}�b�v�i�����b�N�j����ƁA
		// �������ɃA�N�Z�X���邽�߂̏��D3D10_MAPPED_TEXTURE2D�Ɋi�[����܂��B
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

		// �t�H���g���̏�������
		// iOfs_x, iOfs_y : �����o���ʒu(����)
		// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
		// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
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

		// ShaderResourceView�̏����쐬����
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

		// �V�F�[�_�p�ɃT���v�����쐬����
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
