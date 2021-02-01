#ifndef __FishKing_FISH_MANAGER_H__
#define __FishKing_FISH_MANAGER_H__

#include "FishKingGameFishObject.h"
#include "FishKingMessageHead.h"

namespace FishKing
{
	static const float groupFishSpeed = 3.0f;

	class GameTableUI;

	typedef struct  tagFishSpirteInfo
	{
		std::string name;
		BYTE count;			
		BYTE dieCount;
	}T_FISHSPRITEINFO;

	enum LockType
	{
		NORMAL = 0,
		REDFISH,
		BIGFISH
	};

	class GameFishManager
	{
	public:
		typedef std::function<void (INT fishId)> LockFishCallBack;
		LockFishCallBack  onLockFishCallBack;

		typedef std::function<void (INT fishId)> UnLockCallBack;
		UnLockCallBack  unLockFishCallBack;

	public:
		GameFishManager(GameTableUI* gameTableUI);
		~GameFishManager();

		//�����
		Fish* addFish(FishKind fishKind, int fishId, std::vector<Vec2>* initPos, std::vector<FPointAngle> fishTraceList, 
			FishKind fishKind_ex[5], TraceType type = TRACE_LINEAR, bool isGroup = false);

		//��������������
		void setConfig(CMD_S_GameConfig* pcene);
		//�����л�
		void setSwitchScene(ImageView* gameBg, bool bSwitch);
		//��ͣ�������˶�
		void setAllFishIsPause(bool isPause = false);
		//����������
		void setLockFish(Vec2 pos, LockType type);

		//ͨ��id��ȡһ����
		Fish* getFishById(int id);
		//ͨ��id��ȡһ����
		Vector<Fish*> getFishListById(int id);
		//ͨ��kind��ȡһ����
		Vector<Fish*> getFishListByKind(int kind);
		//ͨ��id��ȡ���λ��
		Vec2 getFishPositionByFishId(INT fishId);

		//ץ������ʱ������ǰ��Ļ��Ϣ
		CMD_C_CatchSweepFish catchSweepFish(WORD chairId, int fishId);
		//�Ƴ�������ʾ������
		void removeOrSetFishDieById(INT fishId, bool bDied);

	private:
		void init();

	private:
		GameTableUI*		_gameTableUI;
		INT					_fishMultiple[FISH_KIND_COUNT];
		INT					_fishSpeed[FISH_KIND_COUNT + 1];
		Size				_fishSize[FISH_KIND_COUNT];
		INT 				_fishHitRadius[FISH_KIND_COUNT];
		bool				_isSwitch;

	public:
		//��ǰ���б�
		std::vector<Fish*>	_fishList;
		//�����������id�б�
		std::vector<int>	_lockFishIdList;		

	};

}

#endif // !__FISH_MANAGER_H__

