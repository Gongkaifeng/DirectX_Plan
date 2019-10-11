#pragma once
class CSprite
{
public:
	CSprite();
	~CSprite();
	virtual void Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);		// ��ʼ��
	virtual void Update();					// ���� �麯��
	virtual void Render();					// ���� �麯��

	bool	HitTest(RECT rc1, RECT rc2);	// ����������ײ
	void	Sort4(HITSTRUCT *List);			// ���ݽ�������

public:
	LPD3DXSPRITE		m_pSprite;		    // ͼƬ����
	LPDIRECT3DTEXTURE9  m_Texture;		    // ����

	RECT				m_rect;			    // ͼƬ��������
	D3DXVECTOR3			m_Pos;			    // Ŀ������
	D3DXVECTOR3			m_center;		    // ͼƬ����

	D3DXVECTOR3			m_vSpeed;		    // �ƶ��ٶ�����
	DWORD				m_Speed;			// �ƶ��ٶ�

	D3DXMATRIX			scaleMat;			// ����
	D3DXMATRIX			roteMat;			// ��ת
	D3DXMATRIX			transMat;			// ƽ��
	D3DXMATRIX			matMatrix;	        // �ۺϾ���
	float				m_angle;		    // ��ת�Ƕ�
	double				scaleX;				// x�������ű���
	double				scaleY;				// y�������ű���
	
};

