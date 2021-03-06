#ifndef SKIN_LISTCTRL_HEAD_FILE
#define SKIN_LISTCTRL_HEAD_FILE

#pragma once

#include "SkinUI.h"
#include "ISkinControl.h"

//////////////////////////////////////////////////////////////////////////////////

//排序位置
#define SORT_AFTER					1									//后面位置
#define SORT_FRONT					-1									//前面位置

//////////////////////////////////////////////////////////////////////////////////
//枚举定义

//排序类型
enum enSortType
{
	SortType_NoSort,				//没有排序
	SortType_Ascend,				//升序排序
	SortType_Descale,				//降序排序
};

//////////////////////////////////////////////////////////////////////////////////

//列头控件
class SKINUI_CLASS CSkinHeaderCtrl : public CHeaderCtrl,public ISkinControl
{
	//锁定列表
protected:
	UINT							m_uLockCount;						//锁定数目
	UINT							m_uItemHeight;						//子项高度
	UINT							m_uActiveItem;						//
	bool							m_bPress;

	//资源定义
public:
	CImageEx * m_pBackImg, * m_pPressImg, *m_pGridImg;

	//函数定义
public:
	//构造函数
	CSkinHeaderCtrl();
	//析构函数
	virtual ~CSkinHeaderCtrl();

	//资源加载
public:
	//设置资源
	BOOL SetBackImage(LPCTSTR lpNormal,CONST LPRECT lprcNinePart=NULL);
	//设置资源
	BOOL SetPressImage(LPCTSTR lpNormal,CONST LPRECT lprcNinePart=NULL);
	//设置资源
	BOOL SetGridImage(LPCTSTR lpNormal);

	//重载函数
public:
	//控件绑定
	virtual VOID PreSubclassWindow();
	//控件消息
	virtual BOOL OnChildNotify(UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT * pLResult);

	//功能函数
public:
	//设置锁定
	VOID SetLockCount(UINT uLockCount);
	//设置列高
	VOID SetItemHeight(UINT uItemHeight);

	//消息函数
protected:
	//重画消息
	VOID OnPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//销毁消息
	afx_msg void OnDestroy();
	//左键按下
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//左键抬起
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////
struct  tagItemImage 
{
	CImageEx		*pImage;
	int				nItem;
};

typedef vector<tagItemImage>	CItemImgArray;

//////////////////////////////////////////////////////////////////////////

//列表控件
class SKINUI_CLASS CSkinListCtrl : public CListCtrl,public ISkinControl
{
	//数据变量
protected:
	bool							m_bAscendSort;						//升序标志
	int								m_nHeightItem;
	UINT							m_uActiveItem;
	CItemImgArray					m_ItemImgArray;

	//资源定义
public:
	CImageEx * m_pHovenImg, * m_pSelectImg;
	CImageEx * m_pCheckImg, * m_pUnCheckImg;

	//变量定义
public:
	CSkinHeaderCtrl					m_SkinHeaderCtrl;					//列头控件
	int m_iNumColumns;
	//函数定义
public:
	//构造函数
	CSkinListCtrl();
	//析构函数
	virtual ~CSkinListCtrl();

	//重载函数
public:
	//控件绑定
	virtual VOID PreSubclassWindow();
	//绘画函数
	virtual VOID DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//设置属性
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//设置属性
	virtual void ParseItem(CXmlNode *root);
	//创建控件
	virtual BOOL CreateControl(CWnd* pParentWnd);

	//Report设置资源
public:
	//设置资源
	BOOL SetHovenImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	//设置资源
	BOOL SetSelectImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	//设置资源
	BOOL SetCheckImage(LPCTSTR lpszCheckName,LPCTSTR lpszUnCheckName);
	//插入图标
	BOOL InsertImage(int nItem,LPCTSTR lpszFileName);

	//伪重载函数
public:
	//插入节点
	int InsertItem(const LVITEM* pItem);
	//插入节点
	int InsertItem(int nItem, LPCTSTR lpszItem);
	//插入节点
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	//插入节点
	int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,UINT nStateMask, int nImage, LPARAM lParam);
	//设置风格
	DWORD SetExtendedStyle(DWORD dwNewStyle);
	BOOL SetHeadings(const CString& strHeadings);

	//绘画控制
protected:
	//绘画数据
	VOID DrawReportItem(CDC * pDC, INT nItem, CRect & rcSubItem, INT nColumnIndex);

	//功能设置
public:
	//高度设置
	void SetItemHeight(int nHeight);

	//消息函数
protected:
	//建立消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//销毁消息
	afx_msg void OnDestroy();
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//重绘背景
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//左键按下
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif