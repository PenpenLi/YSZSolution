//***************************************************************
// 类名：核心类管理器
// 作者：钟汶洁
// 日期：2013.6
// 功能：管理游戏中的核心类
//***************************************************************

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// 核心管理器
/// </summary>
public class KernelManager
{
    /// <summary>
    /// 
    /// </summary>
    private static KernelManager m_Instance;
    /// <summary>
    /// 挂载组件
    /// </summary>
    private GameObject m_Kernel;

    /// <summary>
    /// 构造
    /// </summary>
    public KernelManager()
    {
        if (m_Instance == null)
        {
            m_Instance = this;
            GameObject go = GameObject.Find("Kernel");
            if (go == null)
            {
                go = new GameObject("Kernel");
                m_Instance.m_Kernel = go;
                Object.DontDestroyOnLoad(go);
            }
        }
        else
        {
            Debug.LogError("KernelManager is created repeatly!");
        }
    }

    /// <summary>
    /// 单件
    /// </summary>
    /// <returns></returns>
    public static KernelManager Instance()
    {
        return m_Instance;
    }

    /// <summary>
    /// 添加一个核心
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <returns>核心实例</returns>
    public T AddKernel<T>() where T : MonoBehaviour
    {
        T t = m_Instance.m_Kernel.GetComponent<T>();
        if (t != null)
        {
            return t;
        }
        return m_Kernel.AddComponent<T>();
    }

    /// <summary>
    /// 删除一个核心 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public void DeleteKernel<T>() where T : MonoBehaviour
    {
        T t = m_Instance.m_Kernel.GetComponent<T>();
        if (t != null)
        {
            Object.Destroy(t);
        }
    }

    /// <summary>
    /// return: true 是；false 否
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <returns>是否已添加了一个类型的核心</returns>
    public bool IsKernelAdded<T>() where T : Kernel<T>
    {
        T t = m_Instance.m_Kernel.GetComponent<T>();
        if (t == null)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}
