﻿/*****************************************************************************
Copyright (C), 2012-2100, ^^^^^^^^. Co., Ltd.
文 件 名:  Queue.h
作    者:  Herry  
版    本:  1.0
完成日期:  2012-9-13
说明信息:  带同步锁的标准队列
*****************************************************************************/
#pragma once

#include <deque>
#include <mutex>

template <class T>
class CQueue
{
public:
	CQueue(void)  {}
	~CQueue(void) {}

	//********************************************************************
	//函数功能: 往队列尾添加数据
	//第一参数: [IN] 添加的模板对象或指针
	//返回说明: 
	//备注说明: 
	//********************************************************************
	void Add(const T& item)
	{
		std::lock_guard<std::mutex> g(m_cLock);
		m_cQueue.push_back(item);
	}
	//********************************************************************
	//函数功能: 取出队列头的数据
	//第一参数: [OUT] 取出的模板对象或指针
	//返回说明: true  取出成功
	//返回说明: false 取出失败
	//备注说明: 如果锁定失败, 立即返回false
	//********************************************************************
	bool Next(T& result)
	{
		std::lock_guard<std::mutex> g(m_cLock);

		if (m_cQueue.empty())
		{
			return false;
		}
		result = m_cQueue.front();
		m_cQueue.pop_front();
		return true;
	}

	//********************************************************************
	//函数功能: 查看队列头的数据
	//第一参数:
	//返回说明: 
	//备注说明: 
	//********************************************************************
	T& Front(void)
	{
		std::lock_guard<std::mutex> g(m_cLock);
		T& result = m_cQueue.front();
		return result;
	}

	//********************************************************************
	//函数功能: 删除队头的数据
	//第一参数: 
	//返回说明: 
	//备注说明: 
	//********************************************************************
	void PopFront(void)
	{
		std::lock_guard<std::mutex> g(m_cLock);
		m_cQueue.pop_front();
	}

	//********************************************************************
	//函数功能: 检测是否为空队列
	//第一参数: 
	//返回说明: true  空队列
	//返回说明: false 非空队列
	//备注说明: 
	//********************************************************************
	bool IsEmpty(void)
	{
		std::lock_guard<std::mutex> g(m_cLock);
		return m_cQueue.empty();
	}

	//********************************************************************
	//函数功能: 清空队列
	//第一参数: 
	//返回说明:
	//备注说明: 
	//********************************************************************
	void Clear(void)
	{
		std::lock_guard<std::mutex> g(m_cLock);
		m_cQueue.clear();
	}

	//********************************************************************
	//函数功能: 活动队列元素个数
	//第一参数: 
	//返回说明:
	//备注说明: 
	//********************************************************************
	uint32 Size(void)
	{
		return (uint32)m_cQueue.size();
	}
private:
	std::mutex		m_cLock;
	std::deque<T>	m_cQueue;
};

