#ifndef __YZ_FishKing__VORTEXLAYER_H
#define __YZ_FishKing__VORTEXLAYER_H

#include "cocos2d.h"
#include "3d/CCMesh.h"
#include "YZUIExport.h"
#include "YZBaseType.h"

USING_NS_CC;

namespace FishKing
{

//������ʾ��
class VortexLayer : public  YZ::YZLayer
{
	//����ṹ
	struct VortexVertexStruct
	{
		Vec3 Position;
		Vec2 TexUV;
	};

public:
	VortexLayer();
	~VortexLayer();
	//��ʼ����ǰ��
    virtual bool init();  
    CREATE_FUNC(VortexLayer);
	//������Ⱦ
	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
    // a selector callback
    void vortexCloseCallback(float dt);
public:
	//������ȾĿ���
	void setTargetLayer(Layer*	pLayer)
	{
		m_TargetLayer = pLayer;
		if(m_pTarget)
		{
			m_pTarget->addChild(m_TargetLayer);
		}
	}
	//������ת�ĽǶ�
	void setAngle( float f )
	{
		m_angle = f;
	}
	float getAngel() const
	{
		return m_angle;
	}
	//������ת�İ뾶
	void setRadius( float f )
	{
		m_radius = f;
	}
	float getRadius()
	{
		return m_radius;
	}

	float						m_angleSpeed;	//�Ƕ��ٶ�
	float						m_radiusSpeed;	//�뾶�ٶ�
	float						m_Time;			//��ǰʱ��
	float						m_maxTime;		//���ʱ��

private:

	float						m_angle;		//�Ƕ�
	float						m_radius;		//�뾶
	Mesh*						m_RenderMesh;	//��Ⱦģ��
	MeshCommand*				m_pMeshCommand;	//��Ⱦ����
	BlendFunc					m_BlendFunc;	//��Ⱦ״̬
    VortexVertexStruct*			m_VertexArray;	//���õ�ģ�Ͷ���
	GLushort*					m_IndiceArray;	//����
	GLProgramState*			    m_ProgramState;	//Shader������
	Layer*						m_TargetLayer;	//Ŀ��
    RenderTexture*				m_pTarget;		//��ȾĿ��
	timeval						m_lasttime;		//��¼�ϴ�ʱ��

	GLuint						m_vertexBuffer;
	GLuint						m_indexBuffer;
	GLenum						m_primitiveType;
	GLenum						m_indexFormat;
	ssize_t						m_indexCount;
	//RenderState::StateBlock*	m_stateBlock;

public:
	typedef std::function<void ()> CloseCallBack;
	CloseCallBack  onCloseCallBack;
};
}
#endif //__FishKing__VORTEXLAYER_H