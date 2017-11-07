#pragma once

#include "StackedWndCtrl.h"

class CStackedTreeCtrl
{
public:
	CStackedTreeCtrl();
	~CStackedTreeCtrl();

public:
	BOOL					InitializeCtrl();
	BOOL					InsertRootItem();
	BOOL					InsertChildItem();
	BOOL					DeleteChildItem();
	
	BOOL					ExpandingItem();
	BOOL					SelchangingItem();
	
protected:
	BOOL					GetRootNodeData();
	BOOL					GetChildNodeData();
	
	BOOL					PopulateItem();
	
protected:
	CStackedWndCtrl			m_hStackedWncCtrl;
};