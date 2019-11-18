#pragma once

#include <google/protobuf/message.h>

typedef uint64_t USER_ID;
typedef uint32_t USER_HEAD_ID;

typedef uint32_t EVENT_TYPE;
typedef uint64_t EVENT_ID;
typedef uint64_t EVENT_DATA;
typedef uint32_t EVENT_TIME;
typedef std::string EVENT_STR_DATA;
typedef std::string EVENT_BIN_DATA;

typedef uint32_t ITEM_ID;
typedef uint32_t ITEM_CNT;

static const ITEM_CNT ITEM_CNT_MAX = UINT32_MAX;
static const uint32_t USER_EVENT_STR_DATA_LEN_MAX = 20480;
static const uint32_t USER_EVENT_BIN_DATA_LEN_MAX = 65535;
static const uint32_t NICK_LEN = 32;
static const uint32_t ACCOUNT_MAX_LEN = 64;

enum E_USER_LOGIN_STATUS
{
	E_USER_LOGIN_STATUS_CONNECTED = 1,   //已连接成功
	E_USER_LOGIN_STATUS_LOGINING = 2,	//验证登录中
										 //	E_USER_LOGIN_STATUS_APPROVED = 3,//通过身份校验
	E_USER_LOGIN_STATUS_CREATE_ROLE = 4, //创建角色
	E_USER_LOGIN_STATUS_COMPLETE = 5,	//登录完成
};

///////////////////////////////////////////////////////
//用户UID规划
///////////////////////////////////////////////////////
//玩家UID 最小起点,小于 MIN_UID 的都是AI
static const USER_ID MIN_UID = 10142857;
static const USER_ID MAX_UID = 73709551615;

//       1 00 00000000000
//          1 00000000000
//1 844674 40 73709551615
static const USER_ID USER_ID_PLATFORM = 10000000000000;

inline uint32_t g_gen_platform(USER_ID uid)
{
	return (uint32_t)(uid / USER_ID_PLATFORM);
}

#define GEN_UID(__platform__, __server_id__, __uid__) \
	((USER_ID)(__platform__)*USER_ID_PLATFORM + (USER_ID)(__server_id__)*100000000000 + (USER_ID)(__uid__))

inline bool g_is_robot(USER_ID uid)
{
	return uid < MIN_UID;
}

#define DEF_MSG_HANDLE_FUN(__HANDLE_CLASS__, __NAME__)                                                                      \
	class __HANDLE_CLASS__;                                                                                                 \
	typedef int (__HANDLE_CLASS__::*__NAME__##_MSG_HANDLE_FUN)(__NAME__##_MSG_HANDLE_FUN_PAR);                              \
	struct MSG_HANDLE_##__NAME__##_T                                                                                        \
	{                                                                                                                       \
		google::protobuf::Message *prototype;                                                                               \
		__NAME__##_MSG_HANDLE_FUN func;                                                                                     \
		bool is_callback;                                                                                                   \
		MSG_HANDLE_##__NAME__##_T()                                                                                         \
		{                                                                                                                   \
			this->prototype = NULL;                                                                                         \
			this->func = NULL;                                                                                              \
			this->is_callback = true;                                                                                       \
		}                                                                                                                   \
		MSG_HANDLE_##__NAME__##_T(google::protobuf::Message *proto, __NAME__##_MSG_HANDLE_FUN fun, bool is_callback = true) \
		{                                                                                                                   \
			this->prototype = proto;                                                                                        \
			this->func = fun;                                                                                               \
			this->is_callback = is_callback;                                                                                \
		}                                                                                                                   \
	};                                                                                                                      \
	typedef std::map<xr_server::PROTO_CMD, MSG_HANDLE_##__NAME__##_T> __NAME__##_MSG_MAP_T;
	