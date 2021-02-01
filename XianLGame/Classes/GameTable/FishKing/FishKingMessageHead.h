#ifndef __FishKing_MessageHead_h__
#define __FishKing_MessageHead_h__

#include "YZNetExport.h"

namespace FishKing
{
//////////////////////////////////////////////////////////////////////////
//#define GAME_NAME             TEXT("��������")
//////////////////////////////////////////////////////////////////////////

enum FishKing_CONST
{
	GAME_NAME_ID			=			33003206,					//��Ϸ ID
	PLAY_COUNT			    =			6,							//��Ϸ����
	//GAME_PLAYER				=			8,

	//��Ϸ״̬
	GAME_STATUS_FREE		=			0,							//����״̬
	GAME_STATUS_PLAY		=			100,						//��Ϸ״̬
	GAME_STATUS_WAIT		=			200,						//�ȴ�״̬

	INVALID_FISHID			=			0,							//������id
};

const FLOAT kResolutionWidth = 1440;
const FLOAT kResolutionHeight = 900;

/*------------------------------------------------------------------------------*/
#define DEF_SCREEN_WIDTH	  1440			// Ĭ������
#define DEF_SCREEN_HEIGHT	  900			// Ĭ������

/*------------------------------------------------------------------------*/
//��Ϸ���ڴ�С
static float screen_width_	= DEF_SCREEN_WIDTH;
static float screen_height_ = DEF_SCREEN_HEIGHT;
//������ʾ����С
static int screen_width_PC	= DEF_SCREEN_WIDTH;
static int screen_height_PC = DEF_SCREEN_HEIGHT;

static	float g_hscale = 1.0f;
static	float g_vscale = 1.0f;
/*------------------------------------------------------------------------------*/
	
/*
#ifndef SCORE
#define SCORE __int64
#endif
*/

//#ifndef M_PI
//#define M_PI    3.14159265358979323846f
//#define M_PI_2  1.57079632679489661923f
//#define M_PI_4  0.785398163397448309616f
//#define M_1_PI  0.318309886183790671538f
//#define M_2_PI  0.636619772367581343076f
//#endif
//const float kChairDefaultAngle[GAME_PLAYER] = { M_PI, M_PI, M_PI, 0, 0, 0, -M_PI_2, M_PI_2 };

struct Position {
	float x;
	float y;
};

enum TraceType {
  TRACE_LINEAR = 0,
  TRACE_BEZIER
};

struct FPoint {
  float x;
  float y;
};

struct FPointAngle {
  float x;
  float y;
  float angle;
};

enum SceneStyle {
	SCENE_STYLE_1 = 0,
	SCENE_STYLE_2,
	SCENE_STYLE_3,

	SCENE_STYLE_COUNT
};

//////////////////////////////////////////////////////////////////////////
// ��Ϸ����
//////////////////////////////////////////////////////////////////////////

/*
// ��λ��
-------------
  0   1   2 
               
  5   4   3
-------------
*/

enum SceneKind {
  SCENE_KIND_1 = 0,
  SCENE_KIND_2,
  SCENE_KIND_3,
  SCENE_KIND_4,
  SCENE_KIND_5,

  SCENE_KIND_COUNT
};


enum FishKind 
{
	FISH_KIND_1 = 0 ,		//��ţ��
	FISH_KIND_2,			//�̲���
	FISH_KIND_3,			//�Ʋ���
	FISH_KIND_4,			//������
	FISH_KIND_5,			//�Ʊ���
	FISH_KIND_6,			//С����
	FISH_KIND_7,			//С����
	FISH_KIND_8,			//����
	FISH_KIND_9,			//�������
	FISH_KIND_10,			//�̵�����
	FISH_KIND_11,			//����
	FISH_KIND_12,			//������
	FISH_KIND_13,			//������
	FISH_KIND_14,			//��ȸ��
	FISH_KIND_15,			//����
	FISH_KIND_16,			//������
	FISH_KIND_17,			//������
	FISH_KIND_18,			//������
	FISH_KIND_19,			//�𹿰�
	FISH_KIND_20,			//������
	FISH_KIND_21,			//����
	FISH_KIND_22,			//����
	FISH_KIND_23,			//����
	FISH_KIND_24,			//ȫ��ը��
	FISH_KIND_25,			//��ɫ���
	FISH_KIND_26,			//˫ͷ��

	FISH_KIND_27,			//���Ǵ���Ԫ
	FISH_KIND_28,			//ֱ�ߴ���Ԫ
	FISH_KIND_29,			//�ĽǴ���ϲ
	FISH_KIND_30,			//ֱ�ߴ���ϲ

	FISH_KIND_31,			//����--����
	FISH_KIND_32,			//�����ӵ���-����
	FISH_KIND_COUNT
};

//��Ӧ�����ɵĽ������
enum Fish_Coin_Count
{
	FISH_1_COIN_COUNT = 2,
	FISH_2_COIN_COUNT = 3,
	FISH_3_COIN_COUNT = 4,
	FISH_4_COIN_COUNT = 5,
	FISH_5_COIN_COUNT = 6,
	FISH_6_COIN_COUNT = 7,
	FISH_7_COIN_COUNT = 8,
	FISH_8_COIN_COUNT = 9,
	FISH_9_COIN_COUNT = 10,
	FISH_10_COIN_COUNT = 11,
	FISH_11_COIN_COUNT = 12,
	FISH_12_COIN_COUNT = 13,
	FISH_13_COIN_COUNT = 14,
	FISH_14_COIN_COUNT = 15,
	FISH_15_COIN_COUNT = 16,
	FISH_16_COIN_COUNT = 17,
	FISH_17_COIN_COUNT = 18,
	FISH_18_COIN_COUNT = 19,
	FISH_19_COIN_COUNT = 20,
	FISH_20_COIN_COUNT = 21,
	FISH_21_COIN_COUNT = 22,
	FISH_22_COIN_COUNT = 23,
	FISH_23_COIN_COUNT = 24,
	FISH_24_COIN_COUNT = 25,
	FISH_25_COIN_COUNT = 26,
	FISH_26_COIN_COUNT = 27,
	FISH_27_COIN_COUNT = 28,
	FISH_28_COIN_COUNT = 29,
	FISH_29_COIN_COUNT = 30,
	FISH_30_COIN_COUNT = 31,
	FISH_31_COIN_COUNT = 32,
};

//����ָ���� ���ɶ��ٸ���Ҹ���
static unsigned int	G_Fish_Coin_Count[FISH_KIND_COUNT] = 
{
	FISH_1_COIN_COUNT,
	FISH_2_COIN_COUNT,
	FISH_3_COIN_COUNT,
	FISH_4_COIN_COUNT,
	FISH_5_COIN_COUNT,
	FISH_6_COIN_COUNT,
	FISH_7_COIN_COUNT,
	FISH_8_COIN_COUNT,
	FISH_9_COIN_COUNT,
	FISH_10_COIN_COUNT,
	FISH_11_COIN_COUNT,
	FISH_12_COIN_COUNT,
	FISH_13_COIN_COUNT,
	FISH_14_COIN_COUNT,
	FISH_15_COIN_COUNT,
	FISH_16_COIN_COUNT,
	FISH_17_COIN_COUNT,
	FISH_18_COIN_COUNT,
	FISH_19_COIN_COUNT,
	FISH_20_COIN_COUNT,
	FISH_21_COIN_COUNT,
	FISH_22_COIN_COUNT,
	FISH_23_COIN_COUNT,
	FISH_24_COIN_COUNT,
	FISH_25_COIN_COUNT,
	FISH_26_COIN_COUNT,
	FISH_27_COIN_COUNT,
	FISH_28_COIN_COUNT,
	FISH_29_COIN_COUNT,
	FISH_30_COIN_COUNT,
	FISH_31_COIN_COUNT,
};

//������������
static	int G_Fish_Circle_Count[FISH_KIND_COUNT] = {60,60,50,35,30,35,30,25,20,20,10,8,0,0,0,0,0,0,0,0,0,};

enum BulletKind 
{
  BULLET_KIND_1_NORMAL = 0,
  BULLET_KIND_2_NORMAL,
  BULLET_KIND_3_NORMAL,
  BULLET_KIND_4_NORMAL,
  BULLET_KIND_1_ION,
  BULLET_KIND_2_ION,
  BULLET_KIND_3_ION,
  BULLET_KIND_4_ION,

  BULLET_KIND_COUNT
};

const INT kMaxCatchFishCount = 2;

#pragma pack(1)

struct CMD_S_GameStatus 
{
  UINT 						game_version;
  SceneStyle				Scene_Style_Kind;					//��������ID
  INT						iUserFireBase[8];			//����ڻ���
  INT	                    iUserFireCell;
  LLONG 					fish_score[8];			//������Ͻ����
  LLONG 					exchange_fish_score[8];	//������϶һ������������Ϸûʲô��
};

struct CMD_S_GameConfig 
{
	INT 						exchange_ratio_userscore;
	INT 						exchange_ratio_fishscore;
	INT 						exchange_count;

	INT 						min_bullet_multiple;
	INT 						max_bullet_multiple;

	INT 						bomb_range_width;
	INT 						bomb_range_height;

	INT 						fish_multiple[FISH_KIND_COUNT];
	INT 						fish_speed[FISH_KIND_COUNT];
	INT 						fish_bounding_box_width[FISH_KIND_COUNT];
	INT 						fish_bounding_box_height[FISH_KIND_COUNT];
	INT 						fish_hit_radius[FISH_KIND_COUNT];

	INT 						bullet_speed[BULLET_KIND_COUNT];
	INT 						net_radius[BULLET_KIND_COUNT];
};

struct GameStation//�����ػ��õ����ݰ�sdp
{
	//��Ϸ�汾
	BYTE					iVersion;						//��Ϸ�汾��
	BYTE					iVersion2;						//��Ϸ�汾��
	BYTE					game_status;					//״̬��ʶ

	CMD_S_GameStatus		GameStatus;						//״̬����
	CMD_S_GameConfig		GameConfig;						//��������

	BYTE GameMessage[260];//��Ϸ��Ϣ
};

//��ҽ���  ��Ҫ�ǰ���ҵĽ�������͹���
struct CMD_S_GameUserCome
{
	UINT					dwDeskStation;
	LLONG 					i64fish_score;

	CMD_S_GameUserCome()
	{
		memset(this, 0, sizeof(CMD_S_GameUserCome));
		dwDeskStation = 255;
	}
};

struct CMD_S_FishTrace 
{
	FPoint 					init_pos[5];
	INT 					init_count;
	FishKind 				fish_kind;			//���������
	FishKind 				fish_kind_ex[5];	//��ĸ������� 
	INT 					fish_id;
	TraceType 				trace_type;

	void init()
	{
		memset(this, 0, sizeof(CMD_S_FishTrace));
	}
};

struct	CMD_S_CirleFishGroup
{
	bool					bHave;
	FishKind				iFishKind;
	INT						iIndex;
	INT						iCount;
	INT						iRedIndex;
	INT						iRedIndexIndex;

	CMD_S_CirleFishGroup()
	{
		bHave = false;
		iCount = 0;
		iFishKind = FISH_KIND_COUNT;
		iIndex = -1;
		iRedIndex = 0;
		iRedIndexIndex = 0;
	}
};

struct CMD_S_ExchangeFishScore 
{
	WORD 					chair_id;
	LLONG 					swap_fish_score;//��ǰ���ʵ������� ����������
	LLONG 					exchange_fish_score;
};

struct CMD_S_UserFire 
{
	BulletKind 				bullet_kind;			//�ӵ�����
	INT 					bullet_id;				//�ӵ�id
	WORD 					chair_id;				//��λ��
	WORD 					android_chairid;		//��������λ��
	FLOAT 					angle;					//���ڽǶ�
	INT 					bullet_mulriple;		//�ڻ���
	INT 					lock_fishid;			//�������id
	LLONG 					fish_score;				//��Ľ������
	bool 					bIsRobot;				//�Ƿ������

	CMD_S_UserFire()
	{
		memset(this, 0, sizeof(CMD_S_UserFire));
	}
};

struct CMD_S_CatchFish 
{
	WORD 					chair_id;			//��λ��
	INT 					fish_id;			//��id
	FishKind 				fish_kind;			//������
	bool 					bullet_ion;			//�Ƿ�������
	LLONG 					fish_score;			//�����㽱�����
	LLONG					i64UserFishScore_;	//��������ܽ��
};

struct CMD_S_BulletIonTimeout 
{
	WORD 					chair_id;
};

struct CMD_S_CatchSweepFish 
{
	BYTE					byIndex;
	WORD 					chair_id;
	INT 					fish_id;
	LLONG 					i64FishSocre;
	CMD_S_CatchSweepFish()
	{
		memset(this,0,sizeof(CMD_S_CatchSweepFish));
	}	
};

struct CMD_S_CatchSweepFishResult 
{
	WORD					chair_id;
	INT						fish_id;
	INT						catch_fish_count;
	INT						catch_fish_id[200];
	INT						fish_score[200];
	LLONG					fish_score_Sum;
	LLONG					i64UserFishScore_;
};

struct CMD_S_CatchSweepFishResultEx 
{
	CHAR    				cRoomName[61];				//��������
	INT						exchange_ratio_userscore_;	//����������û����
	INT						exchange_ratio_fishscore_;	//������������
	INT						iDeskID;					//����ID
	CHAR					szNickName[61]; 			//�ǳ�
	INT						fish_kind;					//������ID
	LLONG					fish_score;					//������׬����Ǯ
	CHAR    				cFishName[260];				//�������
};

struct CMD_S_HitFishLK 
{
	WORD 					chair_id;
	INT 					fish_id;
	INT 					fish_mulriple;
};

struct CMD_S_SwitchScene 
{
	SceneKind 				scene_kind;
	SceneStyle				Scene_Style;	//����ID
	INT 					fish_count;
	INT 					fish_id[245];
	FishKind 				fish_kindEx[10];
	FishKind 				fish_kind[245];

	CMD_S_SwitchScene()
	{
		memset(this, 0x0, sizeof(CMD_S_SwitchScene));
	}
};

struct CMD_S_GroupFishTrace
{
	BYTE 					byIndex;
	INT 					fish_count;
	FishKind 				fish_kind[250];
	FishKind 				fish_red_kind[5];		//������Ǻ�ɫ����
	INT 					fish_id[250];
};

struct CMD_C_ExchangeFishScore 
{
	bool increase;
};

struct CMD_C_UserFire 
{
	BulletKind 				bullet_kind;
	FLOAT 					angle;
	INT 					bullet_mulriple;
	INT 					lock_fishid;
	INT 					bullet_id;
	bool 					bIsRobot;

	CMD_C_UserFire()
	{
		memset(this, 0, sizeof(CMD_C_UserFire));
	}
};

struct CMD_C_CatchFish 
{
	WORD 					chair_id;
	INT 					fish_id;
	BulletKind 				bullet_kind;
	INT 					bullet_id;
	INT 					bullet_mulriple;
};

struct CMD_C_CatchSweepFish 
{
	WORD 					chair_id;
	INT 					fish_id;
	INT 					catch_fish_count;
	INT 					catch_fish_id[300];

	CMD_C_CatchSweepFish()
	{
		memset(this, 0, sizeof(CMD_C_CatchSweepFish));
	}
};

struct CMD_C_HitFishLK
{
	INT 					fish_id;
};



struct CMD_C_Fish20Config 
{
	UINT 					game_id;
	INT 					catch_count;
	double 					catch_probability;
};

struct CMD_C_AndroidBulletMul 
{
	WORD					chair_id;
	INT						bullet_id;
	INT						bullet_mulriple;
	BulletKind				bullet_kind;
};

//��������
struct CMD_C_LineInfo
{
	FPoint	fpStart;
	FPoint	fpEnd;
	FLOAT	fChange;
	UINT	dwTime;
	
	CMD_C_LineInfo()
	{
		memset(this, 0, sizeof(CMD_C_LineInfo));
	}
};


/////////////////////////////////////////////////////////////////////////////
//���˿���
/////////////////////////////////////////////////////////////////////////////

//���ز������
struct CMD_S_StockOperateResult		
{
	BYTE 					operate_code;	//	0��ѯ 1 ��� 2 ���� 3 ��ѯ��ˮ
	LLONG 					stock_score;	//	�������
};

//���ز���
struct CMD_C_StockOperate 
{
	BYTE 					operate_code;	// 0��ѯ 1 ��� 2 ���� 3 ��ѯ��ˮ
};

struct CMD_C_UserFilter
{
	UINT 					game_id;
	BYTE 					operate_code;	// 0 ������ 1 ������ 2 ���
};

struct S_C_SUPER_CONFIG
{
	bool bSuperUser;
};

//���������Ϣ
struct OnLineUserInfo
{
	BYTE	deskNo;
	char	nickName[61];
	int		i64UserMoney;
	UINT	userID;
	OnLineUserInfo()
	{
		memset(this, 0, sizeof(OnLineUserInfo));
	}
};

struct S_C_SWITCH_INFO
{
	bool special_switch_;				//��������ƿ���
	bool control_switch_;				//��Ҹ��ʿ��ƿ���
	S_C_SWITCH_INFO()
	{
		memset(this, 0, sizeof(S_C_SWITCH_INFO));
	}
};


struct S_C_FISH_NAME
{
	BYTE	byFishKind;
	char	cFishName[4][260];
};

struct S_C_ON_LINE_USER
{	
	bool	bStart;
	OnLineUserInfo user_info_;
	S_C_ON_LINE_USER()
	{
		memset(this, 0, sizeof(S_C_ON_LINE_USER));
	}
};

struct SpecialFish
{
	BYTE fish_kind_;					//������
	int left_num_;						//ʣ������
	int catch_rate_;					//ץ������
	SpecialFish()
	{
		memset(this, 0, sizeof(SpecialFish));
	}
};

struct SpecialUser
{
	SpecialFish special_fish_[4];		//�ܿص���
	int user_id_;						//�ܿص����id
	SpecialUser()
	{
		memset(this, 0, sizeof(SpecialUser));
		user_id_ = -1;
	}
};

struct ControlInfo
{
	bool win_or_lose_;					//�������Ӯ����
	int user_id_;						//�ܿ����id
	int catch_rate_;					//��Ӯ����
	LLONG limit_score_;					//��Ӯ����
	ControlInfo()
	{
		memset(this, 0, sizeof(ControlInfo));
		user_id_ = -1;
	}
};

struct C_S_DELETE_CONTROL_INFO 
{
	int user_id_;
};

struct C_S_ADD_SPECIAL
{
	BYTE fish_kind_;					//������
	int user_id_;						//���id
	int left_num_;						//ʣ������
	int catch_rate_;					//ץ������

	C_S_ADD_SPECIAL()
	{
		memset(this,0,sizeof(C_S_ADD_SPECIAL));
	}
};

struct C_S_DELETE_SPECIAL
{
	int user_id_;
	int fish_kind_;
	C_S_DELETE_SPECIAL()
	{
		memset(this,0,sizeof(C_S_DELETE_SPECIAL));
	}
};

//���¿��������Ϣ
struct S_C_UPDATE_CONTROL_INFO
{
	ControlInfo control_infos_[40];
	S_C_UPDATE_CONTROL_INFO()
	{
		memset(this, 0, sizeof(S_C_UPDATE_CONTROL_INFO));
	}
};

//���������������Ϣ
struct S_C_UPDATE_SPECIAL_INFO
{
	SpecialUser special_infos_[20];
	S_C_UPDATE_SPECIAL_INFO()
	{
		memset(this, 0, sizeof(S_C_UPDATE_SPECIAL_INFO));
	}
};

/////////////////////////////////////////////////////////////////////////

#pragma pack()

enum FishKing_COMMAND
{		
//////////////////////////////////////////////////////////////////////////
// ���������
//////////////////////////////////////////////////////////////////////////
	SUB_S_GAME_CONFIG                  = 100,//������Ϸ����
	SUB_S_FISH_TRACE                   = 101,//��������Ĺ켣
	SUB_S_FISH_GROUP_TRACE             = 102,//������Ⱥ�Ĺ켣
	SUB_S_EXCHANGE_FISHSCORE           = 103,//�һ���ң������ͷ��Ϸ��Ч��
	SUB_S_USER_FIRE                    = 104,//������
	SUB_S_CATCH_FISH                   = 105,//ץ����
	SUB_S_BULLET_ION_TIMEOUT           = 106,//������ʧЧ
	SUB_S_LOCK_TIMEOUT                 = 107,//����ը��ʧЧʱ��
	SUB_S_CATCH_SWEEP_FISH             = 108,//ץ�������㣨ը����������
	SUB_S_CATCH_SWEEP_FISH_RESULT      = 109,//ץ����������
	SUB_S_HIT_FISH_LK                  = 110,//�������ӣ������ͷ��Ϸ��Ч��
	SUB_S_SWITCH_SCENE                 = 111,//�л�������5������
	SUB_S_STOCK_OPERATE_RESULT         = 112,//��ѯ��棬��ˮ
	SUB_S_SCENE_END                    = 113,//�����л�����
	SUB_S_GAMEOUT					   = 114,//�����ǿ���ÿͻ����˳�
	SUB_S_CATCH_SWEEP_FISH_RESULT_EX   = 115,//�㲥֪ͨ������Ҳ�������

	SUB_S_USER_COME	                   = 120,//��ҽ���

	S_C_UPDATE_CONTROL_INFO_SIG		   = 121,//���¿��Ƹ�����Ϣ
	S_C_UPDATE_SPECIAL_INFO_SIG		   = 122,//���¿�����������Ϣ
	S_C_UPDATE_ONLINEUSER_INFO_SIG	   = 123,//�������������Ϣ
	S_C_SWITCH_INFO_SIG				   = 124,//���ƿ�����Ϣ
	S_C_UPDATE_FISH_NAME_SIG		   = 125,//���¿ɿ���������
	S_C_SUPER_CONFIG_SIG			   = 126,//�Ƿ񳬶����
	S_C_END_UPDATE_ONLINEUSER_INFO_SIG = 127,//�������������Ϣ�б�
	
//////////////////////////////////////////////////////////////////////////
// �ͻ�������
//////////////////////////////////////////////////////////////////////////
	SUB_C_EXCHANGE_FISHSCORE           = 1, //�һ���ң������ͷ��Ϸ��Ч��
	SUB_C_USER_FIRE                    = 2, //��ҿ���
	SUB_C_CATCH_FISH                   = 3, //�ӵ�������
	SUB_C_CATCH_SWEEP_FISH             = 4, //���������㣬���浱ǰ��Ļ������Ϣ
	SUB_C_HIT_FISH_I                   = 5, //�������ӣ������ͷ��Ϸ��Ч��
	SUB_C_STOCK_OPERATE                = 6, //��ѯ��棬��ˮ
	SUB_C_USER_FILTER                  = 7, //����
	SUB_C_ANDROID_STAND_UP             = 8, //������վ�������ͷ��Ϸ��Ч��
	SUB_C_FISH20_CONFIG                = 9, //�ϰ泬�˿��ƣ������ͷ��Ϸ��Ч��
	SUB_C_ANDROID_BULLET_MUL           = 10,//�������ӵ���Ŀ�������ͷ��Ϸ��Ч��

	C_S_UPDATE_SUPER_INFO_SIG		   = 11,//����������Ϣ
	C_S_ADD_CONTROL_INFO_SIG		   = 12,//��Ӹ��ʿ�������
	C_S_DELETE_CONTROL_INFO_SIG		   = 13,//ɾ�����ʿ�������
	C_S_ADD_SPECIAL_SIG				   = 14,//������������
	C_S_DELETE_SPECIAL_SIG			   = 15,//ɾ�����������
	C_S_SWITCH_CONTROL_SIG		       = 16,//���ʿ�����������
	C_S_SWITCH_SPECIAL_SIG			   = 17,//�����������������
};

};

#endif // CMD_FISH_H_