﻿#pragma once

#include "DebugModuleBPLibrary.h"

// 默认
DEFINE_LOG_CATEGORY_STATIC(WH_Default, Log, All);

// 编辑器
DEFINE_LOG_CATEGORY_STATIC(WH_Editor, Log, All);

// 控制器
DEFINE_LOG_CATEGORY_STATIC(WH_Controller, Log, All);

// 能力
DEFINE_LOG_CATEGORY_STATIC(WH_Ability, Log, All);

// 资源
DEFINE_LOG_CATEGORY_STATIC(WH_Asset, Log, All);

// 音频
DEFINE_LOG_CATEGORY_STATIC(WH_Audio, Log, All);

// 相机
DEFINE_LOG_CATEGORY_STATIC(WH_Camera, Log, All);

// 角色
DEFINE_LOG_CATEGORY_STATIC(WH_Character, Log, All);

// 事件
DEFINE_LOG_CATEGORY_STATIC(WH_Event, Log, All);

// 状态机
DEFINE_LOG_CATEGORY_STATIC(WH_FSM, Log, All);

// 输入
DEFINE_LOG_CATEGORY_STATIC(WH_Input, Log, All);

// 潜行任务
DEFINE_LOG_CATEGORY_STATIC(WH_LatentAction, Log, All);

// 媒体
DEFINE_LOG_CATEGORY_STATIC(WH_Media, Log, All);

// 网络
DEFINE_LOG_CATEGORY_STATIC(WH_Network, Log, All);

// 对象池
DEFINE_LOG_CATEGORY_STATIC(WH_ObjectPool, Log, All);

// 参数
DEFINE_LOG_CATEGORY_STATIC(WH_Parameter, Log, All);

// 流程
DEFINE_LOG_CATEGORY_STATIC(WH_Procedure, Log, All);

// 引用池
DEFINE_LOG_CATEGORY_STATIC(WH_ReferencePool, Log, All);

// 存档
DEFINE_LOG_CATEGORY_STATIC(WH_SaveGame, Log, All);

// 场景
DEFINE_LOG_CATEGORY_STATIC(WH_Scene, Log, All);

// 步骤
DEFINE_LOG_CATEGORY_STATIC(WH_Step, Log, All);

// 任务
DEFINE_LOG_CATEGORY_STATIC(WH_Task, Log, All);

// 体素
DEFINE_LOG_CATEGORY_STATIC(WH_Voxel, Log, All);

// Web请求
DEFINE_LOG_CATEGORY_STATIC(WH_WebRequest, Log, All);

// UI
DEFINE_LOG_CATEGORY_STATIC(WH_Widget, Log, All);

// 断言实现
#define WH_ENSURE_IMPL(Capture, InExpression, InFormat, ...) \
(LIKELY(!!(InExpression)) || (([Capture] () ->bool \
{ \
	static bool bExecuted = false; \
	if ((!bExecuted)) \
	{ \
		bExecuted = true; \
		FString Expr = #InExpression;\
		FString File = __FILE__;\
		int32 Line = __LINE__;\
		WH_LOG(LogTemp, Error, TEXT("WHFramework CRASH"));\
		WH_LOG(LogTemp, Error, TEXT("Expression : %s, %s, %d"), *Expr, *File, Line);\
		if(InFormat != TEXT("")) \
		{ \
			WH_LOG(LogTemp, Error, InFormat, ##__VA_ARGS__); \
		} \
	} \
	return false; \
})()))

// 用这两个断言, 代替多数仅需要在编辑器中进行判断的断言
#if WITH_EDITOR
	#define ensureEditor(InExpression) ensureAlways(InExpression)
	#define ensureEditorMsgf( InExpression, InFormat, ... ) ensureAlwaysMsgf( InExpression, InFormat, ##__VA_ARGS__)
#else
	#define ensureEditor(InExpression) WH_ENSURE_IMPL( , InExpression, TEXT(""))
	#define ensureEditorMsgf( InExpression, InFormat, ... ) WH_ENSURE_IMPL(&, InExpression, InFormat, ##__VA_ARGS__)
#endif

// 打印
#define WH_LOG(CategoryName, Verbosity, Format, ...) \
{ \
	UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__); \
}

/*
 * 打印日志
 * @param Message 消息内容
 * @param Category 调试类别
 * @param Verbosity 调试级别
 */
FORCEINLINE void WHLog(const FString& Message, EDebugCategory Category = EDC_Default, EDebugVerbosity Verbosity = EDV_Log)
{
	UDebugModuleBPLibrary::LogMessage(Message, Category, Verbosity);
}

/*
 * 输出调试信息
 * @param Message 调试内容
 * @param Mode 调试模式
 * @param Category 调试类别
 * @param Verbosity 调试级别
 * @param DisplayColor 显示颜色
 * @param Duration 持续时间
 * @param Key 调试ID
 * @param bNewerOnTop 不更新在顶部
 */
FORCEINLINE void WHDebug(const FString& Message, EDebugMode Mode = EDebugMode::Screen, EDebugCategory Category = EDC_Default, EDebugVerbosity Verbosity = EDV_Log, const FColor& DisplayColor = FColor::Cyan, float Duration = 1.5f, int32 Key = -1, bool bNewerOnTop = true)
{
	UDebugModuleBPLibrary::DebugMessage(Message, Mode, Category, Verbosity, DisplayColor, Duration, Key, bNewerOnTop);
}
