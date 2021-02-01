#include "FishKingGameVortexLayer.h"
#include <vector>

using namespace std;

namespace FishKing
{

VortexLayer::VortexLayer()
	: m_angle(0.0f)
	, m_radius(0.0f)
	, m_TargetLayer(nullptr)
	, m_angleSpeed(1.5f)
	, m_radiusSpeed(0.5f)
	, m_Time(0.0f)
	, m_maxTime(2.0f)
	, m_pMeshCommand(nullptr)
	//, m_stateBlock(nullptr)
{

}
VortexLayer::~VortexLayer()
{
	CC_SAFE_DELETE(m_pMeshCommand);
	//CC_SAFE_DELETE(m_stateBlock);
	if(m_pTarget)
	{
		if(m_TargetLayer)
		{
			m_pTarget->removeChild(m_TargetLayer);
		}
		removeChild(m_pTarget);
	}
}

bool VortexLayer::init()
{
	scheduleOnce(schedule_selector(VortexLayer::vortexCloseCallback), 1.0f);

	gettimeofday( &m_lasttime, nullptr);

	m_BlendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

	// ȡ���ļ�������
	auto fileUtiles = FileUtils::getInstance();
	fileUtiles->addSearchPath("Games/fishKing/3D");
	// ������Ӧ��Shader�ļ�
    // ����Vortex.vsh��ȡ���ļ������ַ���
    auto vertexFilePath = fileUtiles->fullPathForFilename("Vortex.vsh");
    auto vertSource = fileUtiles->getStringFromFile(vertexFilePath);

    // ����Vortex.fsh��ȡ���ļ������ַ���
    auto fragmentFilePath = fileUtiles->fullPathForFilename("Vortex.fsh");
    auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);

	// ��vsh��fshװ���һ��������Shader�ļ���
    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
	glprogram->bindAttribLocation( "a_position", GLProgram::VERTEX_ATTRIB_POSITION);
    glprogram->bindAttribLocation( "a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);
	glprogram->link();
    glprogram->updateUniforms();

	// ��Shader�ļ��������Shader
    m_ProgramState = GLProgramState::getOrCreateWithGLProgram(glprogram);
	// �������������õ�Shader
    setGLProgramState(m_ProgramState);

	// ������ȾĿ������
	auto  WinSize  = Director::getInstance()->getWinSize();
	m_pTarget = RenderTexture::create(WinSize.width, WinSize.height, Texture2D::PixelFormat::RGBA8888);
	m_pTarget->setClearColor(Color4F(0, 0, 0, 0));
	m_pTarget->setVisible(false);
	addChild(m_pTarget);

	//�У�����
	int		cows = 100;
	int		rows = 100;
	//ÿһ�У��еĶ���λ��ƫ��
	float	vertexStepX = WinSize.width / cows;
	float	vertexStepY = WinSize.height / rows;
	//��һ�У��е���������ƫ��
	float	uStep = 1.0f / rows;
	float	vStep = 1.0f / cows;
	//���㣬���ߣ�ɫ�����������
	vector<float>	positions;
	vector<float>   normals;
	vector<float>   colors;
	vector<float>   texs;

	for (UINT x = 0; x <= cows; ++x )
	{
		for (UINT  y = 0; y <= rows; ++y )
		{
			UINT offset = x + y * ( cows + 1 );

			positions.push_back(x * vertexStepX);
			positions.push_back(y * vertexStepY);
			positions.push_back(10);

			texs.push_back(x * uStep);
			texs.push_back(y * vStep);
		}
	}
	std::vector<WORD> tTriangle;

	for (UINT x = 0; x < cows; ++x )
	{
		for (UINT y = 0; y < rows; ++y )
		{
			WORD* ptr = &(m_IndiceArray[(x+y * cows) * 6]);

			tTriangle.push_back((x+0) + (y+0) * (cows+1));
			tTriangle.push_back((x+0) + (y+1) * (cows+1));
			tTriangle.push_back((x+1) + (y+0) * (cows+1));


			tTriangle.push_back((x+0) + (y+1) * (cows+1));
			tTriangle.push_back((x+1) + (y+1) * (cows+1));
			tTriangle.push_back((x+1) + (y+0) * (cows+1));
		}
	}
	//����ģ��
	m_RenderMesh = Mesh::create(positions, normals, texs, tTriangle);
	m_RenderMesh->retain();

	m_vertexBuffer	= m_RenderMesh->getVertexBuffer();
	m_indexBuffer	= m_RenderMesh->getIndexBuffer();
	m_primitiveType = m_RenderMesh->getPrimitiveType();
	m_indexFormat	= m_RenderMesh->getIndexFormat();
	m_indexCount	= m_RenderMesh->getIndexCount();

	//���ö����ʽ
    long offset = 0;
    auto attributeCount = m_RenderMesh->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = m_RenderMesh->getMeshVertexAttribute(k);
        m_ProgramState->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                             meshattribute.size,
                                             meshattribute.type,
                                             GL_FALSE,
											 m_RenderMesh->getVertexSizeInBytes(),
                                             (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }

	return true;
}

void VortexLayer::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
	//�������ȾĿ��������ָ���Ľ����Ⱦ��Ŀ������
	if( m_pTarget && m_TargetLayer)
	{
		m_pTarget->clear(0, 0, 0, 0);
		m_pTarget->begin();
		m_TargetLayer->visit();
		m_pTarget->end();
	}

	//����ʱ����
	timeval		currtime;
	gettimeofday(&currtime, nullptr);
	float dt = (currtime.tv_sec - m_lasttime.tv_sec) + (currtime.tv_usec - m_lasttime.tv_usec) / 1000000.0f;

	if ( m_Time < m_maxTime )
	{
		setAngle( getAngel() + m_angleSpeed * dt );
		setRadius( getRadius() + m_radiusSpeed * dt );
		m_Time += dt;		
	}
	else
	{
		m_Time = 0.0f;
		setAngle( 0.0f );
		setRadius( 0.0f );
	}

	m_lasttime = currtime;

	/*CC_SAFE_DELETE(m_stateBlock);
	m_stateBlock = new RenderState::StateBlock();
	m_stateBlock->setCullFace(false);
	m_stateBlock->setDepthTest(false);*/

	//����Shader�Ĳ�����
	GLProgramState* programstate = getGLProgramState();

	programstate->setUniformFloat("radius", m_radius);
	programstate->setUniformFloat("angle", m_angle);
	programstate->setUniformTexture("u_texture", m_pTarget->getSprite()->getTexture());

	Color4F color(getDisplayedColor());
	color.a = getDisplayedOpacity() / 255.0f;

	//��Ҫ��Ⱦ����Ϣ������Ⱦ���С�
	GLuint textureID = m_pTarget->getSprite()->getTexture()->getName();
	CC_SAFE_DELETE(m_pMeshCommand);
    m_pMeshCommand = new MeshCommand();

	m_pMeshCommand->genMaterialID(textureID, 
		m_ProgramState, 
		m_vertexBuffer,
		m_indexBuffer,
		m_BlendFunc);

	/*m_pMeshCommand->init(_globalZOrder, 
		textureID,
		programstate,
		m_stateBlock,
		m_vertexBuffer,
		m_indexBuffer,
		m_primitiveType,
		m_indexFormat,
		m_indexCount,
		transform,
		flags);*/

	m_pMeshCommand->setDisplayColor(Vec4(color.r, color.g, color.b, color.a));
	Director::getInstance()->getRenderer()->addCommand(m_pMeshCommand);

	Node::draw(renderer, transform, flags);
}

void VortexLayer::vortexCloseCallback(float dt)
{
	auto colorLayer = LayerColor::create(Color4B(255, 255, 255, 0));
	addChild(colorLayer);

	colorLayer->runAction(FadeIn::create(1.0f));

	this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&]()
	{
		if (nullptr != onCloseCallBack)
		{
			onCloseCallBack();
		}
		this->removeFromParent();
	}), nullptr));
}
}