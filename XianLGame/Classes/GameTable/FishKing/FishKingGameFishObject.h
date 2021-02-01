#ifndef __YZ_FishKing_FishFactory_H__
#define __YZ_FishKing_FishFactory_H__

#include "YZNetExport.h"
#include "YZUIExport.h"
#include "FishKingMessageHead.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>

using namespace ui;
using namespace std;
using namespace cocostudio;

USING_NS_CC;

namespace FishKing
{
	class Fish : public YZ::YZSprite
	{
		struct FishSpirteInfo
		{
			std::string name;
			BYTE	count;
			FLOAT	time;
		};

		FishSpirteInfo _fishName[26];

	public:
		typedef std::function<void (int fishId)> MoveOutCallBack;
		MoveOutCallBack  onMoveOutCallBack;

		typedef std::function<void (INT fishId)> UnLockCallBack;
		UnLockCallBack  onUnLockCallBack;
	public:
		static Fish* create(int fishId, FishKind fishKind, FishKind fishKind_ex[5]);
		virtual bool init();

		//������֡����ͼƬ��Ϣ
		void onRender();
		//�������ζ�֡����
		Animation* addFishData(FishSpirteInfo fish, BYTE kind);

	public:
		Fish(int fishId, FishKind fishKind, FishKind fishKind_ex[5]);
		~Fish();

	public:
		//������ͨ�㣨����0-25��
		void createNormalFish(BYTE fishKind);
		//�������Ǵ���Ԫ��
		void createDaSanYuanFish(BYTE fishKind);
		//����ֱ�ߴ���Ԫ��
		void createZXDaSanYuanFish(BYTE fishKind);
		//�����ĽǴ���ϲ��
		void createDaSixiFish(BYTE fishKind);		
		//����ֱ�ߴ���ϲ��
		void createZXDaSiXiFish(BYTE fishKind);
		//������ɫ����
		void createRedKingFish(BYTE fishKind);
		//���������̵�����
		void createPlatekingFish(BYTE fishKind);
		//���������������
		void playFishDieAction();

	public:		
		virtual void setPosition(const Vec2& pos) override;
		virtual void update(float dt) override;

	public:
		//������ʧ
		void setHide();
		//��������
		void refreshParams();
		//��������ζ�·��
		void setFishTraceList(std::vector<FPointAngle> fishTraceList, bool isUseFishTtrace);
		//�����ζ�����
		void playFishAction(std::vector<Vec2>* fishTrace, TraceType traceType, FLOAT speed);
		//�㰴������·���˶�
		void playFishActionByTraceList();
		//��������ζ�����(ֱ��/����������)
		FiniteTimeAction* getActionInThreePoint(Vec2 first, Vec2 second, Vec2 third, TraceType actionType = TRACE_LINEAR);
		//���㳱�е��㰴Ҫ��ֹͣǰ��
		void setFishStop(std::vector<FPointAngle>::size_type stop_index, std::vector<FPointAngle>::size_type stop_count);
		//��ȡ����������
		FishKind getFishKindEx();

	private:
		Size						_winSize;
		FiniteTimeAction*			_fishMoveAction;				//���˶��Ķ���
		std::vector<FPointAngle>	_fishTraceList;					//5�ֳ�������ͻ��˼������켣
		UINT						_FishTraceIndex;				//���н�����һ�������
		bool						_isDoUpdateFUNC;				//��Ϊpc��ÿ��30֡������60֡�����Կ���2֡����һ�Σ�Ϊ�˸�pcͬ��
		Vec2						_oldPosition;					//��һ�ο��Ƶ�����
		Vec2						_desPosition;					//���ε�����

		std::vector<FPointAngle>::size_type		_stop_index;
		std::vector<FPointAngle>::size_type		_stop_count;
		std::vector<FPointAngle>::size_type		_current_stop_count;

	private:
		CC_SYNTHESIZE(INT,			_fishID, FishID);				//���id���
		CC_SYNTHESIZE(FishKind,		_fishKind, FishKind);			//���������
		CC_SYNTHESIZE(Rect,			_fishRect, FishRect);			//��ľ���
		CC_SYNTHESIZE(Size,			_fishSize, FishSize);			//���SIZE
		CC_SYNTHESIZE(FLOAT,		_fishSpeed, FishSpeed);			//����˷��������ζ��ٶ�
		CC_SYNTHESIZE(bool,			_isTouch, CanTouch);			//���㻹�ܲ��ܱ��ӵ���
		CC_SYNTHESIZE(bool,			_isPause, PauseAction);			//���Ƿ���ͣ�ζ�����
		CC_SYNTHESIZE(bool,			_isUseFishTrace, UseFishTrace);	//�Ƿ�ʹ�÷����λ�ÿ���
		CC_SYNTHESIZE(bool,			_isSwitch, SwitchScene);		//�Ƿ������л�����
		CC_SYNTHESIZE(ImageView*,	_gameBG, GameBG);				//�л�����Ϸ����ͼ�������ڳ����л�ʱ������ײ����
		CC_SYNTHESIZE(bool,			_isLock, FishIsLock);			//�Ƿ��Ѿ�������

	public:
		FishKind					_fishKind_ex[5];				//������������
	};

}

#endif // __FishKing_FishFactory_H__
